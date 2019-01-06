#pragma once
#include "Particle.h"
#include <vector>

class SpatialGrid
{
public:
	SpatialGrid(float right_wall, float base, float kernel_radius);
	
	void hash(std::vector<Particle *>&);
	void sort(std::vector<Particle *>&);
	void point(std::vector<Particle *>);

	int getMainPointer(int);
	int getTopLeftPointer(int);
	int getTopPointer(int);
	int getTopRightPointer(int);
	int getRightPointer(int);
	int getBottomRightPointer(int);
	int getBottomPointer(int);
	int getBottomLeftPointer(int);
	int getLeftPointer(int);

	bool hasTopLeft(int);
	bool hasTop(int);
	bool hasTopRight(int);
	bool hasRight(int);
	bool hasBottomRight(int);
	bool hasBottom(int);
	bool hasBottomLeft(int);
	bool hasLeft(int);

	~SpatialGrid();

private:
	int gridX;
	int gridY;
	float gridLength;
	float gridHeight;
	int indexSize;
	float size;

	std::vector<int> particle_pointers;

	int GetMax(std::vector<Particle *>& addresses);
	void CountSort(std::vector<Particle *>& addresses, int);
};

