#include "pch.h"
#include "Particle.h"


Particle::Particle(float _x, float _y, float _mass, float _viscosity, float rd, float fc)
{
	x = _x;
	y = _y;
	mass = _mass;
	viscosity = _viscosity;
	rest_density = rd;
	fluid_constant = fc;
	minDensity = 9.75;
	v = 0;
	u = 0;
	dv = 0;
	du = 0;
	density = 0;
	pressure = 0;
	col = sf::Color::White;
}

Particle::Particle()
{
	x = 0;
	y = 0;
	mass = 0;
	viscosity = 0;
	v = 0;
	u = 0;
	dv = 0;
	du = 0;
	density = 0;
	pressure = 0;
}

float Particle::getX(){
	return x;
}
float Particle::getY() {
	return y;
}
float Particle::getV(){
	return v;
}
float Particle::getU(){
	return u;
}
float Particle::getDv(){
	return dv;
}
float Particle::getDu(){
	return du;
}
float Particle::getMass(){
	return mass;
}
float Particle::getViscosity(){
	return viscosity;
}
float Particle::getAvDensity(){
	return av_density;
}
float Particle::getDensity(){
	return density;
}
float Particle::getPressure0(){
	return pressure0;
}
float Particle::getPressure(){
	return pressure;
}
int Particle::getIndex(){
	return index;
}

void Particle::setX(float _x) {
	x = _x;
}
void Particle::setY(float _y) {
	y = _y;
}
void Particle::setV(float _u) {
	u = _u;
}
void Particle::setU(float _v) {
	v = _v;
}

void Particle::setIndex(int i) {
	index = i;
}

void Particle::setPressure() {
	pressure = fluid_constant * (density - rest_density);
}

void Particle::addDensity(float d) {
	density += d;
}

void Particle::addForce(float xforce, float yforce) {
	dv += xforce / density;
	du += yforce / density;
}

void Particle::update(float dt) {
	v += dv * dt;
	u += du * dt;

	x += v * dt;
	y += u * dt;

	dv = 0;
	du = 0;

	av_density = 0.98*av_density + 0.02*density;

	density = 0;
	pressure = 0;


}

Particle::~Particle()
{

}
