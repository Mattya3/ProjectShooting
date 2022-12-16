#include <GameEngine/CenterLocation.hpp>
#include <component/Image.hpp>
#include <scenes/Scene.hpp>
using namespace std;

class MyFighter {
  private:
    PngTexture myview;
    double start_posX = 0.4, start_posY = 0.4;
    double rotate = 0, d_rotate = 10;
    vector<int> struc_card_id = vector<int>(3, 0);
    DataOf2D velocity = DataOf2D(0.02, 0.02);

  public:
    CenterLocation pos;
    CenterLocation get_pos(){
      return CenterLocation(pos);
    }
    void set_pos(DataOf2D c){
      pos=CenterLocation(c, pos.get_len());
    }
    void set_card(int num, int card_id) { struc_card_id[num] = card_id; }
    void view() {
        myview.loc = pos.to_Location();
        glPushMatrix();
        glTranslatef(myview.loc.sx + myview.loc.xlen / 2,
                     myview.loc.sy + myview.loc.ylen / 2, 0);
        glRotatef(rotate, 0, 0, 1);
        glTranslatef(-myview.loc.sx - myview.loc.xlen / 2,
                     -myview.loc.sy - myview.loc.ylen / 2, 0);
        myview.view();
        glPopMatrix();
    }
    void accelerate(int gx, int gy) {
        pos.add(gx * velocity.x, gy * velocity.y);
    }
    bool is_collision(CenterLocation bule) {
        return CenterLocation::is_object_collision(pos, bule);
    }
    DataOf2D get_central() {
        return {myview.loc.sx + myview.loc.xlen / 2,
                myview.loc.sy + myview.loc.ylen / 2};
    }

    void change_rotate() { rotate += d_rotate; }
    MyFighter(std::string image_file_name) : myview(image_file_name) {
        myview.loc.sx = start_posX;
        myview.loc.sy = start_posY;
        pos = CenterLocation(myview.loc);
    }
    ~MyFighter() {}
};
