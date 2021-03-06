#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/nodes/SoText3.h>
#include <Inventor/VRMLnodes/SoVRMLCone.h>
#include <Inventor/VRMLnodes/SoVRMLCylinder.h>
#include <Inventor/VRMLnodes/SoVRMLGroup.h>
#include <Inventor/VRMLnodes/SoVRMLMaterial.h>
#include <Inventor/VRMLnodes/SoVRMLTransform.h>
#include <Inventor/misc/SoChildList.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qmenubar.h>
#include <qstatusbar.h>
#include <qgl.h>
#include <qimage.h>
#include <qstrlist.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <string>
#include <exception>
#include <stdexcept>
#include <simhelper/soqt/SaveDialogGl.h>
#include "config.h"
#include "FormMain.h"
#include "FormMainCtrl.h"
#include "LeonardoModel.h"
#include "LeonardoControl.h"

#include <iostream>

using namespace std;
using namespace simhelper::soqt;

const int FormMainCtrl::STATUSBAR_MSG_DURATION = 5000;

FormMainCtrl::FormMainCtrl(FormMain* formMain, QObject* parent, const char* name)
	:QObject(parent, name)
{
	this->formMain = formMain;

	SoQt::init(formMain);

	sceneRoot = new SoSeparator;
	sceneRoot->ref();
	axesRoot = new SoVRMLTransform;
	sceneRoot->addChild(axesRoot);

	viewer = new SoQtExaminerViewer(formMain->frameMain);
	viewer->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_BLEND);
	viewer->setSceneGraph(sceneRoot);
	viewer->show();
	viewer->viewAll();
	formMain->setCaption(PACKAGE_NAME " " PACKAGE_VERSION);

	leonardoModel = new LeonardoModel();
	leonardoControl = new LeonardoControl();

	QObject::connect((QObject*) this->formMain->fileTake_ScreenshotAction, SIGNAL(activated()), this, SLOT(slotFileTake_ScreenshotAction()));
	QObject::connect((QObject*) this->formMain->fileExitAction, SIGNAL(activated()), this, SLOT(slotFileExitAction()));
	QObject::connect((QObject*) this->formMain->viewCoordinate_AxesAction, SIGNAL(toggled(bool)), this, SLOT(slotViewCoordinate_AxesAction(bool)));
	QObject::connect((QObject*) this->formMain->viewFullScreenAction, SIGNAL(toggled(bool)), this, SLOT(slotViewFullScreenAction(bool)));
	QObject::connect((QObject*) this->formMain->helpAboutAction, SIGNAL(activated()), this, SLOT(slotHelpAboutAction()));
	QObject::connect((QObject*) this->formMain->demo1Action, SIGNAL(activated()), this, SLOT(slotDemo1Action()));
	QObject::connect((QObject*) this->formMain->demo2Action, SIGNAL(activated()), this, SLOT(slotDemo2Action()));
	QObject::connect((QObject*) this->formMain->demo3Action, SIGNAL(activated()), this, SLOT(slotDemo3Action()));
	QObject::connect((QObject*) this->formMain->moveAction, SIGNAL(activated()), this, SLOT(slotMoveAction()));
};

FormMainCtrl::~FormMainCtrl()
{
	delete leonardoControl;
	delete leonardoModel;
	
	sceneRoot->unref();
	// delete viewer; Do not delete the viewer widget! It is deleted by its parent
};

void FormMainCtrl::slotFileTake_ScreenshotAction()
{
	try
	{
		SaveDialogGL::show(viewer);
	}
	catch (std::runtime_error& e)
	{
		formMain->statusBar()->message(e.what(), STATUSBAR_MSG_DURATION);
	};
};

void FormMainCtrl::slotFileExitAction()
{
	formMain->close();
};

void FormMainCtrl::slotViewCoordinate_AxesAction(bool on)
{
	if (on)
	{
		addAxes();
	}
	else
	{
		removeAxes();
	};
};

void FormMainCtrl::slotHelpAboutAction()
{
	QString aboutString = PACKAGE_STRING "\n\n"
		"by Martin Wojtczyk <" PACKAGE_BUGREPORT ">\n\n"
		"parts by\n"
		"Markus Rickert\n"
		"Jakob Vogel\n\n";
	QMessageBox::about(formMain, PACKAGE_NAME, aboutString);
};

