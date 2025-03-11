#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_COUNT 100

typedef struct 
{
    int r, g, b;
} 
Color;

typedef struct 
{
    int x1, y1;
    int x2, y2;
    Color color;
} Line;

Line lines[MAX_LINE_COUNT];
int lineCount = 0;

void drawLine(Line* line) 
{
    printf("Szakasz %d: (%d, %d) -> (%d, %d), Szín: RGB(%d, %d, %d)\n",
            lineCount + 1, line->x1, line->y1, line->x2, line->y2,
            line->color.r, line->color.g, line->color.b);
}

void handleMouseClick(int x, int y) 
{
    if (lineCount >= MAX_LINE_COUNT) return;

    if (lineCount % 2 == 0) 
    {
        lines[lineCount].x1 = x;
        lines[lineCount].y1 = y;
        lines[lineCount].color.r = rand() % 256;
        lines[lineCount].color.g = rand() % 256;
        lines[lineCount].color.b = rand() % 256;
    } 
    else 
    {
        lines[lineCount].x2 = x;
        lines[lineCount].y2 = y;
        lineCount++;
    }
}

int main() 
{
    int x, y;
    while (1) 
    {
        printf("Adja meg a szakasz (x1 y1 x2 y2) koordinátáit, vagy -1 ha kilép: ");
        scanf("%d %d %d %d", &x, &y, &lines[lineCount].x2, &lines[lineCount].y2);

        if (x == -1) break;
        
        handleMouseClick(x, y);
        
        for (int i = 0; i < lineCount; i++) 
        {
            drawLine(&lines[i]);
        }
    }
    return 0;
}
