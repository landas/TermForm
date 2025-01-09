// TermForm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include "form.h"

#include "windows_tools.h"

bool quit_function(termform::component& c) {
    auto f = c.get_form();

    if (f != nullptr) {
        f->quit();
        return true;
    }

    return false;
}

/* 
todo: 
Gjør om string_list til display_object -> paint(int  x, int  y);
Ta bor x og y igjen, da display_object håndterer dette.
Hver objekt har et has_changed element... for å vudere om området skal tegnes opp på nytt.
*/

static void std_print(const std::string& s) { std::cout << s << std::flush; };

int main()
{
    int width = 0;
    int height = 0;


    if (!get_console_size(width, height)) 
    {
        std::cout << "Could not get console size" << std::endl;
        return 1;
    }

    std::cout << "Console info" << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;

    /*
    std::string test_string{ "Jeg \033[33mspiser\033[37m mat hver dag" };
    auto codes = termform::ansi_escape_code::find_all(test_string);
    std::cout << test_string << std::endl;
    std::cout << termform::ansi_escape_code::find_first(test_string) << std::endl;
    for (const auto& code : codes) {
        std::cout << code << std::endl;
    }

    return 0;
    */

    termform::form form(width, height, &std_print);;
    auto container = termform::form::make_container<termform::row_container>();

    auto label1 = termform::form::make_control<termform::label>();
    label1->text("Text 1");
    container->add(label1);

    auto label2 = termform::form::make_control<termform::label>();
    label2->text("Text 2");
    container->add(label2);

    auto checkbox1 = termform::form::make_control<termform::checkbox>();
    checkbox1->text("Enable SSL");
    container->add(checkbox1);

    auto menu_item1 = termform::form::make_control<termform::button>();
    menu_item1->text("Button 1");
    container->add(menu_item1);    
    
    auto menu_item2 = termform::form::make_control<termform::button>();
    menu_item2->text("Button 2");
    container->add(menu_item2);

    auto container2 = termform::form::make_container<termform::row_container>();
    
    auto menu_item3 = termform::form::make_control<termform::button>();
    menu_item3->text("Button 3");
    container2->add(menu_item3);

    auto menu_item4 = termform::form::make_control<termform::button>();
    menu_item4->text("Quit");
    menu_item4->set_on_enter(&quit_function);
    container2->add(menu_item4);

    container->add(container2);
   
    auto textinput1 = termform::form::make_control<termform::textfield>(20, "0.0.0.0");
    textinput1->label("IP-address");
    container->add(textinput1);
   
    auto radioA_1 = termform::form::make_control<termform::radio_button>("A");
    radioA_1->label("Radio valg 1");
    container->add(radioA_1);

    auto radioA_2 = termform::form::make_control<termform::radio_button>("A");
    radioA_2->label("Radio valg 1");
    container->add(radioA_2);

    auto radioA_3 = termform::form::make_control<termform::radio_button>("A");
    radioA_3->label("Radio valg 1");
    container->add(radioA_3);

    auto radioB_1 = termform::form::make_control<termform::radio_button>("B");
    radioB_1->label("Radio valg 1");
    container->add(radioB_1);

    auto radioB_2 = termform::form::make_control<termform::radio_button>("B");
    radioB_2->label("Radio valg 1");
    container->add(radioB_2);


    form.set(container);
    form.status("Sizeof termform::button: " + std::to_string(sizeof(termform::button)) +
        ", termform::component: " + std::to_string(sizeof(termform::component)) +
        ", int: " + std::to_string(sizeof(int)) +
        ", uint16_t: " + std::to_string(sizeof(int16_t)) +
        ", std::string: " + std::to_string(sizeof(std::string)));

    std::string test{};

    while (true)
    {
        form.display();
        int16_t key = static_cast<int16_t>(_getch());

        
        if (key == 224) {
            key = static_cast<int16_t>(_getch());
            if (key == 72) 
                key = termform::keycode.arrow_up;
            else if (key == 80)
                key = termform::keycode.arrow_down;
            else if (key == 75)
                key = termform::keycode.arrow_left;
            else if (key == 77)
                key = termform::keycode.arrow_right;
            else
                key = 0;
            
        }
        

        test += std::to_string(key) + ",";
        form.status(test);


        form.input(key);

        if (form.is_quitting()) {
            std::cout << termform::ansi_escape_code::get_clear_all();
            break;
        }
    }
    return 0;
}