void FormMainCtrl::slotViewFullScreenAction(bool on)
{
	if (on)
	{
		formMain->statusBar()->hide();
		formMain->menuBarMain->hide();
		formMain->showFullScreen();
		if ((bool) viewer->isDecoration() == true) viewer->setDecoration(false);
	}
	else
	{
		formMain->statusBar()->show();
		formMain->menuBarMain->show();
		formMain->showNormal();
		if (viewer->isDecoration() == false) viewer->setDecoration(true);
	};
	// set the viewer's state
	viewer->setFullScreen(on);
};

void FormMainCtrl::slotDemo1Action()
{
	this->leonardoControl->moveConfiguration(3, 4, 0, 0, 0, 0, 0, 0, 0, 0);
	this->leonardoControl->moveConfiguration(3, 4, 0, 0, 90, 0, 90, 0, 90, 0);
	this->leonardoControl->moveConfiguration(3, 4, 0, 0, -70, 0, -70, 0, -70, 0);
	this->leonardoControl->moveConfiguration(3, 4, 0, 0, 0, 0, 0, 0, 0, 0);
	this->leonardoControl->moveConfiguration(3, 4, 0, 90, 0, 90, 0, 90, 0, 90);
	this->leonardoControl->moveConfiguration(3, 4, 0, -90, 0, -90, 0, -90, 0, -90);
	this->leonardoControl->moveConfiguration(3, 4, 0, 0, 0, 0, 0, 0, 0, 0);
	this->leonardoControl->moveConfiguration(3, 4, 0, 90, 90, 90, 90, 90, 90, 90);
	this->leonardoControl->moveConfiguration(3, 4, 0, -90, 90, -90, 90, -90, 90, -90);
	this->leonardoControl->moveConfiguration(3, 4, 0, 0, -70, 0, 120, 0, 40, 0);
};

void FormMainCtrl::slotDemo2Action()
{
	this->leonardoControl->moveConfiguration(3.0, 4.0, 0, 0, -70, 0, 120, 0, 40, 0);	
	this->leonardoControl->moveConfiguration(3.0, 6.0, 0, 0, -70, 0, 120, 0, 40, 0);
	this->leonardoControl->moveConfiguration(3.5, 5.0, -45, 0, -70, 0, 120, 0, 40, 0);
	this->leonardoControl->moveConfiguration(5.0, 5.0, 0, 0, -70, 0, 120, 0, 40, 0);
	this->leonardoControl->moveConfiguration(6.0, 5.5, 0, 0, -70, 0, 120, 0, 40, 0);
	this->leonardoControl->moveConfiguration(3.0, 4.0, 0, 0, -70, 0, 120, 0, 40, 0);
};

void FormMainCtrl::slotDemo3Action()
{
	this->leonardoControl->moveConfiguration(3.0, 4.0, 90, 0, -70, 0, 120, 0, 40, 0);
	this->leonardoControl->moveConfiguration(1.0, 4.5, 90, 0, -70, 0, 120, 0, 40, 0);
	this->leonardoControl->moveConfiguration(1.0, 6.5, 0, 0, -70, 0, 120, 0, 40, 0);
	this->leonardoControl->moveConfiguration(1.0, 6.5, 0, -15, 30, 0, 95, 0, 55, -15);
	this->leonardoControl->moveConfiguration(1.0, 6.5, 0, -20, 35, 0, 90, 0, 55, -15);
	this->leonardoControl->moveConfiguration(1.0, 6.5, 0, -30, 40, 0, 80, 0, 60, -30);
	this->leonardoControl->moveConfiguration(1.0, 4.5, -90, 0, -70, 0, 120, 0, 40, 0);
	this->leonardoControl->moveConfiguration(3.0, 4.0, 0, 0, -70, 0, 120, 0, 40, 0);	
};

void FormMainCtrl::slotMoveAction()
{
	this->leonardoControl->moveConfiguration(
		formMain->spinBoxX->value() / 100.0,
		formMain->spinBoxY->value() / 100.0,
		formMain->spinBoxA->value(),
		formMain->spinBoxJ0->value(),
		formMain->spinBoxJ1->value(),
		formMain->spinBoxJ2->value(),
		formMain->spinBoxJ3->value(),
		formMain->spinBoxJ4->value(),
		formMain->spinBoxJ5->value(),
		formMain->spinBoxJ6->value()
	);
};

void FormMainCtrl::lockTabControls()
{
	formMain->pushButtonDemo1->setEnabled(false);
	formMain->pushButtonDemo2->setEnabled(false);
	formMain->pushButtonDemo3->setEnabled(false);
	formMain->pushButtonMove->setEnabled(false);
};

