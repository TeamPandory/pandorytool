#include <iostream>
#include "HelloWorld.h"

HelloWorld::HelloWorld() : m_button("Hello World") {
    // Sets the border width of the window.
    set_border_width(10);

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    m_button.signal_clicked().connect(
            sigc::mem_fun(*this, &HelloWorld::on_button_clicked)
    );

    // This packs the button into the Window (a container).
    add(m_button);

    // The final step is to display this newly created widget...
    m_button.show();
}

void HelloWorld::on_button_clicked() {
    std::cout << "Hello World" << std::endl;
}

HelloWorld::~HelloWorld() {

}

