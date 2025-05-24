#include "RLMath/Matrix.h"

#include <boost/qvm.hpp>

MathTypes::FloatMatrix4x4
RLMath::transposedCopy(const MathTypes::FloatMatrix4x4& mat)
{	
  auto& transposed = boost::qvm::transposed(mat);	
  return MathTypes::FloatMatrix4x4(transposed);
}
