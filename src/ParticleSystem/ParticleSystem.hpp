#pragma once

#include <list>
#include <vector>

#include "Particle.hpp"

namespace ps
{
	class ParticleSystem : public IParticle
	{
	public:
		ParticleSystem() = default;

		ParticleSystem(sf::Vector2f position, const sf::CircleShape& exampleShape, float liveTime, int count) :
			m_shape(new sf::CircleShape(exampleShape)),
			m_particles(count)
		{
			for (auto& particle : m_particles)
			{
				particle = std::unique_ptr<IParticle>(new Particle(position, m_shape, liveTime));

				particle->finished.attach(&ParticleSystem::onParticleFinished, this); // without detach

				setRandomForces(particle.get());
			}
		};

		void addParticleSystem(sf::Vector2f position, const sf::CircleShape& exampleShape, float liveTime, int count)
		{
			m_particles.push_back(std::unique_ptr<IParticle>(new ParticleSystem(position, exampleShape, liveTime, count)));
		}

		void update(float dt) override
		{
			removeDeadParticles();

			for (auto& particle : m_particles)
				particle->update(dt);
		}

	private:
		std::list<std::unique_ptr<IParticle>> m_particles;
		std::list<IParticle*> m_deadParticles;
		std::shared_ptr<sf::Shape> m_shape;

		void draw(sf::RenderTarget& rt, sf::RenderStates rs) const override
		{
			for (auto& particle : m_particles)
				rt.draw(*particle, rs);
		}

		void onParticleFinished(IParticle* particle)
		{
			m_deadParticles.push_back(particle);
			if (m_particles.empty())
				finished(this);
		}

		void setRandomForces(IParticle* particle)
		{
			int forceCircleRadius = 200;
			float angInDeg = rand() % 360;
			float angInRad = angInDeg / (2 * 3.14159265359f);
			sf::Vector2f lin(cos(angInRad), sin(angInRad));
			lin *= static_cast<float>(rand() % forceCircleRadius);

			float ang = (rand() % 200) / 100.f - 100.f;

			particle->applyForce(lin, ang);
		}

		void removeDeadParticles()
		{
			for (auto& particle : m_deadParticles)
				m_particles.remove_if([particle](std::unique_ptr<IParticle>& check) -> bool
					{ return check.get() == particle; });

			m_deadParticles.clear();
		}
	};
}