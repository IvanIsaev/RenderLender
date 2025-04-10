#pragma once

#include <IRenderer.h>

#include <camutils/Manipulator.h>

#include <Vector2D.h>

#include <CMouseCursorHandler.h>

#include <iostream>

void
CMouseCursorHandler::handleMousePress(const IntVector2D& position)
{
  if (m_pCameraManipulator && m_pRenderer) {
    m_pCameraManipulator->grabBegin(position.width, position.height, false);
    m_pRenderer->execute();
  }
}

void
CMouseCursorHandler::handleMouseRelease(const IntVector2D& position)
{
  if (m_pCameraManipulator && m_pRenderer) {
    m_pCameraManipulator->grabEnd();
    m_pRenderer->execute();
  }
}

void
CMouseCursorHandler::handleMouseMove(const IntVector2D& position)
{
  if (m_pCameraManipulator && m_pRenderer) {
    m_pCameraManipulator->grabUpdate(position.width, position.height);
    m_pRenderer->execute();
  }
}

void
CMouseCursorHandler::setRenderer(IRenderer* pRenderer)
{
  m_pRenderer = pRenderer;
}

void
CMouseCursorHandler::setCameraManipulator(
  filament::camutils::Manipulator<float>* pCameraManipulator)
{
  m_pCameraManipulator = pCameraManipulator;
}

