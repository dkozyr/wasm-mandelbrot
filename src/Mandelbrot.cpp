#include "Mandelbrot.h"
#include "Random.h"

#include <unordered_set>

Mandelbrot::Mandelbrot() {
    for(int i = 0; i < kMaxIterations; ++i) {
        auto hue = static_cast<uint8_t>((200 * i) / kMaxIterations);
        _color[i] = HsvToRgb(hue, 255, 255);
    }
    _color[kMaxIterations] = Rgb(0, 0, 0);
}

void Mandelbrot::Fill(const Canvas& canvas) {
    const auto pixel_size_adj = kPixelSize / _zoom;

    auto img = canvas.ptr;
    auto x0 = _x - (canvas.width / 2) * pixel_size_adj;
    auto y  = _y - (canvas.height / 2) * pixel_size_adj;
    for(int h = 0; h < canvas.height; ++h) {
        auto x = x0;
        for(int w = 0; w < canvas.width; ++w) {
            *img = _color[Evaluate(x, y, true)];
            ++img;
            x += pixel_size_adj;
        }
        y += pixel_size_adj;
    }
}

void Mandelbrot::ZoomIn() {
    _zoom *= kZoomStep;
}

void Mandelbrot::ZoomOut() {
    _zoom = std::max(0.5, _zoom / kZoomStep);
}

void Mandelbrot::MoveLeft() {
    _x -= kPixelSize / _zoom;
}

void Mandelbrot::MoveRight() {
    _x += kPixelSize / _zoom;
}

void Mandelbrot::MoveUp() {
    _y -= kPixelSize / _zoom;
}

void Mandelbrot::MoveDown() {
    _y += kPixelSize / _zoom;
}

void Mandelbrot::SetRandomPosition(const Canvas& canvas) {
    _zoom = 1.0;

    const auto delta = kPixelSize / kMaxZoom;
    const auto half_width = canvas.width / 2;
    const auto half_height = canvas.height / 2;

    while(true) {
        const auto target_value = RandomInt(30, 60);

        // x: [-1.8, -1.5]  => max |y|: 0.05
        // x: [-1.5, -0.75] => max |y|: 0.5
        // x: [-0.75, 0.5]  => max |y|: 1.15
        _x = RandFloat() * 2.3 - 1.8;
        if(_x < -1.5)       { _y = RandFloat() * 0.1 - 0.05; }
        else if(_x < -0.75) { _y = RandFloat() * 1.0 - 0.5; }
        else                { _y = RandFloat() * 2.25 - 1.15; }

        if(Evaluate(_x, _y, false) == target_value) {
            std::unordered_set<int> used_colors;

            constexpr auto kRandomPoints = 120;
            for(int i = 0; i < kRandomPoints; ++i) {
                const auto x = _x + RandomInt(-half_width, half_width) * delta;
                const auto y = _y + RandomInt(-half_height, half_height) * delta;

                used_colors.insert(Evaluate(x, y, false));
            }
            if(used_colors.size() > (kRandomPoints / 4)) {
                break;
            }
        }
    }
}

int Mandelbrot::Evaluate(double x0, double y0, bool smoothed) {
    double x = 0;
    double y = 0;
    double xx = 0;
    double yy = 0;

    for(int i = 0; i < kMaxIterations; ++i) {
        if((xx + yy) >= 4.0) {
            if(smoothed) {
                return i + 1 - static_cast<int>(0.5 * std::log2(xx + yy));
            } else {
                return i;
            }
        }

        y = 2.0 * x * y + y0;
        x = (xx - yy) + x0;

        xx = x * x;
        yy = y * y;
    }
    return kMaxIterations;
}
