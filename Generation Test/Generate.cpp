#include "Generate.h"
#include <iostream>

generation::generation(int seed, int elements)
	:seed(seed), elements(elements), pl(nullptr)
{
	this->startPlat = new platform(Vector3(), 0, 0);
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
	Vector3 dVect;
	Vector3 position;
	int stepMax = pl->getJumpDistance();
	float stepMin = pl->getJumpDistance() / 2 * selectedDiff;
	int stepMaxZ = pl->jumpHeight();
	platform* current = startPlat;
	platform* newPlat = nullptr;
	for (int i = 0; i < this->elements; i++) {
		
		dVect.z = (rand() % (2 * stepMax) )- stepMax - 1;
		dVect.z = fmin(dVect.z, stepMaxZ);
		position.z += dVect.z;
		// Using the height the new platform to determine max distance
		stepMax = pl->getJumpDistance(position.z);
		stepMin = pl->getJumpDistance(position.z) / 10 * selectedDiff;
		// Generating x and y pos
		dVect.x = (rand() % (stepMax - (int)stepMin + 1));
		dVect.y = (rand() % (2 * stepMax)) - stepMax - 1;
		position.x += dVect.x;
		position.y += dVect.y;

		if (
			dVect.magnitude() > stepMin &&
			dVect.magnitude() < stepMax)
		{
			newPlat = new platform(position, 0, 1);
			pl->moveto(newPlat->getPos());
			current->next = newPlat;
			this->anchors.push_back(current);
			current = newPlat;
			std::cout << "Hello\n";
		}
		else {
			i -= 1; 
			position.x -= dVect.x;
			position.y -= dVect.y;
			position.z -= dVect.z;
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

