// // There are several different palettes of colors demonstrated here.
// //
// // FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// // OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
// //
// // Additionally, you can manually define your own color palettes, or you can write
// // code that creates color palettes on the fly.  All are shown here.

// // This function fills the palette with totally random colors.
// void SetupTotallyRandomPalette()
// {
//     for (int i = 0; i < 16; ++i)
//     {
//         currentPalette[i] = CHSV(random8(), 255, random8());
//     }
// }

// // This function sets up a palette of black and white stripes,
// // using code.  Since the palette is effectively an array of
// // sixteen CRGB colors, the various fill_* functions can be used
// // to set them up.
// void SetupBlackAndWhiteStripedPalette()
// {
//     // 'black out' all 16 palette entries...
//     fill_solid(currentPalette, 16, CRGB::Black);
//     // and set every fourth one to white.
//     currentPalette[0] = CRGB::White;
//     currentPalette[4] = CRGB::White;
//     currentPalette[8] = CRGB::White;
//     currentPalette[12] = CRGB::White;
// }

// // This function sets up a palette of purple and green stripes.
// void SetupPurpleAndGreenPalette()
// {
//     CRGB purple = CHSV(HUE_PURPLE, 255, 255);
//     CRGB green = CHSV(HUE_GREEN, 255, 255);
//     CRGB black = CRGB::Black;

//     currentPalette = CRGBPalette16(
//         green, green, black, black,
//         purple, purple, black, black,
//         green, green, black, black,
//         purple, purple, black, black);
// }

// // This example shows how to set up a static color palette
// // which is stored in PROGMEM (flash), which is almost always more
// // plentiful than RAM.  A static PROGMEM palette like this
// // takes up 64 bytes of flash.
// const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM = {
//     CRGB::Red,
//     CRGB::Gray, // 'white' is too bright compared to red and blue
//     CRGB::Blue,
//     CRGB::Black,

//     CRGB::Red,
//     CRGB::Gray,
//     CRGB::Blue,
//     CRGB::Black,

//     CRGB::Red,
//     CRGB::Red,
//     CRGB::Gray,
//     CRGB::Gray,
//     CRGB::Blue,
//     CRGB::Blue,
//     CRGB::Black,
//     CRGB::Black};

// void ChangePalettePeriodically()
// {
//     uint8_t secondHand = (millis() / 1000) % 60;
//     static uint8_t lastSecond = 99;

//     if (lastSecond != secondHand)
//     {
//         lastSecond = secondHand;
//         if (secondHand == 0)
//         {
//             currentPalette = RainbowColors_p;
//             currentBlending = LINEARBLEND;
//         }
//         // if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
//         if (secondHand == 15)
//         {
//             currentPalette = RainbowStripeColors_p;
//             currentBlending = LINEARBLEND;
//         }
//         if (secondHand == 20)
//         {
//             SetupPurpleAndGreenPalette();
//             currentBlending = LINEARBLEND;
//         }
//         if (secondHand == 25)
//         {
//             SetupTotallyRandomPalette();
//             currentBlending = LINEARBLEND;
//         }
//         // if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
//         if (secondHand == 35)
//         {
//             SetupBlackAndWhiteStripedPalette();
//             currentBlending = LINEARBLEND;
//         }
//         if (secondHand == 40)
//         {
//             currentPalette = CloudColors_p;
//             currentBlending = LINEARBLEND;
//         }
//         if (secondHand == 45)
//         {
//             currentPalette = PartyColors_p;
//             currentBlending = LINEARBLEND;
//         }
//         // if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
//         if (secondHand == 55)
//         {
//             currentPalette = myRedWhiteBluePalette_p;
//             currentBlending = LINEARBLEND;
//         }
//     }
// }
