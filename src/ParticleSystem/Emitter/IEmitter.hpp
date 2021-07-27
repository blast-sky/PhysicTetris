#pragma once

#include "../Particle.hpp"

namespace ps
{
	class IEmitter
	{
	public:
		virtual ~IEmitter() {};
		virtual void update(Particle* particle, float dt) = 0;
	};
}