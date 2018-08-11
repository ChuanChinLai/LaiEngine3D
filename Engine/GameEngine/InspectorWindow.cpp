#include "InspectorWindow.h"

#include <QtWidgets\QSlider>
#include <QtWidgets\QGridLayout>

InspectorWindow::InspectorWindow(QWidget * parent)
{
	QHBoxLayout* mainLayout = new QHBoxLayout(this);

	QSlider* slider = new QSlider(Qt::Vertical, this);
	slider->setRange(0, 99);
	slider->setValue(0);
	mainLayout->addWidget(slider);


	QSlider* slider1 = new QSlider(Qt::Vertical, this);
	slider1->setRange(0, 99);
	slider1->setValue(0);
	mainLayout->addWidget(slider1);

	setLayout(mainLayout);
}

InspectorWindow::~InspectorWindow()
{

}
