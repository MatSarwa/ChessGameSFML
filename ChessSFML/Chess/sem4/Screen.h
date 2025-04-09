#pragma once
#include <SFML/Graphics.hpp>

/**
 * @class Screen
 * @brief Abstract base class for game screens.
 * @author Mateusz Sarwa
 * @date 2024-04-07
 * This class provides a common interface for game screens, such as menus, gameplay, and settings.
 * It handles events, updates, and rendering for each screen.
 */
class Screen {
protected:
    sf::RenderWindow& window; /**< Reference to the SFML render window. */

public:
    /**
     * @brief Constructor for the Screen class.
     * @param win Reference to the SFML render window.
     */
    Screen(sf::RenderWindow& win) : window(win) {}

    /**
     * @brief Virtual destructor for the Screen class.
     */
    virtual ~Screen() = default;

    /**
     * @brief Called when the screen is entered.
     *
     * This function is called when the screen becomes active. It can be used to initialize
     * screen-specific resources or perform any setup required before the screen is displayed.
     */
    virtual void onEnter() = 0;

    /**
     * @brief Called when the screen is exited.
     *
     * This function is called when the screen is no longer active. It can be used to clean up
     * screen-specific resources or perform any necessary actions before the screen is destroyed.
     */
    virtual void onExit() = 0;

    /**
     * @brief Handles events for the screen.
     * @param event The SFML event to handle.
     * @return A string indicating the next screen to transition to, or an empty string if no transition is required.
     *
     * This function is called when an event occurs while the screen is active. It should handle
     * screen-specific events and return a string indicating the next screen to transition to, if any.
     */
    virtual std::string handleEvent(const sf::Event& event) = 0;

    /**
     * @brief Updates the screen's state.
     *
     * This function is called every frame to update the screen's state, such as updating game objects,
     * processing input, or performing any other necessary updates.
     */
    virtual void update() = 0;

    /**
     * @brief Renders the screen.
     *
     * This function is called every frame to render the screen's graphics. It should use the SFML
     * render window to draw any necessary graphics, such as sprites, text, or shapes.
     */
    virtual void render() = 0;
};