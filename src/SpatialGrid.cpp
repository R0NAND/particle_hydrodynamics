#include "SpatialGrid.h"
#include <iostream>


SpatialGrid::SpatialGrid(float right_wall, float base, float kernel_radius)
{
	gridX = int(right_wall / kernel_radius) + 1;
	gridY = int(base / kernel_radius) + 1;
	gridLength = gridX * kernel_radius;
	gridHeight = gridY * kernel_radius;
	indexSize = gridX * gridY;
	size = kernel_radius;

	particle_pointers.resize(gridX*gridY);
}

void SpatialGrid::hash(std::vector<Particle *>& addresses) {
	for (int i = 0; i < addresses.size(); i++) {
		addresses[i]->setIndex((int(addresses[i]->getX()/size)) + (int(addresses[i]->getY()/size)* gridX));
	}
}

int SpatialGrid::GetMax(std::vector<Particle *>& addresses) {
	int mx = addresses[0]->getIndex();

	for (int i = 1; i < addresses.size(); i++)
		if (addresses[i]->getIndex() > mx)
			mx = addresses[i]->getIndex();
	return mx;
}

//this sorting code was modified from an online source
void SpatialGrid::CountSort(std::vector<Particle *> &addresses, int exp) {
	std::vector<Particle *> addresses_output(addresses.size());

	int i, count[10] = { 0 };

	for (i = 0; i < addresses.size(); i++)
		count[(addresses[i]->getIndex() / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = addresses.size() - 1; i >= 0; i--)
	{
		addresses_output[count[(addresses[i]->getIndex() / exp) % 10] - 1] = addresses[i];
		count[(addresses[i]->getIndex() / exp) % 10]--;
	}

	for (i = 0; i < addresses.size(); i++) {
		addresses[i] = addresses_output[i];
	}
}

void SpatialGrid::sort(std::vector<Particle *> &addresses)
{
	int m = GetMax(addresses);

	for (int exp = 1; m / exp > 0; exp *= 10)
		CountSort(addresses, exp);
}

void SpatialGrid::point(std::vector<Particle *> addresses) {
	int lastIndex = 0;
	bool assigned0Index = false;
	bool assignedLastIndex = false;
	for (int i = 0; i < addresses.size(); i++) {
		if (addresses[i]->getIndex() == 0 && assigned0Index == false) {
			particle_pointers[0] = 0;
			assigned0Index = true;
		}
		else {
			particle_pointers[0] = -1;
		}
		if (addresses[i]->getIndex() > lastIndex) {
			for (int d = lastIndex + 1; d < addresses[i]->getIndex(); d++) {
				particle_pointers[d] = -1;
			}
			particle_pointers[addresses[i]->getIndex()] = i;
			lastIndex = addresses[i]->getIndex();
		}
		if (i == addresses.size() - 1 && addresses[i]->getIndex() < indexSize - 1) {
			for (int d = lastIndex + 1; d < indexSize; d++) {
				particle_pointers[d] = -1;
			}
		}
	}
}

int SpatialGrid::getMainPointer(int index) {
	return particle_pointers[index];
}

int SpatialGrid::getTopLeftPointer(int index) {
	return particle_pointers[index - gridX - 1];
}

int SpatialGrid::getTopPointer(int index) {
	return particle_pointers[index - gridX];
}

int SpatialGrid::getTopRightPointer(int index) {
	return particle_pointers[index - gridX + 1];
}

int SpatialGrid::getRightPointer(int index) {
	return particle_pointers[index + 1];
}

int SpatialGrid::getBottomRightPointer(int index) {
	return particle_pointers[index + gridX + 1];
}

int SpatialGrid::getBottomPointer(int index) {
	return particle_pointers[index + gridX];
}

int SpatialGrid::getBottomLeftPointer(int index) {
	return particle_pointers[index + gridX - 1];
}

int SpatialGrid::getLeftPointer(int index) {
	return particle_pointers[index - 1];
}


bool SpatialGrid::hasTopLeft(int index) {
	if (index%gridX != 0 && index >= gridX) {
		if (particle_pointers[index - gridX - 1] != -1) {
			return true;
		}
	}
	return false;
}

bool SpatialGrid::hasTop(int index) {
	if (index >= gridX) {
		if (particle_pointers[index - gridX] != -1) {
			return true;
		}
	}
	return false;
}

bool SpatialGrid::hasTopRight(int index) {
	if (index%gridX != gridX - 1 && index >= gridX) {
		if (particle_pointers[index - gridX + 1] != -1) {
			return true;
		}
	}
	return false;
}

bool SpatialGrid::hasRight(int index) {
	if (index%gridX != gridX - 1) {
		if (particle_pointers[index + 1] != -1) {
			return true;
		}
	}
	return false;
}

bool SpatialGrid::hasBottomRight(int index) {
	if (index%gridX != gridX - 1 && index < indexSize - gridX) {
		if (particle_pointers[index + gridX + 1] != -1) {
			return true;
		}
	}
	return false;
}

bool SpatialGrid::hasBottom(int index) {
	if (index < indexSize - gridX) {
		if (particle_pointers[index + gridX] != -1) {
			return true;
		}
	}
	return false;
}

bool SpatialGrid::hasBottomLeft(int index) {
	if (index%gridX != 0 && index < indexSize - gridX) {
		if (particle_pointers[index + gridX - 1] != -1) {
			return true;
		}
	}
	return false;
}

bool SpatialGrid::hasLeft(int index) {
	if (index%gridX != 0) {
		if (particle_pointers[index - 1] != -1) {
			return true;
		}
	}
	return false;
}




SpatialGrid::~SpatialGrid()
{
}
