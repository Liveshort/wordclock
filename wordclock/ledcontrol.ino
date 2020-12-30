#include <FastLED.h>
#include "typedef.h"

// led info
#define LED_PIN     25
#define NUM_LEDS    126
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

unsigned char glb_brt_lim = 64;

CRGB leds[NUM_LEDS];
uint8_t glb_led_brt[NUM_LEDS];

CRGBPalette16 currentPalette;
const CRGB *  currentColorScheme;
TBlendType    currentBlending;

// const TProgmemPalette16 customForestPalette_p PROGMEM = {CRGB::DarkGreen, CRGB::DarkGreen, CRGB::DarkGreen, CRGB::DarkGreen, CRGB::Olive, CRGB::Olive, CRGB::Olive, CRGB::Olive, CRGB::Gold, CRGB::Olive, CRGB::Gold, CRGB::Gold, CRGB::Goldenrod, CRGB::Goldenrod, CRGB::Goldenrod, CRGB::Goldenrod};
// const TProgmemPalette16 customLavaPalette_p PROGMEM = {CRGB::Gold, CRGB::Maroon, CRGB::Gold, CRGB::Maroon, CRGB::DarkRed, CRGB::Maroon, CRGB::DarkRed, CRGB::DarkRed, CRGB::DarkRed, CRGB::Red, CRGB::Orange, CRGB::Grey, CRGB::Orange, CRGB::Red, CRGB::Gold};

