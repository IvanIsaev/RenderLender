#pragma once

#include <Vector2D.h>

#include <CMouseCursorHandler.h>

#include <iostream>

void
CMouseCursorHandler::handleMousePress(const IntVector2D& position)
{
  std::cout << "handleMousePress " << position.width << " " << position.height << std::endl;
}

void
CMouseCursorHandler::handleMouseRelease(const IntVector2D& position)
{
  std::cout << "handleMouseRelease " << position.width << " " << position.height << std::endl;
}

void
CMouseCursorHandler::handleMouseMove(const IntVector2D& position)
{
  std::cout << "handleMouseMove " << position.width << " " << position.height << std::endl;
}

