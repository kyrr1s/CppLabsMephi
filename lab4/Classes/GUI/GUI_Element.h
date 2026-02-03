#pragma once

#include <functional>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

//sf::Transformable allows us to manipulate the position of an element on the window

class GUI_Element : public sf::Transformable {

    using ClickHandler = std::function<void()>;
    using HoverHandler = std::function<void()>;

    /// Function, that provides click processing.
    GUI_Element::ClickHandler click_handler;

    // Hover triggered when the user hovers over an element with the mouse, but does not necessarily click on it
    /// Function, that provides hover processing.
    GUI_Element::HoverHandler hover_handler;

    /// 2-dimensional vector, associated with GUI element.
    sf::Vector2f vector;

public:

    using Ptr = std::shared_ptr<GUI_Element>;

    /// Sets element's vector. Default value is {0,0}. These values are width and height of an element's rectangle.
    explicit GUI_Element(sf::Vector2f vector = {0, 0});

    /// Sets a function for click processing.
    void setClickHandler(const ClickHandler &handler);

    /// Sets a function for hover processing.
    void setHoverHandler(const HoverHandler &handler);

    /// Triggers the click handler function.
    virtual void click();

    /// Triggers the hover handler function.
    virtual void hover();

    /// Gets width of an element.
    float getWidth() const;

    /// Gets height of an element.
    float getHeight() const;

    /// Sets width of an element.
    virtual void setWidth(float width);

    /// Sets height of an element.
    virtual void setHeight(float height);
};