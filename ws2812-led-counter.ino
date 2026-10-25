
/*
 * WS2812 LED Counter
 * ------------------
 *
 * Description:
 *   A simple tool to determine the number of WS2812 LEDs
 *   on an addressable LED strip without manually counting them.
 *
 *   The number of illuminated LEDs can be adjusted using
 *   commands sent through the Arduino Serial Monitor.
 *
 * Supported hardware:
 *   - ESP32
 *   - Arduino boards with sufficient RAM
 *
 * Dependencies:
 *   - FastLED library (https://fastled.io)
 *
 * Wiring:
 *   LED strip DIN  -> LED_PIN
 *   LED strip GND  -> GND (common ground)
 *   LED strip +5V  -> External 5V power supply
 *
 * Serial commands:
 *   100  : Illuminate the first 100 LEDs
 *   +10  : Increase the count by 10
 *   -10  : Decrease the count by 10
 *   +1   : Increase the count by 1
 *   -1   : Decrease the count by 1
 *   0    : Turn off all LEDs
 *
 * Serial baud rate: 115200
 *
 * License: MIT
 */

#include <FastLED.h>

// --------------------------------------------------
// Configuration
// --------------------------------------------------

#define LED_PIN       5
#define MAX_LEDS      1000
#define BRIGHTNESS    30
#define LED_TYPE      WS2812B
#define COLOR_ORDER   GRB

// --------------------------------------------------
// Global variables
// --------------------------------------------------

// LED buffer (approximately 3 bytes per LED).
CRGB leds[MAX_LEDS];

// Current number of illuminated LEDs.
int ledCount = 0;

// --------------------------------------------------
// LED control
// --------------------------------------------------

/*
 * Update the LED strip.
 *
 * Illuminates the first ledCount LEDs in white
 * and turns off all remaining LEDs.
 */
void updateLEDs() {
  fill_solid(leds, MAX_LEDS, CRGB::Black);

  for (int i = 0; i < ledCount; i++) {
    leds[i] = CRGB::White;
  }

  FastLED.show();

  Serial.print("LEDs enabled: ");
  Serial.print(ledCount);
  Serial.print(" / ");
  Serial.println(MAX_LEDS);
}

/*
 * Set the number of illuminated LEDs.
 *
 * The value is constrained to the valid range
 * between 0 and MAX_LEDS.
 */
void setLEDCount(int count) {
  ledCount = constrain(count, 0, MAX_LEDS);
  updateLEDs();
}

// --------------------------------------------------
// Serial commands
// --------------------------------------------------

/*
 * Process a command received through the
 * Arduino Serial Monitor.
 */
void processCommand(String command) {
  command.trim();

  if (command.length() == 0) {
    return;
  }

  if (command == "+1") {
    setLEDCount(ledCount + 1);
  }
  else if (command == "-1") {
    setLEDCount(ledCount - 1);
  }
  else if (command == "+10") {
    setLEDCount(ledCount + 10);
  }
  else if (command == "-10") {
    setLEDCount(ledCount - 10);
  }
  else {
    // Accept only unsigned decimal integers.
    // Reject invalid commands and values above MAX_LEDS.
    for (unsigned int i = 0; i < command.length(); i++) {
      if (!isDigit(command[i])) {
        Serial.println("Error: Invalid command.");
        return;
      }
    }

    long value = command.toInt();

    if (value < 0 || value > MAX_LEDS) {
      Serial.println("Error: Value exceeds MAX_LEDS.");
      return;
    }

    setLEDCount((int)value);
  }
}

// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(50);

  // Initialize the LED strip.
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(
    leds, MAX_LEDS
  );

  // Limit brightness to reduce power consumption.
  FastLED.setBrightness(BRIGHTNESS);

  // Start with all LEDs turned off.
  FastLED.clear(true);

  Serial.println();
  Serial.println("==============================");
  Serial.println("      WS2812 LED Counter      ");
  Serial.println("==============================");
  Serial.println();
  Serial.println("Commands:");
  Serial.println("  <number> : Set LED count");
  Serial.println("  +1 / -1  : Adjust by 1");
  Serial.println("  +10/-10  : Adjust by 10");
  Serial.println("  0        : Turn off LEDs");
  Serial.println();
  Serial.println("Enter a command:");
}

// --------------------------------------------------
// Main loop
// --------------------------------------------------

void loop() {
  // Check for incoming serial commands.
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    processCommand(command);
  }
}
