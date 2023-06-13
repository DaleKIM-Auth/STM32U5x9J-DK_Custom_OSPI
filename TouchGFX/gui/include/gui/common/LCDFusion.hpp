#ifndef LCD16BPPFUSION_HPP
#define LCD16BPPFUSION_HPP

#include <touchgfx_nema/LCDGPU2D.hpp>
using namespace touchgfx;

class LCDFusion : public LCDGPU2D
{
    void drawGlyph(uint16_t* wbuf16, Rect widgetArea, int16_t x, int16_t y, uint16_t offsetX, uint16_t offsetY, const Rect& invalidatedArea, const GlyphNode* glyph, const uint8_t* glyphData, uint8_t byteAlignRow, colortype color, uint8_t bitsPerPixel, uint8_t alpha, TextRotation rotation);
};

#endif
