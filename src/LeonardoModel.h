#ifndef LEONARDO_H
#define LEONARDO_H

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/VRMLnodes/SoVRMLTransform.h>

class LeonardoModel
{
private:
	SoSeparator* sceneGraph;
	SoVRMLTransform* trnsfX;
	SoVRMLTransform* trnsfY;
	SoVRMLTransform* trnsfA;
	SoVRMLTransform* trnsfS1;
	SoVRMLTransform* trnsfS2;
	SoVRMLTransform* trnsfS3;
	SoVRMLTransform* trnsfE1;
	SoVRMLTransform* trnsfE2;
	SoVRMLTransform* trnsfW1;
	SoVRMLTransform* trnsfW2;

	static double DEG2RAD;
	static double RAD2DEG;

public:
	LeonardoModel();
	virtual ~LeonardoModel();
	
	void setSceneGraph(SoSeparator* sceneGraph);
	void setConfiguration(double x, double y, double a,
		double s1, double s2, double s3, double e1, double e2,
		double w1, double w2);
};

#endif //LEONARDO_H
