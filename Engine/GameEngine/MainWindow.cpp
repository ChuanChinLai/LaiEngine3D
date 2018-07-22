#include "MainWindow.h"
#include "Window.h"

MainWindow::MainWindow()
{
	pWindow = new Window(this);
	setCentralWidget(pWindow);
}