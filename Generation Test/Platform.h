#include <vector>
#include <math.h>
#include <memory>

class platform {
private:
	std::vector<float> pos;
	int obstacles;
	int difficluty;
public:
	platform();
	platform(std::vector<float> pos, int obstacles, int difficluty);
	~platform();
	void setPosition(float x, float y, float z);
	void move(float xOfset, float yOfset, float zOfset);
	std::vector<float> getPos();
	float distance(std::vector<float> &position);
	platform* next;
};