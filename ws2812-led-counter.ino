#include <FastLED.h>

// Adapter la broche à votre carte (GPIO 6 n'est pas adapté à tous les ESP32).
#define LED_PIN 5
#define MAX_LEDS 1000
#define BRIGHTNESS 25

CRGB leds[MAX_LEDS];
int ledCount = 0;

void displayCount() {
  FastLED.clear();
  for (int i = 0; i < ledCount; i++) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
  Serial.print("LED allumees : ");
  Serial.println(ledCount);
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, MAX_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  displayCount();
  Serial.println("Commandes : nombre (ex: 250), +10, -10, +1, -1, 0");
}

void loop() {
  if (!Serial.available()) return;

  String command = Serial.readStringUntil('\n');
  command.trim();
  if (command.length() == 0) return;

  int nextCount = ledCount;
  if (command == "+10") nextCount += 10;
  else if (command == "-10") nextCount -= 10;
  else if (command == "+1") nextCount++;
  else if (command == "-1") nextCount--;
  else {
    // N'accepter que les entiers decimaux positifs.
    for (unsigned int i = 0; i < command.length(); i++) {
      if (!isDigit(command[i])) {
        Serial.println("Commande invalide.");
        return;
      }
    }
    nextCount = command.toInt();
  }

  if (nextCount < 0 || nextCount > MAX_LEDS) {
    Serial.println("Valeur hors limites (0 a MAX_LEDS).");
    return;
  }
  ledCount = nextCount;
  displayCount();
}
