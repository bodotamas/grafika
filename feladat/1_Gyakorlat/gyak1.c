#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846


typedef struct 
{
    double x, y;
} 
Point;


Point rotate(Point p, double angle) 
{
    // Szög radiánban
    double rad = angle * (M_PI / 180.0);
    
    // Forgatás képlete
    Point rotated;
    rotated.x = p.x * cos(rad) - p.y * sin(rad);
    rotated.y = p.x * sin(rad) + p.y * cos(rad);
    
    return rotated;
}

int main() {
    // Téglalap csúcsainak koordinátái
    Point p1 = {0, 0};  // Bal alsó sarok
    Point p2 = {4, 0};  // Jobb alsó sarok
    Point p3 = {4, 3};  // Jobb felső sarok
    Point p4 = {0, 3};  // Bal felső sarok

    // Forgatás szöge (75 fok)
    double angle = 75;

    // Elforgatott pontok kiszámítása
    Point p1_rotated = rotate(p1, angle);
    Point p2_rotated = rotate(p2, angle);
    Point p3_rotated = rotate(p3, angle);
    Point p4_rotated = rotate(p4, angle);

    // Kiírás
    printf("A téglalap elforgatott csúcsai 75 fokkal:\n");
    printf("P1: (%.2f, %.2f)\n", p1_rotated.x, p1_rotated.y);
    printf("P2: (%.2f, %.2f)\n", p2_rotated.x, p2_rotated.y);
    printf("P3: (%.2f, %.2f)\n", p3_rotated.x, p3_rotated.y);
    printf("P4: (%.2f, %.2f)\n", p4_rotated.x, p4_rotated.y);

    return 0;
}
