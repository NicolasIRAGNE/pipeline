/**
 * @file main.cpp
 * @author Nicolas IRAGNE (nicolas.iragne@alyce.fr)
 * @brief
 * @date 2022-09-25
 *
 * @copyright Copyright Alyce (c) 2022
 */

#include "pipeline.h"
#include <iostream>

using namespace niragne;

int main(int argc, char** argv)
{
    int i = 0;
    auto a = Incrementer(2);
    auto b = Incrementer(3);
    auto c = Stringifier();
    auto d = Printer();

    auto e = a >> b;
    return 0;
}
