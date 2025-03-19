#pragma once

#include <IRenderWindow.h>

#include <QWidget>

class CRenderWindow
  : public QWidget
  , public IRenderWindow
{
  Q_OBJECT

public:
  void* nativeWindow() const override;
};