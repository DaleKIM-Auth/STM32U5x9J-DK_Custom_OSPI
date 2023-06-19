#include <gui/common/FrontendApplication.hpp>

#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

using namespace touchgfx;

FrontendApplication::FrontendApplication(Model &m, FrontendHeap &heap)
    : FrontendApplicationBase(m, heap),
      transitionCallback(),
      frontendHeap(heap),
      model(m)
{
}

void FrontendApplication::gotoMainScreenScreenSlideTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoMainScreenScreenSlideTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenScreenSlideTransitionEastImpl()
{
    touchgfx::makeTransition<MainScreenView, MainScreenPresenter, touchgfx::SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
