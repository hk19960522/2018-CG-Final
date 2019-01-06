#include <fstream>
#include <iostream>
#include <string>
#include "read_data.h"
#define DATA_FILE_NAME	"particle_data.txt"

using namespace std;

float DATA_READER::mParticleScale = 0.01;
float DATA_READER::mParticleRadius = 0.1;
std::string DATA_READER::mParticleMeshName = "sphere.mesh";
float DATA_READER::mParticleMass = 10;
float DATA_READER::mSmoothSize = 0.2f;
float DATA_READER::mInitDensity = 20.0f;
float DATA_READER::pressureCoef = 20.0f;
float DATA_READER::boundX = 10.0;
float DATA_READER::boundZ = 10.0;
float DATA_READER::boundDampingCoef = 0.01;
float DATA_READER::viscosityCoef = 0.018;

DATA_READER::DATA_READER()
{

}

void DATA_READER::readData()
{
	using namespace std;
	std::ifstream *fp;
	fp = new std::ifstream(DATA_FILE_NAME, ios::in | ios::binary);
	if (fp == 0 || fp->fail()) {
		cout << "Cannot open data file:" << DATA_FILE_NAME << endl;
		return;
	}
	
	std::string key;
	double num;
	while (!fp->eof()) {
	*fp >> key;

		if (key.compare("PARTICLE_SCALE") == 0) {
			*fp >> mParticleScale; // bug here
			cout << "particle scale = " << mParticleScale <<endl;
		}

		if (key.compare("PARTICLE_MESH_NAME") == 0) {
			*fp >> mParticleMeshName;
			cout << "particle mesh name = " << mParticleMeshName <<endl;
		}
		if (key.compare("PARTICLE_RADIUS") == 0) {
			*fp >> mParticleRadius;
			cout << "----------------------------------particle radius = " << mParticleRadius <<endl;
		}
		if (key.compare("PARTICLE_MASS") == 0){
			*fp >> mParticleMass;
			cout << "----------------------------------particle mass = " << mParticleMass <<endl;
		}
		if (key.compare("SMOOTH_SIZE") == 0) {
			*fp >> mSmoothSize;
		}
		if (key.compare("INIT_DENSITY") == 0) {
			*fp >> mInitDensity;
		}
		if (key.compare("PRESSURE") == 0) {
			*fp >> pressureCoef;
		}
		if (key.compare("MAX_X") == 0) {
			*fp >> boundX;
		}
		if (key.compare("MAX_Z") == 0) {
			*fp >> boundZ;
		}
		if (key.compare("VISCOSITY") == 0) {
			*fp >> viscosityCoef;
		}
		if (key.compare("DAMP_COEF") == 0) {
			*fp >> boundDampingCoef;
		}
	}

}

float DATA_READER::getParticleScale()
{
	return mParticleScale;
}

std::string DATA_READER::getParticleMeshName()
{
	return mParticleMeshName;
}
	
float DATA_READER::getParticleRadius()
{
	return mParticleRadius;
}

float DATA_READER::getParticleMass()
{
	return mParticleMass;
}