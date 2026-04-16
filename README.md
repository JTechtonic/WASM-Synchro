This repo is for the semester project for class COP 5611 Operating System Design Principles at the University of Central Florida. I, Jeovan Teixiera, worked on this myself.
The basis of the project was to make some synchronization primitives using the WASI SDK and C. As of writing the code compiles and runs using the 20.0+threads version of WASI SDK and the WebAssembly Micro Runtime tool.
No efforts in containerization have been made, but to have this work on your own machine download the following repositories into the same directory:
* [https://github.com/WebAssembly/wasi-sdk/releases/tag/wasi-sdk-20%2Bthreads](URL)
* [https://github.com/bytecodealliance/wasm-micro-runtime/tree/main](URL)

Keep in mind that the "CMakeLists.txt" files is meant to replace the file of the same name in the WAMR repository at this location "wasm-micro-runtime/product-mini/platforms/linux". I did this because I struggled to correctly add the options I wanted when building iwasm.
