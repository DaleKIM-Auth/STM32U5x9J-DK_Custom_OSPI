#ifndef FONTSCREENVIEW_HPP
#define FONTSCREENVIEW_HPP

#include <gui_generated/fontscreen_screen/FontScreenViewBase.hpp>
#include <gui/fontscreen_screen/FontScreenPresenter.hpp>

class FontScreenView : public FontScreenViewBase
{
public:
    FontScreenView();
    virtual ~FontScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // Vector font
    virtual void draw(Rect &rect);

    virtual void handleTickEvent();

    virtual void FusionFontTextUpdate();
    virtual void ChangeVectorFontState();

protected:
    uint32_t tickCounter;
    uint16_t textUpdated;

    int16_t fontSize, vectorFontRefreshZone_X, vectorFontRefreshZone_Y, vectorFontRefreshZone_Width, vectorFontRefreshZone_Height, offset;
    bool increaseFontSize, state;
    float scale;
    int16_t clicked;
};

#endif // FONTSCREENVIEW_HPP
