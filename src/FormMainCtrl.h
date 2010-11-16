#ifndef _FORMMAINCTRL_H_
#define _FORMMAINCTRL_H_

#include <qobject.h>

class FormMain;
class SoSeparator;
class SoQtExaminerViewer;
class SoVRMLGroup;
class LeonardoModel;
class LeonardoControl;

class FormMainCtrl :public QObject
{
	Q_OBJECT

private slots:
	void slotFileTake_ScreenshotAction();
	void slotFileExitAction();
	void slotViewCoordinate_AxesAction(bool on);
	void slotViewFullScreenAction(bool on);
	void slotHelpAboutAction();
	void slotDemo1Action();
	void slotDemo2Action();
	void slotDemo3Action();
	void slotMoveAction();
	void lockTabControls();
	void unlockTabControls();

private:
	static const int STATUSBAR_MSG_DURATION;

	FormMain* formMain;
	SoSeparator* sceneRoot;
	SoVRMLGroup* axesRoot;
	SoQtExaminerViewer* viewer;
	std::string sceneFilename;
	std::string robotFilename;
	LeonardoModel* leonardoModel;
	LeonardoControl* leonardoControl;
	
public:
	FormMainCtrl(FormMain* formMain, QObject* parent = 0, const char* name = NULL);
	virtual ~FormMainCtrl();
	
	void load(std::string& sceneFilename, std::string& robotFilename);
	void addAxes();
	void removeAxes();
};

#endif //_FORMMAINCTRL_H_
