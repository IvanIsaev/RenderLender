#pragma once

#include <IRenderWindow.h>

#include <QWidget>

class QResizeEvent;

class CRenderWindow
  : public QWidget
  , public IRenderWindow
{
  Q_OBJECT

public:
  explicit CRenderWindow(QWidget * = nullptr);

  void* nativeWindow() const override;

  Size2D<int> size() const override;

protected:
  void resizeEvent(QResizeEvent* event) override;

  QPaintEngine* paintEngine() const override;
};