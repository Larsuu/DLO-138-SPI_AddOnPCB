int16_t trigLevel = 0;


// ------------------------
void initIO()	{
// ------------------------
	// set pin I/O direction
	pinMode(BOARD_LED, OUTPUT);
	pinMode(AN_CH1, INPUT_ANALOG);
	pinMode(AN_CH2, INPUT_ANALOG);
	pinMode(DG_CH1, INPUT_PULLDOWN);
	pinMode(DG_CH2, INPUT_PULLDOWN);
	pinMode(TRIGGER_IN, INPUT_PULLUP);
  pinMode(AC_CH1, INPUT_PULLUP);
  pinMode(AC_CH2, INPUT_PULLUP);
	
	// calibrate the ADC channels at startup
	adc_calibrate(ADC1);
	adc_calibrate(ADC2);
	setADC();

	// start 1KHz square wave
	pinMode(TEST_WAVE_PIN, PWM);
	Timer3.setPeriod(1000);
	pwmWrite(TEST_WAVE_PIN, Timer3.getOverflow() / 2);
	DBG_PRINTLN("Test square wave started");
	
	// input button and encoder
	pinMode(ENCODER_SW, INPUT_PULLUP);
	pinMode(ENCODER_A, INPUT_PULLUP);
	pinMode(ENCODER_B, INPUT_PULLUP);
	pinMode(BTN4, INPUT_PULLUP);
	
	attachInterrupt(ENCODER_SW, readESwitchISR, FALLING);
	attachInterrupt(BTN4, btn4ISR, CHANGE);
	
#ifdef USE_ENCODER
	attachInterrupt(ENCODER_A, readEncoderISR, CHANGE);
	attachInterrupt(ENCODER_B, readEncoderISR, CHANGE);
#else
	attachInterrupt(ENCODER_A, readASwitchISR, FALLING);
	attachInterrupt(ENCODER_B, readBSwitchISR, FALLING);
#endif	

	// init trigger level PWM
	// start 20KHz square wave on trigger out reference and negative v gen
	Timer4.setPeriod(50);
	pinMode(TRIGGER_LEVEL, PWM);
	pinMode(VGEN, PWM);
	pwmWrite(VGEN, 700);
	
	blinkLED();
	
	// init scan timeout timer
	initScanTimeout();
}




// ------------------------
void setADC()	{
// ------------------------
	int pinMapADCin1 = PIN_MAP[AN_CH1].adc_channel;
	int pinMapADCin2 = PIN_MAP[AN_CH2].adc_channel;
	
	// opamp is low impedance, set next fastest sampling 
	adc_set_sample_rate(ADC1, ADC_SMPR_7_5);
	adc_set_sample_rate(ADC2, ADC_SMPR_7_5);

	adc_set_reg_seqlen(ADC1, 1);
  adc_set_reg_seqlen(ADC2, 1);
	ADC1->regs->SQR3 = pinMapADCin1;
	// set ADC1 continuous mode
	ADC1->regs->CR2 |= ADC_CR2_CONT; 	
	// set ADC2 in regular simultaneous mode
	ADC1->regs->CR1 |= 0x60000; 		
	ADC1->regs->CR2 |= ADC_CR2_SWSTART;

	// set ADC2 continuous mode
	ADC2->regs->CR2 |= ADC_CR2_CONT; 	
	ADC2->regs->SQR3 = pinMapADCin2;
}



// ------------------------
void blinkLED()	{
// ------------------------
	LED_ON;
	delay(10);
	LED_OFF;
}



// ------------------------
void initScanTimeout()	{
// ------------------------
  Timer2.pause();
  Timer2.setPeriod(100 * 1000);    // 100msec
  Timer2.setCount(0);
  Timer2.attachInterrupt(TIMER_UPDATE_INTERRUPT, scanTimeoutISR);
  Timer2.refresh();
}



// ------------------------
int16_t getTriggerLevel()	{
// ------------------------
	return trigLevel;
}



// ------------------------
void setTriggerLevel(int16_t tLvl)	{
// ------------------------
	trigLevel = tLvl;
	trigger_ad = tLvl + 2048;
}





// ------------------------
void readInpSwitches()	{
// ------------------------
	static uint8_t couplingOld1, couplingOld2, rangeOld;

	uint16_t cpl, pos1, pos2;
	adc_reg_map *ADC1regs = ADC1->regs;

	// check AC/DC switch 1 
  if (digitalRead(AC_CH1) == LOW) {
    couplingPos1 = CPL_AC;
    digitalWrite(OF_CH1, HIGH);
  } else {
    couplingPos1 = CPL_DC;
    digitalWrite(OF_CH1, LOW);
  }
  // check AC/DC switch 2 
  if (digitalRead(AC_CH2) == LOW) {
    couplingPos2 = CPL_AC;
    digitalWrite(OF_CH2, HIGH);
  } else {
    couplingPos2 = CPL_DC;
    digitalWrite(OF_CH2, LOW);
  }
	
	
	// check if switch position changed from previous snap
	if(couplingPos1 != couplingOld1)	{
		couplingOld1 = couplingPos1;
		repaintLabels();
	}
  if(couplingPos2 != couplingOld2)  {
    couplingOld2 = couplingPos2;
    repaintLabels();
  }
	
	if(rangePos1 != rangeOld)	{
		rangeOld = rangePos1;
		repaintLabels();
	}
}
