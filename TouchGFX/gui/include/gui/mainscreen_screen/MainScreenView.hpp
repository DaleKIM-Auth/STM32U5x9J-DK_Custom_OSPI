#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

class MainScreenView : public MainScreenViewBase
{
public:
    MainScreenView();
    virtual ~MainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    void updateMCU(uint16_t mcu);
    void updateFPS(uint16_t fps);
protected:
    uint16_t frameSkippedCounter;
    uint16_t frames;
    uint16_t fps;
    uint16_t previousMcuLoadPct;

    float xAngle3D;
    float yAngle3D;
    float zAngle3D;

    float deltaXangle3D;
    float deltaYangle3D;
    float deltaZangle3D;

    float zAngle2D;

    float deltaZangle2D;

};

#endif // MAINSCREENVIEW_HPP