const CRGB fireColorScheme[48] = { CRGB(255,215,0), CRGB(255,206,0), CRGB(255,198,0), CRGB(255,190,0), CRGB(255,181,0), CRGB(255,173,0), CRGB(255,165,0), CRGB(255,156,0), CRGB(255,148,0), CRGB(255,140,0), CRGB(255,131,0), CRGB(255,123,0), CRGB(255,165,0), CRGB(255,149,0), CRGB(255,133,0), CRGB(255,117,0), CRGB(255,101,0), CRGB(255,85,0), CRGB(255,69,0), CRGB(255,53,0), CRGB(255,37,0), CRGB(255,21,0), CRGB(255,5,0), CRGB(255,-11,0), CRGB(255,69,0), CRGB(255,85,0), CRGB(255,101,0), CRGB(255,117,0), CRGB(255,133,0), CRGB(255,149,0), CRGB(255,165,0), CRGB(255,181,0), CRGB(255,197,0), CRGB(255,213,0), CRGB(255,229,0), CRGB(255,245,0), CRGB(255,165,0), CRGB(255,173,0), CRGB(255,181,0), CRGB(255,190,0), CRGB(255,198,0), CRGB(255,206,0), CRGB(255,215,0), CRGB(255,223,0), CRGB(255,231,0), CRGB(255,240,0), CRGB(255,248,0), CRGB(255,256,0) };
const CRGB forestColorScheme[48] = { CRGB(50,205,50), CRGB(67,205,50), CRGB(84,205,49), CRGB(102,205,50), CRGB(119,205,49), CRGB(136,205,50), CRGB(154,205,50), CRGB(171,205,50), CRGB(188,205,49), CRGB(206,205,50), CRGB(223,205,50), CRGB(240,204,49), CRGB(154,205,50), CRGB(165,208,43), CRGB(177,211,36), CRGB(189,215,30), CRGB(201,218,23), CRGB(213,221,16), CRGB(225,225,10), CRGB(236,228,3), CRGB(248,231,-3), CRGB(260,235,-10), CRGB(272,238,-16), CRGB(284,241,-23), CRGB(225,225,10), CRGB(213,221,16), CRGB(201,218,23), CRGB(189,215,30), CRGB(177,211,36), CRGB(165,208,43), CRGB(154,205,50), CRGB(142,201,56), CRGB(130,198,63), CRGB(118,195,70), CRGB(106,191,76), CRGB(94,188,83), CRGB(154,205,50), CRGB(136,205,50), CRGB(119,205,49), CRGB(102,205,50), CRGB(84,205,49), CRGB(67,205,50), CRGB(50,205,50), CRGB(32,205,50), CRGB(15,205,49), CRGB(-2,205,50), CRGB(-19,205,50), CRGB(-36,204,49) };
const CRGB skyColorScheme[48] = { CRGB(0,191,255), CRGB(0,198,251), CRGB(0,205,248), CRGB(0,213,245), CRGB(0,220,241), CRGB(0,227,238), CRGB(0,235,235), CRGB(0,242,231), CRGB(0,249,228), CRGB(0,257,225), CRGB(0,264,221), CRGB(0,271,218), CRGB(0,235,235), CRGB(10,213,233), CRGB(21,191,231), CRGB(32,170,230), CRGB(43,148,228), CRGB(54,126,226), CRGB(65,105,225), CRGB(75,83,223), CRGB(86,61,221), CRGB(97,40,220), CRGB(108,18,218), CRGB(119,-3,216), CRGB(65,105,225), CRGB(54,126,226), CRGB(43,148,228), CRGB(32,170,230), CRGB(21,191,231), CRGB(10,213,233), CRGB(0,235,235), CRGB(-10,256,236), CRGB(-21,278,238), CRGB(-32,300,240), CRGB(-43,321,241), CRGB(-54,343,243), CRGB(0,235,235), CRGB(0,227,238), CRGB(0,220,241), CRGB(0,213,245), CRGB(0,205,248), CRGB(0,198,251), CRGB(0,191,255), CRGB(0,183,258), CRGB(0,176,261), CRGB(0,169,265), CRGB(0,161,268), CRGB(0,154,271) };
const CRGB whiteColorScheme[48] = { CRGB(240,248,255), CRGB(241,248,255), CRGB(242,247,255), CRGB(244,248,255), CRGB(245,247,255), CRGB(246,248,255), CRGB(248,248,255), CRGB(249,248,255), CRGB(250,247,255), CRGB(252,248,255), CRGB(253,248,255), CRGB(254,247,255), CRGB(248,248,255), CRGB(249,248,254), CRGB(250,248,253), CRGB(251,249,252), CRGB(252,249,251), CRGB(253,249,250), CRGB(255,250,250), CRGB(256,250,249), CRGB(257,250,248), CRGB(258,251,247), CRGB(259,251,246), CRGB(260,251,245), CRGB(255,250,250), CRGB(253,249,250), CRGB(252,249,251), CRGB(251,249,252), CRGB(250,248,253), CRGB(249,248,254), CRGB(248,248,255), CRGB(246,247,255), CRGB(245,247,256), CRGB(244,247,257), CRGB(243,246,258), CRGB(242,246,259), CRGB(248,248,255), CRGB(246,248,255), CRGB(245,247,255), CRGB(244,248,255), CRGB(242,247,255), CRGB(241,248,255), CRGB(240,248,255), CRGB(238,248,255), CRGB(237,247,255), CRGB(236,248,255), CRGB(234,248,255), CRGB(233,247,255) };

// const CRGBPalette16 paletteOptions[] = {customForestPalette_p, OceanColors_p, CloudColors_p, customLavaPalette_p};
const CRGB * colorSchemeOptions[] = {fireColorScheme, forestColorScheme, skyColorScheme, whiteColorScheme};

// setup LED control
void setup_led_control() {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(glb_brt_lim);

    currentColorScheme = colorSchemeOptions[0];
    // currentPalette = paletteOptions[3];
    // currentBlending = LINEARBLEND;
}

// show leds and delay
void showLEDsAndDelay(unsigned delay) {
    FastLED.show();
    FastLED.delay(delay);
}

// print led positions to be filled
void printActiveLedPositions() {
    for (int i=0; i < NUM_LEDS; i++) {
        int j = vert_to_hor[i] - 1;
        if (glb_led_brt[j] > 0) {
            Serial.print(j);
            Serial.print(", ");
        }
    }
    Serial.println(glb_5min_progress);
}

// updates global brightness according to the ambient light level
void updateGlobalBrightness(uint16_t ambientLightLevel) {
    for (unsigned i=0; i < 6; ++i) {
        if (ambientLightLevel >= lightLevelMap[3*i] && ambientLightLevel <= lightLevelMap[3*i+1]) glb_brt_lim = lightLevelMap[3*i+2];
    }

    Serial.printf("updated global brightness to %u from ambient light level %u\n", glb_brt_lim, ambientLightLevel);

    FastLED.setBrightness(glb_brt_lim);
}

