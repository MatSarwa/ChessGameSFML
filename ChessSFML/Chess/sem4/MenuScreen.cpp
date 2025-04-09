#include "MenuScreen.h"

MenuScreen::MenuScreen(sf::RenderWindow& win) :
    Screen(win),
    playButton(200, 200, 180, 40, "Play"),
    optionsButton(200, 260, 180, 40, "Options"),
    exitButton(200, 320, 180, 40, "Exit")
{
    if (!backgroundTexture.loadFromFile("resources/images/menu_background.png")) {
        sf::Image fallbackImage;
        fallbackImage.create(600, 600, sf::Color(50, 50, 150));
        backgroundTexture.loadFromImage(fallbackImage);
    }
    backgroundSprite.setTexture(backgroundTexture);

    sf::Color buttonColor(100, 100, 180);
    sf::Color hoverColor(130, 130, 220);

    playButton.setColors(buttonColor, hoverColor);
    optionsButton.setColors(buttonColor, hoverColor);
    exitButton.setColors(buttonColor, hoverColor);

    window.setSize(sf::Vector2u(600, 600));
}

void MenuScreen::render() {
    sf::Vector2u windowSize = window.getSize();
    sf::View view(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    window.setView(view);

    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setScale(
        (float)windowSize.x / backgroundTexture.getSize().x,
        (float)windowSize.y / backgroundTexture.getSize().y
    );

    window.draw(backgroundSprite);
    playButton.render(window);
    optionsButton.render(window);
    exitButton.render(window);
}

void MenuScreen::onEnter() {
}

void MenuScreen::onExit() {
}

std::string MenuScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (playButton.isClicked(mousePos)) {
            return "game";
        }
        else if (optionsButton.isClicked(mousePos)) {
            return "options";
        }
        else if (exitButton.isClicked(mousePos)) {
            window.close();
        }
    }

    return "current";
}

void MenuScreen::update() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    playButton.update(mousePos);
    optionsButton.update(mousePos);
    exitButton.update(mousePos);
}