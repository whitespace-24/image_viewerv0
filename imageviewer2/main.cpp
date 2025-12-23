#include <utils.h>
#include <SDL2/SDL.h>
// #include <image.h>
#include <ppm.h>
image img;
SDL_Window* win = nullptr;
float zoom_level = 1.0f; 
float offset_x = 0.0f;
float offset_y = 0.0f;
bool is_dragging = false;
int last_mouse_x, last_mouse_y;



void handleresize(int width, int height){
    SDL_Surface* img_surface = SDL_GetWindowSurface(win);
    uint32_t* pixnew = (uint32_t*)img_surface->pixels;
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            int newx = x*img.get_width()/width;
            int newy = y*img.get_height()/height;
            uint8_t r = img.get_pixels()[(newy*img.get_width() + newx)*3];
            uint8_t g = img.get_pixels()[(newy*img.get_width() + newx)*3 +1];
            uint8_t b = img.get_pixels()[(newy*img.get_width() + newx)*3 + 2];
            
            uint32_t color = SDL_MapRGB(img_surface->format, r, g, b);
            pixnew[y * img_surface->w +x] = color;
        }
    }
    SDL_UpdateWindowSurface(win);
}

void render_image() {
    SDL_Surface* win_surface = SDL_GetWindowSurface(win);
    int win_w = win_surface->w;
    int win_h = win_surface->h;
    uint32_t* pixels = (uint32_t*)win_surface->pixels;

    for (int y = 0; y < win_h; y++) {
        for (int x = 0; x < win_w; x++) {
            // Map screen (x, y) to image (src_x, src_y)
            // (ScreenPos / Zoom) + Offset = ImagePos
            int src_x = (int)(x / zoom_level + offset_x);
            int src_y = (int)(y / zoom_level + offset_y);

            // Check if we are within the bounds of the original image
            if (src_x >= 0 && src_x < img.get_width() && src_y >= 0 && src_y < img.get_height()) {
                uint8_t r = img.get_pixels()[(src_y * img.get_width() + src_x) * 3];
                uint8_t g = img.get_pixels()[(src_y * img.get_width() + src_x) * 3 + 1];
                uint8_t b = img.get_pixels()[(src_y * img.get_width() + src_x) * 3 + 2];
                pixels[y * win_w + x] = SDL_MapRGB(win_surface->format, r, g, b);
            } else {
                // Background color for areas outside the image
                pixels[y * win_w + x] = SDL_MapRGB(win_surface->format, 0, 0, 0);
            }
        }
    }
    SDL_UpdateWindowSurface(win);
}

void handlepan(const SDL_Event& E) {
    if (E.type == SDL_MOUSEBUTTONDOWN) {
        if (E.button.button == SDL_BUTTON_LEFT) {
            is_dragging = true;
            last_mouse_x = E.button.x;
            last_mouse_y = E.button.y;
        }
    } 
    else if (E.type == SDL_MOUSEBUTTONUP) {
        if (E.button.button == SDL_BUTTON_LEFT) {
            is_dragging = false;
        }
    } 
    else if (E.type == SDL_MOUSEMOTION) {
        if (is_dragging) {
            // Calculate how far the mouse moved
            int dx = E.motion.x - last_mouse_x;
            int dy = E.motion.y - last_mouse_y;

            // Move the offset inversely to the mouse movement
            // We divide by zoom_level so the image follows the cursor accurately
            offset_x -= (float)dx / zoom_level;
            offset_y -= (float)dy / zoom_level;

            // Update last position for the next motion event
            last_mouse_x = E.motion.x;
            last_mouse_y = E.motion.y;

            render_image(); // Redraw the image at the new position
        }
    }
}

void handlezoom(const SDL_Event& E) {
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    // Calculate the mouse position in "image coordinates" before the zoom
    float before_zoom_x = mouse_x / zoom_level + offset_x;
    float before_zoom_y = mouse_y / zoom_level + offset_y;

    // Adjust zoom level
    float zoom_speed = 1.1f;
    if (E.wheel.y > 0) {
        zoom_level *= zoom_speed; // Zoom in
    } else if (E.wheel.y < 0) {
        zoom_level /= zoom_speed; // Zoom out
    }

    // Calculate the new offset so the mouse stays over the same image point
    offset_x = before_zoom_x - (mouse_x / zoom_level);
    offset_y = before_zoom_y - (mouse_y / zoom_level);

    render_image();
}


int main(int argc, char **argv){
    // if(argc>1){
    //     std::cerr<<"program can display only one image for now";
    // }
    // if(argc==0){
    //     std::cerr<<"please pass image file as argument";
    // }
    char* filename = argv[1];
    // char* ext = strrchr(filename, '.');
    // if (ext != "ppm"){
    //     std::cerr<<"program can only display ppm images for now";
    // }
    img = loadppm(filename);
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Image Viewer v0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, img.get_width(), img.get_height(),SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Surface* img_surface = SDL_GetWindowSurface(win);

    SDL_LockSurface(img_surface); //just to be safe

    uint32_t* pix = (uint32_t*)img_surface->pixels;
    for(int y=0; y<img.get_height(); y++){
        for(int x=0; x<img.get_width(); x++){
            uint8_t r = img.get_pixels()[(y*img.get_width() + x)*3];
            uint8_t g = img.get_pixels()[(y*img.get_width() + x)*3 +1];
            uint8_t b = img.get_pixels()[(y*img.get_width() + x)*3 + 2];
            
            uint32_t color = SDL_MapRGB(img_surface->format, r, g, b);

            pix[y * img_surface->w +x] = color;
        }
    }
    SDL_UnlockSurface(img_surface);
    SDL_UpdateWindowSurface(win );
    bool running =true;
    SDL_Event ev;
    while(running){
        while(SDL_PollEvent(&ev)!=0){
            if(ev.type == SDL_QUIT){
                running =false;
            }
           else if (ev.type == SDL_WINDOWEVENT &&
                ev.window.event == SDL_WINDOWEVENT_RESIZED){
                int newwidth = ev.window.data1;
                int newheight = ev.window.data2;
                handleresize(newwidth,newheight);
            }
            else if (ev.type == SDL_MOUSEWHEEL){
                handlezoom(ev);
            }
            else if(ev.type == SDL_MOUSEBUTTONDOWN || 
                 ev.type == SDL_MOUSEBUTTONUP || 
                 ev.type == SDL_MOUSEMOTION) {
                handlepan(ev);
                 }       
        }

    }
    SDL_DestroyWindow(win);
    SDL_Quit();
}
