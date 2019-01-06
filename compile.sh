#!/usr/bin/env bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
cd "$DIR/src"
g++ -o ../sph_simulation main.cpp Fluid.cpp Particle.cpp SpatialGrid.cpp SPHKernels.cpp common/shader.cpp common/texture.cpp common/controls.cpp -lGL -lrt -lGLU -lGLEW -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lsfml-graphics -lsfml-window -lsfml-system -g
../sph_simulation