#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model cube;
    Model column;
    Model terrain;
    Model roof;
    Model house;
    Model fireplace;
    Model hare;
    Model raptor;
    Material material;
    GLuint skybox_texture;
    GLuint column_texture;
    GLuint terrain_texture;
    GLuint guide_texture;
    GLuint cube_texture;
    GLuint roof_texture;
    GLuint house_texture;
    GLuint fireplace_texture;
    GLuint hare_texture;
    GLuint raptor_texture;
    float diffuse[3];
    float brightness;
    float objectPos;
    float direction;
    bool guide_flag;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Set the scene's brightness
 */
void setBrightness(Scene *scene, float brightness);

/**
 * Load skybox
 */
void load_skybox(Scene scene);

/**
 * Load models for init_scene function
 */
void load_models_init_scene(Scene *scene);

/**
 * Load textures for init_scene function
 */
void load_textures_init_scene(Scene *scene);

/**
 * Load objects
 */
void load_objects(Scene scene);

/**
 * Open a guide which contain the keyboard settings
 */
void show_guide(GLuint texture);

/**
 * Draw water in the corner
 */
void draw_water();

#endif /* SCENE_H */
