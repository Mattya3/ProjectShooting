#include <GameEngine/CenterLocation.hpp>

CenterLocation::CenterLocation() {}
CenterLocation::CenterLocation(DataOf2D cent, DataOf2D len):c(cent), len(len){}
//my_fighter.change_rotate(); CenterLocation(Location(-1,-1,2,2)
CenterLocation::CenterLocation(Location l)  {
    len.x=l.xlen/2.0;
    cout << l.xlen << endl;
    len.y=l.ylen/2.0;
    c = DataOf2D(l.sx + len.x, l.sy + len.y);
}
CenterLocation::CenterLocation(double cx, double cy, double lenx2, double leny2)
    : c(cx, cy), len(lenx2, leny2) {}

CenterLocation::~CenterLocation() {}
void CenterLocation::add(double dx, double dy) {
    c.x += dx;
    c.y += dy;
}
pdd CenterLocation::get_Xboundary() { return {c.x - len.x, c.x + len.x}; }
pdd CenterLocation::get_Yboundary() { return {c.y - len.y, c.y + len.y}; }
bool CenterLocation::is_in_square_pos(DataOf2D p) {
    auto [ax, bx] = get_Xboundary();
    auto [ay, by] = get_Xboundary();
    return ax <= p.x && p.x <= bx && ay <= p.y && p.y <= by;
}

bool CenterLocation::is_object_collision(CenterLocation s, CenterLocation t) {
    auto [ax, bx] = s.get_Xboundary();
    auto [ay, by] = s.get_Yboundary();
    return t.is_in_square_pos(DataOf2D(ax, ay)) ||
           t.is_in_square_pos(DataOf2D(ax, by)) ||
           t.is_in_square_pos(DataOf2D(bx, ay)) ||
           t.is_in_square_pos(DataOf2D(bx, by));
}
