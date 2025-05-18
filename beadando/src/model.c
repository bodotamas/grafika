#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_BUFFER_SIZE 1024

int count_tokens(const char* text)
{
    int i = 0, is_token = 0, count = 0;
    while (text[i] != 0) {
        if (!is_token && text[i] != ' ') {
            ++count;
            is_token = 1;
        } else if (is_token && text[i] == ' ') {
            is_token = 0;
        }
        ++i;
    }
    return count;
}

void extract_tokens(const char* text, struct TokenArray* token_array)
{
    int i = 0, token_length;
    char* token;
    int n_tokens = count_tokens(text);
    token_array->tokens = (char**)malloc(n_tokens * sizeof(char*));
    token_array->n_tokens = 0;
    while (text[i] != 0) {
        if (text[i] != ' ') {
            token_length = calc_token_length(text, i);
            token = copy_token(text, i, token_length);
            insert_token(token, token_array);
            i += token_length;
        } else {
            ++i;
        }
    }
}

char* copy_token(const char* text, int offset, int length)
{
    char* token = (char*)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; ++i) {
        token[i] = text[offset + i];
    }
    token[length] = 0;
    return token;
}

void insert_token(const char* token, struct TokenArray* token_array)
{
    token_array->tokens[token_array->n_tokens++] = (char*)token;
}

int calc_token_length(const char* text, int start_index)
{
    int end_index = start_index;
    while (text[end_index] != 0 && text[end_index] != ' ') {
        ++end_index;
    }
    return end_index - start_index;
}

void free_tokens(struct TokenArray* token_array)
{
    for (int i = 0; i < token_array->n_tokens; ++i) {
        free(token_array->tokens[i]);
    }
    free(token_array->tokens);
}

void print_model_info(const struct Model* model)
{
    printf("Vertices: %d\n", model->n_vertices);
    printf("Texture vertices: %d\n", model->n_texture_vertices);
    printf("Normals: %d\n", model->n_normals);
    printf("Triangles: %d\n", model->n_triangles);
    printf("Quads: %d\n", model->n_quads);
}

void free_model(struct Model* model)
{
    free(model->vertices);
    free(model->texture_vertices);
    free(model->normals);
    free(model->triangles);
    free(model->quads);
}

void count_elements(FILE* file, struct Model* model)
{
    char line[LINE_BUFFER_SIZE];
    init_model_counters(model);
    while (fgets(line, LINE_BUFFER_SIZE, file) != NULL) {
        clear_comment(line);
        count_element_in_line(line, model);
    }
}

void read_elements(FILE* file, struct Model* model)
{
    char line[LINE_BUFFER_SIZE];
    init_model_counters(model);
    model->n_vertices = 1;
    model->n_texture_vertices = 1;
    model->n_normals = 1;
    fseek(file, 0, SEEK_SET);
    while (fgets(line, LINE_BUFFER_SIZE, file) != NULL) {
        clear_comment(line);
        read_element_from_line(line, model);
    }
}

void init_model_counters(Model* model)
{
    model->n_vertices = 0;
    model->n_texture_vertices = 0;
    model->n_normals = 0;
    model->n_triangles = 0;
    model->n_quads = 0;
}

void clear_comment(char* line)
{
    int i = 0;
    while (line[i] != 0 && line[i] != '#' && line[i] != 0x0D && line[i] != 0x0A) ++i;
    while (line[i] != 0) line[i++] = ' ';
}

void count_element_in_line(const char* line, Model* model)
{
    struct TokenArray token_array;
    extract_tokens(line, &token_array);
    if (token_array.n_tokens > 0) {
        char* first_token = token_array.tokens[0];
        if (strcmp(first_token, "v") == 0) ++model->n_vertices;
        else if (strcmp(first_token, "vt") == 0) ++model->n_texture_vertices;
        else if (strcmp(first_token, "vn") == 0) ++model->n_normals;
        else if (strcmp(first_token, "f") == 0) {
            if (token_array.n_tokens == 4) ++model->n_triangles;
            else if (token_array.n_tokens == 5) ++model->n_quads;
            else printf("WARN: Invalid number of face elements! %d\n", token_array.n_tokens);
        }
    }
    free_tokens(&token_array);
}

