#include "description.h"

description::description()
{
}

void description::drawUI()
{
	//Tekent de map.
	std::cout << "\n================ Overleef de zee ====================\n";

	std::string spacer = "";

	std::cout << "\n\n\n";
}

void description::generateDescription()
{
	std::string desc("Je schip ");

	//2*1=2
	std::string Actie[2] = { "vaart", "vecht zich" };
	//desc.append(Actie[utils::random(0, (sizeof(Actie) / sizeof(*Actie)) - 1)] + " ");

	//3*2=6
	std::string Plek[3] = { "door de zee", "door de golven", "richting de haven" };
	//desc.append(Plek[utils::random(0, (sizeof(Plek) / sizeof(*Plek)) - 1)] + ". ");

	setDescription(desc);
}

std::string const description::getDescription() {
	std::string desc = _description;
	desc.append("Voor de rest lijkt het hier rustig te zijn. ");
	return (desc);
}


description::~description()
{
}
