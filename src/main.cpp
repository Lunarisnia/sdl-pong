#include <iostream>
#include <string>
#include <SDL.h>

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;

// Key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL,
};

// Global window where we will be rendering to
SDL_Window *globalWindow = NULL;

// The surface contained within the window
SDL_Surface *globalSurface = NULL;

// The surface that will be shown if everything else's fail
SDL_Surface *lastBastionSurface = NULL;

// Surface for close splash
SDL_Surface *closeSplashSurface = NULL;

// The Images that correspond to each keypress
SDL_Surface *globalKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// Current Displayed Image
SDL_Surface *globalCurrentSurface = NULL;

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

SDL_Surface *loadSurface(std::string path) {
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image! SDL_ERROR: %s\n", SDL_GetError());
        //TODO: Should Raise Some sort of Error Here
    }

    return loadedSurface;
}

// Loads Media
bool loadMedia() {
    bool success = true;

    lastBastionSurface = loadSurface("../images/ass.bmp");
    if (lastBastionSurface == NULL) {
        success = false;
    }

    closeSplashSurface = loadSurface("../images/closeSplash.bmp");
    if (closeSplashSurface == NULL) {
        success = false;
    }

    globalKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("../images/hemlo.bmp");
    if (globalKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        success = false;
    }

    globalKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("../images/up.bmp");
    if (globalKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        success = false;
    }

    globalKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("../images/down.bmp");
    if (globalKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        success = false;
    }

    globalKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("../images/left.bmp");
    if (globalKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        success = false;
    }

    globalKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("../images/right.bmp");
    if (globalKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        success = false;
    }

    return success;
}

// Frees media and shuts down SDL
void close() {
    // Deallocate surface
    SDL_FreeSurface(lastBastionSurface);
    lastBastionSurface = NULL;

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
            // Event Handler
            SDL_Event e;

            // Main Loop Flag
            bool quit = false;

            // Set the default current surface
            globalCurrentSurface = globalKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            // Draw the default screen on surface
            SDL_BlitSurface(globalCurrentSurface, NULL, globalSurface, NULL);
            // Update the surface window
            SDL_UpdateWindowSurface(globalWindow);

            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    // User requests to quit the game
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    // User Presses a key
                    if (e.type == SDL_KEYDOWN) {
                        // Select surfaces based on key press
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                globalCurrentSurface = globalKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                                break;

                            case SDLK_DOWN:
                                globalCurrentSurface = globalKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                                break;

                            case SDLK_LEFT:
                                globalCurrentSurface = globalKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                                break;

                            case SDLK_RIGHT:
                                globalCurrentSurface = globalKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                                break;

                            default:
                                globalCurrentSurface = globalKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                                break;
                        }

                        // Render the surface in the back render
                        SDL_BlitSurface(globalCurrentSurface, NULL, globalSurface, NULL);

                        // Update the screen
                        SDL_UpdateWindowSurface(globalWindow);
                    }
                }
            }
            // Hacky way to keep the window from closing
//            while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; }}

            // Show a splash before closing
            SDL_BlitSurface(closeSplashSurface, NULL, globalSurface, NULL);

            // Update the surface window
            SDL_UpdateWindowSurface(globalWindow);
        }
    }

    // Close SDL
    close();
    return 0;
}
