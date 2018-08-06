#pragma once

#include <QtWidgets\Qwidget>
#include <QtWidgets\QOpenGLWidget>


class MainWindow;
class GLWidget;

class Window : public QWidget
{

//	Q_OBJECT // must include this if you use Qt signals/slots

public:

	Window(MainWindow* parent);

protected:

	void keyPressEvent(QKeyEvent* event) override;

private:

	MainWindow* m_pMainWindow;
	GLWidget* m_pGLWidget;
};
