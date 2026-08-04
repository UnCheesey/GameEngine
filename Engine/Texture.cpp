#include "pch.h"
#include "Texture.h"

#include "Renderer.h"
#include <iostream>

namespace nu {

    Texture::~Texture()
    {
        // if texture exists, destroy texture
        if (m_texture) SDL_DestroyTexture(m_texture);
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        // load image onto surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

        SDL_DestroySurface(surface);
        if (!m_texture)
        {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        return true;
    }
        
    Vector2 Texture::GetSize() {
        Vector2 v;
        SDL_GetTextureSize(m_texture, &v.x, &v.y);
        return v;
    }
}
