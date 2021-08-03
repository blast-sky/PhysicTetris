#pragma once

#include <SFML/Graphics.hpp>

#include "IEmitter.hpp"

namespace ps
{
	class DisapperingAffector : public IEmitter
	{
	public:
		DisapperingAffector();

	private:
		sf::Vector2f m_linearForce;
		float m_angularForce;

		virtual void update(Particle* particle, float dt) override
		{
			
		}
	};
}
