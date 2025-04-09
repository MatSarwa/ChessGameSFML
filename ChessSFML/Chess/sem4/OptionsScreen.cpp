#include "OptionsScreen.h"
#include "ApplicationManager.h"

OptionsScreen::OptionsScreen(sf::RenderWindow& win, ApplicationManager* manager) :
    Screen(win),
    backButton(50, 500, 150, 40, "Back"),
    musicToggleButton(175, 100, 250, 40, "Music: On"),
    volumeSlider(175, 150, 250, 20, 0, 100),
    whiteTimeInput(sf::Vector2f(200, 310), sf::Vector2f(200, 40), "White Player Time"),
    blackTimeInput(sf::Vector2f(200, 380), sf::Vector2f(200, 40), "Black Player Time"),
    isMusicEnabled(false),
    volumeLevel(100),
    appManager(manager)
{
    if (!titleFont.loadFromFile("resources/fonts/arial.ttf")) {
        titleFont.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    titleText.setFont(titleFont);
    titleText.setString("Options");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.width / 2, 0);
    titleText.setPosition(300, 40);

    volumeText.setFont(titleFont);
    volumeText.setCharacterSize(20);
    volumeText.setFillColor(sf::Color::White);
    volumeText.setPosition(175, 200);
    updateVolumeText();

    timerSettingsTitle.setFont(titleFont);
    timerSettingsTitle.setString("Chess Timer Settings");
    timerSettingsTitle.setCharacterSize(24);
    timerSettingsTitle.setFillColor(sf::Color::White);

    sf::FloatRect timerTitleRect = timerSettingsTitle.getLocalBounds();
    timerSettingsTitle.setOrigin(timerTitleRect.width / 2, 0);
    timerSettingsTitle.setPosition(300, 230);

    whiteTimeInput.setTime(10, 0);
    blackTimeInput.setTime(10, 0);

    if (!backgroundTexture.loadFromFile("resources/images/menu_background.png")) {
        sf::Image fallbackImage;
        fallbackImage.create(600, 600, sf::Color(50, 50, 150));
        backgroundTexture.loadFromImage(fallbackImage);
    }
    backgroundSprite.setTexture(backgroundTexture);

    sf::Color buttonColor(100, 100, 180);
    sf::Color hoverColor(130, 130, 220);

    backButton.setColors(buttonColor, hoverColor);
    musicToggleButton.setColors(buttonColor, hoverColor);
}

void OptionsScreen::updateVolumeText() {
    volumeText.setString("Volume: " + std::to_string(volumeLevel) + "%");
}

std::string OptionsScreen::handleEvent(const sf::Event& event) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    whiteTimeInput.handleEvent(event, mousePos);
    blackTimeInput.handleEvent(event, mousePos);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (backButton.isClicked(mousePos)) {
            return "menu";
        }
        else if (musicToggleButton.isClicked(mousePos)) {
            toggleMusic();
        }
        else if (volumeSlider.isClicked(mousePos)) {
            volumeSlider.startDragging();
            volumeLevel = volumeSlider.updateValue(mousePos);
            updateVolumeText();
            updateVolume();
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        if (volumeSlider.isDragging()) {
            volumeLevel = volumeSlider.updateValue(mousePos);
            updateVolumeText();
            updateVolume();
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        volumeSlider.stopDragging();
    }

    return "current";
}

void OptionsScreen::update() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    backButton.update(mousePos);
    musicToggleButton.update(mousePos);
    volumeSlider.update(mousePos);

    whiteTimeInput.update(mousePos);
    blackTimeInput.update(mousePos);
}

void OptionsScreen::render() {

    sf::Vector2u windowSize = window.getSize();
    sf::View view(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    window.setView(view);

    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setScale(
        (float)windowSize.x / backgroundTexture.getSize().x,
        (float)windowSize.y / backgroundTexture.getSize().y
    );

    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(volumeText);
    window.draw(timerSettingsTitle);

    backButton.render(window);
    musicToggleButton.render(window);
    volumeSlider.render(window);
    whiteTimeInput.render(window);
    blackTimeInput.render(window);
}

void OptionsScreen::onEnter() {}

void OptionsScreen::onExit() {
    updateTimers();
}

void OptionsScreen::toggleMusic() {
    isMusicEnabled = !isMusicEnabled;

    if (isMusicEnabled) {
        musicToggleButton.setText("Music: On");
    }
    else {
        musicToggleButton.setText("Music: Off");
    }

    updateVolume();
}

void OptionsScreen::updateVolume() {
    if (appManager) {
        appManager->setMusicVolume(isMusicEnabled ? volumeLevel : 0);
    }
}

void OptionsScreen::updateTimers() {
    if (appManager) {
        appManager->setWhitePlayerTime(whiteTimeInput.getTotalSeconds());
        appManager->setBlackPlayerTime(blackTimeInput.getTotalSeconds());
    }
}