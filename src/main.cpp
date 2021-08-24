
#include "SDL2/SDL_image.h"
#include "button.hpp"
#include "sdlpp/render.hpp"
#include "sdlpp/texture.hpp"
#include "sdlpp/window.hpp"
#include <array>
#include <iostream>
#include <thread>

int main(int argc, char **argv) {
    using namespace std::chrono_literals;
    auto window = sdl::Window{"Hello there",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              500,
                              500,
                              SDL_WINDOW_SHOWN};

    auto renderer = sdl::Renderer{window, -1, SDL_RENDERER_ACCELERATED};

    auto buttonTexture =
        sdl::Texture{IMG_LoadTexture(renderer, "data/button1.png")};
    auto buttonTexture2 =
        sdl::Texture{IMG_LoadTexture(renderer, "data/button2.png")};

    if (!buttonTexture) {
        std::cerr << "could not load button1.png\n";

        std::exit(1);
    }

    renderer.setDrawColor(0, 0, 0, 255);
    renderer.clear();

    const auto rect = sdl::Rect{0, 0, 8, 8};

    renderer.setDrawColor(100, 100, 100, 200);
    renderer.drawLine(0, 0, 100, 100);

    drawButton(renderer, buttonTexture, 8, 8, 40, 20);
    drawButton(renderer, buttonTexture2, 8 + 40, 8, 40, 20);

    renderer.present();

    std::this_thread::sleep_for(10s);

    std::cout << "hello from " << argv[0] << std::endl;
}
