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
#include "CommandInput.h"
#include "LedStripMemory.h"

int serialExchangeSpeed = 115200; // bits per second

// IR control pin
const int irPin = 3;

#define LED_PIN 2
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

// Objects
LED led = LED(8, true);
IRInput irInput(irPin);

// LED Strip
uint16_t ledsNumber = 90;
uint8_t brDelta = 20;
uint8_t *brightness = new uint8_t(255);
uint8_t *paletteIndex = new uint8_t(5);
uint8_t paletteIndexMax = sizeof(palettes) / sizeof(palettes[0]) - 1;
uint8_t paletteIndexMin = 0;

LedStrip *ledStrip = new LedStrip(ledsNumber);
LedStripMemory ledMemory = LedStripMemory(paletteIndex, brightness, ledStrip);

CommandInput<uint16_t> commandInput;

/// Setup IR Remote commands
void SetupCommands()
{
    // setup commands
    commandInput.AddCommand(IRInput::butUp, []()
                            { ledStrip->ChangeBrightness(+brDelta); });

    commandInput.AddCommand(IRInput::butDown, []()
                            { ledStrip->ChangeBrightness(-brDelta); });

    commandInput.AddCommand(IRInput::butHash, []()
                            { ledStrip->SetBrightness(ledStrip->brMax); });

    commandInput.AddCommand(IRInput::butStar, []()
                            { ledStrip->SetBrightness(ledStrip->brMin); });

    commandInput.AddCommand(IRInput::butLeft, []()
                            {
                                if ((int32_t)*paletteIndex - 1 < paletteIndexMin)
                                    *paletteIndex = paletteIndexMax;
                                else
                                {
                                    uint8_t newindex = *paletteIndex - 1;
                                    *paletteIndex = newindex;
                                }

                                ledStrip->SetPalette(palettes[*paletteIndex]); });

    commandInput.AddCommand(IRInput::butRight, []()
                            {
                                 if ((int32_t)*paletteIndex + 1 > paletteIndexMax)
                                    *paletteIndex = paletteIndexMin;
                                else
                                {
                                    uint8_t newindex = *paletteIndex + 1;
                                    *paletteIndex = newindex;
                                }

                                ledStrip->SetPalette(palettes[*paletteIndex]); });
}

void setup()
{
    Serial.begin(serialExchangeSpeed);
    // while (!Serial)
    //      ;

    led.Setup();
    irInput.Setup();

    LedNotifications::BootBlink(led);

    ledStrip->Setup<LED_TYPE, LED_PIN, COLOR_ORDER>();
    ledMemory.Setup();

    ledStrip->SetPalette(palettes[*paletteIndex]);
    ledStrip->SetBrightness(*brightness);

    SetupCommands();
}

void IRInputProcessing()
{
    // IR Input
    if (irInput.irrecv.decode())
    {
        uint16_t cmd = irInput.GetCommand();

        bool cmdRecognized = commandInput.ProcessInputLoop(cmd);

        // Switch button
        if (!cmdRecognized && IRInput::SwitchButton(cmd) != -1)
        {
            int but = IRInput::SwitchButton(cmd);
            if (but <= paletteIndexMax)
            {
                *paletteIndex = but;
                ledStrip->SetPalette(palettes[*paletteIndex]);

                cmdRecognized = true;
            }
        }

        if (cmdRecognized)
            LedNotifications::InstructionAcceptedBlink(led);
        else
            delay(50);

        irInput.Resume();
    }
}

void IRInputProcessingOld()
{
    // IR Input
    if (irInput.irrecv.decode())
    {
        uint16_t cmd = irInput.GetCommand();

        // Serial.println(cmd);

        // uint8_t brDelta = 20;

        bool cmdRecognized = commandInput.ProcessInputLoop(cmd);

        // bool cmdRecognized = true;

        // if (cmd == IRInput::butUp)
        // {
        //     ledStrip.ChangeBrightness(+brDelta);

        //     Serial.print("Brightness set to:");
        //     Serial.println(ledStrip.GetBrightness());

        //     preferences.putInt(stripBrightnessKey, ledStrip.GetBrightness());
        // }
        // else if (cmd == IRInput::butDown)
        // {
        //     ledStrip.ChangeBrightness(-brDelta);

        //     Serial.print("Brightness set to:");
        //     Serial.println(ledStrip.GetBrightness());

        //     preferences.putInt(stripBrightnessKey, ledStrip.GetBrightness());
        // }
        // else if (cmd == IRInput::butHash)
        // {
        //     ledStrip.SetBrightness(ledStrip.brMax);

        //     Serial.print("Brightness set to:");
        //     Serial.println(ledStrip.GetBrightness());

        //     preferences.putInt(stripBrightnessKey, ledStrip.GetBrightness());
        // }
        // else if (cmd == IRInput::butStar)
        // {
        //     ledStrip.SetBrightness(ledStrip.brMin);

        //     Serial.print("Brightness set to:");
        //     Serial.println(ledStrip.GetBrightness());

        //     preferences.putInt(stripBrightnessKey, ledStrip.GetBrightness());
        // }
        // else if (cmd == IRInput::butLeft)
        // {
        //     if ((int32_t)paletteIndex - 1 < 0)
        //         paletteIndex = paletteIndexMax;
        //     else
        //         paletteIndex -= 1;

        //     ledStrip.SetPalette(palettes[paletteIndex]);

        //     Serial.print("Palette set to:");
        //     Serial.println(paletteIndex);

        //     preferences.putInt(paleteIndexKey, paletteIndex);
        // }
        // else if (cmd == IRInput::butRight)
        // {
        //     if ((int32_t)paletteIndex + 1 > paletteIndexMax)
        //         paletteIndex = 0;
        //     else
        //         paletteIndex += 1;

        //     ledStrip.SetPalette(palettes[paletteIndex]);

        //     Serial.print("Palette set to:");
        //     Serial.println(paletteIndex);

        //     preferences.putInt(paleteIndexKey, paletteIndex);
        // }
        // else if (IRInput::SwitchButton(cmd) != -1)
        // {
        //     int but = IRInput::SwitchButton(cmd);
        //     if (but <= paletteIndexMax)
        //     {
        //         paletteIndex = but;
        //         ledStrip.SetPalette(palettes[paletteIndex]);
        //     }

        //     Serial.print("Palette set to:");
        //     Serial.println(paletteIndex);

        //     preferences.putInt(paleteIndexKey, paletteIndex);
        // }
        // else
        // {
        //     cmdRecognized = false;
        // }

        if (cmdRecognized)
            LedNotifications::InstructionAcceptedBlink(led);
        else
            delay(50);

        irInput.Resume();
    }
}

void loop()
{
    ledStrip->Loop();

    IRInputProcessing();
}
