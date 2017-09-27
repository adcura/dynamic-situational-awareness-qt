// Copyright 2017 ESRI
//
// All rights reserved under the copyright laws of the United States
// and applicable international laws, treaties, and conventions.
//
// You may freely redistribute and use this sample code, with or
// without modification, provided you include the original copyright
// notice and use restrictions.
//
// See the Sample code usage restrictions document for further information.
//

#include "MessagesOverlay.h"
#include "GeoView.h"
#include "DictionarySymbolStyle.h"
#include "GraphicsOverlay.h"
#include "Message.h"
#include "DictionaryRenderer.h"

using namespace Esri::ArcGISRuntime;

MessagesOverlay::MessagesOverlay(GeoView* geoView, QObject* parent) :
  MessagesOverlay(geoView, nullptr, parent)
{
}

MessagesOverlay::MessagesOverlay(GeoView* geoView, DictionarySymbolStyle* dictionarySymbolStyle, QObject* parent) :
  QObject(parent),
  m_geoView(geoView),
  m_dictionarySymbolStyle(dictionarySymbolStyle)
{
}

MessagesOverlay::~MessagesOverlay()
{
}

DictionarySymbolStyle* MessagesOverlay::dictionarySymbolStyle() const
{
  return m_dictionarySymbolStyle.data();
}

void MessagesOverlay::setDictionarySymbolStyle(DictionarySymbolStyle* dictionarySymbolStyle)
{
  m_dictionarySymbolStyle = dictionarySymbolStyle;
}

QList<GraphicsOverlay*> MessagesOverlay::graphicsOverlays() const
{
  return m_graphicsOverlays;
}

GeoView* MessagesOverlay::geoView() const
{
  return m_geoView;
}

bool MessagesOverlay::addMessage(const Message& message)
{
  const auto messageId = message.messageId();
  if (messageId.isEmpty())
  {
    emit errorOccurred(QStringLiteral("Failed to add message - message ID is empty"));
    return false;
  }

  const auto symbolId = message.symbolId();
  if (symbolId.isEmpty())
  {
    emit errorOccurred(QStringLiteral("Failed to add message - symbol ID is empty"));
    return false;
  }

  const auto geometry = message.geometry();
  if (geometry.isEmpty())
  {
    emit errorOccurred(QStringLiteral("Failed to add message - geometry is empty"));
    return false;
  }

  if (geometry.isEmpty() || messageId.isEmpty() ||
      symbolId.isEmpty())
    return false;

  if (m_existingGraphics.contains(messageId))
  {
    // update existing graphic attributes and geometry
    // if the graphic already exists in the hash
    Graphic* graphic = m_existingGraphics[messageId];
    if (graphic->geometry().geometryType() != geometry.geometryType())
      return false;

    graphic->setGeometry(geometry);
    graphic->attributes()->setAttributesMap(message.attributes());
    return true;
  }

  // add new graphic
  Graphic* graphic = new Graphic(geometry, message.attributes(), this);

  switch (geometry.geometryType())
  {
  case GeometryType::Point:
  case GeometryType::Multipoint:
    if (!m_pointGraphicsOverlay)
    {
      if (!m_dictionarySymbolStyle || !m_geoView)
      {
        delete graphic;
        return false;
      }

      // add point/multipoint geometry types to a dynamically-rendered graphics overlay
      m_pointGraphicsOverlay = new GraphicsOverlay(this);
      m_pointGraphicsOverlay->setRenderingMode(GraphicsRenderingMode::Dynamic);
      m_pointGraphicsOverlay->setSceneProperties(LayerSceneProperties(SurfacePlacement::Relative));
      m_pointGraphicsOverlay->setRenderer(new DictionaryRenderer(m_dictionarySymbolStyle.data(), this));
      m_graphicsOverlays.append(m_pointGraphicsOverlay);
      m_geoView->graphicsOverlays()->append(m_pointGraphicsOverlay);

      emit graphicsOverlaysChanged();
      emit visibleChanged();
    }

    m_pointGraphicsOverlay->graphics()->append(graphic);
    break;
  case GeometryType::Envelope:
  case GeometryType::Polygon:
  case GeometryType::Polyline:
    if (!m_linePolygonGraphicsOverlay)
    {
      if (!m_dictionarySymbolStyle || !m_geoView)
      {
        delete graphic;
        return false;
      }

      // add polygon/polyline geometry types to a statically-rendered graphics overlay
      m_linePolygonGraphicsOverlay = new GraphicsOverlay(this);
      m_linePolygonGraphicsOverlay->setRenderingMode(GraphicsRenderingMode::Static);
      m_linePolygonGraphicsOverlay->setRenderer(new DictionaryRenderer(m_dictionarySymbolStyle.data(), this));
      m_graphicsOverlays.append(m_linePolygonGraphicsOverlay);
      m_geoView->graphicsOverlays()->append(m_linePolygonGraphicsOverlay);

      emit graphicsOverlaysChanged();
      emit visibleChanged();
    }

    m_linePolygonGraphicsOverlay->graphics()->append(graphic);
    break;
  default:
    delete graphic;
    return false;
  }

  m_existingGraphics.insert(messageId, graphic);

  return true;
}

bool MessagesOverlay::isVisible() const
{
  // at this time, only one graphics overlay per message overlay
  // this could change later...
  if (m_pointGraphicsOverlay)
    return m_pointGraphicsOverlay->isVisible();
  else if (m_linePolygonGraphicsOverlay)
    return m_linePolygonGraphicsOverlay->isVisible();

  return false;
}

void MessagesOverlay::setVisible(bool visible)
{
  if (m_pointGraphicsOverlay)
    m_pointGraphicsOverlay->setVisible(visible);

  if (m_linePolygonGraphicsOverlay)
    m_linePolygonGraphicsOverlay->setVisible(visible);
}