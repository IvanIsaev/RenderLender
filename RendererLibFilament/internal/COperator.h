#pragma once

#include "CameraFwd.h"

#include <Structures.h>

class COperator
{
public:
  COperator(CCameraUnique, CameraManipulatorUnique);
  void setDefaultCameraSetting(const IntSize2D& windowSize);

  void grabBegin(int x, int y, bool strafe);
  void grabUpdate(int x, int y);
  void grabEnd();
  void updateCamera();

private:
  CCameraUnique m_pCamera;
  CameraManipulatorUnique m_pCameraManipulator;
};