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

    virtual void handleTickEvent();

    virtual void FusionFontTextUpdate();
protected:
    uint32_t tickCounter;
    uint16_t textUpdated;
};

#endif // FONTSCREENVIEW_HPP
