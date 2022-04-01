#include "Generate.h"
#include <iostream>
generation::generation(int seed, int elements)
	:seed(seed), elements(elements), pl(nullptr)
{
	this->startPlat = new platform({ 0.0f, 0.0f, 0.0f }, 0,0);
}

generation::~generation()
{
	this->startPlat = nullptr;
	for (int i = 0; i < anchors.size(); i++) {
		delete anchors.at(i);
	}
	anchors.clear();
}

bool generation::start(int selectedDiff)
{
	srand(this->seed);
	float xPos = 0;
	float yPos = 0;
	float zPos = 0;
	float dxPos = 0; 
	float dyPos = 0; 
	float dzPos = 0;
	int stepMax = pl->getJumpDistance();
	int stepMin = pl->getJumpDistance() / 10 * selectedDiff;
	platform* current = startPlat;
	platform* newPlat = nullptr;
	for (int i = 0; i < this->elements; i++) {
		dxPos = stepMin + (rand() % (stepMax - stepMin + 1));
		dyPos = (rand() % (2 * stepMax + 1)) - stepMax;
		dzPos = (rand() % (2 * stepMax + 1)) - stepMax;
		xPos += dxPos;
		yPos += dyPos;
		zPos += dzPos;
		if (this->pl->isJumpPossible({xPos, yPos, zPos}) ){
			newPlat = new platform({ xPos, yPos, zPos }, 0, 1);
			pl->moveto(newPlat->getPos());
			current->next = newPlat;
			this->anchors.push_back(current);
			current = newPlat;
		}
		else {
			i -= 1; 
			xPos -= dxPos;
			yPos -= dyPos;
			zPos -= dzPos;
			std::cout << "Jump not possible\n";
		}
	}
	this->anchors.push_back(newPlat);
	return true;
}

std::vector<platform*> generation::getPlatforms()
{
	return this->anchors;
}

void generation::assignPlayer(player* player)
{
	this->pl = player;
}
