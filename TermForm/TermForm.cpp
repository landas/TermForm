// TermForm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "form.h"

int main()
{
    termform::form form{};
    auto container = termform::form::make_container<termform::row_container>();
    form.add(container);

    auto text1 = termform::form::make_control<termform::text>();
    text1->value("Text 1");
    container->add(text1);

    auto text2 = termform::form::make_control<termform::text>();
    text2->value("Text 2");
    container->add(text2);

    form.print();
}


