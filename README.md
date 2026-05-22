# General
Rave Buddy project is an attempt to create a cyberware piece that combines fashion and utility functions for rave-lovers
## Planned features:
- [~] Dance and face control stickman animation
- [ ] Drinks counter
- [ ] heart-blink (for showing affection to other ravers)

## Watch the video
[![Watch the video](https://img.youtube.com/vi/logA-uAWEIs/maxresdefault.jpg)](https://youtube.com/shorts/logA-uAWEIs?feature=share) 

# Setup
Generate .clangd for correct LSP behaviour:
```bash
. clangd_gen.sh
```

# Project assebly

## Tech Stack
- espidf framework
- platformio
- C

## Hardware

### SD Card
SPI interface:
CS   -> GPIO5
SCK  -> GPIO18
MOSI -> GPIO23
MISO -> GPIO19
VCC  -> V5

### Left LCD display SSD1306
I2C interface:
GND -> GND
VCC -> 3V3
SCL -> GPIO22
SDA -> GPIO21

### Right LCD display SSD1306 (in progress)
SCL -> GPIO25
SDA -> GPIO26

### Buttons
#### Button 1
GPIO27 (INTERNAL_PULLUP) -> button -> GND
#### Button 2
GPIO32 (INTERNAL_PULLUP) -> button -> GND
#### Button 3
GPIO33 (INTERNAL_PULLUP) -> button -> GND