void FormMainCtrl::unlockTabControls()
{
	formMain->pushButtonDemo1->setEnabled(true);
	formMain->pushButtonDemo2->setEnabled(true);
	formMain->pushButtonDemo3->setEnabled(true);
	formMain->pushButtonMove->setEnabled(true);
};

void FormMainCtrl::load(std::string& sceneFilename, std::string& robotFilename)
{
	if (sceneFilename != "")
	{
		this->sceneFilename = sceneFilename;
		
		SoInput in;
		SoSeparator* soSeparator;
		
		if (in.openFile(sceneFilename.c_str()) == false)
		{
			QString error = "Error loading " + QString(sceneFilename.c_str());
			formMain->statusBar()->message(error, STATUSBAR_MSG_DURATION);
		}
		else
		{
			soSeparator = SoDB::readAll(&in);
			in.closeFile();

			SoDB::writelock();
			axesRoot->ref();                // save axesRoot node
			sceneRoot->removeAllChildren(); // remove everything, release memory for everything except axesRoot
//			axesRoot = new SoVRMLTransform;
			sceneRoot->addChild(axesRoot);  // reconnect axesRoot
			axesRoot->unref();              // remove the ref
			if (soSeparator != NULL)
			{
				sceneRoot->addChild(soSeparator);
				SoDB::writeunlock();
				viewer->viewAll();
			}
			else
			{
				SoDB::writeunlock();
				QString error = "Error loading " + QString(sceneFilename.c_str());
				formMain->statusBar()->message(error, STATUSBAR_MSG_DURATION);
			};
		};
	};
	
	if (robotFilename != "")
	{
		this->robotFilename = robotFilename;
		
		SoInput in;
		SoSeparator* soSeparator;
		
		if (in.openFile(robotFilename.c_str()) == false)
		{
			QString error = "Error loading " + QString(robotFilename.c_str());
			formMain->statusBar()->message(error, STATUSBAR_MSG_DURATION);
		}
		else
		{
			soSeparator = SoDB::readAll(&in);
			in.closeFile();

			SoDB::writelock();
//			axesRoot->ref();                // save axesRoot node
//			sceneRoot->removeAllChildren(); // remove everything, release memory for everything except axesRoot
//			axesRoot = new SoVRMLTransform;
//			sceneRoot->addChild(axesRoot);  // reconnect axesRoot
//			axesRoot->unref();              // remove the ref
			if (soSeparator != NULL)
			{
				sceneRoot->addChild(soSeparator);
				SoDB::writeunlock();
				viewer->viewAll();
			}
			else
			{
				SoDB::writeunlock();
				QString error = "Error loading " + QString(robotFilename.c_str());
				formMain->statusBar()->message(error, STATUSBAR_MSG_DURATION);
			};
		};
	};
	
	this->leonardoModel->setSceneGraph(this->sceneRoot);
	this->leonardoControl->setModel(this->leonardoModel);
	this->leonardoControl->setConfiguration(3, 4, 0, 0, 0, 0, 0, 0, 0, 0);
	formMain->spinBoxX->setValue(300);
	formMain->spinBoxY->setValue(400);
};

