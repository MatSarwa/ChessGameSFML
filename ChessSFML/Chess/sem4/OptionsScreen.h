/**
 * @file OptionsScreen.h
 * @brief Header file for the OptionsScreen class that manages the game options interface
 * @author Your Name
 * @date April 2025
 */

#pragma once
#include "Screen.h"
#include "Button.h"
#include "Slider.h" 
#include "TimeInput.h"

class ApplicationManager;

/**
 * @class OptionsScreen
 * @brief Manages the options/settings screen of the chess application
 *
 * This class provides a user interface for adjusting game settings such as
 * music, volume and chess timer settings for both players.
 * It inherits from the Screen base class.
 */
class OptionsScreen : public Screen {
private:
    /** @brief Button to return to the main menu */
    Button backButton;

    /** @brief Button to toggle music on/off */
    Button musicToggleButton;

    /** @brief Slider to adjust volume level */
    Slider volumeSlider;

    /** @brief Time input field for the white player */
    TimeInputField whiteTimeInput;

    /** @brief Time input field for the black player */
    TimeInputField blackTimeInput;

    /** @brief Background texture for the options screen */
    sf::Texture backgroundTexture;

    /** @brief Sprite for displaying the background */
    sf::Sprite backgroundSprite;

    /** @brief Font used for text elements */
    sf::Font titleFont;

    /** @brief Text element for the screen title */
    sf::Text titleText;

    /** @brief Text element for displaying volume level */
    sf::Text volumeText;

    /** @brief Text element for the timer settings section title */
    sf::Text timerSettingsTitle;

    /** @brief Flag indicating whether music is enabled */
    bool isMusicEnabled;

    /** @brief Integer representing volume level (0-100) */
    int volumeLevel;

    /** @brief Pointer to the ApplicationManager for updating global settings */
    ApplicationManager* appManager;

public:
    /**
     * @brief Constructor for the OptionsScreen
     *
     * @param win Reference to the SFML render window
     * @param manager Pointer to the ApplicationManager (default: nullptr)
     */
    OptionsScreen(sf::RenderWindow& win, ApplicationManager* manager = nullptr);

    /**
     * @brief Updates the volume text display based on current volume level
     */
    void updateVolumeText();

    /**
     * @brief Handles user input events
     *
     * @param event The SFML event to handle
     * @return std::string Screen state identifier ("current", "menu", etc.)
     */
    std::string handleEvent(const sf::Event& event) override;

    /**
     * @brief Updates the screen state
     *
     * Called once per frame to update all UI elements
     */
    void update() override;

    /**
     * @brief Renders the screen elements
     *
     * Draws all UI components to the window
     */
    void render() override;

    /**
     * @brief Called when entering this screen
     *
     * Initializes any necessary resources or states
     */
    void onEnter() override;

    /**
     * @brief Called when exiting this screen
     *
     * Updates timers and performs cleanup
     */
    void onExit() override;

private:
    /**
     * @brief Toggles the music on or off
     *
     * Updates the musicToggleButton text and calls updateVolume()
     */
    void toggleMusic();

    /**
     * @brief Updates the volume in the ApplicationManager
     *
     * Sets the volume to zero if music is disabled
     */
    void updateVolume();

    /**
     * @brief Updates player timers in the ApplicationManager
     *
     * Transfers the time values from input fields to the application
     */
    void updateTimers();
};