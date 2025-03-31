# Smar-Queue-Alert-System
The Smart Queue Alert System helps track customer billing time using an IR sensor and provides estimated wait times for the next 10 customers. It features LED indicators to show queue speed (fast, medium, slow) and a buzzer alert for slow billing.


🛠 Smart Queue Alert System with 16x2 LCD (Without Potentiometer)
This version adds a 16x2 LCD display to show:
✅ Billing Time (for the current customer)
✅ Average Billing Time (calculated dynamically)

The Serial Monitor output remains unchanged.

🔩 Components Needed
Component	Quantity
Arduino Uno	1
IR Sensor (FC-51)	1
16x2 LCD Display (Without I2C)	1
Resistors (220Ω for LEDs, 1kΩ for LCD contrast)	4
LEDs (Red, Yellow, Green)	1 each
Buzzer	1
Jumper Wires	As needed
Breadboard	1
🔌 LCD Connections (Without Potentiometer)
LCD Pin	Arduino Pin	Description
VSS	GND	Ground
VDD	5V	Power Supply
V0	GND (via 1kΩ resistor)	Adjust contrast (without potentiometer)
RS	7	Register Select
RW	GND	Always write mode
E	8	Enable
D4	9	Data Pin 4
D5	10	Data Pin 5
D6	11	Data Pin 6
D7	12	Data Pin 7
A (LED+)	5V	LCD Backlight Positive
K (LED-)	GND	LCD Backlight Negative
🔌 IR Sensor, LEDs & Buzzer Connections
Component	Arduino Pin
IR Sensor OUT	2
Green LED	3
Yellow LED	4
Red LED	5
Buzzer	6
