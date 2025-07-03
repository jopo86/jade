# ![Jade Header](jade-header.png)
Jade is a small and user-friendly C++ 2D rendering engine. It is perfect for getting small 2D projects up and running in no time.

The engine is capable of drawing common shapes, images (sprites), and text, and uses a callback-based structure so you don't have to worry about putting things in the right place at the right time inside of loops.  

## Compile
Jade uses CMake and several dependencies, all of which are included in this repository (as submodules or not). Clone the repository and update all submodules (`git submodule update --init --remote --recursive`). Now create a build folder and build using CMake:  
```
mkdir build
cd build
cmake ../
cmake --build .
```
Now you should find the compiled jade library in `build/src/` and compiled examples in `build/examples/`.


