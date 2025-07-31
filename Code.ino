#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Replace 0x27 with your I2C address

// Pin definition for HX711
const int LOADCELL_DOUT_PINS[4] = {2, 4, 5, 6}; // Data pin (DOUT)
const int LOADCELL_SCK_PIN = 3;   // Clock pin (SCK)

HX711 scales[4];

long zero_readings[4] = {0, 0, 0, 0};  // Raw reading when no weight is placed (tare)
long known_reading[4] = {0, 0, 0, 0};  // Raw reading when known weight is placed
float calibration_factors[4] = {1455192.0, 1130672.0, 1474740.0, 1069168};  // Calibration factor, calculated dynamically
float known_weight = 0;  // Known weight in kg

bool is_calibrated = false;  // Flag to indicate calibration is complete

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  
  for (int i = 0; i < 4; i++) {
    scales[i].begin(LOADCELL_DOUT_PINS[i], LOADCELL_SCK_PIN);
    scales[i].set_gain(128); // Set gain to 128 for higher precision
  }

  Serial.println("HX711 initialized. Please remove all weight and press any key to tare.");
  lcd.setCursor(0, 0);
  lcd.print("Remove weight");
  lcd.setCursor(0, 1);
  lcd.print("Press key to tare");
}

void loop() {
  if (!is_calibrated) {
    if (Serial.available() > 0) {
      for (int i = 0; i < 4; i++) {
        
        zero_readings[i] = scales[i].read_average(10);  // Average of 10 readings
        scales[i].tare();  // Set scale to zero
      }
      
      Serial.println("Tare complete.");
      // Serial.println(" Now place the calibration weight on the scale.")
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tare complete!");
      // lcd.setCursor(0, 1);
      // lcd.print("Add cal weight");

      // while (Serial.available() == 0);  // Wait for key press
      // Serial.read();  // Clear the input buffer
      
      // Serial.println("Enter the known weight in kg:");
      // while (Serial.available() == 0);  // Wait for weight input
      // known_weight = Serial.parseFloat();  // Read the known weight value
      
      // Serial.print("Known weight entered: ");
      // Serial.print(known_weight);
      // Serial.println(" kg.");
      
      // lcd.clear();
      // lcd.setCursor(0, 0);
      // lcd.print("Known weight:");
      // lcd.setCursor(0, 1);
      // lcd.print(known_weight, 2);
      // lcd.print(" kg");
      
      // Serial.println("Please ensure the weight is stable and press any key to continue...");
      // while (Serial.available() == 0);  // Wait for confirmation
      // Serial.read(); // Clear input buffer

      // for (int i = 0; i < 4; i++) {
      // //   // known_reading[i] = scales[i].read_average(10);  // Take 10 readings for precision
      // //   // calibration_factors[i] = (known_reading[i] - zero_readings[i]) * 4 / known_weight;
      //   // scales[i].set_scale(calibration_factors[i]);  // Set the calculated calibration factor
      // }

      Serial.println("Calibration complete.");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Calibration done!");
      delay(2000);  // Display message briefly
      is_calibrated = true;
    }
  } else {
    float total_weight = 0.0;
    float weights[4] = {0, 0, 0, 0};  // Array to hold weights from each load cell
    
    for (int i = 0; i < 4; i++) {
      float weight = scales[i].get_units(10)/400000; // Average of 10 readings
      weights[i] = weight;
      
      Serial.print("Weight on load cell ");
      Serial.print(i+1);
      Serial.print(": ");
      Serial.print(weight, 4);
      Serial.print(" kg ");
      
      total_weight += weight;
    }

    Serial.print("Total Weight: ");
    Serial.print(total_weight, 4);
    Serial.println(" kg");
    Serial.print(calibration_factors[0]);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total Weight:");
    lcd.setCursor(0, 1);
    lcd.print(total_weight, 4);
    lcd.print(" kg");
    Serial.print(calibration_factors[0]);
    Serial.print(calibration_factors[1]);
    Serial.print(calibration_factors[2]);
    Serial.print(calibration_factors[3]);
    delay(20);  // Update every second
  }
}



