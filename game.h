#pragma once
#include "settings.h"
#include "meteor.h"
#include <vector>
#include "Player.h"

class Game {
public:
	enum GameState { PLAY, GAME_OVER, YOU_WIN };
	GameState gameState = PLAY;
	Game() : text("GAME OVER", TEXT_POS, FONT_SIZE1), text1("YOU WIN", TEXT_POS1, FONT_SIZE1) {
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
		window.setFramerateLimit(FPS);
		meteorSprites.reserve(METEORS_QTY);
		for (int i = 0; i < METEORS_QTY; i++) {
			meteorSprites.push_back(new Meteor());
		}
	}

	void play() {
		while (window.isOpen()) {// && player.isAlife()
			checkEvents();
			update();
			if (player.getHp() <= 0) gameState = GAME_OVER;
			if (player.getPoint() >= MAX_POINTS) gameState = YOU_WIN;
			checkCollisions();
			draw();
		}
	}

private:
	sf::RenderWindow window;
	std::vector<Meteor*> meteorSprites;
	Player player;
	Textobj text;
	Textobj text1;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	void update() {
		switch (gameState) {
		case PLAY:
			for (auto meteor : meteorSprites) {
				meteor->update();
			}
			player.update();
			break;
		case GAME_OVER:
			text.update("GAME OVER");
			break;
		case YOU_WIN:
			text1.update("YOU WIN");
			break;
		}
	}

	void checkCollisions() {
		sf::FloatRect playerBounds = player.getHitBox();
		for (auto& meteor : meteorSprites) {
			sf::FloatRect meteorBounds = meteor->getHitBox();
			if (meteorBounds.intersects(playerBounds)) {
				meteor->spawn();
				player.hpChange(meteor->GetDamage());
			}
			auto laserSprites = player.getLaserSprites();
			for (auto& laser : *laserSprites) {
				sf::FloatRect laserBounds = laser->getHitBox();
				if (meteorBounds.intersects(laserBounds)) {
					meteor->spawn();
					laser->setHit();
					player.pointChange(meteor->GetDamage());
				}
				if (laser->getPosY() < 0.f) {
					laser->setHit();
				}
			}
			(*laserSprites).remove_if([](Laser* laser) {return laser->isHit(); });
		}
	}

	void draw() {
		switch (gameState) {
		case PLAY:
			window.clear();
			for (auto meteor : meteorSprites) {
				window.draw(meteor->getSprite());
			}
			player.draw(window);
			window.display();
			break;
		case GAME_OVER:
			window.clear();
			text.draw(window);
			window.display();
			break;
		case YOU_WIN:
			window.clear();
			text1.draw(window);
			window.display();
			break;
		}
	}
};