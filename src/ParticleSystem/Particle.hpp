#pragma once

#include "IParticle.hpp"

namespace ps
{
	class Particle : public IParticle, public sf::Transformable
	{
	public:
		std::shared_ptr<sf::Shape> m_shape;
		sf::Color m_color;
		float m_liveTime;
		float m_remainLiveTime;
		
		Particle(sf::Vector2f pos, std::shared_ptr<sf::Shape> shape, float liveTime, sf::Color color = sf::Color::White) :
			m_shape(shape),
			m_color(color),
			m_liveTime(liveTime),
			m_remainLiveTime(liveTime)
		{
			setPosition(pos);
		}

		void applyForce(sf::Vector2f lin, float ang) override
		{
			m_linearForce += lin;
			m_angularForce += ang;
		}

	private:
		sf::Vector2f m_linearForce;
		sf::Vector2f m_linearSpeed;
		float m_angularSpeed;
		float m_angularForce;


		void update(float dt) override
		{
			if ((m_remainLiveTime -= dt) <= 0.f)
			{
				finished(this);
			}
			else
			{
				m_color.a = m_remainLiveTime / m_liveTime * 255;

				m_angularSpeed += m_angularForce * dt;
				rotate(m_angularSpeed * dt);

				m_linearSpeed += m_linearForce * dt;
				move(m_linearSpeed * dt);
			}
		}

		void draw(sf::RenderTarget& rt, sf::RenderStates rs) const override
		{
			m_shape->setFillColor(m_color);
			rt.draw(*m_shape, getTransform());
		}
	};
}