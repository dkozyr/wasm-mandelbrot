#include "Api.h"
#include "Mandelbrot.h"

extern "C" {

// js-function(s)
void ready_callback(int, int, double, double, double);

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

    ready_callback(canvas.width, canvas.height, mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void Resize(int width, int height) {
    auto& canvas = g_data.canvas;
    canvas.width = width;
    canvas.height = height;

    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.Fill(canvas);

    ready_callback(canvas.width, canvas.height, mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void Update() {
    auto& canvas = g_data.canvas;
    Resize(canvas.width, canvas.height);
}

API void ZoomIn() {
    auto& canvas = g_data.canvas;
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.ZoomIn();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(canvas.width, canvas.height, mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void ZoomOut() {
    auto& canvas = g_data.canvas;
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.ZoomOut();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(canvas.width, canvas.height, mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void MoveLeft() {
    auto& canvas = g_data.canvas;
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.MoveLeft();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(canvas.width, canvas.height, mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void MoveRight() {
    auto& canvas = g_data.canvas;
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.MoveRight();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(canvas.width, canvas.height, mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void MoveUp() {
    auto& canvas = g_data.canvas;
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.MoveUp();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(canvas.width, canvas.height, mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void MoveDown() {
    auto& canvas = g_data.canvas;
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.MoveDown();
    mandelbrot.Fill(g_data.canvas);

    ready_callback(canvas.width, canvas.height, mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}

API void SetRandomPosition() {
    auto& canvas = g_data.canvas;
    auto& mandelbrot = g_data.mandelbrot;
    mandelbrot.SetRandomPosition(g_data.canvas);
    mandelbrot.Fill(g_data.canvas);

    ready_callback(canvas.width, canvas.height, mandelbrot.GetReal(), mandelbrot.GetImage(), mandelbrot.GetZoom());
}
