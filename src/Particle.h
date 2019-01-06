#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>
class Particle
{
public:
	Particle(float, float, float, float, float rd, float fc);
	Particle();

	float getX();
	float getY();
	float getV();
	float getU();
	float getDv();
	float getDu();
	float getMass();
	float getViscosity();
	float getAvDensity();
	float getDensity();
	float getPressure0();
	float getPressure();
	int getIndex();


	void setX(float);
	void setY(float);
	void setU(float);
	void setV(float);
	void setIndex(int);
	void setPressure();

	void addDensity(float);

	void addForce(float, float);

	void update(float);

	~Particle();

	sf::Color col;

private:
	float x, y;
	float v, u;
	float dv, du;
	float mass;
	float viscosity;
	float av_density, density;
	float pressure0, pressure;
	float rest_density;
	float fluid_constant;
	float minDensity;

	int index;	
};

