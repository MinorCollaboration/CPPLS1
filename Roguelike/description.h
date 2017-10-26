#ifndef DESCRIPTION_HEADER_INCLUDED
#define DESCRIPTION_HEADER_INCLUDED

#include <string>
#include <iostream>
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

#endif