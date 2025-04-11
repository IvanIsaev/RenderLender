#include "CCamera.h"

#include <filament/Camera.h>

CCamera::CCamera(filament::Camera* pCamera, utils::Entity cameraId)
  : m_pCamera(pCamera)
  , m_cameraId(cameraId)
{
}

const utils::Entity&
CCamera::entityId() const
{
  return m_cameraId;
}

filament::Camera&
CCamera::camera()
{
  return *m_pCamera;
}

void
CCamera::setLensProjection(double focalLengthInMillimeters,
                           double aspect,
                           double near,
                           double far)
{
  m_pCamera->setLensProjection(focalLengthInMillimeters, aspect, near, far);
}

void
CCamera::setScaling(filament::math::double2 scaling)
{
  m_pCamera->setScaling(scaling);
}

void
CCamera::lookAt(filament::math::double3 const& eye,
                filament::math::double3 const& center,
                filament::math::double3 const& up)
{
  m_pCamera->lookAt(eye, center, up);
}