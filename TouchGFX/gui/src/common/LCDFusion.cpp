#include <gui/common/LCDFusion.hpp>
#include <string.h>

#include "KoreanFusionLetters.h"

const uint8_t* glyphs[16][27] =
{
    {image_m_pt_h0001,image_m_pt_h0002,image_m_pt_h0003,image_m_pt_h0004,image_m_pt_h0005,image_m_pt_h0006,image_m_pt_h0007,image_m_pt_h0008,
     image_m_pt_h0009,image_m_pt_h0010,image_m_pt_h0011,image_m_pt_h0012,image_m_pt_h0013,image_m_pt_h0014,image_m_pt_h0015,image_m_pt_h0016,
     image_m_pt_h0017,image_m_pt_h0018,image_m_pt_h0019, 0 },
    {image_m_pt_h0101,image_m_pt_h0102,image_m_pt_h0103,image_m_pt_h0104,image_m_pt_h0105,image_m_pt_h0106,image_m_pt_h0107,image_m_pt_h0108,
     image_m_pt_h0109,image_m_pt_h0110,image_m_pt_h0111,image_m_pt_h0112,image_m_pt_h0113,image_m_pt_h0114,image_m_pt_h0115,image_m_pt_h0116,
     image_m_pt_h0117,image_m_pt_h0118,image_m_pt_h0119, 0 },
    {image_m_pt_h0201,image_m_pt_h0202,image_m_pt_h0203,image_m_pt_h0204,image_m_pt_h0205,image_m_pt_h0206,image_m_pt_h0207,image_m_pt_h0208,
     image_m_pt_h0209,image_m_pt_h0210,image_m_pt_h0211,image_m_pt_h0212,image_m_pt_h0213,image_m_pt_h0214,image_m_pt_h0215,image_m_pt_h0216,
     image_m_pt_h0217,image_m_pt_h0218,image_m_pt_h0219, 0},
    {image_m_pt_h0301,image_m_pt_h0302,image_m_pt_h0303,image_m_pt_h0304,image_m_pt_h0305,image_m_pt_h0306,image_m_pt_h0307,image_m_pt_h0308,
     image_m_pt_h0309,image_m_pt_h0310,image_m_pt_h0311,image_m_pt_h0312,image_m_pt_h0313,image_m_pt_h0314,image_m_pt_h0315,image_m_pt_h0316,
     image_m_pt_h0317,image_m_pt_h0318,image_m_pt_h0319, 0},
    {image_m_pt_h0401,image_m_pt_h0402,image_m_pt_h0403,image_m_pt_h0404,image_m_pt_h0405,image_m_pt_h0406,image_m_pt_h0407,image_m_pt_h0408,
     image_m_pt_h0409,image_m_pt_h0410,image_m_pt_h0411,image_m_pt_h0412,image_m_pt_h0413,image_m_pt_h0414,image_m_pt_h0415,image_m_pt_h0416,
     image_m_pt_h0417,image_m_pt_h0418,image_m_pt_h0419, 0},
    {image_m_pt_h0501,image_m_pt_h0502,image_m_pt_h0503,image_m_pt_h0504,image_m_pt_h0505,image_m_pt_h0506,image_m_pt_h0507,image_m_pt_h0508,
     image_m_pt_h0509,image_m_pt_h0510,image_m_pt_h0511,image_m_pt_h0512,image_m_pt_h0513,image_m_pt_h0514,image_m_pt_h0515,image_m_pt_h0516,
     image_m_pt_h0517,image_m_pt_h0518,image_m_pt_h0519, 0},
    {image_m_pt_h0601,image_m_pt_h0602,image_m_pt_h0603,image_m_pt_h0604,image_m_pt_h0605,image_m_pt_h0606,image_m_pt_h0607,image_m_pt_h0608,
     image_m_pt_h0609,image_m_pt_h0610,image_m_pt_h0611,image_m_pt_h0612,image_m_pt_h0613,image_m_pt_h0614,image_m_pt_h0615,image_m_pt_h0616,
     image_m_pt_h0617,image_m_pt_h0618,image_m_pt_h0619, 0},
    {image_m_pt_h0701,image_m_pt_h0702,image_m_pt_h0703,image_m_pt_h0704,image_m_pt_h0705,image_m_pt_h0706,image_m_pt_h0707,image_m_pt_h0708,
     image_m_pt_h0709,image_m_pt_h0710,image_m_pt_h0711,image_m_pt_h0712,image_m_pt_h0713,image_m_pt_h0714,image_m_pt_h0715,image_m_pt_h0716,
     image_m_pt_h0717,image_m_pt_h0718,image_m_pt_h0719, 0},
    {image_m_pt_h0801,image_m_pt_h0802,image_m_pt_h0803,image_m_pt_h0804,image_m_pt_h0805,image_m_pt_h0806,image_m_pt_h0807,image_m_pt_h0808,
     image_m_pt_h0809,image_m_pt_h0810,image_m_pt_h0811,image_m_pt_h0812,image_m_pt_h0813,image_m_pt_h0814,image_m_pt_h0815,image_m_pt_h0816,
     image_m_pt_h0817,image_m_pt_h0818,image_m_pt_h0819,image_m_pt_h0820,image_m_pt_h0821, 0},
    {image_m_pt_h0901,image_m_pt_h0902,image_m_pt_h0903,image_m_pt_h0904,image_m_pt_h0905,image_m_pt_h0906,image_m_pt_h0907,image_m_pt_h0908,
     image_m_pt_h0909,image_m_pt_h0910,image_m_pt_h0911,image_m_pt_h0912,image_m_pt_h0913,image_m_pt_h0914,image_m_pt_h0915,image_m_pt_h0916,
     image_m_pt_h0917,image_m_pt_h0918,image_m_pt_h0919,image_m_pt_h0920,image_m_pt_h0921, 0},
    {image_m_pt_h1001,image_m_pt_h1002,image_m_pt_h1003,image_m_pt_h1004,image_m_pt_h1005,image_m_pt_h1006,image_m_pt_h1007,image_m_pt_h1008,
     image_m_pt_h1009,image_m_pt_h1010,image_m_pt_h1011,image_m_pt_h1012,image_m_pt_h1013,image_m_pt_h1014,image_m_pt_h1015,image_m_pt_h1016,
     image_m_pt_h1017,image_m_pt_h1018,image_m_pt_h1019,image_m_pt_h1020,image_m_pt_h1021, 0},
    {image_m_pt_h1101,image_m_pt_h1102,image_m_pt_h1103,image_m_pt_h1104,image_m_pt_h1105,image_m_pt_h1106,image_m_pt_h1107,image_m_pt_h1108,
     image_m_pt_h1109,image_m_pt_h1110,image_m_pt_h1111,image_m_pt_h1112,image_m_pt_h1113,image_m_pt_h1114,image_m_pt_h1115,image_m_pt_h1116,
     image_m_pt_h1117,image_m_pt_h1118,image_m_pt_h1119,image_m_pt_h1120,image_m_pt_h1121, 0},
    {image_m_pt_h1201,image_m_pt_h1202,image_m_pt_h1203,image_m_pt_h1204,image_m_pt_h1205,image_m_pt_h1206,image_m_pt_h1207,image_m_pt_h1208,
     image_m_pt_h1209,image_m_pt_h1210,image_m_pt_h1211,image_m_pt_h1212,image_m_pt_h1213,image_m_pt_h1214,image_m_pt_h1215,image_m_pt_h1216,
     image_m_pt_h1217,image_m_pt_h1218,image_m_pt_h1219,image_m_pt_h1220,image_m_pt_h1221,image_m_pt_h1222,image_m_pt_h1223,image_m_pt_h1224,
     image_m_pt_h1225,image_m_pt_h1226,image_m_pt_h1227},
    {image_m_pt_h1301,image_m_pt_h1302,image_m_pt_h1303,image_m_pt_h1304,image_m_pt_h1305,image_m_pt_h1306,image_m_pt_h1307,image_m_pt_h1308,
     image_m_pt_h1309,image_m_pt_h1310,image_m_pt_h1311,image_m_pt_h1312,image_m_pt_h1313,image_m_pt_h1314,image_m_pt_h1315,image_m_pt_h1316,
     image_m_pt_h1317,image_m_pt_h1318,image_m_pt_h1319,image_m_pt_h1320,image_m_pt_h1321,image_m_pt_h1322,image_m_pt_h1323,image_m_pt_h1324,
     image_m_pt_h1325,image_m_pt_h1326,image_m_pt_h1327},
    {image_m_pt_h1401,image_m_pt_h1402,image_m_pt_h1403,image_m_pt_h1404,image_m_pt_h1405,image_m_pt_h1406,image_m_pt_h1407,image_m_pt_h1408,
     image_m_pt_h1409,image_m_pt_h1410,image_m_pt_h1411,image_m_pt_h1412,image_m_pt_h1413,image_m_pt_h1414,image_m_pt_h1415,image_m_pt_h1416,
     image_m_pt_h1417,image_m_pt_h1418,image_m_pt_h1419,image_m_pt_h1420,image_m_pt_h1421,image_m_pt_h1422,image_m_pt_h1423,image_m_pt_h1424,
     image_m_pt_h1425,image_m_pt_h1426,image_m_pt_h1427},
    {image_m_pt_h1501,image_m_pt_h1502,image_m_pt_h1503,image_m_pt_h1504,image_m_pt_h1505,image_m_pt_h1506,image_m_pt_h1507,image_m_pt_h1508,
     image_m_pt_h1509,image_m_pt_h1510,image_m_pt_h1511,image_m_pt_h1512,image_m_pt_h1513,image_m_pt_h1514,image_m_pt_h1515,image_m_pt_h1516,
     image_m_pt_h1517,image_m_pt_h1518,image_m_pt_h1519,image_m_pt_h1520,image_m_pt_h1521,image_m_pt_h1522,image_m_pt_h1523,image_m_pt_h1524,
     image_m_pt_h1525,image_m_pt_h1526,image_m_pt_h1527}
};

