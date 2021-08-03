#pragma once

#include <SFML/Graphics.hpp>

#include "IAffector.hpp"

namespace ps
{
	class DisapperingAffector : public IAffector
	{
	public:

	private:
		virtual void update(Particle* particle, float dt) override
		{
			particle->m_color.a = particle->m_remainLiveTime / particle->m_liveTime * 255;
		}
	};
}