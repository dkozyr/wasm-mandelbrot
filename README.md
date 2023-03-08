# Mandelbrot Fractal WASM Plugin

This is a plugin for building Mandelbrot fractals using the WebAssembly System Interface (WASI) Software Development Kit (SDK).

## Prerequisites

In order to use build plugin, you must have the [WASI SDK](https://github.com/WebAssembly/wasi-sdk) installed on your system and set correct path in `CMakeLists.txt`:

```
set(WASI_VERSION_FULL "19.0")
set(WASI_SDK_PATH $ENV{HOME}/deps/wasi-sdk-${WASI_VERSION_FULL})
```

## Example

[Mandelbrot Fractal WASM](https://dkozyr.github.io/wasm-mandelbrot/)
