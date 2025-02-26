#include "scene.h"

#include <GL/gl.h>

void init_scene(Scene* scene)
{
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    draw_origin();
glBegin(GL_QUADS);

glColor3f(1, 0, 0);
glVertex3f(0, 0, 0);
glVertex3f(0, 0, 1);
glVertex3f(1, 0, 1);
glVertex3f(1, 0, 0);

glColor3f(0, 1, 0);
glVertex3f(0, 0, 0);
glVertex3f(0, 0, 1);
glVertex3f(1, 0, 1);
glVertex3f(1, 0, 0);

glEnd();

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

void render_scene(const Scene* scene)
{
    draw_origin();
    draw_squares();
    draw_triangle();
    draw_sphere();
    draw_cylinder_and_cone();
}

void draw_squares()
{
    glBegin(GL_QUADS);
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            if ((i + j) % 2 == 0)
                glColor3f(0.5, 0.5, 0.5);  
            else
                glColor3f(0.0, 0.0, 0.0);  

            glVertex3f(i, j, 0);
            glVertex3f(i + 1, j, 0);
            glVertex3f(i + 1, j + 1, 0);
            glVertex3f(i, j + 1, 0);
        }
    }
    glEnd();
}

void draw_triangle()
{
    glBegin(GL_TRIANGLES);
    
    glColor3f(1.0, 1.0, 0.0);  
    glVertex3f(0.0, 0.0, 0.0);
    
    glColor3f(0.0, 1.0, 1.0);  
    glVertex3f(1.0, 0.0, 0.0);
    
    glColor3f(1.0, 0.0, 1.0);  
    glVertex3f(0.5, 1.0, 0.0);
    
    glEnd();
}

void draw_sphere()
{
    static GLfloat angle = 0.0;

    glPushMatrix();
    glRotatef(angle, 1.0, 0.0, 0.0);
    glColor3f(0.5, 0.5, 0.5);  
    glutSolidSphere(0.5, 10, 10);  
    glPopMatrix();

    angle += 0.1;  
}

void draw_cylinder_and_cone()
{
    
    glColor3f(1.0, 0.0, 0.0);  
    glPushMatrix();
    glTranslatef(1.5, 0.0, 0.0);
    GLUquadricObj* cyl = gluNewQuadric();
    gluCylinder(cyl, 0.5, 0.5, 1.0, 10, 10);  
    glPopMatrix();

    
    glColor3f(0.0, 1.0, 0.0);  
    glPushMatrix();
    glTranslatef(-1.5, 0.0, 0.0);
    gluCylinder(cyl, 0.0, 0.5, 1.0, 10, 10);  
    glPopMatrix();
}

