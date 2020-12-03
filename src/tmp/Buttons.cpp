#include <iostream>
#include "Buttons.h"

Buttons::Buttons()
{
    c_button.add_pixlabel("info.xpm", "cool button");

    set_title("Pixmap'd buttons!");
    set_border_width(10);

    c_button.signal_clicked().connect( sigc::mem_fun(*this,
                                                     &Buttons::on_button_clicked) );

    add(c_button);

    show_all_children();
}

Buttons::~Buttons()
{
}

void Buttons::on_button_clicked()
{
    std::cout << "The Button was clicked." << c_button.get_active() << std::endl;
}