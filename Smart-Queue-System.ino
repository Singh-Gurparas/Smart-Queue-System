#include <LiquidCrystal.h>

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define IR_SENSOR_PIN 2
#define GREEN_LED 3
#define YELLOW_LED 4
#define RED_LED 5
#define BUZZER 6

bool customerPresent = false;
unsigned long startTime = 0;
int billingTimes[5] = {0, 0, 0, 0, 0}; // Stores last 5 billing times
int billingIndex = 0;

void setup() {
    pinMode(IR_SENSOR_PIN, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    
    Serial.begin(9600);
    Serial.println("Smart Queue Alert System Initialized!");

    lcd.begin(16, 2); // Initialize LCD
    lcd.print("Smart Queue");
    delay(2000);
    lcd.clear();
    lcd.print("Waiting for");
    lcd.setCursor(0, 1);
    lcd.print("Customer...");
}

bool isCustomerPresent() {
    return digitalRead(IR_SENSOR_PIN) == LOW; // IR sensor detects object when LOW
}

void loop() {
    bool detected = isCustomerPresent();

    if (detected && !customerPresent) {  
        customerPresent = true;
        startTime = millis();
        Serial.println("Customer detected! Billing started...");
        
        lcd.clear();
        lcd.print("Billing...");
    }

    if (!detected && customerPresent) {  
        customerPresent = false;
        int billingTime = (millis() - startTime) / 1000;

        if (billingTime < 3) {
            Serial.println("False trigger ignored.");
            return; // Ignore if billing was too short
        }

        Serial.print("Billing completed. Time taken: ");
        Serial.print(billingTime);
        Serial.println(" sec");

        // Store the new billing time
        billingTimes[billingIndex] = billingTime;
        billingIndex = (billingIndex + 1) % 5;

        // Calculate Dynamic Wait Time
        int sum = 0, count = 0;
        for (int i = 0; i < 5; i++) {
            if (billingTimes[i] > 0) {
                sum += billingTimes[i];
                count++;
            }
        }
        int avgBillingTime = (count > 0) ? sum / count : 1;

        Serial.print("Average Billing Time: ");
        Serial.print(avgBillingTime);
        Serial.println(" sec");

        lcd.clear();
        lcd.print("Billing: ");
        lcd.print(billingTime);
        lcd.print("s");
        lcd.setCursor(0, 1);
        lcd.print("Avg: ");
        lcd.print(avgBillingTime);
        lcd.print("s");

        // LED Indicators
        if (avgBillingTime < 60) { 
            digitalWrite(GREEN_LED, HIGH);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(RED_LED, LOW);
            Serial.println("Queue Speed: FAST ✅ (Green LED ON)");
        } 
        else if (avgBillingTime >= 60 && avgBillingTime <= 180) { 
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(YELLOW_LED, HIGH);
            digitalWrite(RED_LED, LOW);
            Serial.println("Queue Speed: MEDIUM ⚠️ (Yellow LED ON)");
        } 
        else { 
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(RED_LED, HIGH);
            digitalWrite(BUZZER, HIGH);
            delay(1000);
            digitalWrite(BUZZER, LOW);
            Serial.println("Queue Speed: SLOW ❌ (Red LED ON, Buzzer Alert!)");
        }

        // **Calculate and Display Estimated Wait Time for Next 10 Customers**
        Serial.println("Estimated Wait Times for Next 10 Customers:");
        for (int i = 1; i <= 10; i++) {
            Serial.print("Customer ");
            Serial.print(i);
            Serial.print(": ~");
            Serial.print(i * avgBillingTime);
            Serial.println(" sec");
        }
    }

    delay(500);
}
