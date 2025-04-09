/**
 * @file TimeInputField.h
 * @brief Class for a time input UI component
 * @author Mateusz Sarwa
 * @date 2024-04-07
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

 /**
  * @class TimeInputField
  * @brief A UI component for inputting time values (minutes and seconds)
  *
  * This class implements a time input field with increment/decrement controls
  * for both minutes and seconds. It supports mouse interaction and provides
  * callback functionality when values change.
  */
class TimeInputField {
private:
    /**
     * @brief Position of the input field on the screen
     */
    sf::Vector2f position;

    /**
     * @brief Size of the input field
     */
    sf::Vector2f size;

    /**
     * @brief Current minutes value
     */
    int minutes;

    /**
     * @brief Current seconds value
     */
    int seconds;

    /**
     * @brief Minimum allowed minutes value
     */
    int minMinutes;

    /**
     * @brief Maximum allowed minutes value
     */
    int maxMinutes;

    /**
     * @brief Minimum allowed seconds value
     */
    int minSeconds;

    /**
     * @brief Maximum allowed seconds value
     */
    int maxSeconds;

    /**
     * @brief Background shape for the entire input field
     */
    sf::RectangleShape background;

    /**
     * @brief Background box for the minutes value
     */
    sf::RectangleShape minutesBox;

    /**
     * @brief Background box for the seconds value
     */
    sf::RectangleShape secondsBox;

    /**
     * @brief Triangle shape for the minutes increment button
     */
    sf::ConvexShape minutesUpArrow;

    /**
     * @brief Triangle shape for the minutes decrement button
     */
    sf::ConvexShape minutesDownArrow;

    /**
     * @brief Triangle shape for the seconds increment button
     */
    sf::ConvexShape secondsUpArrow;

    /**
     * @brief Triangle shape for the seconds decrement button
     */
    sf::ConvexShape secondsDownArrow;

    /**
     * @brief Font used for text display
     */
    sf::Font font;

    /**
     * @brief Text object for displaying minutes
     */
    sf::Text minutesText;

    /**
     * @brief Text object for displaying seconds
     */
    sf::Text secondsText;

    /**
     * @brief Text object for displaying the separator between minutes and seconds
     */
    sf::Text separatorText;

    /**
     * @brief Text object for displaying the input field label
     */
    sf::Text labelText;

    /**
     * @brief Enum for tracking which part of the input is currently active
     */
    enum class ActivePart { None, Minutes, Seconds };

    /**
     * @brief Currently active part of the input field
     */
    ActivePart activePart;

    /**
     * @brief Callback function triggered when time value changes
     */
    std::function<void(int, int)> onChange;

public:
    /**
     * @brief Constructor
     * @param pos Position of the input field
     * @param sz Size of the input field
     * @param label Label text to display (default: "Time")
     */
    TimeInputField(const sf::Vector2f& pos, const sf::Vector2f& sz, const std::string& label = "Time");

    /**
     * @brief Renders the time input field to the window
     * @param window Window in which to render the component
     */
    void render(sf::RenderWindow& window);

    /**
     * @brief Handles UI events (mouse clicks, keyboard input)
     * @param event SFML event to handle
     * @param mousePos Current mouse position
     * @return true if the event was handled by this component, false otherwise
     */
    bool handleEvent(const sf::Event& event, const sf::Vector2i& mousePos);

    /**
     * @brief Updates the input field state
     * @param mousePos Current mouse position
     *
     * This should be called each frame to update hover effects.
     */
    void update(const sf::Vector2i& mousePos);

    /**
     * @brief Sets the callback function for when time value changes
     * @param callback Function to call with (minutes, seconds) parameters
     */
    void setOnChange(std::function<void(int, int)> callback);

    /**
     * @brief Gets the total time in seconds
     * @return Total seconds (minutes * 60 + seconds)
     */
    int getTotalSeconds() const;

    /**
     * @brief Sets the time value
     * @param mins Minutes value
     * @param secs Seconds value
     *
     * Values will be constrained to the min/max ranges.
     */
    void setTime(int mins, int secs);

    /**
     * @brief Gets the current minutes value
     * @return Minutes value
     */
    int getMinutes() const;

    /**
     * @brief Gets the current seconds value
     * @return Seconds value
     */
    int getSeconds() const;

private:
    /**
     * @brief Updates the minutes text display
     */
    void updateMinutesText();

    /**
     * @brief Updates the seconds text display
     */
    void updateSecondsText();

    /**
     * @brief Formats a number as a two-digit string
     * @param number Number to format
     * @return Formatted string (e.g., "05" for 5)
     */
    std::string formatNumber(int number);

    /**
     * @brief Centers a text object within a rectangular box
     * @param text Text to center
     * @param box Box in which to center the text
     */
    void centerTextInBox(sf::Text& text, const sf::RectangleShape& box);

    /**
     * @brief Increments the minutes value
     */
    void incrementMinutes();

    /**
     * @brief Decrements the minutes value
     */
    void decrementMinutes();

    /**
     * @brief Increments the seconds value
     */
    void incrementSeconds();

    /**
     * @brief Decrements the seconds value
     */
    void decrementSeconds();

    /**
     * @brief Notifies the onChange callback of a value change
     */
    void notifyChange();
};