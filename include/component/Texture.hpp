#include <bits/stdc++.h>
#include <component/Image.hpp>

using namespace std;
class Texture {

  private:
    PngTexture _image;
    static int _id;

  public:
    static void init(){
      _id=0;
    }
    Texture(string &fname);
    ~Texture();
};



Texture::Texture(string &fname) {
    // _image=PngTexture(fname, Texture::_id);
    // ++Texture::_id;
}

Texture::~Texture() {}
