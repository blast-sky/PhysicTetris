#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include "../Event.hpp"

class IParticle : public sf::Drawable
{
public:
	event<void(IParticle*)> finished;

	virtual void update(float dt) = 0;
	virtual void applyForce(sf::Vector2f linearForce, float angularForce) {};
	virtual ~IParticle() {};
};