void read_element_from_line(const char* line, Model* model)
{
    struct TokenArray token_array;
    extract_tokens(line, &token_array);
    if (token_array.n_tokens > 0) {
        char* first_token = token_array.tokens[0];
        if (strcmp(first_token, "v") == 0)
            read_vertex(&token_array, &model->vertices[model->n_vertices++]);
        else if (strcmp(first_token, "vt") == 0)
            read_texture_vertex(&token_array, &model->texture_vertices[model->n_texture_vertices++]);
        else if (strcmp(first_token, "vn") == 0)
            read_normal(&token_array, &model->normals[model->n_normals++]);
        else if (strcmp(first_token, "f") == 0) {
            if (token_array.n_tokens == 4) {
                Triangle* tri = &model->triangles[model->n_triangles];
                read_triangle(&token_array, tri);
                if (!is_valid_triangle(tri, model)) printf("line: '%s'\n", line);
                ++model->n_triangles;
            } else if (token_array.n_tokens == 5) {
                Quad* quad = &model->quads[model->n_quads];
                read_quad(&token_array, quad);
                if (!is_valid_quad(quad, model)) printf("line: '%s'\n", line);
                ++model->n_quads;
            }
        }
    }
    free_tokens(&token_array);
}

void create_arrays(struct Model* model)
{
    model->vertices = (Vertex*)malloc((model->n_vertices + 1) * sizeof(Vertex));
    model->texture_vertices = (TextureVertex*)malloc((model->n_texture_vertices + 1) * sizeof(TextureVertex));
    model->normals = (Vertex*)malloc((model->n_normals + 1) * sizeof(Vertex));
    model->triangles = (Triangle*)malloc(model->n_triangles * sizeof(Triangle));
    model->quads = (Quad*)malloc(model->n_quads * sizeof(Quad));
}

void read_vertex(const struct TokenArray* token_array, Vertex* vertex)
{
    vertex->x = atof(token_array->tokens[1]);
    vertex->y = atof(token_array->tokens[2]);
    vertex->z = atof(token_array->tokens[3]);
}

void read_texture_vertex(const struct TokenArray* token_array, TextureVertex* tex)
{
    tex->u = atof(token_array->tokens[1]);
    tex->v = atof(token_array->tokens[2]);
}

void read_normal(const struct TokenArray* token_array, Vertex* normal)
{
    normal->x = atof(token_array->tokens[1]);
    normal->y = atof(token_array->tokens[2]);
    normal->z = atof(token_array->tokens[3]);
}

void read_triangle(const struct TokenArray* token_array, Triangle* triangle)
{
    for (int i = 0; i < 3; ++i)
        read_face_point(token_array->tokens[i + 1], &triangle->points[i]);
}

void read_quad(const struct TokenArray* token_array, Quad* quad)
{
    for (int i = 0; i < 4; ++i)
        read_face_point(token_array->tokens[i + 1], &quad->points[i]);
}

void read_face_point(const char* text, FacePoint* face_point)
{
    int delimiter_count = count_face_delimiters(text);
    const char* token = text;
    int length;

    if (delimiter_count == 0) {
        face_point->vertex_index = read_next_index(token, &length);
        face_point->texture_index = -1;
        face_point->normal_index = -1;
    } else if (delimiter_count == 1) {
        face_point->vertex_index = read_next_index(token, &length);
        token += length;
        face_point->texture_index = read_next_index(token, &length);
        face_point->normal_index = -1;
    } else if (delimiter_count == 2) {
        face_point->vertex_index = read_next_index(token, &length);
        token += length;
        face_point->texture_index = read_next_index(token, &length);
        token += length;
        face_point->normal_index = read_next_index(token, &length);
    } else {
        printf("ERROR: Invalid face token! '%s'\n", text);
    }
}

int count_face_delimiters(const char* text)
{
    int count = 0;
    for (int i = 0; text[i] != 0; ++i)
        if (text[i] == '/') ++count;
    return count;
}

int read_next_index(const char* text, int* length)
{
    int i = 0, j = 0;
    char buffer[32];

    while (text[i] != 0 && !isdigit(text[i])) ++i;
    if (text[i] == 0) return -1;

    while (text[i] != 0 && isdigit(text[i])) {
        buffer[j++] = text[i++];
    }
    buffer[j] = 0;
    *length = i;
    return atoi(buffer);
}

