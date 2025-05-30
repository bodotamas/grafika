#include "scene.h"
#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "assets/models/cube.obj");
    load_model(&(scene->house), "assets/models/cat.obj");
    scene->texture_id = load_texture("assets/textures/cube.png");

    glBindTexture(GL_TEXTURE_2D, scene->texture_id);

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

 
    scene->house_position.x = 0.0f;
    scene->house_position.y = 0.0f;
    scene->house_position.z = 0.0f;
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

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

void update_scene(Scene* scene)
{
  
    if (glutKeyIsDown('w')) {
        scene->house_position.y += 0.1f;  // Fel
    }
    if (glutKeyIsDown('s')) {
        scene->house_position.y -= 0.1f;  // Le
    }
    if (glutKeyIsDown('a')) {
        scene->house_position.x -= 0.1f;  // Balra
    }
    if (glutKeyIsDown('d')) {
        scene->house_position.x += 0.1f;  // Jobbra
    }
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();

    // Kocka forgatása
    static float angle = 0.0f;
    angle += 0.1f;

    glPushMatrix();  
    glTranslatef(2.0f, 2.0f, 0.0f);  
    glRotatef(angle, 0.0f, 1.0f, 0.0f);  
    draw_model(&(scene->cube));  
    glPopMatrix();

    // Ház pozíciójának alkalmazása
    glPushMatrix();
    glTranslatef(scene->house_position.x, scene->house_position.y, scene->house_position.z); 
    draw_model(&(scene->house));  
    glPopMatrix();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}
