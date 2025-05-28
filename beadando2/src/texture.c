#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

GLuint load_texture(char* filename) {
    SDL_Surface* surface;
    GLuint texture_name = 0;

    printf("Attempting to load texture: %s\n", filename);
    surface = IMG_Load(filename);

    if (surface == NULL) {
        printf("[ERROR] Failed to load texture '%s': %s\n", filename, IMG_GetError());
        return 0;
    }
    printf("Successfully loaded surface for texture: %s (w:%d, h:%d)\n", filename, surface->w, surface->h);


    glGenTextures(1, &texture_name);
    if (texture_name == 0) {
        printf("[ERROR] glGenTextures failed for '%s'\n", filename);
        SDL_FreeSurface(surface);
        return 0;
    }

    glBindTexture(GL_TEXTURE_2D, texture_name);
    GLenum format = GL_RGB;
    if (surface->format->BytesPerPixel == 4) {
        format = GL_RGBA;
    }


    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);

    if (texture_name != 0) {
        printf("Successfully created OpenGL texture for: %s (ID: %u)\n", filename, texture_name);
    }
    return texture_name;
}