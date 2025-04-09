#include "scene.h"
#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "assets/models/cube.obj");
    load_model(&(scene->house), "assets/models/cat.obj");
    load_model(&(scene->car), "assets/models/car.obj");  
    load_model(&(scene->tree), "assets/models/tree.obj");  
    scene->texture_id = load_texture("assets/textures/cube.png");

    glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    
    scene->material.ambient.red = 1.0;  
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 0.0;
    scene->material.diffuse.green = 1.0;  
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 1.0; 

    scene->material.shininess = 32.0;  

    scene->house_position.x = 0.0f;
    scene->house_position.y = 0.0f;
    scene->house_position.z = 0.0f;
    
  
    scene->car_position.x = 3.0f;
    scene->car_position.y = 0.0f;
    scene->car_position.z = 0.0f;
    
    scene->tree_position.x = -3.0f;
    scene->tree_position.y = 0.0f;
    scene->tree_position.z = 0.0f;
    
  
    scene->light_position.x = 0.0f;
    scene->light_position.y = 10.0f;
    scene->light_position.z = 10.0f;
}

void set_lighting(float ambient_strength, float diffuse_strength, float specular_strength, int light_mode, const Vector3* light_position)
{

    float ambient_light[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float diffuse_light[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float specular_light[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    
    switch (light_mode)
    {
        case 1:
            ambient_light[0] = ambient_strength;  
            diffuse_light[0] = diffuse_strength;  
            specular_light[0] = specular_strength;  
            break;
        case 2:
            ambient_light[1] = ambient_strength;  
            diffuse_light[1] = diffuse_strength;  
            specular_light[1] = specular_strength; 
            break;
        case 3:
            ambient_light[2] = ambient_strength;  
            diffuse_light[2] = diffuse_strength;  
            specular_light[2] = specular_strength; 
            break;
        case 4:
            ambient_light[3] = ambient_strength;  
            diffuse_light[3] = diffuse_strength;  
            specular_light[3] = specular_strength; 
            break;
    }

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

   
    float position[] = { light_position->x, light_position->y, light_position->z, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void update_scene(Scene* scene)
{
    if (glutKeyIsDown('w')) 
    {
        scene->house_position.y += 0.1f; 
    }
    if (glutKeyIsDown('s')) 
    {
        scene->house_position.y -= 0.1f;  
    }
    if (glutKeyIsDown('a')) 
    {
        scene->house_position.x -= 0.1f;  
    }
    if (glutKeyIsDown('d')) 
    {
        scene->house_position.x += 0.1f;  
    }

  
    static float ambient_strength = 1.0f, diffuse_strength = 1.0f, specular_strength = 1.0f;
    if (glutKeyIsDown('q')) 
    {
        ambient_strength += 0.1f;  
    }
    if (glutKeyIsDown('e')) 
    {
        ambient_strength -= 0.1f; 
    }
    if (glutKeyIsDown('r')) 
    {
        diffuse_strength += 0.1f;
    }
    if (glutKeyIsDown('f'))
    {
        diffuse_strength -= 0.1f;
    }
    if (glutKeyIsDown('t')) 
    {
        specular_strength += 0.1f;
    }
    if (glutKeyIsDown('g')) 
    {
        specular_strength -= 0.1f;
    }

   
    if (glutKeyIsDown('i')) 
    {
        scene->light_position.y += 0.1f;  
    }
    if (glutKeyIsDown('k')) 
    {
        scene->light_position.y -= 0.1f;  
    }
    if (glutKeyIsDown('j')) 
    {
        scene->light_position.x -= 0.1f;  
    }
    if (glutKeyIsDown('l')) 
    {
        scene->light_position.x += 0.1f; 
    }
    if (glutKeyIsDown('u')) 
    {
        scene->light_position.z += 0.1f;  
    }
    if (glutKeyIsDown('o')) 
    {
        scene->light_position.z -= 0.1f; 
    }

    static int light_mode = 1;
    if (glutKeyIsDown('1')) 
    {
        light_mode = 1;  k
    }
    if (glutKeyIsDown('2')) 
    {
        light_mode = 2; 
    }
    if (glutKeyIsDown('3')) 
    {
        light_mode = 3;  
    }
    if (glutKeyIsDown('4')) 
    {
        light_mode = 4;  
    }

    set_lighting(ambient_strength, diffuse_strength, specular_strength, light_mode, &(scene->light_position));
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(1.0f, 1.0f, 1.0f, 1, &(scene->light_position));  
    draw_origin();

    
    static float angle = 0.0f;
    angle += 0.1f;

    glPushMatrix();
    glTranslatef(2.0f, 2.0f, 0.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    draw_model(&(scene->cube));
    glPopMatrix();

   
    glPushMatrix();
    glTranslatef(scene->house_position.x, scene->house_position.y, scene->house_position.z);
    draw_model(&(scene->house));
    glPopMatrix();

    
    glPushMatrix();
    glTranslatef(scene->car_position.x, scene->car_position.y, scene->car_position.z);
    draw_model(&(scene->car));
    glPopMatrix();

  
    glPushMatrix();
    glTranslatef(scene->tree_position.x, scene->tree_position.y, scene->tree_position.z);
    draw_model(&(scene->tree));
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
