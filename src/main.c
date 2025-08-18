#include <app.h>
#include <colors.h>


int main(){
    const char* title = "holy-gui";
    App* app = create_app(title, 640, 480, COLOR_WHITE, COLOR_WHITE);
    while(1){
        mainloop(app);
    }

    free_app(app);

}