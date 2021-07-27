#pragma once

#include "../Particle.hpp"

namespace ps
{
	class IAffector
	{
	public:
		virtual ~IAffector() {};
		virtual void update(Particle* particle, float dt) = 0;
	};
}