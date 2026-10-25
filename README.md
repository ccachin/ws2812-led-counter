# WS2812 LED Counter

A simple Arduino/FastLED tool to **determine how many LEDs are on a WS2812/WS2812B strip** without counting them manually.

## How it works

The sketch lights up the **first N LEDs** on the strip. Using the Serial Monitor, increase or decrease N until **the last LED lights up**. The displayed value is then the number of LEDs on the strip.

> This is not automatic detection: WS2812 LEDs cannot report the total LED count to the microcontroller. The last LED must be visible, and the strip must be working correctly.

## Hardware

- An ESP32 board (recommended for long strips), or an Arduino board with enough RAM
- A WS2812/WS2812B LED strip
- A suitable 5 V power supply for the strip
- The **FastLED** library (install it using the Arduino IDE Library Manager)

## Wiring

| LED strip | Connection |
| --- | --- |
| `DIN` | GPIO specified by `LED_PIN` (default: 5; adjust for your board) |
| `GND` | Power supply GND **and** microcontroller GND |
| `+5V` | External power supply +5 V |

**Important:** Do not power a long LED strip from the board's 5 V pin. Check the strip's data direction (`DIN` / arrow). For an ESP32 (3.3 V data signal), a 3.3 V-to-5 V logic level shifter is recommended for reliable operation. A series resistor of approximately 330 Ω on the data line is also recommended.

## Installation

1. Install **FastLED** in the Arduino IDE.
2. Open `ws2812-led-counter.ino`.
3. Set `LED_PIN` to the GPIO you are using and `MAX_LEDS` to a suitable estimated upper limit.
4. Upload the sketch to your board.
5. Open the **Serial Monitor at 115200 baud** and set the line ending to **Newline**.

## Commands

| Command | Action |
| --- | --- |
| `100` | Light up the first 100 LEDs |
| `+10` / `-10` | Add / remove 10 lit LEDs |
| `+1` / `-1` | Add / remove 1 lit LED |
| `0` | Turn all LEDs off |

**Example:** Send `200`, then `+10` until you get close to the end of the strip, and finally `+1` to find the exact count.

## Limitations and safety notes

- The sketch allocates approximately **3 bytes of RAM per LED** (`MAX_LEDS = 1000` uses about 3 KB), in addition to other memory requirements. A classic Arduino Uno does not have enough RAM for this configuration.
- Brightness is limited (`BRIGHTNESS = 25`), but an appropriately sized power supply is still essential.
- Once the end of the strip has been reached, increasing N will not produce any visible change. Start below the expected count and increase it until the last LED lights up.
- A faulty LED or data connection may lead to an incorrect result.
- WS2812 and WS2812B strips are supported by the default configuration. For other models, adjust the LED type and color order in FastLED.

## License

MIT — see [LICENSE](LICENSE).
