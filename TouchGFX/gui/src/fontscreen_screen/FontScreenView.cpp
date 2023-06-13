#include <gui/fontscreen_screen/FontScreenView.hpp>
#include <touchgfx/Utils.hpp>

FontScreenView::FontScreenView() : tickCounter(0),
                                   textUpdated(0)
{
}

void FontScreenView::setupScreen()
{
    FontScreenViewBase::setupScreen();
}

void FontScreenView::tearDownScreen()
{
    FontScreenViewBase::tearDownScreen();
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