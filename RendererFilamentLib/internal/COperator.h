#pragma once

#include "CameraFwd.h"

#include <MathTypes/Size.h>

class COperator
{
public:
  COperator(CCameraUnique, CameraManipulatorUnique);
  void setDefaultCameraSetting(const UIntSize2D& windowSize);

  void grabBegin(int x, int y, bool strafe);
  void grabUpdate(int x, int y);
  void grabEnd();
  void updateCamera();

private:
  CCameraUnique m_pCamera;
  CameraManipulatorUnique m_pCameraManipulator;
};