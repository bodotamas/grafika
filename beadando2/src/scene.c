#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

#include<GL/glu.h>
#include<math.h>


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
    scene->skybox_texture = load_texture("assets/textures/skybox/skybox.png");
    scene->terrain_texture = load_texture("assets/textures/grass2.jpg");
    scene->house_texture = load_texture("assets/textures/wood.jpg");
    scene->fireplace_texture = load_texture("assets/textures/brick.jpg");
    scene->guide_texture = load_texture("assets/textures/guide2.png");
    scene->raptor_texture = load_texture("assets/textures/raptor.png");
    scene->hare_texture = load_texture("assets/textures/hare.jpg");
}

void load_skybox(Scene scene) {
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, scene.skybox_texture);

    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;
    int n_slices, n_stacks;
    double radius;
    int i, k;
    n_slices = 15;
    n_stacks = 15;
    radius = 70;

    glPushMatrix();

    glScaled(radius, radius, radius);

    glColor3f(1, 1, 1);

    glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double) i / n_stacks;
        v2 = (double) (i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k) {
            u = (double) k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1) - 0.25;
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2) - 0.25;
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();

    glPopMatrix();

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
    load_skybox(*scene);
    load_objects(*scene);
    draw_water();
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
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-2.5f, 2.0f, -3.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(2.5f, 2.0f, -3.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(2.5f, -2.0f, -3.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-2.5f, -2.0f, -3.0f);
    glEnd();


    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

}

void setBrightness(Scene *scene, float brightness) {
    scene->brightness = brightness;
}

void draw_water(void){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.4f, 0.8f, 0.5f);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-62.0f, 57.0f, -5.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-62.0f, 22.0f, -5.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-22.0f, 22.0f, -5.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-22.0f, 65.0f, -5.0f);
    glEnd();

    glBlendFunc(GL_ONE,GL_ZERO);
    glDisable(GL_BLEND);
}
