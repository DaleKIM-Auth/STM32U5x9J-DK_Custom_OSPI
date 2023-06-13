#ifndef FONTSCREENPRESENTER_HPP
#define FONTSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class FontScreenView;

class FontScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    FontScreenPresenter(FontScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~FontScreenPresenter() {};

private:
    FontScreenPresenter();

    FontScreenView& view;
};

#endif // FONTSCREENPRESENTER_HPP
