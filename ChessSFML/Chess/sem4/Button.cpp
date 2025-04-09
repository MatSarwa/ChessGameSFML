#include "Button.h"

Button::Button(float x, float y, float width, float height, const std::string& buttonText, unsigned int fontSize)
    : isHovered(false),
    idleColor(sf::Color(100, 100, 100)),
    hoverColor(sf::Color(150, 150, 150)) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(idleColor);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);

    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    text.setFont(font);

    try {
        text.setString(buttonText);
    }
    catch (const std::exception&) {
        text.setString("Przycisk");
    }

    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        x + (width - textBounds.width) / 2.0f,
        y + (height - textBounds.height) / 2.0f - textBounds.top
    );
}

void Button::setFont(const sf::Font& newFont) {
    font = newFont;
    text.setFont(font);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        shape.getPosition().x + (shape.getSize().x - textBounds.width) / 2.0f,
        shape.getPosition().y + (shape.getSize().y - textBounds.height) / 2.0f - textBounds.top
    );
}

void Button::setPosition(float x, float y) {
    shape.setPosition(x, y);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        x + (shape.getSize().x - textBounds.width) / 2.0f,
        y + (shape.getSize().y - textBounds.height) / 2.0f - textBounds.top
    );
}

void Button::setColors(const sf::Color& idle, const sf::Color& hover) {
    idleColor = idle;
    hoverColor = hover;
    shape.setFillColor(idleColor);
}

bool Button::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}

bool Button::isClicked(const sf::Vector2i& mousePos) const {
    return shape.getGlobalBounds().contains(sf::Vector2f(mousePos));
}

void Button::update(const sf::Vector2i& mousePos) {
    isHovered = contains(sf::Vector2f(mousePos));
    shape.setFillColor(isHovered ? hoverColor : idleColor);
}

void Button::render(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void Button::setText(const std::string& newText) {
    text.setString(newText);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        shape.getPosition().x + (shape.getSize().x - textBounds.width) / 2.0f,
        shape.getPosition().y + (shape.getSize().y - textBounds.height) / 2.0f - textBounds.top
    );
}

void Button::setTextColor(const sf::Color& color) {
    text.setFillColor(color);
}