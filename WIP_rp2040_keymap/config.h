/*
This is the c configuration file for the keymap

Copyright 2021 Chris Farrell <chris@thefarrells.nyc>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2

// Taps and Holds
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 250 // 200 is default
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY

// Auto Shift
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_NO_SETUP

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Mouse key speed and acceleration.
// #define MK_KINETIC_SPEED
// #define MOUSEKEY_DELAY                          8
// #define MOUSEKEY_INTERVAL                       8
// #define MOUSEKEY_MOVE_DELTA                     32
// #define MOUSEKEY_INITIAL_SPEED                  128
// #define MOUSEKEY_BASE_SPEED                     1024
// #define MOUSEKEY_DECELERATED_SPEED              256
// #define MOUSEKEY_ACCELERATED_SPEED              4096
// #define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS        16
// #define MOUSEKEY_WHEEL_BASE_MOVEMENTS           32
// #define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS    64
// #define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS    8


// Setting a cap that will appear sane to iOS devices
#define USB_MAX_POWER_CONSUMPTION 100

// This is for macOS so keyboard can work after sleep
#define NO_USB_STARTUP_CHECK

// Using the default font for now
#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

// Should help with some mods in keycombo aliases
#define PREVENT_STUCK_MODIFIERS

// I don't know what these do
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// Allow double tap of reset to enter flash mode
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET