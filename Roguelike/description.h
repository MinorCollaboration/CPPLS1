#pragma once
#include <string>
#include <iostream>
#include "Utils.h"
#include <list>

class description
{
private:
	std::string _description;


public:
	void drawUI();
	void generateDescription();
	std::string const getDescription();
	void setDescription(const std::string& description) { _description = description; }
	enum Direction { N, E, S, W };

	description();
	~description();
};

