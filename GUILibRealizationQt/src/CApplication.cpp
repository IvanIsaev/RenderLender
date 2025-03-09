#pragma once

#include "CApplication.h"

CApplication::CApplication ( int argc, char* argv[] ) : QApplication ( argc, argv )
{ }

CApplication::~CApplication ( )
{ }

bool CApplication::execute ( )
{
	return QApplication::exec();
}
