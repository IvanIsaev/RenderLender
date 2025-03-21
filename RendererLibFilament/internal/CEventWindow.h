#pragma once

#include <IEventWindow.h>

class CEventWindow : public IEventWindow
{
public:
  void resize(const Size2D<int>&) override;

private:
  Size2D<int> m_newSize;
};