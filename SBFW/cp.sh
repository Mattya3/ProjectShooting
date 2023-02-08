g++ -std=c++17 -c ext_math/*.cpp src/element/ViewContent.cpp \
src/element/texture/ImageManager.cpp \
src/scene/*.cpp \
lodepng/*.cpp \
-I./include \
-I./include/ext_math \
-I./lodepng \
-DGL_SILENCE_DEPRECATION=1 \
-I/Users/itihiotu/Documents/Develop/cpp/ProjectShooting/include/ \
-I/opt/homebrew/Cellar/glfw/3.3.8/include/ \
-L/opt/homebrew/Cellar/glfw/3.3.8/lib -lglfw \
& ar rc libsbfw.a *.o