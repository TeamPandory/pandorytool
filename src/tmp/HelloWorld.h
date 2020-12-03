//
// Created by dajoho on 08.11.20.
//

#ifndef PANDORY_HELLOWORLD_H
#define PANDORY_HELLOWORLD_H


#include <gtkmm/window.h>
#include <gtkmm/button.h>

class HelloWorld : public Gtk::Window {
public:
    HelloWorld();

    virtual ~ HelloWorld();

protected:
    //Signal handlers:
    void on_button_clicked();

    //Member widgets:
    Gtk::Button m_button;
};


#endif //PANDORY_HELLOWORLD_H
