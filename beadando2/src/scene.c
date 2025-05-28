#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_models_init_scene(scene);
    load_textures_init_scene(scene);


    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
    scene->brightness = 0.0;

    scene->objectPos = 0.0f;
    scene->direction = 1.0f;

    scene->guide_flag = false;

    scene->diffuse[0] = 1.0f;
    scene->diffuse[1] = 1.0f;
    scene->diffuse[2] = 1.0f;
    }

void load_models_init_scene(Scene *scene) {

    load_model(&(scene->terrain), "assets/models/terrain.obj");
    load_model(&(scene->house), "assets/models/house3.obj");
    load_model(&(scene->fireplace), "assets/models/fireplace3.obj");
    load_model(&(scene->raptor),"assets/models/raptor.obj");
    load_model(&(scene->hare),"assets/models/hare.obj");
}

void load_textures_init_scene(Scene *scene) {
    scene->skybox_textures[SKYBOX_RIGHT] = load_texture("assets/textures/skybox/right.jpg");
    scene->skybox_textures[SKYBOX_LEFT] = load_texture("assets/textures/skybox/left.jpg");
    scene->skybox_textures[SKYBOX_TOP] = load_texture("assets/textures/skybox/top.jpg");
    scene->skybox_textures[SKYBOX_BOTTOM] = load_texture("assets/textures/skybox/bottom.jpg");
    scene->skybox_textures[SKYBOX_FRONT] = load_texture("assets/textures/skybox/front.jpg");
    scene->skybox_textures[SKYBOX_BACK] = load_texture("assets/textures/skybox/back.jpg");
    
    for (int i = 0; i < 6; ++i) {
        if (scene->skybox_textures[i] == 0) {
            printf("[ERROR] Skybox face texture %d failed to load.\n", i);
        }
    }
    scene->terrain_texture = load_texture("assets/textures/grass2.jpg");
    scene->house_texture = load_texture("assets/textures/wood.jpg");
    scene->fireplace_texture = load_texture("assets/textures/brick.jpg");
    scene->guide_texture = load_texture("assets/textures/guide2.png");
    scene->raptor_texture = load_texture("assets/textures/raptor.png");
    scene->hare_texture = load_texture("assets/textures/hare.jpg");
}

void draw_skybox_cube(const Scene* scene) {
    GLboolean fog_was_enabled = glIsEnabled(GL_FOG);
    if (fog_was_enabled) {
        glDisable(GL_FOG);
    }
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    float size = 500.0f;


    // Top face
    glBindTexture(GL_TEXTURE_2D, scene->skybox_textures[SKYBOX_TOP]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( size, -size,  size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size,  size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size,  size,  size);
    glEnd();

    // Bottom face
    glBindTexture(GL_TEXTURE_2D, scene->skybox_textures[SKYBOX_BOTTOM]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size, -size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( size,  size, -size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, -size, -size);
    glEnd();

    // Back face
    glBindTexture(GL_TEXTURE_2D, scene->skybox_textures[SKYBOX_BACK]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size,  size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-size,  size,  size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size, -size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, -size, -size);
    glEnd();

    // Front face
    glBindTexture(GL_TEXTURE_2D, scene->skybox_textures[SKYBOX_FRONT]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size,  size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( size, -size, -size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size, -size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( size,  size,  size);
    glEnd();

    // Right face
    glBindTexture(GL_TEXTURE_2D, scene->skybox_textures[SKYBOX_RIGHT]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, -size, -size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( size, -size, -size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);
    glEnd();

    // Left face
    glBindTexture(GL_TEXTURE_2D, scene->skybox_textures[SKYBOX_LEFT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size,  size,  size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size,  size,  size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);
    glEnd();

    if (fog_was_enabled) {
        glEnable(GL_FOG);
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void load_objects(Scene scene) {
    
    glEnable(GL_COLOR_MATERIAL);

    //Raptor betöltése
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene.raptor_texture);
    glRotatef(90.0f,0.0f,0.0f,1.0f);
    glScalef(6.0f, 6.0f, 6.0f);
    glTranslatef(scene.objectPos, 4.06f, -0.5f);
    draw_model(&(scene.raptor));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene.hare_texture);
    glScalef(0.25f, 0.25f, 0.25f);
    glTranslatef(scene.objectPos, -5.0f, -8.0f);
    draw_model(&(scene.hare));
    glPopMatrix();

    //Ház betöltése
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene.house_texture);
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    glRotatef(90.0f,0.0f,0.0f,1.0f);
    glScalef(6.0f, 6.0f, 6.0f);
    glTranslatef(1.0f, -0.1f, 3.5f);
    draw_model(&(scene.house));
    glPopMatrix();

    // Kandalló betöltése
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,scene.fireplace_texture);
    glRotatef(270.0f,0.0f,1.0f,0.0f);
    glRotatef(90.0f,0.0f,0.0f,1.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(12.5f,5.0f,-46.5f);
    draw_model(&(scene.fireplace));
    glPopMatrix();

    //aljzat betöltése
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene.terrain_texture);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -3.5f, 0.0f);
    glScalef(4.0f, 4.0f, 4.0f);
    draw_model(&(scene.terrain));
    glPopMatrix();
    
}

void set_lighting(const Scene *scene)
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = {scene->diffuse[0], scene->diffuse[1], scene->diffuse[2], 1.0f};
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 50.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, double time)
{
    scene->objectPos += 0.1f * scene->direction;

    if (scene->objectPos > 5.0f || scene->objectPos < -5.0f)
    {
        scene->direction *= -1.0f;
    }
    

    scene->diffuse[0] += scene->brightness * (float) time;
    scene->diffuse[1] += scene->brightness * (float) time;
    scene->diffuse[2] += scene->brightness * (float) time;
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(scene);
    draw_skybox_cube(scene);
    load_objects(*scene);
    draw_water();
    // draw_origin();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100);

    glEnd();
}
void show_guide(GLuint texture) {
    glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT | GL_TRANSFORM_BIT | GL_POLYGON_BIT);

    GLint previous_matrix_mode;
    glGetIntegerv(GL_MATRIX_MODE, &previous_matrix_mode);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-2.5, 2.5, -2.0, 2.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    glEnable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3d(-2.5f, 2.0f, -3.0f); // Use a consistent Z
    glTexCoord2f(1.0f, 0.0f); glVertex3d(2.5f, 2.0f, -3.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3d(2.5f, -2.0f, -3.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3d(-2.5f, -2.0f, -3.0f);
    glEnd();

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(previous_matrix_mode);

    glPopAttrib();
}

void setBrightness(Scene *scene, float brightness) {
    scene->brightness = brightness;
}

void draw_water(void){
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.4f, 0.8f, 0.5f);

    glBegin(GL_QUADS);
    glVertex3f(-62.0f, 57.0f, -5.0f);
    glVertex3f(-62.0f, 22.0f, -5.0f);
    glVertex3f(-22.0f, 22.0f, -5.0f);
    glVertex3f(-22.0f, 65.0f, -5.0f);
    glEnd();

    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}