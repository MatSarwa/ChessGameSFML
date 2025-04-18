#include "TimeInput.h"

TimeInputField::TimeInputField(const sf::Vector2f& pos, const sf::Vector2f& sz, const std::string& label)
    : position(pos),
    size(sz),
    minutes(0),
    seconds(0),
    minMinutes(0),
    maxMinutes(59),
    minSeconds(0),
    maxSeconds(59),
    activePart(ActivePart::None)
{
    if (!font.loadFromFile("assets/font.ttf")) {
        if (!font.loadFromFile("resources/fonts/arial.ttf")) {
            font.loadFromFile("C:/Windows/Fonts/arial.ttf");
        }
    }

    background.setPosition(position.x - 10, position.y - 5);
    background.setSize(sf::Vector2f(size.x + 20, size.y + 10));
    background.setFillColor(sf::Color(20, 20, 20));
    background.setOutlineThickness(1);
    background.setOutlineColor(sf::Color(50, 50, 50));

    labelText.setFont(font);
    labelText.setString(label);
    labelText.setCharacterSize(14);
    labelText.setFillColor(sf::Color(255, 255, 255));
    labelText.setStyle(sf::Text::Bold);
    labelText.setPosition(position.x, position.y - 25);

    float boxWidth = (size.x - 30) / 2;
    float boxHeight = size.y;
    float separatorWidth = 20;

    minutesBox.setSize(sf::Vector2f(boxWidth, boxHeight));
    minutesBox.setPosition(position.x, position.y);
    minutesBox.setFillColor(sf::Color(15, 15, 15));
    minutesBox.setOutlineThickness(1);
    minutesBox.setOutlineColor(sf::Color(40, 40, 40));

    secondsBox.setSize(sf::Vector2f(boxWidth, boxHeight));
    secondsBox.setPosition(position.x + boxWidth + separatorWidth, position.y);
    secondsBox.setFillColor(sf::Color(15, 15, 15));
    secondsBox.setOutlineThickness(1);
    secondsBox.setOutlineColor(sf::Color(40, 40, 40));

    separatorText.setFont(font);
    separatorText.setString(":");
    separatorText.setCharacterSize(32);
    separatorText.setFillColor(sf::Color(180, 180, 180));
    separatorText.setPosition(position.x + boxWidth + 5, position.y + size.y / 2 - 16);

    minutesText.setFont(font);
    minutesText.setCharacterSize(32);
    minutesText.setFillColor(sf::Color::White);
    updateMinutesText();

    secondsText.setFont(font);
    secondsText.setCharacterSize(32);
    secondsText.setFillColor(sf::Color::White);
    updateSecondsText();
}

void TimeInputField::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(minutesBox);
    window.draw(secondsBox);

    if (labelText.getString() != "") {
        window.draw(labelText);
    }
    window.draw(minutesText);
    window.draw(secondsText);
    window.draw(separatorText);
}

bool TimeInputField::handleEvent(const sf::Event& event, const sf::Vector2i& mousePos) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (minutesBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            activePart = ActivePart::Minutes;
            updateMinutesText();
            updateSecondsText();
            return true;
        }
        else if (secondsBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            activePart = ActivePart::Seconds;
            updateMinutesText();
            updateSecondsText();
            return true;
        }
        else {
            activePart = ActivePart::None;
            updateMinutesText();
            updateSecondsText();
        }
    }
    else if (event.type == sf::Event::KeyPressed && activePart != ActivePart::None) {
        if (activePart == ActivePart::Minutes) {
            if (event.key.code == sf::Keyboard::Up) {
                incrementMinutes();
                return true;
            }
            else if (event.key.code == sf::Keyboard::Down) {
                decrementMinutes();
                return true;
            }
            else if (event.key.code == sf::Keyboard::Right) {
                activePart = ActivePart::Seconds;
                updateMinutesText();
                updateSecondsText();
                return true;
            }
            else if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9) {
                int digit = event.key.code - sf::Keyboard::Num0;
                minutes = (minutes * 10 + digit) % 100;
                if (minutes > maxMinutes) minutes = maxMinutes;
                updateMinutesText();
                notifyChange();
                return true;
            }
        }
        else if (activePart == ActivePart::Seconds) {
            if (event.key.code == sf::Keyboard::Up) {
                incrementSeconds();
                return true;
            }
            else if (event.key.code == sf::Keyboard::Down) {
                decrementSeconds();
                return true;
            }
            else if (event.key.code == sf::Keyboard::Left) {
                activePart = ActivePart::Minutes;
                updateMinutesText();
                updateSecondsText();
                return true;
            }
            else if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9) {
                int digit = event.key.code - sf::Keyboard::Num0;
                seconds = (seconds * 10 + digit) % 100;
                if (seconds > maxSeconds) seconds = maxSeconds;
                updateSecondsText();
                notifyChange();
                return true;
            }
        }
    }

    return false;
}

