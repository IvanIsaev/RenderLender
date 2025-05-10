#include "Utils.h"

MathTypes::FloatMatrix4x4
SceneImporter::convertMatrix(const aiMatrix4x4& mat)
{
  MathTypes::FloatMatrix4x4 outMat;

  using namespace boost::qvm;
  A00(outMat) = mat.a1;
  A01(outMat) = mat.a2;
  A02(outMat) = mat.a3;
  A03(outMat) = mat.a4;

  A10(outMat) = mat.b1;
  A11(outMat) = mat.b2;
  A12(outMat) = mat.b3;
  A13(outMat) = mat.b4;

  A20(outMat) = mat.c1;
  A21(outMat) = mat.c2;
  A22(outMat) = mat.c3;
  A23(outMat) = mat.c4;

  A30(outMat) = mat.d1;
  A31(outMat) = mat.d2;
  A32(outMat) = mat.d3;
  A33(outMat) = mat.d4;

  return outMat;
}
