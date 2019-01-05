#ifndef __DATA_READER_H__
#define __DATA_READER_H__

#include <string>

class DATA_READER {
protected:
	static float mParticleRadius;
	static float mParticleMass;
	static std::string mParticleMeshName;
	static float mParticleScale;
	static float mSmoothSize;
	static float mInitDensity;
	static float pressureCoef;
public:
	DATA_READER();
	static void readData();
	static float getParticleScale();
	static std::string getParticleMeshName();
	static float getParticleRadius();
	static float getParticleMass();
	static float getSmoothSize() { return mSmoothSize; };
	static float getInitDensity() { return mInitDensity; };
	static float getPressureCoef() { return pressureCoef; };
};

#endif