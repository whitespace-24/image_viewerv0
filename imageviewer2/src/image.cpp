#include<image.h>

int image::get_width(){
    return this->width;
}
int image::get_height(){
    return this->height;
}
std::vector<uint8_t> image::get_pixels(){
    return this->pixels;
}
void image::set_width(int width){
    this->width = width;
}
void image::set_height(int height){
    this->height = height;
}
void image::set_pixels(std::vector<uint8_t> pixels){
    this->pixels = pixels;
}
// void image::set_maxval(int maxval){
//     this->maxval = maxval;
// }