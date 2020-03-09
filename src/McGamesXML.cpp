#include "McGamesXML.h"
#include <tinyxml2.h>
#include "Fs.h"

void McGamesXML::generate(std::string filename) {
    std::FILE* fp = std::fopen(filename.c_str(), "w");
    tinyxml2::XMLPrinter xml(fp);
    xml.PushDeclaration("xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"");

    // # Game
    xml.OpenElement("game" );
    xml.PushAttribute("emulator", emulatorId.c_str());
    xml.PushAttribute("name", romShortId.c_str());
    // ## Information
    xml.OpenElement("information" );
    // ### Description
    xml.OpenElement("description");
    xml.PushText(romDescription.c_str());
    xml.CloseElement();
    xml.OpenElement("cloneof");
    xml.CloseElement();
    xml.OpenElement("language");
    xml.PushText(language.c_str());
    xml.CloseElement();
    xml.OpenElement("year" );
    xml.PushText(year);
    xml.CloseElement();
    xml.OpenElement("manufacturer" );
    xml.PushText(romDeveloper.c_str());
    xml.CloseElement();
    xml.OpenElement("player" );
    xml.PushText(players.c_str());
    xml.CloseElement();
    xml.OpenElement("genre" );
    xml.PushText(genre);
    xml.CloseElement();
    xml.OpenElement("bootleg" );
    xml.PushText(false);
    xml.CloseElement();
    // ### /Description
    xml.CloseElement(); // ## /Information

    // ### File
    xml.OpenElement("file" );
    xml.OpenElement("rom" );
    xml.PushAttribute("name", romFileName.c_str());
    xml.CloseElement();
    xml.CloseElement();
    // ### /File

    // ### Translation
    xml.OpenElement("translation" );
    xml.OpenElement("string" );
    xml.PushAttribute("language", "EN");
    xml.OpenElement("name" );
    xml.PushText(romFullName.c_str());
    xml.CloseElement(); // name
    xml.OpenElement("detail" );
    xml.PushText(romDescription.c_str());
    xml.CloseElement(); // detail
    xml.CloseElement(); // string
    xml.CloseElement(); // translation
    // ### /File

    // ### Config
    xml.OpenElement("config" );
    xml.OpenElement("flag" );
    xml.PushText(0);
    xml.CloseElement(); // flag
    xml.OpenElement("load_time" );
	xml.PushText(emulatorLoad.c_str());
    // xml.PushText("ARSELOAD"); //TODO
    xml.CloseElement(); // load_time

    xml.OpenElement("free_play" );
    xml.PushText(true); //TODO
    xml.CloseElement(); // free_play

    xml.OpenElement("save_state" );
    xml.PushText(saveState);
    xml.CloseElement(); // save_state

    xml.OpenElement("start_directly" );
    xml.PushText(true); //TODO
    xml.CloseElement(); // start_directly

    xml.CloseElement(); // config
    // ### /Config

    xml.CloseElement(); // game
    fclose(fp);
}


