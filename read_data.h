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
	static float boundX;
	static float boundZ;
	static float boundDampingCoef;
	static float viscosityCoef;
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
	static float getBoundX() { return boundX; };
	static float getBoundZ() { return boundZ; };
	static float getBoundDampingCoef() { return boundDampingCoef; };
	static float getViscosityCoef() { return viscosityCoef; };
};

#endif