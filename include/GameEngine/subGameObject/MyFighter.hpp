#include <GameEngine/CenterLocation.hpp>
#include <component/Image.hpp>
#include <scenes/Scene.hpp>
using namespace std;

class MyFighter {
  private:
    PngTexture myview;
    vector<int> struc_card_id = vector<int>(3, 0);
    DataOf2D velocity = DataOf2D(0.02, 0.02);

  public:
    double rotate = 0, d_rotate = 10;
    void set_card(int num, int card_id) { struc_card_id[num] = card_id; }
    void view(Location l) {
        glPushMatrix();
        glTranslatef(l.sx + l.xlen / 2, l.sy + l.ylen / 2, 0);
        glRotatef(rotate, 0, 0, 1);
        glTranslatef(-l.sx - l.xlen / 2, -l.sy - l.ylen / 2, 0);
        myview.view_clone(l);
        glPopMatrix();
    }
    // void accelerate(int gx, int gy) {
    //     pos.add(gx * velocity.x, gy * velocity.y);
    // }
    // bool is_collision(CenterLocation bule) {
    //     return CenterLocation::is_object_collision(pos, bule);
    // }
    // DataOf2D get_central() {
    //     return {myview.loc.sx + myview.loc.xlen / 2,
    //             myview.loc.sy + myview.loc.ylen / 2};
    // }

    void change_rotate() { rotate += d_rotate; }
    MyFighter(std::string image_file_name) : myview(image_file_name) {
        // pos = CenterLocation(myview.loc);
    }
    ~MyFighter() {}
};
