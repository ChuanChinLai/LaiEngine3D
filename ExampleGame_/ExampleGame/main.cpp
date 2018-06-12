#include <iostream>

#include <External\Qt\Includes.h>
#include <Engine\GameEngine\Example.h>


int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	GLWidget window;
	window.resize(800, 600);
	window.show();

	return app.exec();

	return 0;
}