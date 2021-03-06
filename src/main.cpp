/*
 * A minimalistic VRML/Inventor-Viewer based on SoQt, coin3d, Qt
 * started 06.12.2004 by Martin Wojtczyk
 */
#include <qapplication.h>
#include "config.h"
#include "FormMain.h"
#include "FormMainCtrl.h"
#include "main.h"
#include <stdexcept>
#include <exception>
#include <string>
#include <iostream>

#ifdef WIN32
#include <Windows.h>
#endif // WIN32

using namespace std;

int main(int argc, char** argv)
{
	try
	{
		QApplication application(argc, argv);
		FormMain formMain;
		application.setMainWidget(&formMain);
		FormMainCtrl formMainCtrl(&formMain);
	
		formMain.show();
		
		string sceneFilename = "data/world/03.09.023/room.wrl";
		string robotFilename = "data/robot/Leonardo2.wrl";

		if (argc > 1)
		{
			sceneFilename = argv[1];
		};
		if (argc > 2)
		{
			robotFilename = argv[2];
		};
		formMainCtrl.load(sceneFilename, robotFilename);
		
		return application.exec();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << endl;
	}
};

#ifdef WIN32
int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return main(__argc, __argv);
}
#endif // WIN32
