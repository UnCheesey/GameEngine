#include "pch.h"
#include "Engine.h"
#include "framework.h"

#include <iostream>

// TODO: This is an example of a library function

namespace nu {

	bool Engine::Initialize() {
        m_renderer.Initialize("Game Engine", 1920, 1024);
        m_input.Initialize();
		m_audio.Initialize();
		m_particleSystem.Initialize(5000);
		fe::SetWorkingDirectory("Assets");

		return true;
	}

	void Engine::Shutdown() {
		m_renderer.Shutdown();
		m_input.Shutdown();
		m_audio.Shutdown();
		m_particleSystem.Shutdown();
	}

	void Engine::Update() {
		m_audio.Update();
		m_input.Update();
		m_time.Tick();
		m_particleSystem.Update(m_time.GetDeltaTime());
	}
}
