#include <component/Image.hpp>
#include <scenes/Scene.hpp>

using namespace std;

class MyFighter {
  private:
    PngTexture myview;
    double start_posX = 0.4, start_posY = 0.4;
    double rotate = 0, d_rotate = 10;
    vector<int> struc_card_id = vector<int>(3, 0);

  public:
    void set_card(int num, int card_id) { struc_card_id[num] = card_id; }
    void view() {
        glPushMatrix();
        glTranslatef(myview.loc.sx - myview.loc.xlen / 2,
                     myview.loc.sy - myview.loc.ylen / 2, 0);
        glRotatef(rotate, 0, 0, 1);
        glTranslatef(-myview.loc.sx - myview.loc.xlen / 2,
                     -myview.loc.sy - myview.loc.ylen / 2, 0);
        myview.view();
        glPopMatrix();
    }
    void change_loc(double vx, double vy) {
        myview.loc.sy += vy;
        myview.loc.sx += vx;
    }
    pair<double, double> get_central() {
        return {myview.loc.sx + myview.loc.xlen / 2,
                myview.loc.sy + myview.loc.ylen / 2};
    }
    Location &get_loc() { return myview.loc; }
    void change_rotate() { rotate += d_rotate; }
    MyFighter(std::string image_file_name) : myview(image_file_name) {}
    ~MyFighter() {}
};
