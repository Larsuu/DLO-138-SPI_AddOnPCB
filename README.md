Lets compare viability of which one to fork:

https://github.com/ardyesp/DLO-138
or
https://github.com/siliconvalley4066/DLO-138-SPI

Introduction to Extending the DSO138 Oscilloscope DIY Kit

The DSO138 DIY oscilloscope is a popular, affordable kit for electronics beginners. This project aims to enhance it into a portable mobile oscilloscope while keeping it newbie-friendly, cheap, and modular for future upgrades. By adding simple extensions, we can maintain the spirit of the original kit while improving its functionality.
Main Goal for This Project:

    Add a second analog channel as an addon.
    Integrate a battery holder for portable, battery-powered operation.

Requirements:

    Ensure compatibility with DLO138 firmware, which will allow expanded features while maintaining the simplicity of the original design:
        Two analog channels for more versatile signal analysis.
        Two digital logic channels using the SWDIO and SWCLK pins (PA13 and PA14) on board.
        Serial port interface for captured waveform data transfer.
        Selectable trigger source from Analog Channel 1 or Digital Channel.
        Rotary encoder option to replace +, -, and SEL switches.
        2K sample depth to enhance signal resolution.

Project Goals:

    Maintain affordability with low-cost components.
    Newbie-friendly design for easy implementation.
    Portability through battery-powered operation.
    Modular and future-proof for easy upgrades.
    Preserve the learning aspect of the original kit.

Wild Ideas with Great taste of Feature Creep Potential:

Here are some ideas that could significantly enhance the oscilloscope's functionality. Input is welcome on which of these would be easy and simple to implement with the right code:

    Battery Power Integration: Add Li-ion battery and charging circuit.
    Enhanced Input Protection: Safeguard against accidental high-voltage inputs.
    Improved Display Options: Larger or external display support.
    Better Probe Connectivity: Use standard BNC connectors for professional-grade probes.
    Signal Storage: Add SD card slot for waveform saving.
    USB/PC Connectivity: Enable USB data transfer for real-time monitoring on a PC.
    Signal Processing Upgrades: Co-processor for advanced analysis, like FFT.
    Wi-Fi Connectivity: Integrate a Wi-Fi module for remote control and data transfer.
    Bluetooth Interface: Wirelessly stream data to mobile devices.
    Function Generator: Add XR2206 1Hz-1MHz function signal generator (Sine/Triangle/Square output) with adjustable frequency and amplitude.
    Adjustable Power Source: Add a 5A 75W adjustable step-down converter module for powering external circuits during testing.

Feedback on which of these ideas are cost-effective and easy to implement is encouraged. Some could be nearly free to add with the right software and slight hardware tweaks!

First step: ToDo

    DSO138 3D model: Create a KiCAD-compatible 3D model of the DSO138 for easy matching and designing for footprint.

