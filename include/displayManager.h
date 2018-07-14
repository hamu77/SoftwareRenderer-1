#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "SDL.h"
#include "buffer.h"


//Manages all low level display and window SDL stuff
//Currently set up to work using SDL2 hardware rendering
//I tested software rendering and although it was faster for simple color passes
//It was slower when I tried to implement alpha blending, so I decided to revert
//Back to the hardware accelerated backend.
class DisplayManager{

    public:
        const static int SCREEN_WIDTH  = 640; //640
        const static int SCREEN_HEIGHT = 480; //480
        const static int SCREEN_PITCH  = SCREEN_HEIGHT*sizeof(Uint32);

        //Dummy Constructor / Destructor
        DisplayManager();
        ~DisplayManager();

        //Initializes SDL context and creates window according to values above 
        bool startUp();
        void shutDown();

        //Clear screens to black
        void clear();

        //Swaps the pixel buffer with the texture buffer and draws to screen
        void swapBuffers(Buffer<Uint32> *pixelBuffer);

    private:
        bool startSDL();
        bool createWindow();
        bool createSDLRenderer();
        bool createScreenTexture();

        SDL_Texture  *mTexture;
        SDL_Renderer *mSDLRenderer;
        SDL_Window   *mWindow;

        //These are only really needed for the texture copying operation
        int           mTexturePitch;
        void         *mTexturePixels;
};

#endif