#ifndef SOME_HEADER_H1
#define SOME_HEADER_H1
#include <FastLED.h>
#include "Palletes.h"

CRGB red[] = {CRGB::Red};
CRGB redYellow[] = {CRGB::Red, CRGB::Yellow};
CRGB bluepuple[] = {CRGB::Blue, CRGB::Purple};
CRGB cyanpink[] = {CRGB::Cyan, CRGB::DeepPink};
CRGB redWhite[] = {CRGB::Red, 0xff3131, CRGB::Red};
CRGB bluepink[] = {CRGB::Blue, CRGB::DeepPink};
CRGB yellowpink[] = {CRGB::Yellow, CRGB::DeepPink};
CRGB greenwpink[] = {CRGB::LimeGreen, CRGB::DeepPink};
CRGB greenYellow[] = {CRGB::Green, CRGB::Gold};
CRGB rain[] = {CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::Green, CRGB::Cyan, CRGB::Blue, CRGB::Purple};

CRGBPalette16* palettes[] = {
    Palletes::CreatePallete(red, 1),
    Palletes::CreatePallete(redYellow, 2),
    Palletes::CreatePallete(bluepuple, 2),
    Palletes::CreatePallete(cyanpink, 2),
    Palletes::CreatePallete(redWhite, 2),
    Palletes::CreatePallete(bluepink, 2),
    Palletes::CreatePallete(yellowpink, 2),
    Palletes::CreatePallete(greenwpink, 2),
    Palletes::CreatePallete(greenYellow, 2),
    Palletes::CreatePallete(rain, 7)};

#endif
