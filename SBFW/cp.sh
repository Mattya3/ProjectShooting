#!/bin/zsh
/opt/homebrew/Cellar/gcc/12.2.0/bin/g++-12 -c \
src/*.cpp \
src/math2D/*.cpp \
src/lodepng/lodepng.cpp \
-DGL_SILENCE_DEPRECATION=1 \
-I/opt/homebrew/Cellar/glfw/3.3.8/include/ \
&& \
ar rc libsbfw.a *.o