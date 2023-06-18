/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FONTSCREENVIEWBASE_HPP
#define FONTSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/fontscreen_screen/FontScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/Container.hpp>

class FontScreenViewBase : public touchgfx::View<FontScreenPresenter>
{
public:
    FontScreenViewBase();
    virtual ~FontScreenViewBase();
    virtual void setupScreen();
    virtual void handleKeyEvent(uint8_t key);

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box BackGround_FS;
    touchgfx::TextArea TextKoreanFusion;
    touchgfx::TextArea TextVectorFont;
    touchgfx::TextAreaWithOneWildcard FusionFont;
    touchgfx::Container VectorFont_Container;

    /*
     * Wildcard Buffers
     */
    static const uint16_t FUSIONFONT_SIZE = 50;
    touchgfx::Unicode::UnicodeChar FusionFontBuffer[FUSIONFONT_SIZE];

private:

};

#endif // FONTSCREENVIEWBASE_HPP
