#include "Api.h"
#include "Mandelbrot.h"

extern "C" {

// js-function(s)
void ready_callback(double, double, double);

}

struct InternalData{
    Canvas canvas;
    Mandelbrot mandelbrot;
};

static InternalData g_data;

API void Init(uint8_t* ptr, int width, int height) {
    auto& canvas = g_data.canvas;
    canvas.ptr = reinterpret_cast<Rgba*>(ptr);
    canvas.width = width;
    canvas.height = height;

    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.SetRandomPosition(canvas);
    mandelbrot.Fill(canvas);

    ready_callback(mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void ZoomIn() {
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.ZoomIn();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void ZoomOut() {
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.ZoomOut();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void MoveLeft() {
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.MoveLeft();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void MoveRight() {
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.MoveRight();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void MoveUp() {
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.MoveUp();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void MoveDown() {
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.MoveDown();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void SetRandomPosition() {
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.SetRandomPosition(g_data.canvas);
    mandelbrot.Fill(g_data.canvas);

    ready_callback(mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}
