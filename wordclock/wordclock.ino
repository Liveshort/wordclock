#include "typedef.h"

// global constants
#define CLOCK_UPDATES_PER_SECOND 10
#define AMBIENT_UPDATES_PER_SECOND 1
#define SERVER_TIME_UPDATE_RATE 3600
#define SAYING_RATE 300
#define SAYING_DURATION 15
#define ANIMATION_FRAMES_PER_SECOND 25

// wifi info
const char* ssid       = "Gulag-LangeAfstandRadar";
const char* password   = "inspiratieloos";

// define appropriate globals for the time
unsigned glb_hour = 0;
unsigned glb_min = 0;
unsigned glb_min_rounded = 0;
float glb_5min_progress = 0;
unsigned long glb_time_string_last_updated = 0;
unsigned long glb_server_time_last_updated = 0;
unsigned long glb_last_saying = 140;

// global time string variables
enum words prev_time_string[8];
enum words curr_time_string[8];

// global flags
bool flagChangePalette = false;
bool flagSayingActive = false;

// other globals
uint16_t ambientLightLevel = 100;
unsigned long glb_ambient_last_updated = 0;

void setup() {
    // start serial
    Serial.begin(115200);

    // properly initialize the time strings
    clearTimeString("both");

    // update the time from the server via wifi
    updateTimeFromServer();
    // print via serial
    printESPTime();

    // set up randomizer
    randomSeed(0);

    // set up light sensors
    setup_ambient_light_sensors();

    // initialize led array
    delay(2000); // power-up safety delay
    setup_led_control();
}

void loop() {
    // esp_sleep_enable_timer_wakeup(5000000);
    // esp_light_sleep_start();

    printESPTime();

    // if (millis() - glb_server_time_last_updated > SERVER_TIME_UPDATE_RATE * 1000) updateTimeFromServer();

    updateTimeString(prev_time_string, curr_time_string);
    printTimeString(curr_time_string);

    if (flagSayingActive && millis() - glb_last_saying > SAYING_DURATION * 1000) {
        glb_last_saying = millis();
        flagSayingActive = false;

        updateTimeString(prev_time_string, curr_time_string);
    }

    if (!flagSayingActive && millis() - glb_last_saying > SAYING_RATE * 1000) {
        glb_last_saying = millis();
        flagSayingActive = true;

        byte curr_saying = random(7);
        for (unsigned i=0; i < 8; ++i) {
            prev_time_string[i] = curr_time_string[i];
            curr_time_string[i] = sayings[curr_saying][i];
        }

        simple_transition(prev_time_string, curr_time_string, &flagChangePalette);

        for (unsigned i=0; i < 8; ++i) prev_time_string[i] = curr_time_string[i];
    }

    updatePaletteCounter(&flagChangePalette);

    if (millis() - glb_ambient_last_updated > 1000/AMBIENT_UPDATES_PER_SECOND) {
        updateAmbientLightLevel(&ambientLightLevel);
        updateGlobalBrightness(ambientLightLevel);
    }

    if (cmpts(prev_time_string, curr_time_string)) simple_transition(prev_time_string, curr_time_string, &flagChangePalette);

    setLedBrightnessFromTimeString(curr_time_string);
    // printActiveLedPositions();

    writePaletteToLEDs();
    showLEDsAndDelay(1000/CLOCK_UPDATES_PER_SECOND);
}
