import { WASI } from "@wasmer/wasi";
import wasiBindings from "@wasmer/wasi/lib/bindings/browser";
import { WasmFs } from "@wasmer/wasmfs";

let instance = null;
let data = null;

let OnReady = function(real, image, zoom) {
    const fractal = {'real':real, 'image':image, 'zoom':zoom};
    window.OnReady(data, fractal);
}

let OnInit = async function(width, height) {
    const wasmfs = new WasmFs();
    const wasi = new WASI({
      bindings: {
        ...wasiBindings.default,
        fs: wasmfs.fs
      }
    });
  
    const module = await WebAssembly.compileStreaming(fetch('mandelbrot.wasm'));
    const { wasi_snapshot_preview1 } = wasi.getImports(module);
  
    const memory = new WebAssembly.Memory({ initial: 32 });
    wasi.setMemory(memory);
    const env = { memory,
      'ready_callback': OnReady
    };
  
    instance = await WebAssembly.instantiate(module, { env, wasi_snapshot_preview1 });
  
    let seed0 = BigInt(new Date().getMilliseconds() * 1234567890123);
    let seed1 = BigInt(new Date().getSeconds() * 3210987654321);
    instance.exports.RandSeed(seed0, seed1);
  
    let data_offset = 65536; // In place of "malloc"
    data = new Uint8ClampedArray(memory.buffer, data_offset, 4 * width * height);

    instance.exports.Init(data_offset, width, height);
}

let OnZoomIn = async function() { if(instance != null) { instance.exports.ZoomIn(); } }
let OnZoomOut = async function() { if(instance != null) { instance.exports.ZoomOut(); } }
let OnMoveLeft = async function() { if(instance != null) { instance.exports.MoveLeft(); } }
let OnMoveRight = async function() { if(instance != null) { instance.exports.MoveRight(); } }
let OnMoveUp = async function() { if(instance != null) { instance.exports.MoveUp(); } }
let OnMoveDown = async function() { if(instance != null) { instance.exports.MoveDown(); } }
let OnSetRandomPosition = async function() { if(instance != null) { instance.exports.SetRandomPosition(); } }

window.Init = OnInit;
window.ZoomIn = OnZoomIn;
window.ZoomOut = OnZoomOut;
window.MoveLeft = OnMoveLeft;
window.MoveRight = OnMoveRight;
window.MoveUp = OnMoveUp;
window.MoveDown = OnMoveDown;
window.SetRandomPosition = OnSetRandomPosition;
