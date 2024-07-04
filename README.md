# STM32-VOLTMETER-12V
STM32 voltmeter 12V displaying the data on an integrated LCD.

## Description
In this project, an STM32F303RET6 Nucleo-64 board is utilized as a voltmeter to measure the voltage in a circuit or battery. The maximum measurable voltage, for safe operation without damaging the microcontroller, is between 12V and 12.5V. The STM32F303 board was programmed using STM32CubeIDE and STM32CubeMX.
In the STM32CubeMX configuration:

* Pins PA6 to PA11 are configured as digital outputs and are used to interface with the LCD.
* Pins PA2 and PA3 are configured for USART communication.
* Pin PC2 is configured as an ADC input for voltage measurement.

The STM32F303 can measure voltages higher than its 3.3V power supply thanks to a voltage divider circuit composed of two resistors: R1 = 7 kΩ and R2 = 3.27 kΩ. The voltage to be measured is applied across the two resistors, while the ADC pin (PC2) is connected between R1 and R2. The voltage data retrieved from PC2 is displayed on an LCD in millivolts, updating every second.

## Circuit diagram

## Component used
* STM32303RET6 Nucleo-64 board
* R1 = 7 Kohm
* R2 = 3.27 Kohm
* HD44780 16x2 LCD
* Breadboard
* jumper wires

 ## Possible upgrades
 * Add Wi-Fi or Bluetooth connectivity features
