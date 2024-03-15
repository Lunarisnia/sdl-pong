#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;

// Global window where we will be rendering to
SDL_Window *globalWindow = NULL;

// The surface contained within the window
SDL_Surface *globalSurface = NULL;

// The surface where to load our hello world
SDL_Surface *globalHelloWorldSurface = NULL;

// Starts up SDL and create a window
bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Initialization failed! SDL_ERROR: %s\n", SDL_GetError());
        success = false;
    } else {
        globalWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (globalWindow == NULL) {
            printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
            success = false;
        } else {
            // Get window Surface
            globalSurface = SDL_GetWindowSurface(globalWindow);
        }
    }
    return success;
}

// Loads Media
bool loadMedia() {
    bool success = true;

    globalHelloWorldSurface = SDL_LoadBMP("../ass.bmp");
    if (globalHelloWorldSurface == NULL) {
        printf("Unable to load image! SDL_ERROR: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

// Frees media and shuts down SDL
void close() {
    // Deallocate surface
    SDL_FreeSurface(globalHelloWorldSurface);
    globalHelloWorldSurface = NULL;

    // Destroy Window
    SDL_DestroyWindow(globalWindow);
    globalWindow = NULL;

    // Quit SDL Subsystem
    SDL_Quit();
}


int main(int argc, char *argv[]) {
    // Unused argc, argv
    (void) argc;
    (void) argv;

    //Initialize SDL
    if (!init()) {
        printf("Failed to initialize\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load img\n");
        } else {
            // Draw the hello world on the main surface
            SDL_BlitSurface(globalHelloWorldSurface, NULL, globalSurface, NULL);
            // Update the surface window
            SDL_UpdateWindowSurface(globalWindow);

            //Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; }}
        }
    }

    // Close SDL
    close();
    return 0;
}
