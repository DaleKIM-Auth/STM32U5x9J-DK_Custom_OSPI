/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#ifndef TOUCHGFX_GENERATEDFONT_HPP
#define TOUCHGFX_GENERATEDFONT_HPP

#include <touchgfx/ConstFont.hpp>

namespace touchgfx
{
class GeneratedFont : public ConstFont
{
public:
    GeneratedFont(const GlyphNode* glyphs, uint16_t numGlyphs, uint16_t height, uint16_t baseline, uint8_t pixAboveTop, uint8_t pixBelowBottom, uint8_t bitsPerPixel, uint8_t byteAlignRow, uint8_t maxLeft, uint8_t maxRight, const uint8_t* const* glyphDataInternalFlash, const KerningNode* kerningList, const Unicode::UnicodeChar fallbackChar, const Unicode::UnicodeChar ellipsisChar, const uint16_t* const gsubData, const FontContextualFormsTable* formsTable);

    using ConstFont::getGlyph;

    virtual const uint8_t* getPixelData(const GlyphNode* glyph) const;

    virtual int8_t getKerning(Unicode::UnicodeChar prevChar, const GlyphNode* glyph) const;

    virtual const uint16_t* getGSUBTable() const
    {
        return gsubTable;
    }

    virtual const FontContextualFormsTable* getContextualFormsTable() const
    {
        return arabicTable;
    }

protected:
    GeneratedFont()
        : ConstFont(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), glyphData(0), kerningData(0), gsubTable(0), arabicTable(0)
    {
    }

    const void* glyphData;          ///< The glyphs
    const KerningNode* kerningData; ///< The kerning
    const uint16_t* gsubTable;      ///< The GSUB tables

    const FontContextualFormsTable* arabicTable; ///< Contextual forms
};

class FusedFont : public GeneratedFont
{
public:
    FusedFont(const GlyphNode* glyphs, uint16_t numGlyphs, uint16_t height, uint16_t baseline, uint8_t pixAboveTop, uint8_t pixBelowBottom, uint8_t bitsPerPixel, uint8_t byteAlignRow, uint8_t maxLeft, uint8_t maxRight, const uint8_t* const* glyphDataInternalFlash, const KerningNode* kerningList, const Unicode::UnicodeChar fallbackChar, const Unicode::UnicodeChar ellipsisChar, const uint16_t* const gsubData, const FontContextualFormsTable* formsTable)
        : GeneratedFont(glyphs, numGlyphs, height, baseline, pixAboveTop, pixBelowBottom, bitsPerPixel, byteAlignRow,
                        maxLeft, maxRight, glyphDataInternalFlash, kerningList, fallbackChar, ellipsisChar,
                        gsubData, formsTable)
    { }

virtual const GlyphNode* getGlyph(Unicode::UnicodeChar unicode, const uint8_t*& pixelData, uint8_t& bitsPerPixel) const;
};

struct BinaryFontData
{
    uint32_t fontIndex;                // The font index (as used by TypedTextDatabase)
    uint32_t sizeOfFontData;           // Size of the complete BinaryFont
    uint32_t offsetToTable;            // GlyphNode[]
    uint32_t offsetToKerning;          // KerningNode[]
    uint32_t offsetToGlyphs;           // uint8_t[]
    uint32_t offsetToGSUB;             // uint16_t[]
    uint32_t offsetToArabicTable;      // FontContextualFormsTable
    uint16_t numberOfGlyphs;           // Number of glyphs in Table and Glyphs
    uint16_t fontHeight;               // Font height
    uint16_t baseline;                 // Distance to baseline
    uint8_t pixAboveTop;               // Max pixels above top
    uint8_t pixBelowBottom;            // Max pixels below bottom
    uint8_t bitsPerPixel;              // Bpp
    uint8_t byteAlignRow;              // A4/A2/A1
    uint8_t maxLeft;                   // The maximum a glyph extends to the left
    uint8_t maxRight;                  // The maximum a glyph extends to the right
    Unicode::UnicodeChar fallbackChar; // Fallback Character for the font
    Unicode::UnicodeChar ellipsisChar; // Ellipsis Character for the font
};

class BinaryFont : public GeneratedFont
{
public:
    BinaryFont(const struct touchgfx::BinaryFontData* data)
        : GeneratedFont((const GlyphNode*)((const uint8_t*)data + data->offsetToTable),
                        data->numberOfGlyphs,
                        data->fontHeight,
                        data->baseline,
                        data->pixAboveTop,
                        data->pixBelowBottom,
                        data->bitsPerPixel,
                        data->byteAlignRow,
                        data->maxLeft,
                        data->maxRight,
                        0,
                        (const KerningNode*)((const uint8_t*)data + data->offsetToKerning),
                        data->fallbackChar,
                        data->ellipsisChar,
                        (data->offsetToGSUB == 0) ? 0 : (const uint16_t*)((const uint8_t*)data + data->offsetToGSUB),
                        0),
          glyphData((const uint8_t*)data + data->offsetToGlyphs)
    {
        if (data->offsetToArabicTable > 0)
        {
            setupContextualTable(data);
        }
    }

    BinaryFont()
        : GeneratedFont()
    {
    }

    virtual const uint8_t* getPixelData(const GlyphNode* glyph) const
    {
        const uint8_t* data = (const uint8_t*)glyphData;
        return &(data[glyph->dataOffset]);
    }

protected:
    const uint8_t* glyphData;
    FontContextualFormsTable contextualForms;

private:
    typedef const Unicode::UnicodeChar (*array5ptr)[5];
    typedef const Unicode::UnicodeChar (*array4ptr)[4];
    void setupContextualTable(const struct touchgfx::BinaryFontData* data)
    {
        const uint16_t* const base = (const uint16_t*)(((const uint8_t*)data) + data->offsetToArabicTable);
        // First elements in binary font are offsets to arrays in 16bit words
        contextualForms.contextualForms4Long = (array5ptr)(base + base[0]);
        contextualForms.contextualForms3Long = (array5ptr)(base + base[1]);
        contextualForms.contextualForms2Long = (array5ptr)(base + base[2]);
        contextualForms.contextualForms0621_063a = (array4ptr)(base + base[3]);
        contextualForms.contextualForms0641_064a = (array4ptr)(base + base[4]);
        contextualForms.contextualForms06XX = (array5ptr)(base + base[5]);
        contextualForms.contextualForms4LongSize = base[6];
        contextualForms.contextualForms3LongSize = base[7];
        contextualForms.contextualForms2LongSize = base[8];
        contextualForms.contextualForms06XXSize = base[9];
        arabicTable = &contextualForms;
    }
};
} // namespace touchgfx

#endif // TOUCHGFX_GENERATEDFONT_HPP
