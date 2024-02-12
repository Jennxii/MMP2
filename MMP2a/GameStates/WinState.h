//MultiMediaTechnology FHS
//MultiMediaProjekt 2a
//Kevin Raffetseder, Julian Resch, Jennifer Strohmer
#pragma once
#include "../DebugDraw.h"
#include "../GameObject.h"
#include "../Manager/AssetManager.h"
#include "GameState.h"


class WinState : public GameState
{
public:
	void init(sf::RenderWindow& rWindow) override;
	void exit() override;
	void update(float deltaTime) override;
	void render() override;

private:
	sf::RectangleShape createButton(std::string name, sf::Vector2f size, sf::Vector2f pos, sf::Color fillColor);

	std::vector<std::shared_ptr<GameObject>> gameObjects;

	std::shared_ptr<sf::RenderWindow> window;
	sf::Sprite backgroundSprite;

	std::shared_ptr<sf::Music> cw;

	sf::RectangleShape startButton;
	sf::RectangleShape exitButton;

	sf::Sprite restartSprite;
	sf::Sprite exitSprite;

	std::vector<std::pair<sf::Text, sf::RectangleShape>> buttonList;
	std::map<std::string, sf::RectangleShape> buttonMap;

	bool isControllerConnected = false;
	bool isPlaySelected = true;
	bool isExitSelected = false;
};