void FormMainCtrl::addAxes()
{
	SoVRMLTransform* axes = new SoVRMLTransform();
	axes->scale.setValue(0.25f, 0.25f, 0.25f);
	axesRoot->addChild(axes);
	
	SoVRMLCylinder* cylinder = new SoVRMLCylinder();
	cylinder->height = 0.18f / 0.27f;
	cylinder->radius = 0.01f / 0.27f;
	
	SoSFVec3f cylinderTransform;
	cylinderTransform.setValue(0.0f, cylinder->height.getValue() / 2.0f, 0.0f);
	
	SoVRMLCone* cone = new SoVRMLCone();
	cone->bottomRadius = 0.03f / 0.27f;
	cone->height = 0.09f / 0.27f;
	
	SoSFVec3f coneTransform;
	coneTransform.setValue(0.0f, cylinder->height.getValue() / 2.0f + cone->height.getValue() / 2.0f, 0.0f);
	
	SoSFVec3f textScale;
	textScale.setValue(0.01f / 0.27f, 0.01f / 0.27f, 0.01f / 0.27f);
	
	SoSFVec3f textTranslation;
	textTranslation.setValue(0.1f / 0.27f, cylinder->height.getValue() / 2.0f + cone->height.getValue() / 2.0f, 0.0f);
	
	SoFont* font = new SoFont();
	font->name.setValue("Arial, Helvetica, Sans");
	axes->addChild(font);
	
	// x
	SoVRMLTransform* xAxis = new SoVRMLTransform();
	xAxis->rotation.setValue(SbVec3f(1.0f, 1.0f, 0.0f), (float) -M_PI);
	axes->addChild(xAxis);
	
	SoVRMLMaterial* xAxisMaterial = new SoVRMLMaterial();
	xAxisMaterial->diffuseColor.setValue(1.0f, 0.0f, 0.0f);
	xAxis->addChild(xAxisMaterial);
	
	SoVRMLTransform* xCylinderTransform = new SoVRMLTransform();
	xCylinderTransform->translation = cylinderTransform;
	xAxis->addChild(xCylinderTransform);
	xCylinderTransform->addChild(cylinder);
	
	SoVRMLTransform* xConeTransform = new SoVRMLTransform();
	xConeTransform->translation = coneTransform;
	xCylinderTransform->addChild(xConeTransform);
	xConeTransform->addChild(cone);
	
	SoVRMLTransform* xTextTransform = new SoVRMLTransform();
	xTextTransform->scale = textScale;
	xTextTransform->translation.setValue(-0.15f / 0.27f, textTranslation.getValue()[1], textTranslation.getValue()[2]);
	xAxis->addChild(xTextTransform);
	
	SoText3* xText = new SoText3();
	xText->parts.setValue(SoText3::ALL);
	xText->string.setValue("x");
	xTextTransform->addChild(xText);
	
	// y
	SoVRMLTransform* yAxis = new SoVRMLTransform();
	yAxis->rotation.setValue(SbVec3f(1.0f, 0.0f, 0.0f), 2.0f * (float) M_PI);
	axes->addChild(yAxis);
	
	SoVRMLMaterial* yAxisMaterial = new SoVRMLMaterial();
	yAxisMaterial->diffuseColor.setValue(0.0f, 1.0f, 0.0f);
	yAxis->addChild(yAxisMaterial);
	
	SoVRMLTransform* yCylinderTransform = new SoVRMLTransform();
	yCylinderTransform->translation = cylinderTransform;
	yAxis->addChild(yCylinderTransform);
	yCylinderTransform->addChild(cylinder);
	
	SoVRMLTransform* yConeTransform = new SoVRMLTransform();
	yConeTransform->translation = coneTransform;
	yCylinderTransform->addChild(yConeTransform);
	yConeTransform->addChild(cone);
	
	SoVRMLTransform* yTextTransform = new SoVRMLTransform();
	yTextTransform->scale = textScale;
	yTextTransform->translation = textTranslation;
	yAxis->addChild(yTextTransform);
	
	SoText3* yText = new SoText3();
	yText->parts.setValue(SoText3::ALL);
	yText->string.setValue("y");
	yTextTransform->addChild(yText);
	
	// z
	SoVRMLTransform* zAxis = new SoVRMLTransform();
	zAxis->rotation.setValue(SbVec3f(0.0f, 1.0f, 1.0f), (float) M_PI);
	axes->addChild(zAxis);
	
	SoVRMLMaterial* zAxisMaterial = new SoVRMLMaterial();
	zAxisMaterial->diffuseColor.setValue(0.0f, 0.0f, 1.0f);
	zAxis->addChild(zAxisMaterial);
	
	SoVRMLTransform* zCylinderTransform = new SoVRMLTransform();
	zCylinderTransform->translation = cylinderTransform;
	zAxis->addChild(zCylinderTransform);
	zCylinderTransform->addChild(cylinder);
	
	SoVRMLTransform* zConeTransform = new SoVRMLTransform();
	zConeTransform->translation = coneTransform;
	zCylinderTransform->addChild(zConeTransform);
	zConeTransform->addChild(cone);
	
	SoVRMLTransform* zTextTransform = new SoVRMLTransform();
	zTextTransform->scale = textScale;
	zTextTransform->translation = textTranslation;
	zAxis->addChild(zTextTransform);
	
	SoText3* zText = new SoText3();
	zText->parts.setValue(SoText3::ALL);
	zText->string.setValue("z");
	zTextTransform->addChild(zText);
};

void FormMainCtrl::removeAxes()
{
//	axesRoot->removeAllChildren();

	SoDB::writelock();
	sceneRoot->removeChild(axesRoot);
	axesRoot = new SoVRMLTransform;
	sceneRoot->addChild(axesRoot);
	SoDB::writeunlock();
};
