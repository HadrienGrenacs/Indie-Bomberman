/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "initGame.hpp"

int main()
{
    try
    {
        initGame init(1920, 1080);
        init.loop();
    }
    catch (const runtime_error &str)
    {
        cerr << str.what() << endl;
    }
    catch (const std::string &str)
    {
        cerr << str << endl;
    }

    return (0);
}