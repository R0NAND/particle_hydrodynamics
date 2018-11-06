#pragma once
#include "Particle.h"
#include <math.h>
class SPHKernels
{
public:
	SPHKernels(float r);

	void density(Particle*, Particle*);
	void viscosity(Particle*, Particle*);
	void pressure(Particle*, Particle*);
	void surface_tension(Particle*, Particle*);

	~SPHKernels();

private:
	const float pi = 3.1415927;
	float st;
	float kernel_radius;
	float kernel_radius_squared;
	float spiky_const;
	float poly_6_const;
	float poly_6_grad_const;
	float poly_6_lap_const;
	float visc_const;
};

