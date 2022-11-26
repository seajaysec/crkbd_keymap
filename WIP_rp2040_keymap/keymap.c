/*
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
along with this program.  If not, see <http: //www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "features/caps_word.h"

enum layers { BASE, MOUSE, NAV, NUM, SYM, MEDIA, FUN };

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD,
    TRIPLE_SINGLE_TAP,
    NO_TAP_STATE
};

enum {
    // tap dances
    TAGR,
    TRI,
    CBR,
    PRN,
    BRC,
    // keycodes
    AND = SAFE_RANGE,
    OR,
    GREATEQ,
    LESSEQ,
    PLUSEQ,
    MINUSEQ,
    ISEQ,
    NOTEQ,
    DECR,
    INCR,
    XEQ,
    DIVEQ,
    SHRUGS,
};

// Left-hand home row mods
#define HOME_A LCTL_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOM_SCL RCTL_T(KC_SCLN)

// Screenshot Shortcuts
#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen

//Aliases for Navigation layer
#define C_CL   LALT(KC_LEFT) // Move cursor one word back
#define C_CR   LALT(KC_RGHT) // Move cursor one word forward
#define C_CU   LALT(KC_UP)   // Move line up a row
#define C_CD   LALT(KC_DOWN) // Move line down a row

//Indentation Shortcuts
#define INDENT LGUI(KC_RBRC)
#define DEDENT LGUI(KC_LBRC)

//Zoom Shortcuts
#define BIGGER LGUI(KC_PLUS)
#define TINIER LGUI(KC_MINS)
#define OLDSIZ LGUI(KC_0)

//Copy Paste Shortcuts
#define CUT  LGUI(KC_X)
#define COPY LGUI(KC_C)
#define PAST LGUI(KC_V)
#define UNFR LGUI(LCTL(KC_V)) // ⌘⌃V is defined in BTT as an unformatted paste shortcut

//Undo Redo Shortcuts
# define UNDO LGUI(KC_Z)
# define REDO LSFT(LGUI(KC_Z))

// Layer Shortcuts
#define MOSC LT(MOUSE, KC_ESC)  // 1: Escape; Mouse Layer
#define TAVI LT(NAV, KC_TAB)    // 2: Tab; Navigation Layer
#define SPUM LT(NUM, KC_SPC)    // 3: Space; Numpad Layer
#define SYNT LT(SYM, KC_ENT)    // 4: Enter; Symbol Layer
#define BAMD LT(MEDIA, KC_BSPC) // 5: Backspace; Media Layer
#define FUND LT(FUN, KC_DEL)    // 6: Delete; Function Layer

// Layer Definitions
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//,-----------------------------------------------------.      0: Base       ,-----------------------------------------------------.
//     `   |   Q    |   W    |   E    |   R    |    T   |                    |    Y   |   U    |   I    |   O    |   P    |   \    |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//   Caps  |   A[⌃] |   S[⌥] |   D[⌘] |   F[⇧] |    G   |                    |    H   |   J[⇧] |   K[⌘] |   L[⌥] |   ;[⌃] |   '    |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//    Meh  |   Z    |   X    |   C    |   V    |    B   |                    |    N   |   M    |   ,    |   .    |   /    |  Hyper |
//|--------+--------+--------+--------+--------+--------|--------|  |--------|--------+--------+--------+--------+--------+--------|
//                                    |  [NAV] | [MOUSE]|  [NUM] |  |  [SYM] | [MEDIA]|  [FUN] |
//                                    |   Esc  |   Tab  |  Space |  |  Enter | BackSp | Delete |
                                    //`--------------------------'  `--------------------------'
[BASE] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_GRV,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSLS,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_CAPS,  HOME_A,  HOME_S,  HOME_D,  HOME_F,    KC_G,                         KC_H,  HOME_J,  HOME_K,  HOME_L, HOM_SCL, KC_QUOT,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_MEH,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_HYPR,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           MOSC,    TAVI,   SPUM,       SYNT,    BAMD,    FUND
                                    //`--------------------------'  `--------------------------'
),

//,-----------------------------------------------------.      1: Mouse      ,-----------------------------------------------------.
//         |        | TINIER | BIGGER | OLDSIZ |        |                    |MouseWh←|MouseWh↑|MouseWh↓|MouseWh→|        |        |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//         |    ⌃   |    ⌥   |    ⌘   |    ⇧   |        |                    | Mouse← | Mouse↓ | Mouse↑ | Mouse→ |MouseWh↓|MouseWh↑|
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//   REDO  |  UNDO  |   CUT  |  COPY  |  PASTE |   ⌘⌃V  |                    |        | Accel0 | Accel1 | Accel2 |MouseWh←|MouseWh→|
//|--------+--------+--------+--------+--------+--------|--------|  |--------|--------+--------+--------+--------+--------+--------|
//                                    | [Base] |  Tab   |  Space |  | LftClk | RgtClk | MidClk |
                                    //`--------------------------'  `--------------------------'
[MOUSE] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
    XXXXXXX, XXXXXXX,  TINIER,  BIGGER,  OLDSIZ, XXXXXXX,                      KC_WH_L, KC_WH_U ,KC_WH_D, KC_WH_R, XXXXXXX, XXXXXXX,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       REDO,    UNDO,     CUT,    COPY,    PAST,    UNFR,                      XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, XXXXXXX,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           MOSC,  KC_TAB,  KC_SPC,    KC_BTN1, KC_BTN2, KC_BTN3
                                    //`--------------------------'  `--------------------------'
),

//,-----------------------------------------------------.      2: Nav        ,-----------------------------------------------------.
//         |   ⇧⌘1  |   ⇧⌘2  |   ⇧⌘3  |   ⇧⌘4  |        |                    |   ⌥←   |   ⌥↓   |   ⌥↑   |   ⌥→   |        |        |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//         |    ⌃   |    ⌥   |    ⌘   |    ⇧   |    `   |                    |    ←   |    ↓   |    ↑   |    →   |MouseWh↓|MouseWh↑|
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//         |        |        |        |        |        |                    |  Home  |  PgDn  |  PgUp  |   End  |MouseWh←|MouseWh→|
//|--------+--------+--------+--------+--------+--------|--------|  |--------|--------+--------+--------+--------+--------+--------|
//                                    | [Base] |    ⌥   |  Space |  |    ⌘   |   ⌘[   |   ⌘]   |
                                    //`--------------------------'  `--------------------------'
[NAV] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
    XXXXXXX, KC_CAPW, KC_CAPP, KC_CPYW, KC_CPYP, XXXXXXX,                         C_CL,    C_CD,    C_CU,    C_CR, XXXXXXX, XXXXXXX,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,  KC_GRV,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_WH_D, KC_WH_U,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_WH_L, KC_WH_R,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_ESC,    TAVI,  KC_SPC,    KC_RGUI,  DEDENT,  INDENT
                                    //`--------------------------'  `--------------------------'
),

//,-----------------------------------------------------.      3: NumPad     ,-----------------------------------------------------.
//     ~   |    1   |    2   |    3   |    4   |    5   |                    |    6   |    7   |    8   |    9   |    0   |    =   |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//         |    ⌃   |    ⌥   |    ⌘   |    ⇧   |    `   |                    |        |    4   |    5   |    6   |    *   |    +   |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//   REDO  |  UNDO  |   CUT  |  COPY  |  PASTE |   ⌘⌃V  |                    |        |    1   |    2   |    3   |    /   |    -   |
//|--------+--------+--------+--------+--------+--------|--------|  |--------|--------+--------+--------+--------+--------+--------|
//                                    |   Esc  |   Tab  | [Base] |  |  Enter |    0   |    .   |
                                    //`--------------------------'  `--------------------------'
[NUM] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_TILD,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_EQL,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,  KC_GRV,                      XXXXXXX,    KC_4,    KC_5,    KC_6, KC_ASTR, KC_PLUS,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       REDO,    UNDO,     CUT,    COPY,    PAST,    UNFR,                      XXXXXXX,    KC_1,    KC_2,    KC_3, KC_SLSH, KC_MINS,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_ESC,  KC_TAB,    SPUM,     KC_ENT,    KC_0,  KC_DOT
                                    //`--------------------------'  `--------------------------'
),

//,-----------------------------------------------------.      4: Symbols    ,-----------------------------------------------------.
//     ~   |    !   |    @   |    #   |    $   |    %   |                    |    ^   |    &   |    *   |    (   |    )   |   <>   |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//    >=   |   &&   |   ||   |   ++   |   --   |    `   |                    |    -   |    =   |    \   |    [   |    ]   |   |    |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//    <=   |   *=   |   *=   |   {}   |   ()   |   []   |                    |    _   |    +   |   +=   |    {   |    }   |   -=   |
//|--------+--------+--------+--------+--------+--------|--------|  |--------|--------+--------+--------+--------+--------+--------|
//                                    |    ⌘   |   +=   |  Shift |  | [Base] | BackSp | Delete |
                                   //`---------------------------'  `--------------------------'
[SYM] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, TD(TRI),
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    GREATEQ,    ISEQ,     AND,      OR,    INCR,    DECR,                      KC_MINS,  KC_EQL, KC_BSLS, KC_LBRC, KC_RBRC, KC_PIPE,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     LESSEQ,   DIVEQ,     XEQ, TD(CBR), TD(PRN), TD(BRC),                      KC_UNDS, KC_PLUS,  PLUSEQ, KC_LCBR, KC_RCBR, MINUSEQ,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_LGUI,  PLUSEQ, KC_LSFT,       SYNT, KC_BSPC,  KC_DEL
                                    //`--------------------------'  `--------------------------'
),

//,-----------------------------------------------------.      5: Media      ,-----------------------------------------------------.
//         |   ⇧⌘1  |   ⇧⌘2  |   ⇧⌘3  |   ⇧⌘4  |        |                    |        |   ⇧⌘4  |   ⇧⌘3  |   ⇧⌘2  |   ⇧⌘1  |        |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//         |  Mute  | RewTrk | RewTrk |  Pause | FwdTrk |                    | RewTrk |  Mute  | FwdTrk |  Mute  |        |        |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//         | Brght↓ | Brght↑ |  Vol↓  |  Vol↑  |        |                    |        |  Vol↓  |  Vol↑  | Brght↓ | Brght↑ |        |
//|--------+--------+--------+--------+--------+--------|--------|  |--------|--------+--------+--------+--------+--------+--------|
//                                    |   Esc  |   Tab  |  Space |  |  Enter | [Base] | Delete |
                                    //`--------------------------'  `--------------------------'
[MEDIA] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
    XXXXXXX, KC_CAPW, KC_CAPP, KC_CPYW, KC_CPYP, XXXXXXX,                      XXXXXXX, KC_CPYP, KC_CPYW, KC_CAPP, KC_CAPW, XXXXXXX,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    XXXXXXX, XXXXXXX, KC_MUTE, KC_MRWD, KC_MPLY, KC_MFFD,                      KC_MRWD, KC_MUTE, KC_MPLY, KC_MFFD, XXXXXXX, XXXXXXX,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    XXXXXXX, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, XXXXXXX,                      XXXXXXX, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, XXXXXXX,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_ESC,  KC_TAB,  KC_SPC,     KC_ENT,    BAMD,  KC_DEL
                                    //`--------------------------'  `--------------------------'
),

//,-----------------------------------------------------.      6: Function   ,-----------------------------------------------------.
//         |   F12  |   F7   |   F8   |   F9   |        |                    |    1   |    2   |    3   |    4   |    5   |    6   |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//         |   F11  |   F4   |   F5   |   F6   |        |                    |    ←   |    ↓   |    ↑   |    →   |        |        |
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//         |   F10  |   F1   |   F2   |   F3   |        |                    |        |        |        |        |        |  Reset |
//|--------+--------+--------+--------+--------+--------|--------|  |--------|--------+--------+--------+--------+--------+--------|
//                                    |   Esc  |   Tab  |  Space |  |  Enter | BackSp | [Base] |
                                    //`--------------------------'  `--------------------------'
[FUN] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
    XXXXXXX,  KC_F12,   KC_F7,   KC_F8,   KC_F9, XXXXXXX,                         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    XXXXXXX,  KC_F11,   KC_F4,   KC_F5,   KC_F6, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    XXXXXXX,  KC_F10,   KC_F1,   KC_F2,   KC_F3, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_ESC,  KC_TAB,  KC_SPC,     KC_ENT, KC_BSPC,    FUND
                                    //`--------------------------'  `--------------------------'
)
};

#ifdef OLED_ENABLE
#    include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}
return rotation;
}

#define L_BASE 0
#define L_MOUSE 2
#define L_NAV 4
#define L_NUM 8
#define L_SYM 16
#define L_MEDIA 32
#define L_FUN 64

void oled_render_layer_state(void) {
    oled_write_P(PSTR("L: "), false);

    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case L_MOUSE:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case L_NAV:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case L_NUM:
            oled_write_ln_P(PSTR("Number Pad"), false);
            break;
        case L_SYM:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case L_MEDIA:
            oled_write_ln_P(PSTR("Media Keys"), false);
            break;
        case L_FUN:
            oled_write_ln_P(PSTR("Function"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Unhandled!"), false);
            break;
    }
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

#    define KEYLOG_LEN 5
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    oled_write_P(PSTR("BTMGK"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    oled_render_layer_state();
    render_keylock_status(host_keyboard_leds());
    render_mod_status(get_mods());
    render_bootmagic_status();

    render_keylogger_status();
}

void oled_task_user(void) {
    update_log();
    if (is_keyboard_master()) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_crkbd_logo();
    }
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_caps_word(keycode, record)) { return false; }
switch (keycode) {
    case BASE:
    if (record->event.pressed) {
        set_single_persistent_default_layer(BASE);
    }
    return false;
    break;
    return false;
    break;
    case SHRUGS:
    if (record->event.pressed) {
        SEND_STRING("¯\\_(ツ)_/¯");
    }
    break;
    case AND:
    if (record->event.pressed) {
        SEND_STRING("&&");
    }
    break;
    case OR:
    if (record->event.pressed) {
        SEND_STRING("||");
    }
    break;
    case GREATEQ:
    if (record->event.pressed) {
        SEND_STRING(">=");
    }
    break;
    case LESSEQ:
    if (record->event.pressed) {
        SEND_STRING("<=");
    }
    break;
    case PLUSEQ:
    if (record->event.pressed) {
        SEND_STRING("+=");
    }
    break;
    case MINUSEQ:
    if (record->event.pressed) {
        SEND_STRING("-=");
    }
    break;
    case ISEQ:
    if (record->event.pressed) {
        SEND_STRING("==");
    }
    break;
    case NOTEQ:
    if (record->event.pressed) {
        SEND_STRING("!=");
    }
    break;
    case DECR:
    if (record->event.pressed) {
        SEND_STRING("--");
    }
    break;
    case INCR:
    if (record->event.pressed) {
        SEND_STRING("++");
    }
    break;
    case XEQ:
    if (record->event.pressed) {
        SEND_STRING("*=");
    }
    break;
    case DIVEQ:
    if (record->event.pressed) {
        SEND_STRING("/=");
    }
    break;
}
return true;
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_A):
        case LT(1, KC_S):
        case LT(1, KC_D):
        case LT(1, KC_F):
        case LT(1, KC_J):
        case LT(1, KC_K):
        case LT(1, KC_L):
        case LT(1, KC_SCLN):
        return true;
        default:
        return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_A):
        case LT(1, KC_S):
        case LT(1, KC_D):
        case LT(1, KC_F):
        case LT(1, KC_J):
        case LT(1, KC_K):
        case LT(1, KC_L):
        case LT(1, KC_SCLN):
            return true;
        default:
            return false;
    }
}

int get_dance_status(qk_tap_dance_state_t *state) {
//NOTE: Interrupted means we are trying to do separate taps

if (state->count == 1) {
    return (state->interrupted || !state->pressed) ? SINGLE_TAP: SINGLE_HOLD;
}
else if (state->count == 2) {
    if (state->interrupted)
    return DOUBLE_SINGLE_TAP;
    return state->pressed ? DOUBLE_HOLD: DOUBLE_TAP;
}
else if (state->count == 3) {
    if (state->interrupted)
    return TRIPLE_SINGLE_TAP;
    return state->pressed ? TRIPLE_HOLD: TRIPLE_TAP;
}

return NO_TAP_STATE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TAGR]= ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_GRV),
    [TRI] = ACTION_TAP_DANCE_DOUBLE(KC_LT, KC_GT),
    [CBR] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
};
