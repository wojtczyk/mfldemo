#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/VRMLnodes/SoVRMLTransform.h>
#include <Inventor/actions/SoSearchAction.h>
#include <cmath>
#include "LeonardoModel.h"

#include <iostream>

using namespace std;

double LeonardoModel::RAD2DEG = 180.0 / M_PI;

double LeonardoModel::DEG2RAD = M_PI / 180.0;

LeonardoModel::LeonardoModel()
{
};

LeonardoModel::~LeonardoModel()
{
};

void LeonardoModel::setSceneGraph(SoSeparator* sceneGraph)
{
	this->sceneGraph = sceneGraph;

	SoSearchAction* searchAction;
	SoPathList pathList;
	SoFullPath* path;
	
	searchAction = new SoSearchAction;
	searchAction->setInterest(SoSearchAction::ALL);
	searchAction->setName("X");
	searchAction->setType(SoVRMLTransform::getClassTypeId());
	searchAction->apply(sceneGraph);
	pathList = searchAction->getPaths();
	
	cout << "Found " << pathList.getLength() << " paths" << endl;
	
	for (int i = 0; i < pathList.getLength(); i++)
	{
		path = (SoFullPath*) pathList[i];
	};

	if (pathList.getLength() > 0)
	{
		path = (SoFullPath*) pathList[0];
		SoNode* node = path->getTail(); // TODO: typecheck
		trnsfX = (SoVRMLTransform*) node;
 	}
	
	delete searchAction;

	searchAction = new SoSearchAction;
	searchAction->setInterest(SoSearchAction::ALL);
	searchAction->setName("Y");
	searchAction->setType(SoVRMLTransform::getClassTypeId());
	searchAction->apply(sceneGraph);
	pathList = searchAction->getPaths();
	
	cout << "Found " << pathList.getLength() << " paths" << endl;
	
	for (int i = 0; i < pathList.getLength(); i++)
	{
		path = (SoFullPath*) pathList[i];
	};

	if (pathList.getLength() > 0)
	{
		path = (SoFullPath*) pathList[0];
		SoNode* node = path->getTail(); // TODO: typecheck
		trnsfY = (SoVRMLTransform*) node;
 	}
	
	delete searchAction;

	searchAction = new SoSearchAction;
	searchAction->setInterest(SoSearchAction::ALL);
	searchAction->setName("Rotate");
	searchAction->setType(SoVRMLTransform::getClassTypeId());
	searchAction->apply(sceneGraph);
	pathList = searchAction->getPaths();
	
	cout << "Found " << pathList.getLength() << " paths" << endl;
	
	for (int i = 0; i < pathList.getLength(); i++)
	{
		path = (SoFullPath*) pathList[i];
	};

	if (pathList.getLength() > 0)
	{
		path = (SoFullPath*) pathList[0];
		SoNode* node = path->getTail(); // TODO: typecheck
		trnsfA = (SoVRMLTransform*) node;
 	}
	
	delete searchAction;

	searchAction = new SoSearchAction;
	searchAction->setInterest(SoSearchAction::ALL);
	searchAction->setName("S1");
	searchAction->setType(SoVRMLTransform::getClassTypeId());
	searchAction->apply(sceneGraph);
	pathList = searchAction->getPaths();
	
	cout << "Found " << pathList.getLength() << " paths" << endl;
	
	for (int i = 0; i < pathList.getLength(); i++)
	{
		path = (SoFullPath*) pathList[i];
	};

	if (pathList.getLength() > 0)
	{
		path = (SoFullPath*) pathList[0];
		SoNode* node = path->getTail(); // TODO: typecheck
		trnsfS1 = (SoVRMLTransform*) node;
 	}
	
	delete searchAction;

	searchAction = new SoSearchAction;
	searchAction->setInterest(SoSearchAction::ALL);
	searchAction->setName("S2");
	searchAction->setType(SoVRMLTransform::getClassTypeId());
	searchAction->apply(sceneGraph);
	pathList = searchAction->getPaths();
	
	cout << "Found " << pathList.getLength() << " paths" << endl;
	
	for (int i = 0; i < pathList.getLength(); i++)
	{
		path = (SoFullPath*) pathList[i];
	};

	if (pathList.getLength() > 0)
	{
		path = (SoFullPath*) pathList[0];
		SoNode* node = path->getTail(); // TODO: typecheck
		trnsfS2 = (SoVRMLTransform*) node;
 	}
	
	delete searchAction;

	searchAction = new SoSearchAction;
	searchAction->setInterest(SoSearchAction::ALL);
	searchAction->setName("S3");
	searchAction->setType(SoVRMLTransform::getClassTypeId());
	searchAction->apply(sceneGraph);
	pathList = searchAction->getPaths();
	
	cout << "Found " << pathList.getLength() << " paths" << endl;
	
	for (int i = 0; i < pathList.getLength(); i++)
	{
		path = (SoFullPath*) pathList[i];
	};

	if (pathList.getLength() > 0)
	{
		path = (SoFullPath*) pathList[0];
		SoNode* node = path->getTail(); // TODO: typecheck
		trnsfS3 = (SoVRMLTransform*) node;
 	}
	
	delete searchAction;
	
	searchAction = new SoSearchAction;
	searchAction->setInterest(SoSearchAction::ALL);
	searchAction->setName("E1");
	searchAction->setType(SoVRMLTransform::getClassTypeId());
	searchAction->apply(sceneGraph);
	pathList = searchAction->getPaths();
	
	cout << "Found " << pathList.getLength() << " paths" << endl;
	
	for (int i = 0; i < pathList.getLength(); i++)
	{
		path = (SoFullPath*) pathList[i];
	};

	if (pathList.getLength() > 0)
	{
		path = (SoFullPath*) pathList[0];
		SoNode* node = path->getTail(); // TODO: typecheck
		trnsfE1 = (SoVRMLTransform*) node;
 	}
	
	delete searchAction;
	
	searchAction = new SoSearchAction;
	searchAction->setInterest(SoSearchAction::ALL);
	searchAction->setName("E2");
	searchAction->setType(SoVRMLTransform::getClassTypeId());
	searchAction->apply(sceneGraph);
	pathList = searchAction->getPaths();
	
	cout << "Found " << pathList.getLength() << " paths" << endl;
	
	for (int i = 0; i < pathList.getLength(); i++)
	{
		path = (SoFullPath*) pathList[i];
	};

	if (pathList.getLength() > 0)
	{
		path = (SoFullPath*) pathList[0];
		SoNode* node = path->getTail(); // TODO: typecheck
		trnsfE2 = (SoVRMLTransform*) node;
 	}
	
	delete searchAction;

	searchAction = new SoSearchAction;
	searchAction->setInterest(SoSearchAction::ALL);
	searchAction->setName("W1");
	searchAction->setType(SoVRMLTransform::getClassTypeId());
	searchAction->apply(sceneGraph);
	pathList = searchAction->getPaths();
	
	cout << "Found " << pathList.getLength() << " paths" << endl;
	
	for (int i = 0; i < pathList.getLength(); i++)
	{
		path = (SoFullPath*) pathList[i];
	};

	if (pathList.getLength() > 0)
	{
		path = (SoFullPath*) pathList[0];
		SoNode* node = path->getTail(); // TODO: typecheck
		trnsfW1 = (SoVRMLTransform*) node;
 	}
	
	delete searchAction;

	searchAction = new SoSearchAction;
	searchAction->setInterest(SoSearchAction::ALL);
	searchAction->setName("W2");
	searchAction->setType(SoVRMLTransform::getClassTypeId());
	searchAction->apply(sceneGraph);
	pathList = searchAction->getPaths();
	
	cout << "Found " << pathList.getLength() << " paths" << endl;
	
	for (int i = 0; i < pathList.getLength(); i++)
	{
		path = (SoFullPath*) pathList[i];
	};

	if (pathList.getLength() > 0)
	{
		path = (SoFullPath*) pathList[0];
		SoNode* node = path->getTail(); // TODO: typecheck
		trnsfW2 = (SoVRMLTransform*) node;
 	}
	
	delete searchAction;

	// set rotation centers for joints
	trnsfS1->center.setValue(-0.1675, 0.0, 0.5625);
	trnsfS2->center.setValue(-0.1675, 0.0, 0.8795);
	trnsfS3->center.setValue(-0.1675, 0.0, 0.8795);
	trnsfE1->center.setValue(-0.1675, 0.0, 1.3295);
	trnsfE2->center.setValue(-0.1675, 0.0, 1.3295);
	trnsfW1->center.setValue(-0.1675, 0.0, 1.8095);
	trnsfW2->center.setValue(-0.1675, 0.0, 1.8095);
};

void LeonardoModel::setConfiguration(double x, double y, double a,
	double s1, double s2, double s3, double e1, double e2,
	double w1, double w2)
{
	// prepare rotation vectors
	SbVec3f rotationVecZ(0, 0, 1);
	SbVec3f rotationVecY(0, -1, 0);

	// set platform	
	trnsfX->translation.setValue(-x, 0, 0);
	trnsfY->translation.setValue(0, -y, 0);
	trnsfA->rotation.setValue(rotationVecZ, a * DEG2RAD);
	
	trnsfS1->rotation.setValue(rotationVecZ, s1 * DEG2RAD);
	trnsfS2->rotation.setValue(rotationVecY, s2 * DEG2RAD);
	trnsfS3->rotation.setValue(rotationVecZ, s3 * DEG2RAD);
	trnsfE1->rotation.setValue(rotationVecY, e1 * DEG2RAD);
	trnsfE2->rotation.setValue(rotationVecZ, e2 * DEG2RAD);
	trnsfW1->rotation.setValue(rotationVecY, w1 * DEG2RAD);
	trnsfW2->rotation.setValue(rotationVecZ, w2 * DEG2RAD);
};
