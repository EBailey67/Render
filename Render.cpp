// Render.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Globals.h"
#include "Random.h"
#include "Renderer.h"

int main(int argc, char *argv[], char *envp[])
{
	Renderer renderer;

    std::cout << Globals::Version << std::endl;
	renderer.ProcessCommandline(argc, argv);

	std::cout << GetNextRand();
}

