#include <CRenderWindow.h>

void* CRenderWindow::nativeWindow ( ) const
{
	return reinterpret_cast<void*>(QWidget::winId());
}
