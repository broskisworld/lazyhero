#include <iostream>
#include <vector>

using namespace std;

class World
{
	int WORLD_WIDTH_BLOCK = 100;
	int WORLD_HEIGHT_BLOCK = 100;
	double WORLD_SCALE_BLOCK = 1;
	vector<vector<Block>> worldData;
	vector<Line> blockRigidBodies;
public:
	World();
	void buildLevel0();
	Block getBlockAt(int x, int y);
	void createWorldFromList();
	int getBlockWidth();
	int getBlockHeight();
	double getBlockScale();
	~World();
}