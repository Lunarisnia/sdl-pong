#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;

// Key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_SPACE,
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

// Global Renderer
SDL_Renderer *globalRenderer = NULL;

// Global Texture
SDL_Texture *globalTexture = NULL;

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
            // Create renderer for window
            globalRenderer = SDL_CreateRenderer(globalWindow, -1, SDL_RENDERER_ACCELERATED);
            if (globalRenderer == NULL) {
                printf("Renderer could not be created! SDL_ERROR: %s\n", SDL_GetError());
                success = false;
            } else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(globalRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG Loading
                int imgFlags = IMG_INIT_PNG;
                // 0000 0010 & 0000 0010
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_Image could not be initialized! SDL_Image Error: %s\n", IMG_GetError());
                    success = false;
                } else {
                    // Get Window surface
                    globalSurface = SDL_GetWindowSurface(globalWindow);
                }
            }
        }
    }
    return success;
}

// Load image as surface
SDL_Surface *loadSurface(const std::string &path) {
    // Place for optimized surface
    SDL_Surface *optimizedSurface = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image! SDL_ERROR: %s\n", SDL_GetError());
    }

    optimizedSurface = SDL_ConvertSurface(loadedSurface, globalSurface->format, 0);
    if (optimizedSurface == NULL) {
        printf("Unable to optimize image! SDL_ERROR: %s\n", SDL_GetError());
    }

    // Free the old loaded Surface
    SDL_FreeSurface(loadedSurface);

    return optimizedSurface;
}

// Load image as texture
SDL_Texture *loadTexture(const std::string &path) {
    SDL_Texture *newTexture = NULL;

    newTexture = IMG_LoadTexture(globalRenderer, path.c_str());
    if (newTexture == NULL) {
        printf("Unable to load texture %s\n", IMG_GetError());
    }

    return newTexture;
}

// Loads Media
bool loadMedia() {
    bool success = true;

    globalTexture = loadTexture("../images/texture.png");
    if (globalTexture == NULL) {
        success = false;
    }

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

    globalKeyPressSurfaces[KEY_PRESS_SURFACE_SPACE] = loadSurface("../images/stickman.png");
    if (globalKeyPressSurfaces[KEY_PRESS_SURFACE_SPACE] == NULL) {
        success = false;
    }

    return success;
}

// Frees media and shuts down SDL
void close() {
    // Free loaded texture/image
    SDL_DestroyTexture(globalTexture);
    globalTexture = NULL;

    // Deallocate surface
    SDL_FreeSurface(lastBastionSurface);
    lastBastionSurface = NULL;

    // Destroy Window
    SDL_DestroyRenderer(globalRenderer);
    SDL_DestroyWindow(globalWindow);
    globalWindow = NULL;
    globalRenderer = NULL;

    // Quit SDL Subsystem
    SDL_Quit();
    IMG_Quit();
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
                    /**
                     *
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

                            case SDLK_SPACE:
                                globalCurrentSurface = globalKeyPressSurfaces[KEY_PRESS_SURFACE_SPACE];
                                break;

                            default:
                                globalCurrentSurface = globalKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                                break;
                        }

                        SDL_Rect stretchRect;
                        stretchRect.x = 0;
                        stretchRect.y = 0;
                        stretchRect.w = SCREEN_WIDTH;
                        stretchRect.h = SCREEN_HEIGHT;

                        // Render the surface in the back render also scaling it to the screen size
                        SDL_BlitScaled(globalCurrentSurface, NULL, globalSurface, &stretchRect);

                        // Update the screen
                        SDL_UpdateWindowSurface(globalWindow);
                    }
                     */

                    // Clear Screen
                    SDL_RenderClear(globalRenderer);

                    // Render Texture to the screen
                    SDL_RenderCopy(globalRenderer, globalTexture, NULL, NULL);

                    // Update the screen
                    SDL_RenderPresent(globalRenderer);
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
