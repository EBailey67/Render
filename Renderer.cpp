#include "Renderer.h"

#include <iostream>

int Renderer::ProcessCommandline(int argc, char* argv[])
{
	if (argc < 2)	// No parameters passed in.
	{
		std::cout << "Scene description file :";
		std::getline(std::cin, InputFilename);

		std::cout << "Output image name (.raw) :";
		std::getline(std::cin, OutputFilename);
		std::cout << std::endl;

		return OpenFiles();
	}

	return true;
}

int Renderer::OpenFiles()
{
	InputStream.open(InputFilename, std::ios::in);
	if (!InputStream.is_open())
	{
		std::cerr << "Unable to open " << InputFilename << " for the scene." << std::endl;
		return false;
	}

	OutputStream.open(OutputFilename, std::ios::out);
	if (!OutputStream.is_open())
	{
		std::cerr << "Unable to create " << OutputFilename << " for the image." << std::endl;
		return false;
	}
}