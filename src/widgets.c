#include <widgets.h>
#include <colors.h>
#include <stdlib.h>
#include <stdio.h>
#include <app.h>

void render_button(Button* b, SDL_Renderer* r){
    if (!b|| !b->rect){
        printf("Rendering ERR: Button or button rect is not defined!");
        return;
    };

    _set_render_draw_color(b->bgcolor, r);
    SDL_RenderFillRect(r, b->rect);
}
void free_button(Widget* w){
    Button* b = (Button*)w;
    if (!b) return;
    if (b->rect) free(b->rect);
    free(b);
}

Button* create_button(int w, int h, int x, int y, SDL_Color bgcolor){
   

    Button* b = malloc(sizeof(Button));
    if (b==NULL){
        //return error;
    }


    b->bgcolor = bgcolor;
    
    SDL_FRect* rect = malloc(sizeof(SDL_FRect));
    rect->h = h;
    rect->w = w;
    rect->x = x;
    rect->y = y;

    b->rect = rect;
    
    Widget* base = create_widget(WIDGET_TYPE_BUTTON, b->rect);
    b->base = base;
    b->base->render = (WidgetRenderFn)render_button;
    b->base->free = (WidgetFreeFn)free_button;
    return b;
}

Widget* create_widget(WidgetType type, SDL_FRect* rect) {
    Widget* w = malloc(sizeof(Widget));
    if (!w) return NULL;
    w->type = type;
    w->rect = rect;
    w->render = NULL;
    w->free = NULL;
    return w;
}

void free_widget(Widget* w){
    if(w&& w->free){
        w->free(w);
    }
}
void render_widget(Widget* w, SDL_Renderer* r){
    SDL_RenderFillRect(r, w->rect);
}