// write the actual values to the leds
void writePaletteToLEDs() {
    static uint16_t startNumber = 0;
    static uint8_t startIndex = 0;
    // set up motion speed of color changes
    startNumber += 4;
    startIndex = startNumber/256;

    uint8_t colorIndex = startIndex;
    for(unsigned i = 0; i < NUM_LEDS; i++) {
        unsigned r = (4*vert_to_row[i] + startIndex) % 48;
        CRGB currColor = currentColorScheme[r];

        leds[i] = glb_led_brt[i]*currColor;
    }
}

// // write the actual values to the leds
// void writePaletteToLEDs() {
//     static uint16_t startNumber = 0;
//     static uint8_t startIndex = 0;
//     // set up motion speed of color changes
//     startNumber += 16;
//     startIndex = startNumber/256;
//
//     uint8_t colorIndex = startIndex;
//     for(unsigned i = 0; i < NUM_LEDS; i++) {
//         unsigned j = vert_to_hor[i] - 1;
//
//         leds[j] = ColorFromPalette(currentPalette, colorIndex, glb_led_brt[j], currentBlending);
//         colorIndex += 2;
//     }
// }

// update a value that rotates through palettes every once in a while
void updatePaletteCounter(bool * flagChangePalette) {
    static uint16_t paletteCounter = 1;

    if (paletteCounter == 0) *flagChangePalette = true;

    // Serial.printf("current palette counter = %u\n", paletteCounter);

    paletteCounter++;
}

// updates current palette
void cycleCurrentPalette() {
    static byte paletteIndex = 0;

    paletteIndex = (paletteIndex + 1) % 4;

    // currentPalette = paletteOptions[paletteIndex];
    currentColorScheme = colorSchemeOptions[paletteIndex];
}

// write led brightnesses to be filled
void setLedBrightnessFromTimeString(enum words * time_string) {
    clearLedBrightness();

    for (int i=0; i < 8; i++) {
        for (int j=0; j < 6; j++) {
            int curr = led_positions[time_string[i]][j];

            if (curr > 0) glb_led_brt[curr-1] = 255;
        }
    }

    for (int i=0; i < 5; i++) {
        if (glb_5min_progress - i > 1) {
            glb_led_brt[NUM_LEDS - 1 - i] = 255;
        } else if (glb_5min_progress - i > 0) {
            glb_led_brt[NUM_LEDS - 1 - i] = square_root[unsigned((glb_5min_progress - i)*255)];
        }
    }
}

// simple transition
void simple_transition(enum words * prev_time_string, enum words * curr_time_string, bool * flagChangePalette) {
    clearLedBrightness();

    int frames = 50;

    for (int t=0; t <= frames; t++) {
        for (int i=0; i < 8; i++) {
            for (int j=0; j < 6; j++) {
                int curr = led_positions[prev_time_string[i]][j];

                if (curr > 0) glb_led_brt[curr-1] = square_root[unsigned(255 * (1.0*(frames - t)/frames))];
            }
        }

        writePaletteToLEDs();
        FastLED.delay(1000 / ANIMATION_FRAMES_PER_SECOND);
    }

    if (*flagChangePalette) {
        cycleCurrentPalette();
        *flagChangePalette = false;
    }

    for (int t=0; t <= frames; t++) {
        for (int i=0; i < 8; i++) {
            for (int j=0; j < 6; j++) {
                int curr = led_positions[curr_time_string[i]][j];

                if (curr > 0) glb_led_brt[curr-1] = square_root[unsigned(255 * (1.0*t/frames))];
            }
        }

        writePaletteToLEDs();
        FastLED.delay(1000 / ANIMATION_FRAMES_PER_SECOND);
    }
}

// clear led brightnesses to be filled
void clearLedBrightness() {
    for (int i=0; i < NUM_LEDS; i++) {
        glb_led_brt[i] = 0;
    }
}
