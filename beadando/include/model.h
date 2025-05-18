#ifndef MODEL_H_
#define MODEL_H_

#include <stdio.h>
#include <ctype.h>

#define INVALID_VERTEX_INDEX -1

struct TokenArray {
    char** tokens;
    int n_tokens;
};

struct Vertex {
    double x, y, z;
};

struct TextureVertex {
    double u, v;
};

struct FacePoint {
    int vertex_index;
    int texture_index;
    int normal_index;
};

struct Triangle {
    struct FacePoint points[3];
};

struct Quad {
    struct FacePoint points[4];
};

typedef struct Model {
    int n_vertices;
    int n_texture_vertices;
    int n_normals;
    int n_triangles;
    int n_quads;
    struct Vertex* vertices;
    struct TextureVertex* texture_vertices;
    struct Vertex* normals;
    struct Triangle* triangles;
    struct Quad* quads;
} Model;

typedef struct {
    Model model;
    int texture;
    float material_ambient[4];
} Entity;

typedef struct {
    Entity skybox;
    Entity earth;
    Entity sun;
    Entity deathstar;
    Entity falcon;
    Entity mars;
    Entity mercury;
    Entity jupiter;
    Entity saturn;
} World;

int count_tokens(const char* text);
int calc_token_length(const char* text, int start_index);
char* copy_token(const char* text, int offset, int length);
void insert_token(const char* token, struct TokenArray* token_array);
void extract_tokens(const char* text, struct TokenArray* token_array);
void free_tokens(struct TokenArray* token_array);
int load_model(const char* filename, struct Model* model);
void print_model_info(const struct Model* model);
void free_model(struct Model* model);
void count_elements(FILE* file, struct Model* model);
void read_elements(FILE* file, struct Model* model);
void init_model_counters(struct Model* model);
void clear_comment(char* line);
void count_element_in_line(const char* line, struct Model* model);
void read_element_from_line(const char* line, struct Model* model);
void create_arrays(struct Model* model);
void read_vertex(const struct TokenArray* token_array, struct Vertex* vertex);
void read_texture_vertex(const struct TokenArray* token_array, struct TextureVertex* texture_vertex);
void read_normal(const struct TokenArray* token_array, struct Vertex* normal);
void read_triangle(const struct TokenArray* token_array, struct Triangle* triangle);
void read_quad(const struct TokenArray* token_array, struct Quad* quad);
void read_face_point(const char* text, struct FacePoint* face_point);
int count_face_delimiters(const char* text);
int read_next_index(const char* text, int* length);
int is_valid_triangle(const struct Triangle* triangle, const struct Model* model);
int is_valid_quad(const struct Quad* quad, const struct Model* model);
void print_bounding_box(const struct Model* model);
void scale_model(struct Model* model, double sx, double sy, double sz);
void init_entities(World* world);

typedef struct Vertex Vertex;
typedef struct TextureVertex TextureVertex;
typedef struct Triangle Triangle;
typedef struct Quad Quad;
typedef struct FacePoint FacePoint;

#endif // MODEL_H_
