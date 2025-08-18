#ifndef WIDGETS_H
#define WIDGETS_H

#include <SDL3/SDL.h>

typedef enum {
    WIDGET_TYPE_BUTTON,
    WIDGET_TYPE_LABEL,
} WidgetType;

struct Widget; // forward declaration

typedef void (*WidgetRenderFn)(struct Widget*, SDL_Renderer*);
typedef void (*WidgetFreeFn)(struct Widget*);

typedef struct Widget {
    WidgetType type;
    SDL_FRect* rect;
    WidgetRenderFn render;
    WidgetFreeFn free;
} Widget;

typedef struct Label{
    // Font* font; Font TODO!
    char* text;
    SDL_Color color;
    SDL_FRect* rect;
};

typedef struct Button {
    // Label text;
    Widget* base;
    SDL_Color bgcolor;
    SDL_FRect* rect;

} Button;
Button* create_button(int w, int h, int x, int y, SDL_Color bgcolor);
Widget* create_widget(WidgetType wtype, SDL_FRect* rect);
void free_button(Widget* w);
void render_widget(Widget* w, SDL_Renderer* renderer);
void free_widget(Widget* w);

#endif WIDGETS_H