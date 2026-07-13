#pragma once

#include <SDL3/SDL.h>

namespace nu
{
	class Renderer
	{
	public:
		bool Initialize(const char* name, int width, int height);
		void Shutdown();

		void Clear() const;
		void Present() const;

		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) const;
		void SetColor(float r, float g, float b, float a = 1.0f) const;

		void DrawPoint(float x, float y) const;
		void DrawLine(float xStart, float yStart, float xEnd, float yEnd) const;
		void DrawFillRect(float x, float y, float w, float h) const;
		void DrawRect(float x, float y, float w, float h) const;

		int GetWidth() const {
			return m_width;
		}

		int GetHeight() const {
			return m_height;
		}

	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

		int m_width = 0;
		int m_height = 0;
	};
}