#include <WiFi.h>
#include "time.h"
#include "typedef.h"

// time server info
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

// updates time from server
int updateTimeFromServer() {
    // connect to WiFi
    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" CONNECTED");

    // init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
    
    // disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);

    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        return 1;
    }

    glb_server_time_last_updated = millis();

    return 0;
}

// prints the local time directly from the time info
void printESPTime() {
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

// translates the current timestamp to a timestring
void updateTimeString(enum words * prev_time_string, enum words * curr_time_string) {
    // if a saying is active, do nothing
    if (flagSayingActive) return;

    // save the old time string for future reference
    for (int i = 0; i < 8; i++) prev_time_string[i] = curr_time_string[i];

    // update the time from the local time
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        return;
    }

    // update the current hour and minute
    glb_hour = ((unsigned) timeinfo.tm_hour) % 12;
    glb_min = (unsigned) timeinfo.tm_min;
    glb_min_rounded = (glb_min/5)*5;
    glb_5min_progress = float(timeinfo.tm_sec) / 60 + glb_min % 5;

    // float min_float = (float) glb_min;

    // set the word string to none's
    clearTimeString("curr");

    // the first two words are always the same
    //curr_time_string[0] = HET;
    //curr_time_string[1] = IS;

    // set up the rest of the time
    int next_idx = 2;
    bool round_hour_up = true;

    switch (glb_min_rounded) {
        case 0:
            round_hour_up = false;
            break;
        case 5:
            curr_time_string[2] = VIJF_0;
            curr_time_string[3] = OVER;
            next_idx = 4;
            round_hour_up = false;
            break;
        case 10:
            curr_time_string[2] = TIEN_0;
            curr_time_string[3] = OVER;
            next_idx = 4;
            round_hour_up = false;
            break;
        case 15:
            curr_time_string[2] = KWART;
            curr_time_string[3] = OVER;
            next_idx = 4;
            round_hour_up = false;
            break;
        case 20:
            curr_time_string[2] = TIEN_0;
            curr_time_string[3] = VOOR;
            curr_time_string[4] = HALF;
            next_idx = 5;
            break;
        case 25:
            curr_time_string[2] = VIJF_0;
            curr_time_string[3] = VOOR;
            curr_time_string[4] = HALF;
            next_idx = 5;
            break;
        case 30:
            curr_time_string[0] = HET;
            curr_time_string[1] = IS;
            curr_time_string[2] = HALF;
            next_idx = 3;
            break;
        case 35:
            curr_time_string[2] = VIJF_0;
            curr_time_string[3] = OVER;
            curr_time_string[4] = HALF;
            next_idx = 5;
            break;
        case 40:
            curr_time_string[2] = TIEN_0;
            curr_time_string[3] = OVER;
            curr_time_string[4] = HALF;
            next_idx = 5;
            break;
        case 45:
            curr_time_string[2] = KWART;
            curr_time_string[3] = VOOR;
            next_idx = 4;
            break;
        case 50:
            curr_time_string[2] = TIEN_0;
            curr_time_string[3] = VOOR;
            next_idx = 4;
            break;
        case 55:
            curr_time_string[2] = VIJF_0;
            curr_time_string[3] = VOOR;
            next_idx = 4;
            break;
        default:
            Serial.println("Unknown rounded minute encountered in updateTimeString()...");
            break;
    }

    // if whole hour, make sure the UUR mark will light up
    if (next_idx == 2) {
        curr_time_string[0] = HET;
        curr_time_string[1] = IS;
        curr_time_string[3] = UUR;
    }

    // get the correct hour
    unsigned tmp_hour = glb_hour;
    if (round_hour_up) tmp_hour = (tmp_hour + 1) % 12;

    // select the correct hour
    switch (tmp_hour) {
        case 0:
            curr_time_string[next_idx] = TWAALF;
            break;
        case 1:
            curr_time_string[next_idx] = EEN;
            break;
        case 2:
            curr_time_string[next_idx] = TWEE;
            break;
        case 3:
            curr_time_string[next_idx] = DRIE;
            break;
        case 4:
            curr_time_string[next_idx] = VIER;
            break;
        case 5:
            curr_time_string[next_idx] = VIJF;
            break;
        case 6:
            curr_time_string[next_idx] = ZES;
            break;
        case 7:
            curr_time_string[next_idx] = ZEVEN;
            break;
        case 8:
            curr_time_string[next_idx] = ACHT;
            break;
        case 9:
            curr_time_string[next_idx] = NEGEN;
            break;
        case 10:
            curr_time_string[next_idx] = TIEN;
            break;
        case 11:
            curr_time_string[next_idx] = ELF;
            break;
        default:
            Serial.println("Unknown hour encountered in updateTimeStamp()...");
            break;
    }

    glb_time_string_last_updated = millis();

    return;
}

// prints the current timestring
void printTimeString(enum words * time_string) {
    for (int i=0; i < 8; i++) {
        Serial.print(text[time_string[i]]);
    }

    Serial.println("");
}

// initializes timestring
void clearTimeString(const char * name) {
    for (int i=0; i < 8; i++) {
        if (strcmp(name, "prev") == 0 || strcmp(name, "both") == 0) prev_time_string[i] = NONE;
        if (strcmp(name, "curr") == 0 || strcmp(name, "both") == 0) curr_time_string[i] = NONE;
    }
}

// compare two time strings
int cmpts(enum words * time_string_1, enum words * time_string_2) {
    int res = 0;
    for (int i=0; i < 8; i++) if (time_string_1[i] != time_string_2[i]) res++;
    // Serial.printf("%d %d %d %d %d %d %d %d | %d %d %d %d %d %d %d %d | res = %d\n", time_string_1[0], time_string_1[1], time_string_1[2], time_string_1[3], time_string_1[4], time_string_1[5], time_string_1[6], time_string_1[7], time_string_2[0], time_string_2[1], time_string_2[2], time_string_2[3], time_string_2[4], time_string_2[5], time_string_2[6], time_string_2[7], res);

    return res;
}
