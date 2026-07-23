// Engine.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "Engine.h"
#include "framework.h"

#include <iostream>

// TODO: This is an example of a library function

namespace nu {

	bool Engine::Initialize() {
        m_renderer.Initialize("Game Engine", 1920, 1024);
        m_input.Initialize();

		return true;
	}

	void Engine::Shutdown() {
		m_input.Shutdown();
		m_renderer.Shutdown();
	}

	void Engine::Update() {
		m_input.Update();
		m_time.Tick();
	}
}
