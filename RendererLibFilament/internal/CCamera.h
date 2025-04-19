#pragma once

#include "FilamentComponentCleaner.h"

#include <math/vec2.h>
#include <math/vec3.h>
#include <utils/Entity.h>

#include <memory>

namespace filament {
class Camera;
}

class CCamera
{
public:
  CCamera(filament::Camera*, utils::Entity);

  const utils::Entity& entityId() const;
  filament::Camera& camera();

  void setLensProjection(double focalLengthInMillimeters,
                         double aspect,
                         double near,
                         double far);
  void setScaling(filament::math::double2 scaling);
  void lookAt(filament::math::double3 const& eye,
              filament::math::double3 const& center,
              filament::math::double3 const& up = filament::math::double3{ 0,
                                                                           1,
                                                                           0 });

private:
  filament::Camera* const m_pCamera;
  const utils::Entity m_cameraId;
};

