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
    
    }
};
