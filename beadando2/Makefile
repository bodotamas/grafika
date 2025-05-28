APP_SRCS = src/app.c src/camera.c src/scene.c src/texture.c src/utils.c
OBJ_LOADER_SRCS = src/obj/model.c src/obj/load.c src/obj/draw.c

INCLUDE_PATHS = -Iinclude 

CFLAGS = -Wall -Wextra -Wpedantic $(INCLUDE_PATHS)

all:
	@echo "--- Compiling for Windows (all) ---"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "APP_SRCS: $(APP_SRCS)"
	@echo "OBJ_LOADER_SRCS: $(OBJ_LOADER_SRCS)"
	gcc $(CFLAGS) src/main.c $(APP_SRCS) $(OBJ_LOADER_SRCS) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lm -o fahaz.exe
	@echo "--- Windows (all) build finished ---"

linux:
	@echo "--- Compiling for Linux ---"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "APP_SRCS: $(APP_SRCS)"
	@echo "OBJ_LOADER_SRCS: $(OBJ_LOADER_SRCS)"
	gcc $(CFLAGS) src/main.c $(APP_SRCS) $(OBJ_LOADER_SRCS) -lSDL2 -lSDL2_image -lGL -lm -o fahaz
	@echo "--- Linux build finished ---"

clean:
	@echo "--- Cleaning ---"
	rm -f fahaz.exe fahaz *.o src/obj/*.o
	@echo "--- Clean finished ---"