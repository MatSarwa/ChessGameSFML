#include "ApplicationManager.h"
#include "MenuScreen.h"
#include "OptionsScreen.h"
#include "GameScreen.h"

void ApplicationManager::initialize() {
    window.create(sf::VideoMode(600, 600), "Chess Game", sf::Style::Close | sf::Style::Titlebar);

    if (backgroundMusic.openFromFile("resources/audio/music.mp3")) {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(musicVolume);
        if (isMusicEnabled) {
            backgroundMusic.play();
        }
    }

    screens["menu"] = new MenuScreen(window);
    screens["options"] = new OptionsScreen(window, this);
    screens["game"] = new GameScreen(window);

    optionsScreenPtr = static_cast<OptionsScreen*>(screens["options"]);

    setScreen("menu");
}

void ApplicationManager::setScreen(const std::string& screenName) {
    auto it = screens.find(screenName);
    if (it != screens.end()) {
        if (currentScreen) {
            currentScreen->onExit();
        }

        if (screenName == "game") {
            window.setSize(sf::Vector2u(1280, 720));
            sf::FloatRect visibleArea(0, 0, 1280, 720);
            window.setView(sf::View(visibleArea));

            GameScreen* gameScreen = static_cast<GameScreen*>(it->second);
            gameScreen->setPlayerTimes(whitePlayerTimeSeconds, blackPlayerTimeSeconds);
        }
        else if (currentScreen == screens["game"]) {
            window.setSize(sf::Vector2u(600, 600));
            sf::FloatRect visibleArea(0, 0, 600, 600);
            window.setView(sf::View(visibleArea));
        }

        currentScreen = it->second;
        currentScreen->onEnter();
    }
}

void ApplicationManager::toggleMusic(bool enable) {
    isMusicEnabled = enable;
    if (isMusicEnabled) {
        backgroundMusic.play();
    }
    else {
        backgroundMusic.pause();
    }
}

void ApplicationManager::setMusicVolume(float volume) {
    musicVolume = volume;
    backgroundMusic.setVolume(musicVolume);
}

bool ApplicationManager::getMusicEnabled() const {
    return isMusicEnabled;
}

void ApplicationManager::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (currentScreen == screens["game"]) {
                if (event.type == sf::Event::Resized) {
                    sf::Vector2u currentSize = window.getSize();
                    if (currentSize.x < 1280 || currentSize.y < 720) {
                        sf::Vector2u newSize(
                            std::max(currentSize.x, 1280u),
                            std::max(currentSize.y, 720u)
                        );
                        window.setSize(newSize);
                    }

                    sf::FloatRect visibleArea(0, 0, currentSize.x, currentSize.y);
                    window.setView(sf::View(visibleArea));
                }
            }
            else {
                if (event.type == sf::Event::Resized) {
                    sf::Vector2u currentSize = window.getSize();
                    if (currentSize.x < 600 || currentSize.y < 600) {
                        sf::Vector2u newSize(
                            std::max(currentSize.x, 600u),
                            std::max(currentSize.y, 600u)
                        );
                        window.setSize(newSize);
                    }

                    sf::FloatRect visibleArea(0, 0, currentSize.x, currentSize.y);
                    window.setView(sf::View(visibleArea));
                }
            }

            if (currentScreen) {
                std::string nextScreen = currentScreen->handleEvent(event);
                if (!nextScreen.empty() && nextScreen != "current") {
                    setScreen(nextScreen);
                }
            }
        }

        if (currentScreen) {
            currentScreen->update();
            window.clear();
            currentScreen->render();
            window.display();
        }
    }
}

void ApplicationManager::setPlayerTimes(int whiteTimeSeconds, int blackTimeSeconds) {
    whitePlayerTimeSeconds = whiteTimeSeconds;
    blackPlayerTimeSeconds = blackTimeSeconds;
}