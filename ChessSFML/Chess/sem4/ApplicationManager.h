/**
 * @file application_manager.h
 * @brief Contains the ApplicationManager class definition
 * @author Mateusz Sarwa
 * @date 2024-04-07
 * This header defines the main application management class responsible for
 * managing screens, window, and application-wide settings in a chess game.
 */
#pragma once

#include <map>
#include <string>
#include <SFML/Audio.hpp>
#include "Screen.h"

 // Forward declarations
class Button;
class MenuScreen;
class OptionsScreen;
class GameScreen;

/**
 * @class ApplicationManager
 * @brief Manages the overall application state, screens, and global settings
 *
 * Responsible for:
 * - Creating and managing application windows
 * - Handling screen transitions
 * - Managing background music
 * - Tracking player time settings
 */
class ApplicationManager {
private:
    sf::RenderWindow window;  ///< Main application render window

    /// Map of named screens in the application
    std::map<std::string, Screen*> screens;

    Screen* currentScreen;  ///< Pointer to the currently active screen

    sf::Music backgroundMusic;  ///< Background music for the application

    bool isMusicEnabled;  ///< Flag to track music playback state

    float musicVolume;  ///< Current music volume (0.0f to 100.0f)

    OptionsScreen* optionsScreenPtr;  ///< Pointer to the options screen

    /// Time remaining for white player in seconds
    int whitePlayerTimeSeconds = 600;

    /// Time remaining for black player in seconds
    int blackPlayerTimeSeconds = 600;

public:
    /**
     * @brief Default constructor
     *
     * Initializes the application with default settings:
     * - No current screen
     * - Music enabled
     * - Default music volume
     */
    ApplicationManager() : currentScreen(nullptr), isMusicEnabled(true), musicVolume(50.0f) {}

    /**
     * @brief Destructor
     *
     * Cleans up dynamically allocated screen resources
     */
    ~ApplicationManager() {
        // Free allocated screen resources
        for (auto& pair : screens) {
            delete pair.second;
        }
    }

    /**
     * @brief Get the options screen pointer
     * @return OptionsScreen* Pointer to the options screen
     */
    OptionsScreen* getOptionsScreen() { return optionsScreenPtr; }

    /**
     * @brief Set the time remaining for the white player
     * @param seconds Time in seconds
     */
    void setWhitePlayerTime(int seconds) { whitePlayerTimeSeconds = seconds; }

    /**
     * @brief Set the time remaining for the black player
     * @param seconds Time in seconds
     */
    void setBlackPlayerTime(int seconds) { blackPlayerTimeSeconds = seconds; }

    /**
     * @brief Get the time remaining for the white player
     * @return int Time in seconds
     */
    int getWhitePlayerTime() const { return whitePlayerTimeSeconds; }

    /**
     * @brief Get the time remaining for the black player
     * @return int Time in seconds
     */
    int getBlackPlayerTime() const { return blackPlayerTimeSeconds; }

    /**
     * @brief Set times for both players simultaneously
     * @param whiteTimeSeconds Time for white player in seconds
     * @param blackTimeSeconds Time for black player in seconds
     */
    void setPlayerTimes(int whiteTimeSeconds, int blackTimeSeconds);

    /**
     * @brief Initialize the application
     *
     * Sets up initial screens, resources, and application state
     */
    void initialize();

    /**
     * @brief Switch to a specific screen
     * @param screenName Name of the screen to switch to
     */
    void setScreen(const std::string& screenName);

    /**
     * @brief Toggle background music on or off
     * @param enable True to enable music, false to disable
     */
    void toggleMusic(bool enable);

    /**
     * @brief Set the volume of background music
     * @param volume Music volume (0.0f to 100.0f)
     */
    void setMusicVolume(float volume);

    /**
     * @brief Check if music is currently enabled
     * @return bool True if music is enabled, false otherwise
     */
    bool getMusicEnabled() const;

    /**
     * @brief Main application run loop
     *
     * Handles the primary application execution,
     * including event processing and screen rendering
     */
    void run();
};