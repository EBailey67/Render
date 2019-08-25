#pragma once
#include <string>

class Globals
{
public:
	static constexpr int BPP = 8;
	static constexpr int MaxRow = 1080;
	static constexpr int MaxCol = 1920;
	static constexpr int DisplayWidth = 11;
	static constexpr int DisplayHeight = 8;
	static constexpr int MaxGray = 255;
	static constexpr double Epsilon = 0.00001;

	static const std::string Version;
};

