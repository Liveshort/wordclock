#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeterR(0x23);
BH1750 lightMeterL(0x5C);

byte ambientLightLevelHistory[] = {100,100,100,100,100,100,100,100,100,100};

void setup_ambient_light_sensors() {
    lightMeterR.begin(BH1750_CONTINUOUS_HIGH_RES_MODE_2);
    lightMeterL.begin(BH1750_CONTINUOUS_HIGH_RES_MODE_2);
}

void updateAmbientLightLevel(uint16_t * ambientLightLevel) {
    static byte currLLIdx = 0;

    glb_ambient_last_updated = millis();

    uint16_t llR = lightMeterR.readLightLevel();
    uint16_t llL = lightMeterL.readLightLevel();

    uint16_t avgLL = (llR + llL) / 2;

    ambientLightLevelHistory[currLLIdx] = avgLL;

    currLLIdx = (currLLIdx + 1) % 10;

    Serial.print("current ambient ll history: [ ");

    uint32_t avg = 0;
    for (unsigned i=0; i < 10; ++i) {
        avg += ambientLightLevelHistory[i];
        Serial.print(ambientLightLevelHistory[i]);
        Serial.print(" ");
    }

    Serial.printf("] --> %u\n", avg);

    *ambientLightLevel = uint16_t(avg/10);
}
