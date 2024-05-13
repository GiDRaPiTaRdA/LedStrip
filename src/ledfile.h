#include <Arduino.h>
#include "Colors.h"
#include <FastLED.h>

#define LED_PIN     2
#define NUM_LEDS    30
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds1[NUM_LEDS];


#define UPDATES_PER_SECOND 50
#define MAGICNUM 3

uint8_t paletteIndex = 0;
uint8_t paletteIndexMax = 0;

CRGBPalette16 currentPalette;
TBlendType currentBlending;
uint8_t brightness = 90;

void FillLEDsFromPaletteColors(uint8_t colorIndex)
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        leds1[i] = ColorFromPalette(currentPalette, colorIndex, 255, currentBlending);
        colorIndex += MAGICNUM;
    }
}

void LedLoop()
{
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

    FillLEDsFromPaletteColors(startIndex);

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void StupLed(){
    
    currentPalette = palettes[paletteIndex];
    currentBlending = LINEARBLEND;

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds1, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(255);

    paletteIndexMax = sizeof(palettes) / sizeof(palettes[0]) - 1;
}

//  bool IRInputProcessing(IRInput irInput)
// {
//     // IR Input
//     if (irInput.irrecv.decode())
//     {
//         uint16_t cmd = irInput.GetCommand();

//         // Serial.println(cmd);

//         uint8_t brDelta = 20;

//         bool cmdRecognized = true;

//         if (cmd == IRInput::butHash)
//         {
//             brightness = 255;

//             Serial.print("Brightness set to:");
//             Serial.println(brightness);
//         }
//         else if (cmd == IRInput::butStar)
//         {
//             brightness = 0;

//             Serial.print("Brightness set to:");
//             Serial.println(brightness);
//         }
//         else if (cmd == IRInput::butLeft)
//         {
//             if ((int32_t)paletteIndex - 1 < 0)
//                 paletteIndex = paletteIndexMax;
//             else
//                 paletteIndex -= 1;

//             currentPalette = palettes[paletteIndex];

//             Serial.print("Palette set to:");
//             Serial.println(paletteIndex);
//         }
//         else if (cmd == IRInput::butRight)
//         {
//             if ((int32_t)paletteIndex + 1 > paletteIndexMax)
//                 paletteIndex = 0;
//             else
//                 paletteIndex += 1;
                
//             currentPalette = palettes[paletteIndex];

//             Serial.print("Palette set to:");
//             Serial.println(paletteIndex);
//         }
//         else if (IRInput::SwitchButton(cmd) != -1)
//         {
//             int but = IRInput::SwitchButton(cmd);
//             if (but <= paletteIndexMax)
//             {
//                 paletteIndex = but;
//                 currentPalette = palettes[paletteIndex];
//             }

//             Serial.print("Palette set to:");
//             Serial.println(paletteIndex);
//         }
//         else
//         {
//             cmdRecognized = false;
//         }

//         delay(50);

//         irInput.Resume();

//         return cmdRecognized;       
//     }

//     return false;
// }

//  void IRInputProcessing()
// {
//     // IR Input
//     if (irInput.irrecv.decode())
//     {
//         uint16_t cmd = irInput.GetCommand();

//         // Serial.println(cmd);

//         uint8_t brDelta = 20;

//         bool cmdRecognized = true;

//         if (cmd == IRInput::butUp)
//         {
//             ledStrip.ChangeBrightness(+brDelta);

//             Serial.print("Brightness set to:");
//             Serial.println(ledStrip.GetBrightness());
//         }
//         else if (cmd == IRInput::butDown)
//         {
//             ledStrip.ChangeBrightness(-brDelta);

//             Serial.print("Brightness set to:");
//             Serial.println(ledStrip.GetBrightness());
//         }
//         else if (cmd == IRInput::butHash)
//         {
//             ledStrip.SetBrightness(ledStrip.brMax);

//             Serial.print("Brightness set to:");
//             Serial.println(ledStrip.GetBrightness());
//         }
//         else if (cmd == IRInput::butStar)
//         {
//             ledStrip.SetBrightness(ledStrip.brMin);

//             Serial.print("Brightness set to:");
//             Serial.println(ledStrip.GetBrightness());
//         }
//         else if (cmd == IRInput::butLeft)
//         {
//             if ((int32_t)paletteIndex - 1 < 0)
//                 paletteIndex = paletteIndexMax;
//             else
//                 paletteIndex -= 1;
//             ledStrip.SetPalette(palettes[paletteIndex]);

//             Serial.print("Palette set to:");
//             Serial.println(paletteIndex);
//         }
//         else if (cmd == IRInput::butRight)
//         {
//             if ((int32_t)paletteIndex + 1 > paletteIndexMax)
//                 paletteIndex = 0;
//             else
//                 paletteIndex += 1;
//             ledStrip.SetPalette(palettes[paletteIndex]);

//             Serial.print("Palette set to:");
//             Serial.println(paletteIndex);
//         }
//         else if (IRInput::SwitchButton(cmd) != -1)
//         {
//             int but = IRInput::SwitchButton(cmd);
//             if (but <= paletteIndexMax)
//             {
//                 paletteIndex = but;
//                 ledStrip.SetPalette(palettes[paletteIndex]);
//             }

//             Serial.print("Palette set to:");
//             Serial.println(paletteIndex);
//         }
//         else
//         {
//             cmdRecognized = false;
//         }

//         if (cmdRecognized)
//             LedNotifications::InstructionAcceptedBlink(led);
//         else
//             delay(50);

//         irInput.Resume();
//     }
// }