void TimeInputField::update(const sf::Vector2i& mousePos) {}

void TimeInputField::setOnChange(std::function<void(int, int)> callback) {
    onChange = callback;
}

int TimeInputField::getTotalSeconds() const {
    return minutes * 60 + seconds;
}

void TimeInputField::setTime(int mins, int secs) {
    minutes = mins;
    if (minutes < minMinutes) minutes = minMinutes;
    if (minutes > maxMinutes) minutes = maxMinutes;

    seconds = secs;
    if (seconds < minSeconds) seconds = minSeconds;
    if (seconds > maxSeconds) seconds = maxSeconds;

    updateMinutesText();
    updateSecondsText();
}

int TimeInputField::getMinutes() const {
    return minutes;
}

int TimeInputField::getSeconds() const {
    return seconds;
}

void TimeInputField::updateMinutesText() {
    minutesText.setString(formatNumber(minutes));
    centerTextInBox(minutesText, minutesBox);

    if (activePart == ActivePart::Minutes) {
        minutesText.setFillColor(sf::Color::Yellow);
        minutesBox.setOutlineColor(sf::Color::Yellow);
    }
    else {
        minutesText.setFillColor(sf::Color::White);
        minutesBox.setOutlineColor(sf::Color(60, 60, 60));
    }
}

void TimeInputField::updateSecondsText() {
    secondsText.setString(formatNumber(seconds));
    centerTextInBox(secondsText, secondsBox);

    if (activePart == ActivePart::Seconds) {
        secondsText.setFillColor(sf::Color::Yellow);
        secondsBox.setOutlineColor(sf::Color::Yellow);
    }
    else {
        secondsText.setFillColor(sf::Color::White);
        secondsBox.setOutlineColor(sf::Color(60, 60, 60));
    }
}

std::string TimeInputField::formatNumber(int number) {
    return (number < 10 ? "0" : "") + std::to_string(number);
}

void TimeInputField::centerTextInBox(sf::Text& text, const sf::RectangleShape& box) {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        box.getPosition().x + (box.getSize().x - textBounds.width) / 2,
        box.getPosition().y + (box.getSize().y - textBounds.height) / 2 - 5
    );
}

void TimeInputField::incrementMinutes() {
    minutes++;
    if (minutes > maxMinutes) {
        minutes = minMinutes;
    }
    updateMinutesText();
    notifyChange();
}

void TimeInputField::decrementMinutes() {
    minutes--;
    if (minutes < minMinutes) {
        minutes = maxMinutes;
    }
    updateMinutesText();
    notifyChange();
}

void TimeInputField::incrementSeconds() {
    seconds++;
    if (seconds > maxSeconds) {
        seconds = minSeconds;
        incrementMinutes();
    }
    updateSecondsText();
    notifyChange();
}

void TimeInputField::decrementSeconds() {
    seconds--;
    if (seconds < minSeconds) {
        seconds = maxSeconds;
        decrementMinutes();
    }
    updateSecondsText();
    notifyChange();
}

void TimeInputField::notifyChange() {
    if (onChange) {
        onChange(minutes, seconds);
    }
}