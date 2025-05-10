#pragma once

#include <MathTypes/Point.h>
#include <MathTypes/Size.h>

#include <boost/signals2/signal.hpp>

namespace IGUI {
class IRenderWindow
{
public:
  using MouseSignal = boost::signals2::signal<void(const MathTypes::UIntPoint2D&)>;
  using SlotForMouseSignal = MouseSignal::slot_type;

public:
  virtual ~IRenderWindow() = default;

  virtual void* nativeWindow() const = 0;

  virtual MathTypes::UIntSize2D size() const = 0;

  virtual void trackMousePress(const SlotForMouseSignal&) const = 0;
  virtual void trackMouseRelease(const SlotForMouseSignal&) const = 0;
  virtual void trackMouseMove(const SlotForMouseSignal&) const = 0;
};
}