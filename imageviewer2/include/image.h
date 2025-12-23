#include <vector>
#include <cstdint>
class image{
    private: 
        int width;
        int height;
        std::vector<uint8_t> pixels;
    public:
        void set_width(int width);
        void set_height(int height);
        void set_pixels(std::vector<uint8_t> pixels);
        int get_height();
        int get_width();
        std::vector<uint8_t> get_pixels();

    };
