#ifndef PANDORY_RADIOBUTTONS_H
#define PANDORY_RADIOBUTTONS_H


#include <gtkmm/window.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/box.h>
#include <gtkmm/separator.h>

class RadioButtons : public Gtk::Window {
public:
    RadioButtons();
    virtual ~RadioButtons();

protected:
    //Signal handlers:
    void on_button_clicked();

    //Child widgets:
    Gtk::Box m_Box_Top;
    //Child widgets:
    Gtk::Box m_Box1;
    //Child widgets:
    Gtk::Box m_Box2;
    Gtk::RadioButton m_RadioButton1, m_RadioButton2, m_RadioButton3;
    Gtk::Separator m_Separator;
    Gtk::Button m_Button_Close;
};


#endif //PANDORY_RADIOBUTTONS_H
