#include "ChessTimer.h"
#include <sstream>
#include <iomanip>

ChessTimer::ChessTimer(sf::RenderWindow& win, const sf::Vector2f& pos, const sf::Vector2f& sz, bool isWhite)
    : window(&win),
    position(pos),
    size(sz),
    totalTimeSeconds(600.0f),
    remainingTimeSeconds(600.0f),
    isRunning(false),
    isWhitePlayer(isWhite),
    isLowOnTime(false)
{
    lastUpdateTime = std::chrono::high_resolution_clock::now();
    background.setSize(size);
    background.setPosition(position);
    background.setFillColor(sf::Color(70, 70, 70));
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color(100, 100, 100));

    if (!font.loadFromFile("resources/fonts/arial.ttf")) {
        if (!font.loadFromFile("font.ttf")) {
        }
    }

    playerNameText.setFont(font);
    playerNameText.setString(isWhitePlayer ? "White" : "Black");
    playerNameText.setCharacterSize(18);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setPosition(position.x + 10, position.y + 5);
    timeText.setFont(font);
    timeText.setString(formatTime());
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(position.x + 10, position.y + 30);
}

void ChessTimer::render() {
    window->draw(background);
    window->draw(playerNameText);
    window->draw(timeText);
}

void ChessTimer::update() {
    if (isRunning) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastUpdateTime).count();
        double elapsedSeconds = elapsed / 1000000.0;
        if (elapsedSeconds > 0.1) {
            elapsedSeconds = 0.1;
        }
        lastUpdateTime = currentTime;
        remainingTimeSeconds -= static_cast<float>(elapsedSeconds);
        if (remainingTimeSeconds < 0) {
            remainingTimeSeconds = 0;
            isRunning = false;
        }
        isLowOnTime = remainingTimeSeconds < 60.0f;
        timeText.setFillColor(isLowOnTime ? sf::Color::Red : sf::Color::White);
        timeText.setString(formatTime());
    }
}

void ChessTimer::start() {
    if (!isRunning) {
        isRunning = true;
        lastUpdateTime = std::chrono::high_resolution_clock::now();
    }
}

void ChessTimer::stop() {
    if (isRunning) {
        isRunning = false;
    }
}

void ChessTimer::reset(float initialTimeSeconds) {
    totalTimeSeconds = initialTimeSeconds;
    remainingTimeSeconds = initialTimeSeconds;
    isRunning = false;
    isLowOnTime = false;
    timeText.setFillColor(sf::Color::White);
    timeText.setString(formatTime());
    lastUpdateTime = std::chrono::high_resolution_clock::now();
}

void ChessTimer::addTime(float secondsToAdd) {
    remainingTimeSeconds += secondsToAdd;
    timeText.setString(formatTime());
}

std::string ChessTimer::formatTime() const {
    int minutes = static_cast<int>(remainingTimeSeconds) / 60;
    int seconds = static_cast<int>(remainingTimeSeconds) % 60;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << seconds;
    return ss.str();
}

void ChessTimer::setRemainingTime(int seconds) {
    remainingTimeSeconds = static_cast<float>(seconds);
    isLowOnTime = remainingTimeSeconds < 60.0f;
    timeText.setFillColor(isLowOnTime ? sf::Color::Red : sf::Color::White);
    timeText.setString(formatTime());
    lastUpdateTime = std::chrono::high_resolution_clock::now();
}