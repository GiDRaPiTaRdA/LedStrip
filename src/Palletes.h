#ifndef SOME_HEADER_H
#define SOME_HEADER_H

#include <Arduino.h>
#include <FastLED.h>

class Palletes
{
    public:
        static CRGBPalette16 *CreatePallete(CRGB colors[], int colorsCount)
        {
            CRGBPalette16 *customPallete = new CRGBPalette16;

            int size = 16;

            int partSize = size / colorsCount;
            int part = 0;

            for (size_t i = 0; i < size; i++)
            {
                if (i > (part + 1) * partSize)
                    part++;

                customPallete->entries[i] = colors[part];
            }

            return customPallete;
        }

        static CRGBPalette16 *CreatePallete(CRGB color)
        {
            CRGB clrs[] = {color};
            CRGBPalette16 *pal = CreatePallete(clrs, sizeof(clrs) / sizeof(clrs[0]));
            return pal;
        }

        static CRGB GetColor(int hexValue)
{
    CRGB rgbColor;
    u_int8_t r = ((hexValue >> 16) & 0xFF); // Extract the RR byte
    u_int8_t g = ((hexValue >> 8) & 0xFF);  // Extract the GG byte
    u_int8_t b = ((hexValue)&0xFF);         // Extract the BB byte

    return CRGB(r, g, b);

}
static CRGB GetColor(String stringHexValue)
{
    int number = (int)strtol(stringHexValue.c_str(), NULL, 16);
    CRGB rgbColor = GetColor(number);
    return rgbColor;
}
};
#endif

