#pragma once
#include "settings.h"
class Bonus {
public:
	enum BonusType {MULTY_LASER,HP,SHIELD};
	Bonus(BonusType type, sf::Vector2f position);
	void update();
	void draw(sf::RenderWindow& window);
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
	void setDel();
	bool isToDel();
private:
	sf::Texture texture;
	sf::Sprite sprite;
	BonusType type;
	bool del = false;
};

Bonus::Bonus(BonusType type, sf::Vector2f position) {
	switch (type) {
	case MULTY_LASER:
		this->type = type;
		texture.loadFromFile(MULTY_BONUS_FILENAME);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		break;
	}
}
void Bonus::update() { sprite.move(0.f, BONUS_SPEED); }
void Bonus::draw(sf::RenderWindow& window) { window.draw(sprite); }
sf::FloatRect Bonus::getHitBox() { return sprite.getGlobalBounds(); }
sf::Vector2f Bonus::getPosition() { return sprite.getPosition(); }
bool Bonus::isToDel() { return del; }
void Bonus::setDel() { del = true; }