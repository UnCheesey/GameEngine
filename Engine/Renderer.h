#pragma once

#include <SDL3/SDL.h>

namespace nu
{
	class Renderer
	{
	public:
		bool Initialize(const char* name, int width, int height);

		void Clear();
		void Present();

		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		void SetColor(float r, float g, float b, float a = 1.0f);

		void DrawPoint(float x, float y);
		void DrawLine(float xStart, float yStart, float xEnd, float yEnd);
		void DrawFillRect(float x, float y, float w, float h);
		void DrawRect(float x, float y, float w, float h);

		void Shutdown();

	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
	};
}