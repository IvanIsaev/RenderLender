#pragma once

#include <IRenderWindow.h>

#include <IEventWindow.h>

#include <QWidget>

class QResizeEvent;

class CRenderWindow
  : public QWidget
  , public IRenderWindow
{
  Q_OBJECT

public:
  explicit CRenderWindow(IEventWindow& eventWindow);

  void* nativeWindow() const override;

protected:
  void resizeEvent(QResizeEvent* event) override;

private:
  IEventWindow& m_eventWindow;
};