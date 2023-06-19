#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model &m, FrontendHeap &heap);
    virtual ~FrontendApplication() {}

    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }

    void gotoMainScreenScreenSlideTransitionEast();

private:
protected:
    touchgfx::Callback<FrontendApplication> transitionCallback;
    FrontendHeap &frontendHeap;
    Model &model;

    void gotoMainScreenScreenSlideTransitionEastImpl();
};

#endif // FRONTENDAPPLICATION_HPP
