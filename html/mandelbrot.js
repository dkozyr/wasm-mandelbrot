import { WASI } from "@wasmer/wasi";
import wasiBindings from "@wasmer/wasi/lib/bindings/browser";
import { WasmFs } from "@wasmer/wasmfs";

const memory = new WebAssembly.Memory({ initial: 32 });
const kDataOffset = 65536;

let instance = null;
let data = null;

let OnReady = function(width, height, real, image, zoom) {
    const fractal = {'width':width, 'height':height, 'real':real, 'image':image, 'zoom':zoom};
    data = new Uint8ClampedArray(memory.buffer, kDataOffset, 4 * width * height);
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
  
    wasi.setMemory(memory);
    const env = { memory,
      'ready_callback': OnReady
    };
  
    instance = await WebAssembly.instantiate(module, { env, wasi_snapshot_preview1 });
  
    let seed0 = BigInt(new Date().getMilliseconds() * 1234567890123);
    let seed1 = BigInt(new Date().getSeconds() * 3210987654321);
    instance.exports.RandSeed(seed0, seed1);

    instance.exports.Init(kDataOffset, width, height);
}

let OnResize = async function(width, height) {
    if(instance != null) {
        instance.exports.Resize(width, height);
    }
}

let OnUpdate = async function() { if(instance != null) { instance.exports.Update(); } }
let OnZoomIn = async function() { if(instance != null) { instance.exports.ZoomIn(); } }
let OnZoomOut = async function() { if(instance != null) { instance.exports.ZoomOut(); } }
let OnMoveLeft = async function() { if(instance != null) { instance.exports.MoveLeft(); } }
let OnMoveRight = async function() { if(instance != null) { instance.exports.MoveRight(); } }
let OnMoveUp = async function() { if(instance != null) { instance.exports.MoveUp(); } }
let OnMoveDown = async function() { if(instance != null) { instance.exports.MoveDown(); } }
let OnSetRandomPosition = async function() { if(instance != null) { instance.exports.SetRandomPosition(); } }

window.Init = OnInit;
window.Resize = OnResize;
window.Update = OnUpdate;
window.ZoomIn = OnZoomIn;
window.ZoomOut = OnZoomOut;
window.MoveLeft = OnMoveLeft;
window.MoveRight = OnMoveRight;
window.MoveUp = OnMoveUp;
window.MoveDown = OnMoveDown;
window.SetRandomPosition = OnSetRandomPosition;
