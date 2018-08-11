#include "MainWindow.h"
#include "Window.h"

MainWindow::MainWindow()
{
	m_pWindow = new Window(this);
	setWindowTitle("LaiEngine 3D");
	setCentralWidget(m_pWindow);
}