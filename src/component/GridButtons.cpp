#include <component/GridButtons.hpp>

GridButtons::GridButtons(Location draw_domain, int number_xbtn, int number_ybtn,
                         double x_interval, double y_interval)
    : xn(number_xbtn), yn(number_ybtn), x_interval(x_interval),
      y_interval(y_interval) {
    this->draw_domain = draw_domain;
    buttons.assign(yn, vector<Button_ONOF *>(xn));
    double sx = draw_domain.sx, sy = draw_domain.sy;
    double xlen = (draw_domain.xlen - (xn - 1) * x_interval) / xn;
    double ylen = (draw_domain.ylen - (yn - 1) * y_interval) / yn;
    for(int i = 0; i < yn; i++) {
        for(int j = 0; j < xn; j++) {
            glBegin(GL_LINE_LOOP);
            glVertex2d(sx, sy);
            glVertex2d(sx + xlen, sy);
            glVertex2d(sx + xlen, sy + ylen);
            glVertex2d(sx, sy + ylen);
            glEnd();
            buttons[i][j] = new Button_ONOF(sx, sy, xlen, ylen);
            sx += xlen + x_interval;
        }
        sx = draw_domain.sx;
        sy += ylen + y_interval;
    }
}

void GridButtons::view() {
    for(int i = 0; i < yn; i++) {
        for(int j = 0; j < xn; j++) {
            bool has = false;
            for(auto &&e : valids) {
                if(e == card_id_of_index(i, j)) {
                    has = true;
                    break;
                }
            }
            vector<double> col = {0.0, 1.0, 0.0};
            if(!has) {
                buttons[i][j]->set_color(col);
                buttons[i][j]->button_view();
            } else if(selected_y == i && selected_x == j) {
                buttons[i][j]->button_filled_view();
            } else {
                buttons[i][j]->button_view();
            }
        }
    }
}
void GridButtons::btns_valid(double x, double y) {
    for(int i = 0; i < yn; i++) {
        for(int j = 0; j < xn; j++) {
            if(buttons[i][j]->valid_push_location(x, y)) {
                buttons[i][j]->action_when_pushed();
                selected_x = j;
                selected_y = i;
            }
        }
    }
}
GridButtons::~GridButtons() {}
