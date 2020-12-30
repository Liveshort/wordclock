#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

// enum for the words that can be used as indices
enum words {
    HET,
    IS,
    HOOG,
    KWART,
    TIEN_0,
    VIJF_0,
    LATER,
    TIJD,
    DAN,
    OVER,
    VOOR,
    JE,
    HALF,
    ACHT,
    TIEN,
    NEGEN,
    TWEE,
    EEN,
    TWAALF,
    DENKT,
    BORREL,
    REL,
    DRIE,
    ZES,
    VIJF,
    NIEUWE,
    ZEVEN,
    ELF,
    VIER,
    UUR,
    NONE
};

// text literal for printing the time to serial
const char text[][8] = {
    "HET ",
    "IS ",
    "HOOG ",
    "KWART ",
    "TIEN ",
    "VIJF ",
    "LATER ",
    "TIJD ",
    "DAN ",
    "OVER ",
    "VOOR ",
    "JE ",
    "HALF ",
    "ACHT ",
    "TIEN ",
    "NEGEN ",
    "TWEE ",
    "EEN ",
    "TWAALF ",
    "DENKT ",
    "BORREL ",
    "REL ",
    "DRIE ",
    "ZES ",
    "VIJF ",
    "NIEUWE ",
    "ZEVEN ",
    "ELF ",
    "VIER ",
    "UUR ",
    "- "
};

// first element is H top left, with index 1
// index travels downwards from there and in a snake to the end
// uninitialized values will be zero and need to be filtered out
const byte led_positions[][6] = {
    {1, 22, 23},                // het
    {45, 66},                   // is
    {88, 89, 110, 111},         // hoog
    {2, 21, 24, 43, 46},        // kwart
    {87, 90, 109, 112},         // tien
    {3, 20, 25, 42},            // vijf
    {69, 86, 91, 108, 113},     // later
    {4, 19, 26, 41},            // tijd
    {41, 48, 63},               // dan
    {85, 92, 107, 114},         // over
    {5, 18, 27, 40},            // voor
    {49, 62},                   // je
    {84, 93, 106, 115},         // half
    {6, 17, 28, 39},            // acht
    {39, 50, 61, 72},           // tien
    {72, 83, 94, 105, 116},     // negen
    {7, 16, 29, 38},            // twee
    {29, 38, 51},               // een
    {60, 73, 82, 95, 104, 117}, // twaalf
    {8, 15, 30, 37, 52},        // denkt
    {59, 74, 81, 96, 103, 118}, // borrel
    {96, 103, 118},             // rel
    {9, 14, 31, 36},            // drie
    {53, 58, 75},               // zes
    {80, 97, 102, 119},         // vijf
    {10, 13, 32, 35, 54, 57},   // nieuwe
    {76, 79, 98, 101, 120},     // zeven
    {11, 12, 33},               // elf
    {34, 55, 56, 77},           // vier
    {99, 100, 121},             // uur
    {0, 0, 0, 0, 0, 0}          // none
};

// translate the snaked vertical values to horizontal rows to
// to produce better color range
const byte vert_to_hor[] = {1, 22, 23, 44, 45, 66, 67, 88, 89, 110, 111, 112, 109, 90, 87, 68, 65, 46, 43, 24, 21, 2, 3, 20, 25, 42, 47, 64, 69, 86, 91, 108, 113, 114, 107, 92, 85, 70, 63, 48, 41, 26, 19, 4, 5, 18, 27, 40, 49, 62, 71, 84, 93, 106, 115, 116, 105, 94, 83, 72, 61, 50, 39, 28, 17, 6, 7, 16, 29, 38, 51, 60, 73, 82, 95, 104, 117, 118, 103, 96, 81, 74, 59, 52, 37, 30, 15, 8, 9, 14, 31, 36, 53, 58, 75, 80, 97, 102, 119, 120, 101, 98, 79, 76, 57, 54, 35, 32, 13, 10, 11, 12, 33, 34, 55, 56, 77, 78, 99, 100, 121, 126, 125, 124, 123, 122};

const byte vert_to_row[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 11, 11, 11, 11};

// hardcoded square root function
const byte square_root[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 10, 10, 11, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 22, 22, 23, 23, 24, 25, 25, 26, 27, 27, 28, 29, 29, 30, 31, 31, 32, 33, 33, 34, 35, 36, 36, 37, 38, 39, 40, 40, 41, 42, 43, 44, 44, 45, 46, 47, 48, 49, 50, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 79, 80, 81, 82, 83, 84, 85, 87, 88, 89, 90, 91, 93, 94, 95, 96, 97, 99, 100, 101, 102, 104, 105, 106, 108, 109, 110, 112, 113, 114, 116, 117, 118, 120, 121, 122, 124, 125, 127, 128, 129, 131, 132, 134, 135, 137, 138, 140, 141, 143, 144, 146, 147, 149, 150, 152, 153, 155, 156, 158, 160, 161, 163, 164, 166, 168, 169, 171, 172, 174, 176, 177, 179, 181, 182, 184, 186, 188, 189, 191, 193, 195, 196, 198, 200, 202, 203, 205, 207, 209, 211, 212, 214, 216, 218, 220, 222, 224, 225, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255};

const uint16_t lightLevelMap[] = {0, 5, 0, 6, 20, 31, 21, 50, 63, 51, 100, 127, 101, 200, 191, 201, 65535, 255};

const enum words saying_1[8] = {HET, IS, HOOG, TIJD, NONE, NONE, NONE, NONE};
const enum words saying_2[8] = {HET, IS, LATER, DAN, JE, DENKT, NONE, NONE};
const enum words saying_3[8] = {HET, IS, TIJD, VOOR, EEN, NIEUWE, NONE, NONE};
const enum words saying_4[8] = {HET, IS, TIJD, VOOR, EEN, BORREL, NONE, NONE};
const enum words saying_5[8] = {HOOG, TIJD, VOOR, EEN, BORREL, NONE, NONE, NONE};
const enum words saying_6[8] = {HOOG, TIJD, VOOR, EEN, NIEUWE, NONE, NONE, NONE};
const enum words saying_8[8] = {HOOG, OVER, NONE, NONE, NONE, NONE, NONE, NONE};
const enum words * sayings[7] = {saying_1, saying_2, saying_3, saying_4, saying_5, saying_6, saying_8};

#endif
