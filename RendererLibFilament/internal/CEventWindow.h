#pragma once

#include <IEventWindow.h>

class CEventWindow : public IEventWindow
{
public:
  void resize(const Size&) override;

private:
  Size m_newSize;
};