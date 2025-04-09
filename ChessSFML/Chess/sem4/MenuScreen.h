/**
 * @file menu_screen.h
 * @brief Contains the MenuScreen class definition
 * @author Mateusz Sarwa
 * @date 2024-04-07
 * This header defines the main menu screen for the chess application,
 * managing navigation and initial user interactions.
 */
#pragma once

#include "Screen.h"
#include "Button.h"

 /**
  * @class MenuScreen
  * @brief Represents the main menu screen of the chess application
  *
  * Manages the initial screen with options to:
  * - Start a new game
  * - Access options
  * - Exit the application
  */
class MenuScreen : public Screen {
private:
    Button playButton;        ///< Button to start a new game
    Button optionsButton;     ///< Button to access game options
    Button exitButton;        ///< Button to exit the application

    sf::Texture backgroundTexture;  ///< Texture for the menu background
    sf::Sprite backgroundSprite;    ///< Sprite to render the background

public:
    /**
     * @brief Constructor for MenuScreen
     * @param win Reference to the application's render window
     *
     * Initializes menu buttons and background:
     * - Creates buttons for play, options, and exit
     * - Loads background image or creates a fallback
     * - Sets button colors
     * - Configures initial window size
     */
    MenuScreen(sf::RenderWindow& win);

    /**
     * @brief Renders the menu screen
     *
     * Draws the background and menu buttons:
     * - Adjusts view to window size
     * - Scales background to fill window
     * - Renders buttons
     */
    void render() override;

    /**
     * @brief Called when entering the menu screen
     *
     * Performs any necessary initialization or reset
     * when transitioning to this screen
     */
    void onEnter() override;

    /**
     * @brief Called when leaving the menu screen
     *
     * Performs cleanup or saves state when
     * transitioning away from this screen
     */
    void onExit() override;

    /**
     * @brief Handles input events for the menu screen
     * @param event SFML event to process
     * @return std::string Name of the next screen
     *
     * Processes mouse clicks on menu buttons:
     * - Play button starts a new game
     * - Options button opens options screen
     * - Exit button closes the application
     */
    std::string handleEvent(const sf::Event& event) override;

    /**
     * @brief Updates menu screen state
     *
     * Updates button states based on mouse position:
     * - Handles button hover effects
     */
    void update() override;
};