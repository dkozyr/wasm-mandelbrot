#pragma once

#include "Canvas.h"
#include <array>

class Mandelbrot {
public:
    static constexpr auto kMaxIterations = 80;
    static constexpr double kPixelSize = 0.007;
    static constexpr double kMaxZoom = 1e7;
    static constexpr double kZoomStep = 1.05;

public:
    Mandelbrot();

    void Fill(const Canvas& canvas);
    void ZoomIn();
    void ZoomOut();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void SetRandomPosition(const Canvas& canvas);

    double GetReal() const { return _x; }
    double GetImage() const { return _y; }
    double GetZoom() const { return _zoom; }

private:
    static int Evaluate(double x0, double y0, bool smoothed);

private:
    double _x;
    double _y;
    double _zoom;

    std::array<Rgba, kMaxIterations + 1> _color;
};
