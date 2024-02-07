#include "stdafx.h"
#include "WinState.h"
#include "../Components/Graphics_Components/AnimatedGraphicsCP.h"
#include "../Components/Graphics_Components/StandardGraphicsCP.h"
#include "../Components/Transformation_Components/TransformationCP.h"
#include "../Components/Transformation_Components/BackgroundTransformationCP.h"
#include "../Components/Input_Components/MovementInputWASDCP.h"
#include "../Components/Input_Components/MovementInputArrowsCP.h"
#include "../Components/Collision_Components/RectCollisionCP.h"
#include "../Components/Render_Components/RenderCP.h"
#include "../Components/CameraCP.h"
#include "../Components/Transformation_Components/CameraTransformationCP.h"
#include "../Components/Render_Components/SpriteRenderCP.h"

#include "../Manager/GameStateManager.h"


#include <SFML/Graphics.hpp>
#include <iostream>


void WinState::init(sf::RenderWindow& rWindow)
{
	this->window.reset(&rWindow, [](sf::RenderWindow*) {});

	DebugDraw::getInstance().initialize(*window);

	AssetManager::getInstance().loadMusic("Celestial_Wanderer", "Assets\\Music\\Celestial_Wanderer.mp3");
	cw = AssetManager::getInstance().Music["Celestial_Wanderer"];
	cw->setVolume(10);
	cw->play();

	window->setView(sf::View(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2), (sf::Vector2f)window->getSize()));

	AssetManager::getInstance().loadTexture("BackgroundImage", "Assets\\Textures\\winScreen.png");
	AssetManager::getInstance().loadTexture("restartImage", "Assets\\Textures\\restart.png");
	AssetManager::getInstance().loadTexture("exitImage", "Assets\\Textures\\exit.png");

	if (!AssetManager::getInstance().Textures["BackgroundImage"])
	{
		std::cout << "Background-Image not found " << std::endl;
	}


	bgTexture = *AssetManager::getInstance().Textures["BackgroundImage"];
	backgroundSprite.setTexture(bgTexture);
	sf::Vector2f viewCenterVec = sf::Vector2f((window->getSize().x / 2), (window->getSize().y / 2));
	sf::Vector2f startButtonPos = sf::Vector2f((window->getSize().x / 2), (window->getSize().y / 2) + 150);
	sf::Vector2f exitButtonPos = sf::Vector2f((window->getSize().x / 2), (window->getSize().y / 2) + 250);
	backgroundSprite.setOrigin(sf::Vector2(backgroundSprite.getGlobalBounds().width / 2, backgroundSprite.getGlobalBounds().height / 2));
	backgroundSprite.setPosition(viewCenterVec);

	restartTexture = *AssetManager::getInstance().Textures["restartImage"];
	restartSprite.setTexture(restartTexture);
	restartSprite.setOrigin(sf::Vector2(restartSprite.getGlobalBounds().width / 2, restartSprite.getGlobalBounds().height / 2));
	restartSprite.setPosition(startButtonPos);
	restartSprite.setScale(0.5f, 0.5f);

	exitTexture = *AssetManager::getInstance().Textures["exitImage"];
	exitSprite.setTexture(exitTexture);
	exitSprite.setOrigin(sf::Vector2(exitSprite.getGlobalBounds().width / 2, exitSprite.getGlobalBounds().height / 2));
	exitSprite.setPosition(exitButtonPos);
	exitSprite.setScale(0.5f, 0.5f);

	sf::Color red = sf::Color(255, 0, 0, 255);
	sf::Color black = sf::Color(0, 0, 0);
	sf::Color white = sf::Color(255, 255, 255, 255);


	createButton("Start", sf::Vector2f(750, 50), startButtonPos, black);
	createButton("Exit", sf::Vector2f(750, 50), exitButtonPos, black);

	
	close = false;
}

void WinState::exit()
{
	cw->stop();
	AssetManager::getInstance().unloadAssets();
	DebugDraw::getInstance().unload();
}

void WinState::update(float deltaTime)
{
	for (auto& button : buttonMap)
	{
		sf::FloatRect buttonBounds = button.second.getGlobalBounds();
		sf::Vector2i mousePos = InputManager::getInstance().getMousePosition();

		button.second.setFillColor(sf::Color::Black);
		button.second.setOutlineThickness(1.f);
		button.second.setOutlineColor(sf::Color::Red);

		if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePos)))
		{
			button.second.setOutlineColor(sf::Color::White);

			if (button.first == "Start" && InputManager::getInstance().getMouseUp(sf::Mouse::Left))
			{
				std::cout << "start pressed" << std::endl;
				GameStateManager::getInstance().setState("Gameplay", *window);

			}
			if (button.first == "Exit" && InputManager::getInstance().getMouseUp(sf::Mouse::Left))
			{
				std::cout << "Exit pressed" << std::endl;
				GameStateManager::getInstance().setState("Exit", *window);

			}

		}
		else if (isControllerConnected = sf::Joystick::isConnected(0))
		{
			sf::Vector2f joyStickLocation = InputManager::getInstance().getLeftStickPosition(0);
			if (isPlaySelected)
			{
				if (button.first == "Start")
				{
					button.second.setOutlineColor(sf::Color::White);
					if (sf::Joystick::isButtonPressed(0, GamepadButton::A))
					{
						std::cout << "start pressed" << std::endl;
						GameStateManager::getInstance().setState("Gameplay", *window);
					}
				}
			}

			if (joyStickLocation.y >= 0.2f)
			{
				isPlaySelected = false;
				isExitSelected = true;

			}
			else if (joyStickLocation.y <= -0.2f)
			{
				isPlaySelected = true;
				isExitSelected = false;
			}
			if (isExitSelected)
			{

				std::cout << "down" << std::endl;

				if (button.first == "Start")
				{
					button.second.setOutlineColor(sf::Color::Red);
				}
				else
				{
					button.second.setOutlineColor(sf::Color::White);
				}
				if (sf::Joystick::isButtonPressed(0, static_cast<GamepadButton>(A)))
				{
					std::cout << "Exit pressed" << std::endl;
					GameStateManager::getInstance().setState("Exit", *window);

				}
			}
		}
	}
}

void WinState::render()
{

	window->clear(sf::Color::Black);
	window->draw(backgroundSprite);
	for (auto& pair : buttonMap) {
		window->draw(pair.second);

	}

	window->draw(restartSprite);
	window->draw(exitSprite);
}

sf::RectangleShape WinState::createButton(std::string name, sf::Vector2f size, sf::Vector2f pos, sf::Color fillColor)
{
	sf::RectangleShape button;
	button.setSize(size);
	button.setOrigin(sf::Vector2f(button.getSize().x / 2, button.getSize().y / 2));
	button.setFillColor(fillColor);
	button.setPosition(pos);

	buttonMap[name] = button;

	return button;
}