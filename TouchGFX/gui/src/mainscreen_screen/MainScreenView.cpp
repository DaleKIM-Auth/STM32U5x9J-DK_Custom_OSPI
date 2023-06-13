#include <gui/mainscreen_screen/MainScreenView.hpp>

MainScreenView::MainScreenView()
{

}

void MainScreenView::setupScreen()
{
    MainScreenViewBase::setupScreen();
}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
}

void MainScreenView::handleTickEvent()
{
    /* MCU Load */
    uint16_t mcuLoadpct = touchgfx::HAL::getInstance()->getMCULoadPct();
    if(mcuLoadpct != previousMcuLoadPct)
    {
        previousMcuLoadPct = mcuLoadpct;
        updateMCU(previousMcuLoadPct);
    }
    /* FPS measurement */
    if(HAL::getInstance()->getLCDRefreshCount() > 1)
    {
        frameSkippedCounter++;
    }
    else
    {
        frames++;
    }

    if(frames + frameSkippedCounter > 60)
    {
        fps = frames;
        updateFPS(fps);
        frameSkippedCounter = 0;
        frames = 0;
    }
   
}

void MainScreenView::updateMCU(uint16_t mcu)
{

}

void MainScreenView::updateFPS(uint16_t fps)
{

}