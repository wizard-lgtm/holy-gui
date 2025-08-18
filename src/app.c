#include <app.h>
#include <SDL3/SDL.h>
#include <colors.h>
#include <stdlib.h>
#include <stdio.h>

App* create_app(const char* title, int w, int h, SDL_Color bgcolor, SDL_Color fgcolor) {
    SDL_Init(SDL_INIT_VIDEO);

    App* app = (App*)malloc(sizeof(App));
    if (!app) {
        perror("Can't initialize app: Memory error");
        SDL_Quit();
        exit(1);
    }

    app->window_w = w;
    app->window_h = h;
    app->window_x = SDL_WINDOWPOS_CENTERED;
    app->window_y = SDL_WINDOWPOS_CENTERED;
    app->title = title;
    app->bg_color = bgcolor;
    app->fg_color = fgcolor;
    app->widgets = NULL;

    app->window = SDL_CreateWindow(
        title,
        w, h,
        0
    );

    if (!app->window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        free(app);
        SDL_Quit();
        exit(1);
    }

    app->renderer = SDL_CreateRenderer(app->window, NULL);
    if (!app->renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(app->window);
        free(app);
        SDL_Quit();
        exit(1);
    }

    // Optionally clear the window with bg_color
    SDL_SetRenderDrawColor(app->renderer,
                           app->bg_color.r, app->bg_color.g,
                           app->bg_color.b, app->bg_color.a);
    SDL_RenderClear(app->renderer);
    SDL_RenderPresent(app->renderer);

    return app;
}

void free_app(App* app) {
    if (!app) return;

    if (app->renderer) SDL_DestroyRenderer(app->renderer);
    if (app->window) SDL_DestroyWindow(app->window);
    free(app);

    SDL_Quit();
}

// util
void _set_render_draw_color(SDL_Color color, SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void render_single_widget(App* app, Button* button){
    if (!button || !button->rect){
        printf("Button or button rect is not defined!");
        return;
    };

    _set_render_draw_color(button->bgcolor, app->renderer);
    SDL_RenderFillRect(app->renderer, button->rect);
}

void render_widgets(App* app){
    // Example button
    Button* b = create_button(200, 100, 300, 200, COLOR_BLUE);

    // Render the button
    render_single_widget(app, b);

    // Free the button after rendering (or store it in app->widgets later)
}

void mainloop(App* app) {
    SDL_Event event;

    // Process events
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            free_app(app);
            exit(0); // Exit the program when window is closed
        }
    }

    // Set background color
    _set_render_draw_color(COLOR_WHITE, app->renderer);

    // Clear the renderer
    SDL_RenderClear(app->renderer);

    render_widgets(app);

    // Present the renderer (update the window)
    SDL_RenderPresent(app->renderer);

}
