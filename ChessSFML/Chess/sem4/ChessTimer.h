/**
 * @file ChessTimer.h
 * @brief Class for managing and displaying chess game timers
 * @author Mateusz Sarwa
 * @date 2024-04-07
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <string>

 /**
  * @class ChessTimer
  * @brief Manages the chess game clock for a player
  *
  * This class handles the timer functionality for chess games, including
  * displaying the remaining time, starting/stopping the clock, and
  * providing visual feedback when time is running low.
  */
class ChessTimer {
private:
    /**
     * @brief Pointer to the rendering window
     */
    sf::RenderWindow* window;

    /**
     * @brief Font used for displaying text
     */
    sf::Font font;

    /**
     * @brief Position of the timer on the screen
     */
    sf::Vector2f position;

    /**
     * @brief Size of the timer display
     */
    sf::Vector2f size;

    /**
     * @brief Background shape for the timer
     */
    sf::RectangleShape background;

    /**
     * @brief Text displaying the player's name
     */
    sf::Text playerNameText;

    /**
     * @brief Text displaying the remaining time
     */
    sf::Text timeText;

    /**
     * @brief Total allocated time in seconds
     */
    float totalTimeSeconds;

    /**
     * @brief Remaining time in seconds
     */
    float remainingTimeSeconds;

    /**
     * @brief Flag indicating if the timer is currently running
     */
    bool isRunning;

    /**
     * @brief Timestamp of the last timer update
     */
    std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime;

    /**
     * @brief Flag indicating if this timer is for white player
     */
    bool isWhitePlayer;

    /**
     * @brief Flag indicating if time is running low (for visual warning)
     */
    bool isLowOnTime;

public:
    /**
     * @brief Constructor
     * @param window Reference to the rendering window
     * @param position Position of the timer on screen
     * @param size Size of the timer display
     * @param isWhitePlayer Whether this timer is for the white player
     */
    ChessTimer(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size, bool isWhitePlayer);

    /**
     * @brief Renders the timer to the window
     */
    void render();

    /**
     * @brief Updates the timer state
     *
     * Should be called once per frame to update the remaining time
     * when the timer is running.
     */
    void update();

    /**
     * @brief Starts the timer
     *
     * Begins counting down the remaining time.
     */
    void start();

    /**
     * @brief Stops the timer
     *
     * Pauses the countdown of remaining time.
     */
    void stop();

    /**
     * @brief Resets the timer to the specified initial time
     * @param initialTimeSeconds The initial time in seconds
     */
    void reset(float initialTimeSeconds);

    /**
     * @brief Adds time to the timer
     * @param secondsToAdd Number of seconds to add (e.g., bonus time per move)
     */
    void addTime(float secondsToAdd);

    /**
     * @brief Gets the remaining time
     * @return Remaining time in seconds
     */
    float getRemainingTime() const { return remainingTimeSeconds; }

    /**
     * @brief Checks if time has expired
     * @return true if time is up, false otherwise
     */
    bool isTimeExpired() const { return remainingTimeSeconds <= 0; }

    /**
     * @brief Checks if the timer is currently running
     * @return true if timer is active, false otherwise
     */
    bool isActive() const { return isRunning; }

    /**
     * @brief Sets the remaining time
     * @param seconds New remaining time in seconds
     */
    void setRemainingTime(int seconds);

    /**
     * @brief Formats the remaining time as a string
     * @return Formatted time string (e.g., "05:32")
     */
    std::string formatTime() const;
};