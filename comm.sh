g++ -std=c++20 -LSBFW/ -lsbfw test.cpp -I./SBFW/include -I./SBFW/ext_math -I/opt/homebrew/Cellar/glfw/3.3.8/include/ \
-L/opt/homebrew/Cellar/glfw/3.3.8/lib -lglfw \
-L/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries -lGL -lGLU \
-DGL_SILENCE_DEPRECATION