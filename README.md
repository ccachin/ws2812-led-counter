# WS2812 LED Counter

Un petit outil Arduino/FastLED pour **déterminer le nombre de LED d'un ruban WS2812/WS2812B**, sans les compter une par une.

## Principe

Le programme allume les **N premières LED** du ruban. Depuis le moniteur série, on augmente ou diminue N jusqu'à ce que **la dernière LED soit allumée**. Le nombre affiché est alors le nombre de LED du ruban.

> Ce n'est pas une détection automatique : les WS2812 ne renvoient pas leur nombre au microcontrôleur. La dernière LED doit être visible et le ruban doit fonctionner correctement.

## Matériel

- Une carte ESP32 (recommandée pour les longs rubans), ou une carte Arduino avec suffisamment de RAM
- Un ruban WS2812/WS2812B
- Une alimentation 5 V adaptée au ruban
- La bibliothèque **FastLED** (à installer depuis le gestionnaire de bibliothèques de l'IDE Arduino)

## Branchement

| Ruban | Connexion |
| --- | --- |
| `DIN` | GPIO défini par `LED_PIN` (5 par défaut, à adapter à la carte) |
| `GND` | GND de l'alimentation **et** GND de la carte |
| `+5V` | +5 V de l'alimentation externe |

**Important :** ne pas alimenter un long ruban depuis la broche 5 V de la carte. Vérifier le sens du ruban (`DIN` / flèche). Pour un ESP32 (signal 3,3 V), un convertisseur de niveau logique 3,3 V → 5 V est recommandé pour une liaison fiable. Une résistance série d'environ 330 Ω sur les données est également recommandée.

## Installation

1. Installer **FastLED** dans l'IDE Arduino.
2. Ouvrir `ws2812-led-counter.ino`.
3. Adapter `LED_PIN` à la broche réellement utilisée et `MAX_LEDS` au maximum estimé.
4. Téléverser le programme.
5. Ouvrir le **moniteur série à 115200 bauds**, avec fin de ligne **Nouvelle ligne**.

## Commandes

| Commande | Action |
| --- | --- |
| `100` | Allumer les 100 premières LED |
| `+10` / `-10` | Ajouter / retirer 10 LED |
| `+1` / `-1` | Ajouter / retirer 1 LED |
| `0` | Tout éteindre |

**Exemple :** envoyer `200`, puis `+10` jusqu'à approcher de la fin, et enfin `+1` pour trouver le nombre exact.

## Limites et précautions

- Le programme réserve environ **3 octets de RAM par LED** (`MAX_LEDS = 1000` ≈ 3 Ko), hors autres besoins du programme : un Arduino Uno classique n'a pas assez de RAM pour cette configuration.
- La luminosité est limitée (`BRIGHTNESS = 25`), mais une alimentation adaptée reste indispensable.
- Si la fin du ruban est déjà atteinte, augmenter N ne change plus rien visuellement : repartir d'une valeur inférieure et avancer jusqu'à l'allumage de la dernière LED.
- Si une LED ou une connexion de données est défectueuse, le résultat peut être incorrect.
- Les références WS2812 et WS2812B sont prises en charge par la configuration par défaut. Pour d'autres modèles, adapter le type de LED et l'ordre des couleurs dans FastLED.

## Licence

MIT — voir [LICENSE](LICENSE).
