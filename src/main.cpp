
#include "SDL2/SDL_image.h"
#include "sdlpp/render.hpp"
#include "sdlpp/texture.hpp"
#include "sdlpp/window.hpp"
#include <iostream>
#include <thread>

auto loadTexture(sdl::Renderer &renderer, std::string_view filename)
    -> sdl::Texture {
    return {IMG_LoadTexture(renderer, filename.data())};
}

int main(int argc, char **argv) {
    using namespace std::chrono_literals;
    auto window = sdl::Window{"Hello there", 0, 0, 500, 500, SDL_WINDOW_SHOWN};

    auto renderer = sdl::Renderer{window, -1, SDL_RENDERER_ACCELERATED};

    auto buttonTexture = loadTexture(renderer, "data/button1.png");

    if (!buttonTexture) {
        std::cerr << "could not load button1.png\n";

        std::exit(1);
    }

    renderer.setDrawColor(0, 0, 0, 255);
    renderer.clear();

    const auto rect = sdl::Rect{0, 0, 8, 8};

    renderer.copy(buttonTexture, nullptr, &rect);

    renderer.setDrawColor(100, 100, 100, 200);
    renderer.drawLine(0, 0, 100, 100);

    renderer.present();

    std::this_thread::sleep_for(10s);

    std::cout << "hello from " << argv[0] << std::endl;
}