int is_valid_triangle(const Triangle* triangle, const Model* model)
{
    for (int k = 0; k < 3; ++k) {
        if (triangle->points[k].vertex_index >= model->n_vertices) return 0;
        if (triangle->points[k].texture_index >= model->n_texture_vertices) return 0;
        if (triangle->points[k].normal_index >= model->n_normals) return 0;
    }
    return 1;
}

int is_valid_quad(const Quad* quad, const Model* model)
{
    for (int k = 0; k < 4; ++k) {
        if (quad->points[k].vertex_index < 0 || quad->points[k].vertex_index >= model->n_vertices) return 0;
        if (quad->points[k].texture_index < 0 || quad->points[k].texture_index >= model->n_texture_vertices) return 0;
        if (quad->points[k].normal_index < 0 || quad->points[k].normal_index >= model->n_normals) return 0;
    }
    return 1;
}

void print_bounding_box(const Model* model)
{
    if (model->n_vertices == 0) return;
    double min_x = model->vertices[0].x, max_x = min_x;
    double min_y = model->vertices[0].y, max_y = min_y;
    double min_z = model->vertices[0].z, max_z = min_z;

    for (int i = 1; i < model->n_vertices; ++i) {
        double x = model->vertices[i].x;
        double y = model->vertices[i].y;
        double z = model->vertices[i].z;
        if (x < min_x) min_x = x; else if (x > max_x) max_x = x;
        if (y < min_y) min_y = y; else if (y > max_y) max_y = y;
        if (z < min_z) min_z = z; else if (z > max_z) max_z = z;
    }

    printf("Bounding box:\n");
    printf("x in [%.2lf, %.2lf]\n", min_x, max_x);
    printf("y in [%.2lf, %.2lf]\n", min_y, max_y);
    printf("z in [%.2lf, %.2lf]\n", min_z, max_z);
}

void scale_model(Model* model, double sx, double sy, double sz)
{
    for (int i = 0; i < model->n_vertices; ++i) {
        model->vertices[i].x *= sx;
        model->vertices[i].y *= sy;
        model->vertices[i].z *= sz;
    }
}

int load_model(const char* filename, Model* model)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("ERROR: Cannot open model file %s\n", filename);
        return 0;
    }
    count_elements(file, model);
    create_arrays(model);
    read_elements(file, model);
    fclose(file);
    return 1;
}

void init_entities(World* world)
{
    world->skybox.texture = load_texture("assets/textures/sky.png");

    load_model("assets/models/geoid.obj", &world->sun.model);
    world->sun.texture = load_texture("assets/textures/sun.png");
    scale_model(&world->sun.model, 1.7, 1.7, 1.7);

    load_model("assets/models/deathstar.obj", &world->deathstar.model);
    world->deathstar.texture = load_texture("assets/textures/deathstar.png");
    scale_model(&world->deathstar.model, 0.001, 0.001, 0.001);

    load_model("assets/models/geoid.obj", &world->earth.model);
    world->earth.texture = load_texture("assets/textures/earth.png");
    scale_model(&world->earth.model, 0.4, 0.4, 0.4);

    load_model("assets/models/falcon.obj", &world->falcon.model);
    world->falcon.texture = load_texture("assets/textures/falcon.png");
    scale_model(&world->falcon.model, 0.3, 0.3, 0.3);

    load_model("assets/models/mars.obj", &world->mars.model);
    world->mars.texture = load_texture("assets/textures/mars.png");
    scale_model(&world->mars.model, 20.0, 20.0, 20.0);

    load_model("assets/models/mercury.obj", &world->mercury.model);
    world->mercury.texture = load_texture("assets/textures/mercury.png");
    scale_model(&world->mercury.model, 15.0, 15.0, 15.0);

    load_model("assets/models/jupiter.obj", &world->jupiter.model);
    world->jupiter.texture = load_texture("assets/textures/jupiter.png");
    scale_model(&world->jupiter.model, 13.0, 13.0, 13.0);

    load_model("assets/models/saturn.obj", &world->saturn.model);
    world->saturn.texture = load_texture("assets/textures/saturnbody.png");
    scale_model(&world->saturn.model, 18.0, 18.0, 18.0);
}
