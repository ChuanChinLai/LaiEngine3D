#include <iostream>

#include <External\Qt\Includes.h>
#include <Engine\GameEngine\GLWidget.h>
#include <Engine\GameEngine\MainWindow.h>

#include <QtWidgets/QMainWindow>

int main(int argc, char** argv)
{
	int res = 0;

	{
		QApplication app(argc, argv);

		MainWindow mainWindow;
		mainWindow.resize(800, 800);
		mainWindow.show();

		res = app.exec();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return res;
}