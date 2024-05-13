// #include <Arduino.h>
// #include <FastLED.h>
// #include "StringExtension.h"

// class Input{
//     static CRGB *GetColors(String stringHexValues, uint8_t &colorsCount)
// {
//     uint8_t substringsCount;
//     String *stringColors = StringExtension::SplitString(stringHexValues, ' ', &substringsCount);
//     CRGB *colors = new CRGB[substringsCount];
//     for (uint8_t i = 0; i < substringsCount; i++)
//     {
//         String colorText = GetParam(stringColors[i], "#");
//         Serial.println(colorText);
//         colors[i] = GetColor(colorText);
//     }
//     colorsCount = substringsCount;

//     return colors;
// }

// CRGB GetColor(String colorString, bool &colorFound)
// {
//     CRGB c;
//     colorFound = true;
//     if (colorString == "White")
//         c = CRGB::White;
//     else if (colorString == "Red")
//         c = CRGB::Red;
//     else if (colorString == "Yellow")
//         c = CRGB::Yellow;
//     else if (colorString == "Green")
//         c = CRGB::Green;
//     else if (colorString == "GreenYellow")
//         c = CRGB::GreenYellow;
//     else if (colorString == "Purple")
//         c = CRGB::Purple;
//     else if (colorString == "Blue")
//         c = CRGB::Blue;
//     else if (colorString == "BlueViolet")
//         c = CRGB::BlueViolet;
//     else if (colorString == "Cyan")
//         c = CRGB::Cyan;
//     else if (colorString == "DeepPink")
//         c = CRGB::DeepPink;
//     else if (colorString == "Pink")
//         c = CRGB::Pink;
//     else if (colorString == "Gold")
//         c = CRGB::Gold;
//     else if (colorString == "MintCream")
//         c = CRGB::MintCream;
//     else if (colorString == "MistyRose")
//         c = CRGB::MistyRose;
//     else if (colorString == "Olive")
//         c = CRGB::Olive;
//     else
//     {
//         colorFound = false;
//     }

//     return c;
// }

// void Command(String cmd)
// {
//     String fanCmd = "br ";
//     String colorCmd = "color ";
//     String closeCmd = "close ";
//     String blendCmd = "blend ";
//     String colorsCmd = "colors ";

//     // BRIGHTNESS
//     if (cmd.startsWith(fanCmd))
//     {
//         brightness = GetOneIntValue(cmd, fanCmd);
//         FastLED.setBrightness(brightness);
//     }
//     // COLOR
//     else if (cmd.startsWith(colorCmd))
//     {
//         String param = GetParam(cmd, colorCmd);

//         if (param == "rain")
//         {
//             currentPalette = *CreatePallete(rain, sizeof(rain) / sizeof(rain[0]));
//         }
//         else if (param == "blpl")
//         {
//             currentPalette = *CreatePallete(bluepuple, sizeof(bluepuple) / sizeof(bluepuple[0]));
//         }
//         else if (param == "cypi")
//         {
//             currentPalette = *CreatePallete(cyanpink, sizeof(cyanpink) / sizeof(cyanpink[0]));
//         }
//         else if (param == "grnylw")
//         {
//             currentPalette = *CreatePallete(greenYellow, sizeof(greenYellow) / sizeof(greenYellow[0]));
//         }
//         else if (param == "rdylw")
//         {
//             currentPalette = *CreatePallete(redYellow, sizeof(redYellow) / sizeof(redYellow[0]));
//         }
//         else if (param == "ywpi")
//         {
//             currentPalette = *CreatePallete(yellowpink, sizeof(yellowpink) / sizeof(yellowpink[0]));
//         }
//         else if (param == "blpi")
//         {
//             currentPalette = *CreatePallete(bluepink, sizeof(bluepink) / sizeof(bluepink[0]));
//         }
//         else if (param == "redw")
//         {
//             currentPalette = *CreatePallete(redWhite, sizeof(redWhite) / sizeof(redWhite[0]));
//         }
//         else if (param == "grpi")
//         {
//             currentPalette = *CreatePallete(greenwpink, sizeof(greenwpink) / sizeof(greenwpink[0]));
//         }
//         else
//         {
//             bool colorFound;

//             CRGB c = GetColor(param, colorFound);

//             if (colorFound)
//             {
//                 currentPalette = *CreatePallete(c);
//             }
//             else
//             {
//                 String hash = "#";
//                 if (param.startsWith(hash))
//                 {
//                     currentPalette = *CreatePallete(GetColor(GetParam(param, hash)));
//                 }
//             }
//         }
//     }
//     // COLORS
//     else if (cmd.startsWith(colorsCmd))
//     {
//         String param = GetParam(cmd, colorsCmd);

//         uint8_t countColors;
//         CRGB *colors = GetColors(param, countColors);

//         currentPalette = *CreatePallete(colors, countColors);
//     }
//     // BLEND
//     else if (cmd.startsWith(blendCmd))
//     {
//         String param = GetParam(cmd, blendCmd);

//         if (param == "y")
//         {
//             currentBlending = LINEARBLEND;
//         }
//         else if (param == "n")
//         {
//             currentBlending = NOBLEND;
//         }
//     }
//     else
//     {
//         Serial.println("Unknown command");
//         return;
//     }
//     led.Blink(2, 100);
// }

// }