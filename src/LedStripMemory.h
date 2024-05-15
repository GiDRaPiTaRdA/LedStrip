#pragma once

#include <Preferences.h>
#include "LedStrip.h"

class LedStripMemory
{
private:
    // Preferences
    const char *preferencesAppName = "led-strip";
    const char *paleteIndexKey = "paleteIndex";
    const char *stripBrightnessKey = "stripBrightness";

    Preferences preferences;
    uint8_t *paletteIndex;
    uint8_t *brightness;
    LedStrip *ledStrip;

public:
    LedStripMemory(uint8_t *paletteIndex, uint8_t *brightness, LedStrip* ledStrip)
    {
        this->paletteIndex = paletteIndex;
        this->brightness = brightness;
        this->ledStrip =  ledStrip;
    }

    void Setup()
    {
        LoadPreferences();
        SubscribeLedStripEvents();
    }

    void LoadPreferences()
    {
        preferences.begin(preferencesAppName, false); // false: read-only

        
             Serial.println("Load preferences");

        if (preferences.isKey(paleteIndexKey))
        {
            auto i = preferences.getUChar(paleteIndexKey);
            *paletteIndex = i;

             Serial.println("Loaded Index "+i);
        }

        if (preferences.isKey(stripBrightnessKey))
        {
            auto br = preferences.getUChar(stripBrightnessKey);
            *brightness = br;

             Serial.println("Loaded Brightness "+br);
        }
    }

    void SubscribeLedStripEvents()
    {
        ledStrip->brightnessChanged.Subscribe([this]()
                                             { 
                                                // auto s = preferences.getUChar(stripBrightnessKey);
                                                preferences.putUChar(stripBrightnessKey, ledStrip->GetBrightness());
                                                // Serial.println(" Get Brightness");
                                                // Serial.println(s);
                                                 });

        ledStrip->palleteChanged.Subscribe([this]()
                                          {                                             preferences.putUChar(paleteIndexKey, *paletteIndex);
                                          });
    }
};