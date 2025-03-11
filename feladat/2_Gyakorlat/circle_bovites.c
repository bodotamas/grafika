#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#define MAX_CIRCLE_COUNT 10
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_STEP_COUNT 360

typedef struct 
{
    double x, y;
    double radius;
    SDL_Color color;
} 
Circle;

Circle circles[MAX_CIRCLE_COUNT];
int circleCount = 0;

void set_circle_data(Circle* circle, double x, double y, double radius, SDL_Color color) 
{
    circle->x = x;
    circle->y = y;
    circle->radius = radius;
    circle->color = color;
}

double calc_circle_area(const Circle* circle) 
{
    return circle->radius * circle->radius * M_PI;
}

void draw_circle(SDL_Renderer* renderer, const Circle* circle, int steps) 
{
    int i;
    double angleStep = 2 * M_PI / steps;
    for (i = 0; i < steps; i++) 
    {
        double angle1 = i * angleStep;
        double angle2 = (i + 1) * angleStep;
        int x1 = (int)(circle->x + circle->radius * cos(angle1));
        int y1 = (int)(circle->y + circle->radius * sin(angle1));
        int x2 = (int)(circle->x + circle->radius * cos(angle2));
        int y2 = (int)(circle->y + circle->radius * sin(angle2));
        SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, 255);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

void draw_cross(SDL_Renderer* renderer, const Circle* circle) 
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    SDL_RenderDrawLine(renderer, (int)circle->x - 10, (int)circle->y, (int)circle->x + 10, (int)circle->y);
    SDL_RenderDrawLine(renderer, (int)circle->x, (int)circle->y - 10, (int)circle->x, (int)circle->y + 10);
}

void handle_mouse_click(SDL_Event* event, int* selectedCircleIndex, int* mouseOverCircle) 
{
    int x = event->button.x;
    int y = event->button.y;

    for (int i = 0; i < circleCount; i++) 
    {
        double distance = sqrt(pow(x - circles[i].x, 2) + pow(y - circles[i].y, 2));
        if (distance <= circles[i].radius) 
        {
            *selectedCircleIndex = i;
            *mouseOverCircle = 1;
            return;
        }
    }
    *selectedCircleIndex = -1;
    *mouseOverCircle = 0;
}

void move_circle(Circle* circle, int x, int y) 
{
    circle->x = x;
    circle->y = y;
}

int main() 
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("SDL init hiba: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Kör Rajzoló", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) 
    {
        printf("Aablak létrehozása nem sikerült: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) 
    {
        printf("Renderer létrehozása hiba: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Color colors[] = 
    {
        {255, 0, 0, 255},   // Red
        {0, 255, 0, 255},   // Green
        {0, 0, 255, 255},   // Blue
        {255, 255, 0, 255}, // Yellow
        {0, 255, 255, 255}, // Cyan
        {255, 0, 255, 255}  // Magenta
    };

    set_circle_data(&circles[circleCount++], 200, 200, 50, colors[0]);
    set_circle_data(&circles[circleCount++], 400, 300, 75, colors[1]);

    int running = 1;
    int selectedCircleIndex = -1;
    int mouseOverCircle = 0;
    int mouseX = 0, mouseY = 0;

    while (running) 
    {
        SDL_RenderClear(renderer);

        for (int i = 0; i < circleCount; i++) 
        {
            draw_circle(renderer, &circles[i], 360);
            if (mouseOverCircle && i == selectedCircleIndex) 
            {
                draw_cross(renderer, &circles[i]);
            }
        }

        SDL_RenderPresent(renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) 
            {
                running = 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) 
            {
                handle_mouse_click(&event, &selectedCircleIndex, &mouseOverCircle);
            }
            if (event.type == SDL_MOUSEMOTION) 
            {
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                if (mouseOverCircle && selectedCircleIndex != -1) 
                {
                    move_circle(&circles[selectedCircleIndex], mouseX, mouseY);
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
