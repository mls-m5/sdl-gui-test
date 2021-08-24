
#include "button.hpp"

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