#define BASE_OF_SYLLABLES 0xAC00 // Korean characters Unicode start at 0xAC00

const uint16_t cho[]=
{
    //1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
    0,0,0,0,0,0,0,0,0,1,3, 3, 3, 1, 2, 4, 4, 4, 2, 1, 3, 0
};

const uint16_t cho2[]=
{
    0,6,6,6,6,6,6,6,6,7,8,8,8,7,7,8,8,8,7,7,8,6
};

const uint16_t jong[]=
{
    0,0,2,0,2,1,2,1,2,3,0,2,1,3,3,1,2,1,3,3,1,1
};

void LCDFusion::drawGlyph(uint16_t* wbuf16, Rect widgetArea, int16_t x, int16_t y, uint16_t offsetX, uint16_t offsetY, const Rect& invalidatedArea, const GlyphNode* glyph, const uint8_t* glyphData, uint8_t byteAlignRow, colortype color, uint8_t bitsPerPixel, uint8_t alpha, TextRotation rotation)
{
    if (glyphData != 0)
    {
        LCDGPU2D::drawGlyph(wbuf16, widgetArea, x, y, offsetX, offsetY, invalidatedArea, glyph, glyphData, byteAlignRow, color, bitsPerPixel, alpha, rotation);
    } else {
        const uint16_t index_of_syllable = glyph->unicode - BASE_OF_SYLLABLES;
        const uint16_t index_of_cho = index_of_syllable / 588;
        const uint16_t index_of_jung = (index_of_syllable % 588) / 28;
        const uint16_t index_of_jong = index_of_syllable % 28;

        // We need to modify a bit the index result to match actual "Hangul code"
        int first = index_of_cho + 1;   // Index of the leading consonant (between 1 and 19)
        int middle = index_of_jung + 1; // Index of the vowel (between 1 and 20)
        int last = index_of_jong;       // Index of the (optional) trailing consonant

        int bul1 = 0;
        int bul2 = 0;
        int bul3 = 0;

        // Let's compute the bul numbers
        // First let's check if there's a trailing consonant
        if(last == 0) // No trailing consonant
        {
            bul1 = cho[middle];
            if(first == 1 || first == 24)
            {
                bul2 = 1;
            }
            else
            {
                bul2 = 2;
            }
        }
        else // We have a trailing consonant
        {
            bul1 = cho2[middle]-1;
            if(first == 1 || first == 24)
            {
                bul2 = 3;
            }
            else
            {
                bul2 = 4;
            }
            bul3 = jong[middle];
        }

        // Now combine the 2 or 3 bitmaps to a single bitmap (output)
        // The width of 21 bits is rounded to 3 bytes for a total of
        // 90 bytes (30 rows)
        uint8_t output[90];
        memset(output, 0x00, sizeof(output));

        // Sequences of Zero bytes are encoded as 0x00 LEN
        // Eg. 0x00, 0x00, 0x00 is encoded as 0x00 0x03
        const uint8_t* firstBitmap = glyphs[bul1][first-1];

        // Expand the bitmap in to result
        uint8_t* end = &output[90];
        uint8_t* dst = output;
        const uint8_t* src = firstBitmap;
        while (dst < end)
        {
            const uint8_t byte = *src++;
            if (byte == 0x00)
            {
                const uint8_t len = *src++;
                dst += len;
            }
            else
            {
                *dst++ = byte;
            }
        }

        // Or the pixels from the second bitmap, skip zeroes
        const uint8_t* secondBitmap = glyphs[7 + bul2][middle-1];
        dst = output;
        src = secondBitmap;
        while (dst < end)
        {
            const uint8_t byte = *src++;
            if (byte == 0x00)
            {
                const uint8_t len = *src++;
                dst += len;
            }
            else
            {
                *dst |= byte;
                dst++;
            }
        }

        // Or the pixels from the third bitmap, skip zeroes
        if (last != 0)
        {
            const uint8_t* thirdBitmap = glyphs[12 + bul3][last-1];
            dst = output;
            src = thirdBitmap;
            while (dst < end)
            {
                const uint8_t byte = *src++;
                if (byte == 0x00)
                {
                    const uint8_t len = *src++;
                    dst += len;
                }
                else
                {
                    *dst |= byte;
                    dst++;
                }
            }
        }

        // Now draw the combined 1bpp glyph
        LCDGPU2D::drawGlyph(wbuf16, widgetArea, x, y, offsetX, offsetY, invalidatedArea, glyph,
                            output , 1, color, 1, alpha, rotation);
    }    
}
