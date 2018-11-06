#include "pch.h"
#include "SPHKernels.h"

int test = 0;
SPHKernels::SPHKernels(float r)
{
	kernel_radius = r;
	kernel_radius_squared = r * r;
	spiky_const = 15.0 / (pi*pow(kernel_radius, 6));
	poly_6_const = 315.0 / (64*pi*pow(kernel_radius, 9));
	poly_6_grad_const = -945.0 / (32 * pi*pow(kernel_radius, 9));
	poly_6_lap_const = -945.0 / (32 * pi*pow(kernel_radius, 9));
	visc_const = 20 / (pi * pow(kernel_radius, 6));
	st = 50;
}

void SPHKernels::density(Particle* p1, Particle* p2) {
	float xDistance = p1->getX() - p2->getX();
	float yDistance = p1->getY() - p2->getY();
	float distanceSquared = xDistance * xDistance + yDistance * yDistance;
	if (kernel_radius_squared > distanceSquared) {
		float extra_density = (p1->getMass())*poly_6_const*pow((kernel_radius_squared - distanceSquared), 3);
		//assumes p1 and p2 have same mass
		p1->addDensity(extra_density);
		p2->addDensity(extra_density);
	}
}

void SPHKernels::viscosity(Particle* p1, Particle* p2) {
	test++;
	float xDistance = p1->getX() - p2->getX();
	float yDistance = p1->getY() - p2->getY();
	float distanceSquared = xDistance * xDistance + yDistance * yDistance;
	float distance = sqrt(distanceSquared);
	float du, dv, visc_force ;
	if (kernel_radius_squared > distanceSquared) {
			visc_force = visc_const*p2->getMass() * ((p2->getU() - p1->getU()) / p2->getDensity()) * (kernel_radius-distance);
			du = visc_force;
			visc_force = visc_const*p2->getMass() * ((p2->getV() - p1->getV()) / p2->getDensity()) * (kernel_radius-distance);
			dv = visc_force;
			p1->addForce(dv, du);
			visc_force = visc_const*p1->getMass() * ((p1->getU() - p2->getU()) / p1->getDensity()) * (kernel_radius-distance);
			du = visc_force;
			visc_force = visc_const*p1->getMass() * ((p1->getV() - p2->getV()) / p1->getDensity()) * (kernel_radius-distance);
			dv = visc_force;
			p2->addForce(dv, du);
	}
}

void SPHKernels::pressure(Particle* p1, Particle* p2) {
	float xDistance = p1->getX() - p2->getX();
	float yDistance = p1->getY() - p2->getY();
	float distanceSquared = xDistance * xDistance + yDistance * yDistance;
	if (kernel_radius_squared > distanceSquared) {
		float pressure_force = ((p1->getPressure() + p2->getPressure()) / (2 * p2->getDensity())) * 24 / (pi*pow(kernel_radius, 5)) * (sqrt(kernel_radius_squared) - sqrt(distanceSquared));
		float du = pressure_force * (xDistance / sqrt(distanceSquared));
		float dv = pressure_force * (yDistance / sqrt(distanceSquared));
		p1->addForce(du, dv);
		pressure_force = ((p2->getPressure() + p1->getPressure()) / (2 * p1->getDensity())) * 24 / (pi*pow(kernel_radius, 5)) * (sqrt(kernel_radius_squared) - sqrt(distanceSquared));
		du = -pressure_force * (xDistance / sqrt(distanceSquared));
		dv = -pressure_force * (yDistance / sqrt(distanceSquared));
		p2->addForce(du, dv);
	}
}

void SPHKernels::surface_tension(Particle* p1, Particle* p2) {
	float xDistance = p1->getX() - p2->getX();
	float yDistance = p1->getY() - p2->getY();
	float distanceSquared = xDistance * xDistance + yDistance * yDistance;
	if (kernel_radius_squared > distanceSquared) {
		float n = (p1->getMass()/p1->getDensity()) * poly_6_grad_const * pow((kernel_radius_squared - distanceSquared), 2);
		float surface_force = st*(p1->getMass() / p1->getDensity()) * poly_6_lap_const * (distanceSquared-kernel_radius_squared)*(5*distanceSquared-kernel_radius_squared)* n / abs(n);
		float du = surface_force * (xDistance / sqrt(distanceSquared));
		float dv = surface_force * (yDistance / sqrt(distanceSquared));
		p1->addForce(du, dv);
		n = (p2->getMass() / p2->getDensity()) * poly_6_grad_const * pow((kernel_radius_squared - distanceSquared), 2);
		surface_force = st*(p2->getMass() / p2->getDensity()) * poly_6_lap_const * (distanceSquared - kernel_radius_squared)*(5 * distanceSquared - kernel_radius_squared)* n / abs(n);
		du = -surface_force * (xDistance / sqrt(distanceSquared));
		dv = -surface_force * (yDistance / sqrt(distanceSquared));
		p2->addForce(du, dv);
	}
}

SPHKernels::~SPHKernels()
{
}
