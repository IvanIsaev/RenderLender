# RenderLender
Simple rendering engine is based on Google Filament rendering engine.

# Dependencies
Make sure you have all dependencies installed:
- Qt 6.7.0
- Boost 1.87
- filament
- Vulkan 1.4.309
- assimp

## filament
Before building filament make sure that `Vulkan 1.4.309` is installed and its system variables is amid environment variables.

Next snippet of code demonstrates how to build filament that will be suitable for current project:
```console
cd filament
mkdir out
cd out
cmake -DUSE_STATIC_CRT:BOOL=OFF -DFILAMENT_SUPPORTS_OPENGL:BOOL=OFF -DFILAMENT_SUPPORTS_VULKAN:BOOL=ON ..
cmake --build . --config Debug -j 8
cmake --install . --config Debug
```
Built artefacts will be situated in directory:
```filament/install```

Add environment variables `FILAMENT_DEBUG_LIBS_PATH`, `FILAMENT_RELEASE_LIBS_PATH` and `FILAMENT_INCLUDE_PATH` with full path to artifacts. For example:
```
FILAMENT_INCLUDE_PATH = e:\filament\out\install\include
FILAMENT_DEBUG_LIBS_PATH = e:\filament\out\install\lib\x86_64\Debug
FILAMENT_RELEASE_LIBS_PATH = e:\filament\out\install\lib\x86_64\Release
```






