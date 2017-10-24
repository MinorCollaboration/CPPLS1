#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <random>

namespace Utils {
	std::string getCustomPath();
	int Random();
	int Random(int);
	int Random(int, int);
	void Print(std::string text);
	void PrintLine(std::string text);
	void PrintCool(std::string text);
	int ReadLine();
	std::string ReadString();
	void SaveFile(std::string file);
	void ReadFile(std::string file);
	struct Vector {
		int x;
		int y;
		int z;
	public:
		bool Equals(Vector v)
		{
			return (x == v.x && y == v.y && z == v.z);
		}
	};
	Vector RandomLocation(int width, int height, int floor);
	Vector Location(int x, int y, int z);
	void cClear();
	void cPauze();
	bool change(int perc);


}

