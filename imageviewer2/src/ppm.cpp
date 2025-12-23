#include <iostream>
// #include <image.h>
#include <fstream>
#include "ppm.h"
image loadppm(const std::string& filename){
    image img;
    std::ifstream file(filename);
    std::string type;
    std::string s;
    getline(file, type);  
    file>>s;
    if(s[0]=='#'){
        getline(file, s);
        file>>s;
    }
    int width = std::stoi(s);
    file>>s;
    int height = std::stoi(s);
    file>>s;
    int maxvalue = std::stoi(s);
    img.set_width(width);
    img.set_height(height);
    std::vector<uint8_t> pixels(width*height*3);
    if(type == "P3"){
        for(int i=0; i<width*height*3; i++){
            file>>s;
            pixels[i] = std::stoi(s);
        }
    }
    else if(type == "P6"){
        file.read((char*)pixels.data(), height*width*3);
    }
    img.set_pixels(pixels);
    return img;
}
