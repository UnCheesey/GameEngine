#pragma once

#include <SDL3/SDL.h>

namespace nu
{
	class Renderer
	{
	public:
		bool Initialize(const char* name, int width, int height);

		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

		void Clear();
		void Present();

		void DrawPoint(float x, float y);
		void DrawFillRect(float x, float y, float w, float h);
		void DrawRect(float x, float y, float w, float h);

		void Shutdown();

	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
	};
}