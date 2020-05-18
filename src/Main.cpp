#include "Application.h"

#include <iostream>

int main(int argc, char* argv[])
{
    Application app(1280, 800, "Minecraft Clone");

    app.run();

    return 0;
}