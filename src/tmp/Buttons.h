//
// Created by dajoho on 08.11.20.
//

#ifndef PANDORY_BUTTONS_H
#define PANDORY_BUTTONS_H


#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/checkbutton.h>

class Buttons : public Gtk::Window {
public:
    Buttons();
    virtual ~Buttons();
protected:
    //Signal handlers:
    void on_button_clicked();

    //Child widgets:
    Gtk::Button m_button;
    Gtk::ToggleButton t_button;
    Gtk::CheckButton c_button;
};


#endif //PANDORY_BUTTONS_H
