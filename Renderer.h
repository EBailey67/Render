#pragma once

#include <string>
#include <iostream>
#include <fstream>

class Renderer
{
private:
	int OpenFiles();

protected:
	std::string InputFilename;
	std::string OutputFilename;
	std::ofstream InputStream;
	std::ofstream OutputStream;

public:

	int ProcessCommandline(int argc, char* argv[]);
};

