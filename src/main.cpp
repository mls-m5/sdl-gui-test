
#include "SDL2/SDL_image.h"
#include "sdlpp/render.hpp"
#include "sdlpp/texture.hpp"
#include "sdlpp/window.hpp"
#include <array>
#include <iostream>
#include <thread>

auto loadTexture(sdl::Renderer &renderer, std::string_view filename)
    -> sdl::Texture {
    return {IMG_LoadTexture(renderer, filename.data())};
}

void drawButton(sdl::Renderer &renderer,
                sdl::Texture &texture,
                int x,
                int y,
                int w,
                int h) {
    constexpr auto border = 2;
    const auto halfW = (w - border * 2) / 2; // Will fail sometimes probably
    const auto halfH = (h - border * 2) / 2; // Will fail sometimes probably

    // Draw all part of the button
#pragma unloop
    for (int ny = 0; ny < 4; ++ny) {
#pragma unloop
        for (int nx = 0; nx < 4; ++nx) {
            auto src = sdl::Rect{nx * border, ny * border, border, border};
            auto dst = sdl::Rect{0, 0, border, border};

            switch (nx) {
            case 0:
                break;
            case 1:
                dst.x = border;
                dst.w = halfW;
                break;
            case 2:
                dst.x = halfW + border;
                dst.w = halfW;
                break;
            case 3:
                dst.x = w - border;
                break;
            }

            switch (ny) {
            case 0:
                break;
            case 1:
                dst.y = border;
                dst.h = halfH;
                break;
            case 2:
                dst.y = halfH + border;
                dst.h = halfH;
                break;
            case 3:
                dst.y = h - border;
                break;
            }

            dst.x += x;
            dst.y += y;

            renderer.copy(texture, &src, &dst);
        }
    }
}

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
