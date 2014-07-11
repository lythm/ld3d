#pragma once

namespace ld3d
{
	namespace particle
	{
		class ParticleEmitter
		{
		public:
			ParticleEmitter(GameObjectManagerPtr pManager) : GameObjectComponent("Particle.Emitter", pManager){}
			virtual ~ParticleEmitter(void){}
		};


	}
}
