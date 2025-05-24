#include "Conversation.h"


filament::math::mat4f
RendererFilament::convertToFilamentMat(const MathTypes::FloatMatrix4x4& mat)
{
  return filament::math::mat4f{ mat.a[0][0], mat.a[0][1], mat.a[0][2],
                                mat.a[0][3], mat.a[1][0], mat.a[1][1],
                                mat.a[1][2], mat.a[1][3], mat.a[2][0],
                                mat.a[2][1], mat.a[2][2], mat.a[2][3],
                                mat.a[3][0], mat.a[3][1], mat.a[3][2],
                                mat.a[3][3] };
}
