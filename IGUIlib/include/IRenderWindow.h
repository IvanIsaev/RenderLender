#pragma once

#include <Vector2D.h>

#include <boost/signals2/signal.hpp>

class IRenderWindow
{
public:
	using MouseSignal = boost::signals2::signal<void(const IntVector2D&)>;
	using SlotForMouseSignal = MouseSignal::slot_type;

public:
  virtual ~IRenderWindow() = default;

  virtual void* nativeWindow() const = 0;

  virtual IntVector2D size() const = 0;

  virtual void trackMousePress(const SlotForMouseSignal&) const = 0;
  virtual void trackMouseRelease(const SlotForMouseSignal&) const = 0;
  virtual void trackMouseMove(const SlotForMouseSignal&) const = 0;
};