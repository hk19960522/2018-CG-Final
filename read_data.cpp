#include <fstream>
#include <iostream>
#include <string>
#include "read_data.h"
#define DATA_FILE_NAME	"particle_data.txt"

using namespace std;

float DATA_READER::mParticleScale = 0.01;
float DATA_READER::mParticleRadius = 10;
std::string DATA_READER::mParticleMeshName = "sphere.mesh";
float DATA_READER::mParticleMass = 10;

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