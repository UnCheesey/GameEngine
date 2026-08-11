#pragma once

// Utilities
#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"
#include "MathUtils.h"
#include "StringUtils.h"
#include "File.h"
#include "Json.h"


// Text
#include "Texture.h"
#include "Text.h"

#include "Factory.h"

// Systems
#include "Renderer.h"
#include "Font.h"
#include "Input.h"
#include "Audio.h"
#include "GameTime.h"
#include "ParticleSystem.h"

#include "Game.h"
#include "Actor.h"
#include "Scene.h"

namespace nu {
	class Engine {
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Audio& GetAudio() { return m_audio; }
		Time& GetTime() { return m_time; }
		ParticleSystem& GetParticleSystem() { return m_particleSystem;  }

		Engine(const Engine&) = delete;
		Engine& operator = (const Engine&) = delete;


	private:
		Engine() = default;

		Input m_input;
		Renderer m_renderer;
		Audio m_audio;
		Time m_time;
		ParticleSystem m_particleSystem;
	};
}
