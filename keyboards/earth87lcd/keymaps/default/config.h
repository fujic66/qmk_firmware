#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 3

#define VENDOR_ID 0x4144
#define PRODUCT_ID 0x0002
#define DEVICE_VER 0x0100
#define MANUFACTURER "alektor_diy"
#define PRODUCT "earth87lcd"

#define LCD_WIDTH 160
#define LCD_HEIGHT 80
#define SPI_MODE 3
#define ST7735
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE

// 【参考】RP2040-LCDにおけるOLED関連のピンアサイン
// SCK (Serial Clock): LCD_CLK = GP10
// MOSI (Master Out Slave In): LCD_DIN = GP11
// CS (Chip Select): LCD_CS = GP9
// DC (Data/Command): LCD_DC = GP8
// Reset: LCD_RST = GP12
// Backlight: LCD_BL = GP25

#define ENCODERS_PAD_A { GP0 }
#define ENCODERS_PAD_B { GP1 }