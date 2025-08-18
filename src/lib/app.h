#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include "widgets.h"

// Forward declaration of Widget
typedef struct Widget Widget;

// Node for linked list of widgets
typedef struct WidgetsNode {
    Widget* current;
    struct WidgetsNode* next;
} WidgetsNode;

// Main application struct
typedef struct App {
    int window_w;
    int window_h;
    int window_x;
    int window_y;
    const char* title;
    SDL_Color bg_color;
    SDL_Color fg_color;
    SDL_Renderer* renderer;
    SDL_Window* window;
    WidgetsNode* widgets;  // Linked list of widgets
} App;

// Application lifecycle
App* create_app(const char* title, int w, int h, SDL_Color bgcolor, SDL_Color fgcolor);
void free_app(App* app);
void mainloop(App* app);

// Rendering utility
void _set_render_draw_color(SDL_Color color, SDL_Renderer* renderer);

// Widget rendering
void render_single_widget(App* app, Button* button);
void render_widgets(App* app);

#endif // APP_H
