# image_viewerv0
This is project made completely by myself in a week, this was done to get basic knowledge of sdl2 and continue programming in vacation.
# PPM Image Viewer

A lightweight image viewer for PPM format images built in C++ with SDL2. Supports zooming, panning, and window resizing with smooth performance.

## Features

- **View PPM Images**: Display P3 and P6 format PPM images
- **Zoom**: Scroll wheel to zoom in/out (0.1x to 10x)
- **Pan**: Click and drag to move around the image
- **Resizable Window**: Automatically scales image to fit window size
- **Smooth Controls**: Responsive zoom and pan with mouse-centric zoom (zooms toward cursor)

## Prerequisites

- C++11 or later
- SDL2 library
- Make

### Installing SDL2

**On Ubuntu/Debian:**
```bash
sudo apt-get install libsdl2-dev
```

**On macOS (with Homebrew):**
```bash
brew install sdl2
```

**On Windows (MinGW):**
Download SDL2 from [libsdl.org](https://www.libsdl.org/) and configure your compiler path.

## Building

```bash
make
```

This compiles the project and generates an executable named `image_viewer`.

## Usage

```bash
./image_viewer <path_to_ppm_file>
```

**Example:**
```bash
./image_viewer sample.ppm
```

## Controls

| Action | Control |
|--------|---------|
| **Zoom In** | Scroll wheel up |
| **Zoom Out** | Scroll wheel down |
| **Pan/Move** | Click and drag with left mouse button |
| **Quit** | Close window or press Ctrl+C |

## Project Structure

```
image-viewer/
├── src/              # Source files
├── include/          # Header files
├── Makefile          # Build configuration
└── README.md         # This file
```

## Implementation Details

### Key Components

- **PPM Parser**: Reads and parses P3 and P6 format PPM files
- **Rendering Engine**: SDL2-based pixel-by-pixel rendering with coordinate transformation
- **Zoom System**: Mouse-aware zoom that keeps the cursor position fixed during zoom
- **Pan System**: Smooth panning with offset tracking

### Technical Highlights

- Efficient coordinate transformation for zoom/pan operations
- Direct surface pixel manipulation for fine-grained control
- Event-driven architecture for responsive user input
- Bounds checking to handle out-of-image areas

## Testing

Test the viewer with PPM images. You can create simple test images or use existing PPM files.

**Example PPM format (P3 - ASCII):**
```
P3
2 2
255
255 0 0     0 255 0
0 0 255     255 255 0
```

## Future Enhancements

- Support for additional formats (PNG, JPEG, BMP)
- Keyboard shortcuts (Home to reset view, arrow keys for fine pan)
- On-screen display of zoom level and image information
- Performance optimization using SDL2 textures
- File browser for loading images without command-line arguments

## Notes

- Window resizing automatically adjusts the image scaling
- Zoom level is limited between 0.1x and 10x to prevent extreme scaling
- Black areas outside the image bounds indicate areas beyond the image dimensions

## Author

Created as a portfolio project demonstrating SDL2 graphics programming, file I/O, and coordinate mathematics.

## License

This project is open source. Feel free to use and modify as needed.
