#pragma once

#include <IRenderArea.h>

#include <QtWidgets/QTabWidget>


class CRenderArea : public QTabWidget, public IRenderArea
{
	Q_OBJECT

public:
	void addRenderWindow ( std::string_view ) override;
	IRenderWindow* renderWindow ( ) override;

private:


};