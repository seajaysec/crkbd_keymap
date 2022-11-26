# Originally for Elite-C; Converting to Blok
#pragma once
#define I2C_DRIVER I2CD1

CONVERT_TO = blok
SRC += features/caps_word.c

MCU = RP2040
BOOTLOADER = rp2040

EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes

OLED_ENABLE = no
OLED_DRIVER = SSD1306
SPLIT_KEYBOARD = yes
