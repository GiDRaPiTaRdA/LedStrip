#include <Arduino.h>
#include <FastLED.h>
#include "Palletes.h"
#include "Colors.h"

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.

#define MAGICNUM 3


// #define LED_PIN     2
// #define BRIGHTNESS  64
// #define LED_TYPE    WS2811
// #define COLOR_ORDER GRB

class LedStrip
{
private:
    uint8_t pin;
    uint8_t ledsCount;
    int speed = 1;
    uint8_t brightness = 90;
    uint8_t updatesPerSecond = 60;
    CRGBPalette16 currentPalette = *Palletes::CreatePallete(red,1);
    TBlendType currentBlending = LINEARBLEND;
    CRGB *leds;
    
    void FillLEDsFromPaletteColors(uint8_t colorIndex)
    {
        for (int i = 0; i < ledsCount; ++i)
        {
            leds[i] = ColorFromPalette(currentPalette, colorIndex, 255, currentBlending);
            colorIndex += MAGICNUM;
        }
    }

public:
    static const uint8_t brMax = 255;
    static const uint8_t brMin = 0;

    LedStrip(int ledsCount)
    {
        LedStrip::ledsCount = ledsCount;
    }

    // // Template function to mimic FastLED.addLeds
    template <template<uint8_t DATA_PIN, EOrder RGB_ORDER> class CHIPSET, uint8_t DATA_PIN, EOrder RGB_ORDER>
    void Setup()
    {
        leds = new CRGB[ledsCount];

        FastLED.addLeds<CHIPSET, DATA_PIN, RGB_ORDER>(leds, ledsCount);
        FastLED.setBrightness(brightness);
    }


    void SetBlending(TBlendType blending){
          currentBlending = blending;
    }

    TBlendType GetBlending(){
        return currentBlending;
    }

    void ChangeBrightness(int8_t deltaValue){
        SetBrightness(brightness+deltaValue);
    }

    void SetBrightness(int8_t value)
    {
        if (value < brMin)
            brightness = brMin;
        else if (value > brMax)
        {
            brightness = brMax;
        }
        else
        {
            brightness = value;
        }

         FastLED.setBrightness(brightness);
    }

    uint8_t GetBrightness()
    {
        return brightness;
    }

    void SetColor(CRGB color)
    {
        currentPalette = *Palletes::CreatePallete(color);
    }

    void SetColor(int color)
    {
        currentPalette = *Palletes::CreatePallete(color);
    }

    void SetPalette(CRGBPalette16* pallete)
    {
        currentPalette = *pallete;
    }

    uint16_t GetSpeed(){
        return speed;
    }

    void SetSpeed(uint16_t speed){
        LedStrip::speed=speed;
    }

    void ChangeSpeed(int deltaValue){
         SetSpeed(speed+deltaValue);
    }

    uint8_t GetUpdatesPerSecond(){
        return updatesPerSecond;
    }

     void SetUpdatesPerSecond(uint8_t updatesPerSecond){
        LedStrip::updatesPerSecond = updatesPerSecond;
    }

    void Loop()
    {
        static uint8_t startIndex = 0;
        startIndex = startIndex + speed; /* motion speed */

        FillLEDsFromPaletteColors(startIndex);

        FastLED.show();
        FastLED.delay(1000 / updatesPerSecond);
    }
};