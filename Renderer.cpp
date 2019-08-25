#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <vector>

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

	ReadSceneFile();
}

void Renderer::ReadSceneFile()
{
	std::string line;

	while (!InputStream.eof())
	{
		std::vector<std::string> tokens;
		std::string tstring;

		std::getline(InputStream, line);
		std::stringstream linestream(line);

		while (std::getline(linestream, tstring, ' '))
		{
			tokens.push_back(tstring);
		}

		//for (int i = 0; i < tokens.size(); ++i)
		//{
		//	std::cout << tokens[i] << ",";
		//}

		if (tokens.size() < 1)
			return;

		if (tokens[0] == "R")
		{
			RenderTime = std::stod(tokens[1]);
			std::cout << "Render time :" << RenderTime << std::endl;
		}
		else if (tokens[0] == "&")
		{
			if (tokens.size() < 3)
			{
				std::cerr << "Error parsing row start and end" << std::endl;
				return;
			}

			StartRow = std::stoi(tokens[1]);
			EndRow = std::stoi(tokens[2]);

			std::cout << "Start and End Rows :" << StartRow << " - " << EndRow << std::endl;
		}
		else if (tokens[0] == "N")
		{
			IndexOfRefraction = std::stod(tokens[1]);
			std::cout << "Index of Refraction :" << IndexOfRefraction << std::endl;
		}
		else if (tokens[0] == "Z")
		{
			Histogram = std::stoi(tokens[1]);
			std::cout << "Histogram :" << Histogram << std::endl;
		}
		else if (tokens[0] == "a")
		{
			AmbientScale = std::stod(tokens[1]);
			std::cout << "Ambient Scale :" << AmbientScale << std::endl;
		}
		else if (tokens[0] == "A")
		{
			if (tokens.size() < 3)
			{
				std::cerr << "Error parsing antialias" << std::endl;
				return;
			}

			Antialias = std::stoi(tokens[1]);
			AntialiasVariance = std::stod(tokens[2]);

			std::cout << "Antialias :" << Antialias << " - Variance :" << AntialiasVariance << std::endl;
		}
	}
}