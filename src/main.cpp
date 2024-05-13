#include <Arduino.h>

#include <FastLED.h>
#include <vector>
#include "IRremote.h"

#include <Array.h>
#include "LedNotifications.h"
#include "StringExtension.h"
#include "IRInput.h"

// #include "file.h"
#include "LedStrip.h"
#include "Colors.h"

#include <Preferences.h>

int serialExchangeSpeed = 115200; // bits per second

// IR control pin
const int irPin = 3;

#define LED_PIN     2
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

// Objects
LED led = LED(8, true);
IRInput irInput(irPin);

const char* paleteIndexKey = "paleteIndex";
const char* stripBrightnessKey = "stripBrightness";
Preferences preferences;

LedStrip ledStrip = LedStrip(90);

int8_t defaultBrightness = 255;
uint8_t paletteIndex = 5;

uint8_t paletteIndexMax = sizeof(palettes) / sizeof(palettes[0]) - 1;

void LoadPreferences(){
    preferences.begin("led-strip", false); // false: read-only
    
    if(preferences.isKey(paleteIndexKey))
    {
        paletteIndex = preferences.getInt(paleteIndexKey);
    }

    if(preferences.isKey(stripBrightnessKey))
    {
        defaultBrightness = preferences.getInt(stripBrightnessKey);
    }
}

void setup()
{
    Serial.begin(serialExchangeSpeed);
    // while (!Serial)
    //      ;

    led.Setup();
    irInput.Setup();

    LedNotifications::BootBlink(led);

    ledStrip.Setup<LED_TYPE, LED_PIN, COLOR_ORDER>();

    LoadPreferences();

    ledStrip.SetPalette(palettes[paletteIndex]);
    ledStrip.SetBrightness(defaultBrightness);
}


void IRInputProcessing()
{
    // IR Input
    if (irInput.irrecv.decode())
    {
        uint16_t cmd = irInput.GetCommand();

        // Serial.println(cmd);

        uint8_t brDelta = 20;

        bool cmdRecognized = true;

        if (cmd == IRInput::butUp)
        {
            ledStrip.ChangeBrightness(+brDelta);

            Serial.print("Brightness set to:");
            Serial.println(ledStrip.GetBrightness());

            preferences.putInt(stripBrightnessKey, ledStrip.GetBrightness());
        }
        else if (cmd == IRInput::butDown)
        {
            ledStrip.ChangeBrightness(-brDelta);

            Serial.print("Brightness set to:");
            Serial.println(ledStrip.GetBrightness());

            preferences.putInt(stripBrightnessKey, ledStrip.GetBrightness());
        }
        else if (cmd == IRInput::butHash)
        {
            ledStrip.SetBrightness(ledStrip.brMax);

            Serial.print("Brightness set to:");
            Serial.println(ledStrip.GetBrightness());

            preferences.putInt(stripBrightnessKey, ledStrip.GetBrightness());
        }
        else if (cmd == IRInput::butStar)
        {
            ledStrip.SetBrightness(ledStrip.brMin);

            Serial.print("Brightness set to:");
            Serial.println(ledStrip.GetBrightness());

            preferences.putInt(stripBrightnessKey, ledStrip.GetBrightness());
        }
        else if (cmd == IRInput::butLeft)
        {
            if ((int32_t)paletteIndex - 1 < 0)
                paletteIndex = paletteIndexMax;
            else
                paletteIndex -= 1;
                
            ledStrip.SetPalette(palettes[paletteIndex]);

            Serial.print("Palette set to:");
            Serial.println(paletteIndex);

            preferences.putInt(paleteIndexKey, paletteIndex);
        }
        else if (cmd == IRInput::butRight)
        {
            if ((int32_t)paletteIndex + 1 > paletteIndexMax)
                paletteIndex = 0;
            else
                paletteIndex += 1;

            ledStrip.SetPalette(palettes[paletteIndex]);

            Serial.print("Palette set to:");
            Serial.println(paletteIndex);

            preferences.putInt(paleteIndexKey, paletteIndex);
        }
        else if (IRInput::SwitchButton(cmd) != -1)
        {
            int but = IRInput::SwitchButton(cmd);
            if (but <= paletteIndexMax)
            {
                paletteIndex = but;
                ledStrip.SetPalette(palettes[paletteIndex]);
            }

            Serial.print("Palette set to:");
            Serial.println(paletteIndex);

            preferences.putInt(paleteIndexKey, paletteIndex);
        }
        else
        {
            cmdRecognized = false;
        }

        if (cmdRecognized)
            LedNotifications::InstructionAcceptedBlink(led);
        else
            delay(50);

        irInput.Resume();
    }
}

void loop()
{
    ledStrip.Loop();

    IRInputProcessing();
}
