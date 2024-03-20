#include <SDL2/SDL.h>
#include <map>

typedef struct Function
{
    //Node* root;                                   // root node of the function
    size_t paramCount;                              // number of parameters of the function

    uint8_t r;                                      // color
    uint8_t g;
    uint8_t b;

    bool show;                                      // whether or not to show the function
} Function;

typedef struct Variable
{
    float value;                                    // current value of the variable
    bool constant;                                  // whether or not the variable is a constant
} Variable;

typedef struct ModuleContext
{
    /* Rendering Context */
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Point camera;
    bool open = false;

    /* Module Context*/
    double ppu;                                     // pixels per unit

    std::map<std::string, Function> functions;      // map identifiers to functions
    std::map<std::string, Variable> variables;      // map identifiers to variables
} ModuleContext;