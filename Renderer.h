#pragma once

#include <string>
#include <iostream>
#include <fstream>

class Renderer
{
private:
	int OpenFiles();

	// Renderer state values
	double RenderTime = 1.0;			// Time (in hours) to allow the renderer to run
	int StartRow = 0;					// Starting scanline
	int EndRow = 512;					// Ending scanline
	double IndexOfRefraction = 1.0;		// Index of refraction
	double AmbientScale = 1.0;			// Ambient light scale
	int Histogram = 0;					// Generate a histogram
	int Antialias = 1;					// Should we perform antialiasing
	double AntialiasVariance = 0.00097;	// Variance for antialiasing


protected:
	std::string InputFilename;
	std::string OutputFilename;
	std::ifstream InputStream;
	std::ofstream OutputStream;

public:

	int ProcessCommandline(int argc, char* argv[]);
	void ReadSceneFile();
};

