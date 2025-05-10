#include "COperator.h"

#include "CCamera.h"

#include <camutils/Manipulator.h>
#include <math/vec3.h>

#include <memory>

using namespace RendererFilament;

COperator::COperator(CCameraUnique pCamera,
                     CameraManipulatorUnique pCameraManipulator)
  : m_pCamera(std::move(pCamera))
  , m_pCameraManipulator(std::move(pCameraManipulator))
{
}

void
COperator::setDefaultCameraSetting(const MathTypes::UIntSize2D& windowSize)
{
  const auto width = windowSize.x();
  const auto height = windowSize.y();
  const auto aspectRatio = double(width) / height;

  m_pCamera->setLensProjection(28, 1.0, 0.1, 100.0);
  m_pCamera->setScaling({ 1.0 / aspectRatio, 1.0 });
}

void
COperator::grabBegin(int x, int y, bool strafe)
{
  m_pCameraManipulator->grabBegin(x, y, strafe);
  updateCamera();
}

void
COperator::grabUpdate(int x, int y)
{
  m_pCameraManipulator->grabUpdate(x, y);
  updateCamera();
}

void
COperator::grabEnd()
{
  m_pCameraManipulator->grabEnd();
  updateCamera();
}

void
COperator::updateCamera()
{
  filament::math::float3 eye, center, up;
  m_pCameraManipulator->getLookAt(&eye, &center, &up);
  m_pCamera->lookAt(eye, center, up);
}