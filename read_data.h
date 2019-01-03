#ifndef __DATA_READER_H__
#define __DATA_READER_H__

#include <string>

class DATA_READER {
protected:
	static float mParticleRadius;
	static float mParticleMass;
	static std::string mParticleMeshName;
	static float mParticleScale;
public:
	DATA_READER();
	static void readData();
	static float getParticleScale();
	static std::string getParticleMeshName();
	static float getParticleRadius();
	static float getParticleMass();
};

#endif