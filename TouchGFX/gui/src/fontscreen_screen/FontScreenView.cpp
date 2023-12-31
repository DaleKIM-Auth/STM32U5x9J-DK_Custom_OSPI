#include <gui/fontscreen_screen/FontScreenView.hpp>
#include <touchgfx/Utils.hpp>

#include <BitmapDatabase.hpp>

extern "C"
{
    void fpga_demo_draw_font_scale(uint16_t *const fb, const int32_t x, const int32_t y, const uint32_t w, const uint32_t h, const float scale, const int offset, bool state);
    void fpga_demo_setup_font();
    void fpga_demo_release_font();
}

static const uint16_t koreanTextTempAsUnicode16[] = {
    0xC0BC, 0xC131, 0x0020, 0xC0DD, 0xD65C, 0x0020, 0xAC00, 0xC804, 0x0}; // 삼성 생활 가전
static uint8_t koreanTextTempAsUTF8[256] = {0};

FontScreenView::FontScreenView() : tickCounter(0),
                                   textUpdated(0),
                                   fontSize(0),
                                   vectorFontRefreshZone_X(VectorFont_Container.getX()),
                                   vectorFontRefreshZone_Y(VectorFont_Container.getY()),
                                   vectorFontRefreshZone_Width(VectorFont_Container.getWidth()),
                                   vectorFontRefreshZone_Height(VectorFont_Container.getHeight()),
                                   offset(0),
                                   increaseFontSize(true),
                                   state(false),
                                   scale(1.0f),
                                   clicked(0)
{
}

void FontScreenView::setupScreen()
{
    FontScreenViewBase::setupScreen();

    fpga_demo_setup_font();
}

void FontScreenView::tearDownScreen()
{
    FontScreenViewBase::tearDownScreen();

    fpga_demo_release_font();
}

void FontScreenView::draw(Rect &rect)
{
    FontScreenViewBase::draw(rect);

    /* draw nema here, using rect as clipping */
    touchgfx::HAL *const hal = HAL::getInstance();
    uint16_t *fb = hal->lockFrameBuffer();

    fpga_demo_draw_font_scale(fb, vectorFontRefreshZone_X, vectorFontRefreshZone_Y,
                              vectorFontRefreshZone_Width, vectorFontRefreshZone_Height, scale, offset, state);
    hal->unlockFrameBuffer();
}

void FontScreenView::handleTickEvent()
{
    tickCounter++;
    if (tickCounter % 200 == 0)
    {
        textUpdated++;
    }

    switch (textUpdated)
    {
    case 1:
        memset(FusionFontBuffer, 0x0, FUSIONFONT_SIZE);
        FusionFont.invalidate();
        Unicode::fromUTF8((uint8_t *)"에스티마이크로일렉트로닉스", FusionFontBuffer, FUSIONFONT_SIZE);
        break;
    case 2:
        memset(FusionFontBuffer, 0x0, FUSIONFONT_SIZE);
        FusionFont.invalidate();
        Unicode::fromUTF8((uint8_t *)"삼성 생활 가전", FusionFontBuffer, FUSIONFONT_SIZE);
        break;
    case 3:
        memset(FusionFontBuffer, 0x0, FUSIONFONT_SIZE);
        FusionFont.invalidate();
        Unicode::fromUTF8((uint8_t *)"한글 조합형 폰트 출력 데모", FusionFontBuffer, FUSIONFONT_SIZE);
        break;
    default:
        textUpdated = 0;
        break;
    }

    FusionFont.resizeToCurrentText();
    FusionFont.invalidate();
}

void FontScreenView::FusionFontTextUpdate()
{
    char temp_str[] = "에스티마이크로일렉트로닉스";
    Unicode::fromUTF8((uint8_t *)temp_str, FusionFontBuffer, FUSIONFONT_SIZE);

    FusionFont.resizeToCurrentText();
    FusionFont.invalidate();
}

void FontScreenView::ChangeVectorFontState()
{
    VectorFont_Container.invalidateContent();

    if (increaseFontSize && (fontSize != 2))
    {
        fontSize++;
    }
    else if (!increaseFontSize && (fontSize == 0))
    {
        application().gotoMainScreenScreenSlideTransitionEast();
    }
    else
    {
        increaseFontSize = false;
        fontSize--;
    }

    switch (fontSize)
    {
    case 0:        
        scale = 1.0f;
        offset = 0;
        break;
    case 1:
        state = !state;
        scale = 1.5f;
        offset = 56;
        break;
    case 2:
        scale = 2.0f;
        offset = 84;
        break;
    default:
        break;
    }
    Rect r(vectorFontRefreshZone_X, vectorFontRefreshZone_Y, vectorFontRefreshZone_Width, vectorFontRefreshZone_Height);
    invalidate();

    VectorFont_Container.invalidateContent();    
}