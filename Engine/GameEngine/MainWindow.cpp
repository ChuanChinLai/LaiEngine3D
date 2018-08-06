#include "MainWindow.h"
#include "Window.h"

MainWindow::MainWindow()
{
	m_pWindow = new Window(this);
	setCentralWidget(m_pWindow);
}