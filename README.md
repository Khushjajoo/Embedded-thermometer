Temperature Display and Counter Using AVR and 7-Segment Display

This project (thermo.c) displays real-time temperature readings from an analog temperature sensor using an AVR microcontroller and a 4-digit 7-segment display. The system continuously reads data through the onboard ADC, calculates the temperature in both Celsius and Fahrenheit, and displays it based on user input. When a button is pressed, the temperature is shown in Celsius; otherwise, it defaults to Fahrenheit. The display logic uses multiplexing for smooth digit rendering and handles decimal representation for more accurate readings.

The other project (screen.c) showcases a live counter display on the same 7-segment setup, demonstrating flexible usage of the display and timing logic. 





