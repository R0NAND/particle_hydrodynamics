#pragma once
#include <vector>
#include "Particle.h"
#include "SpatialGrid.h"
#include "SPHKernels.h"
#include <SFML/Graphics.hpp>

class Fluid
{
public:
	Fluid(int, float);
	void update(float dt);
	void getCoordinates(std::vector<float> &x, std::vector<float> &y);
	void getCol(std::vector<sf::Color> &col);
	void walls(float dt);
	void mousePush(float x, float y, float x_f, float y_f);
	~Fluid();
private:
	int num_particles;
	std::vector<Particle> Particles;
	std::vector<Particle *> addresses;

	SpatialGrid *optimize;
	SPHKernels *forces;

	int kernel_radius;

	float ex_x;
	float ex_y;
	float ex_force_x;
	float ex_force_y;

	const float rest_density = 0.05;
	const float fluid_constant = 600;

	void calculatePressure();
	void calculateForces();
	void color();
	void integrate(float dt);

};


