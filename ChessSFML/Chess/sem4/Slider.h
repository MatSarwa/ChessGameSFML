/**
 * @file Slider.h
 * @brief Class for a customizable UI slider component
 * @author Mateusz Sarwa
 * @date 2024-04-07
 */

#pragma once
#include <SFML/Graphics.hpp>

 /**
  * @class Slider
  * @brief A graphical slider component for selecting numeric values
  *
  * This class implements a slider UI element that allows users to select
  * a value from a specified range by dragging a handle along a track.
  */
class Slider {
private:
    /**
     * @brief The track part of the slider
     */
    sf::RectangleShape track;

    /**
     * @brief The draggable handle of the slider
     */
    sf::RectangleShape handle;

    /**
     * @brief Minimum value of the slider range
     */
    int minValue;

    /**
     * @brief Maximum value of the slider range
     */
    int maxValue;

    /**
     * @brief Current value of the slider
     */
    int currentValue;

    /**
     * @brief Flag indicating if the slider is currently being dragged
     */
    bool isDragged;

public:
    /**
     * @brief Constructor
     * @param x X position of the slider
     * @param y Y position of the slider
     * @param width Width of the slider track
     * @param height Height of the slider track
     * @param min Minimum value of the slider range
     * @param max Maximum value of the slider range
     */
    Slider(float x, float y, float width, float height, int min, int max);

    /**
     * @brief Renders the slider to the window
     * @param window Window in which to render the slider
     */
    void render(sf::RenderWindow& window);

    /**
     * @brief Updates the slider state based on mouse position
     * @param mousePos Current mouse position
     *
     * This should be called each frame to update the slider position when dragging.
     */
    void update(sf::Vector2i mousePos);

    /**
     * @brief Checks if the slider handle was clicked
     * @param mousePos Mouse click position
     * @return true if the handle was clicked, false otherwise
     */
    bool isClicked(sf::Vector2i mousePos);

    /**
     * @brief Updates the slider value based on mouse position
     * @param mousePos Current mouse position
     * @return The new slider value
     *
     * This method updates the slider's current value based on the mouse
     * position along the track.
     */
    int updateValue(sf::Vector2i mousePos);

    /**
     * @brief Gets the current value of the slider
     * @return Current slider value
     */
    int getValue() const;

    /**
     * @brief Checks if the slider is currently being dragged
     * @return true if the slider is being dragged, false otherwise
     */
    bool isDragging() const;

    /**
     * @brief Stops the dragging of the slider
     *
     * This method should be called when the mouse button is released.
     */
    void stopDragging();

    /**
     * @brief Starts the dragging of the slider
     *
     * This method should be called when the mouse button is pressed on the handle.
     */
    void startDragging() { isDragged = true; }
};