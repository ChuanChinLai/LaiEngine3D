#pragma once

#include <QtWidgets\QMainWindow>

class Window;
class GLWidget;

class MainWindow : public QMainWindow
{
//	Q_OBJECT

public:

	MainWindow();

private:

	Window* pWindow;
};
