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

#include "AlertCondition.h"
#include "AlertConditionData.h"
#include "AlertListModel.h"
#include "GraphicAlertSource.h"

#include "GraphicsOverlay.h"
#include "GraphicListModel.h"

using namespace Esri::ArcGISRuntime;

/*!
  \class AlertCondition
  \inherits QObject
  \brief Represents a condition which will be coninuosly monitored and will
  trigger an alert when met.

  An AlertCondition is made up of an \l AlertSource (generally some form of real-time feed)
  a query and an \l AlertTarget (a real time feed or an overlay).

  The condition is applied to all source objects, creating an \l AlertConditionData for each.

  When either the source or target is changed for a given data element, the condition can be
  re-tested using an \l AlertQuery to determine whether an elert should be triggered.

  \sa AlertSource
  \sa AlertTarget
  \sa AlertConditionData
  */

/*!
  \brief Constructor taking an \l AlertLevel (\a level) the \a name of the condition and
  an optional \a parent.
 */
AlertCondition::AlertCondition(const AlertLevel& level,
                               const QString& name,
                               QObject* parent):
  QObject(parent),
  m_level(level),
  m_name(name)
{

}

/*!
  \brief Initialises the condition with a \a source and \target.

  A new \a AlertConditionData will be created to track changes to the
  source and target.
 */
void AlertCondition::init(AlertSource* source, AlertTarget* target)
{
  AlertConditionData* newData = createData(source, target);
  addData(newData);
}

/*!
  \brief Initialises the condition with a \a sourceFeed and \target.

  A new \a AlertConditionData will be created for each \l Esri::ArcGISRuntime::Graphic
  in the source feed, to track changes to the source and target.
 */
void AlertCondition::init(GraphicsOverlay* sourceFeed, AlertTarget* target)
{
  if (!sourceFeed)
    return;

  GraphicListModel* graphics = sourceFeed->graphics();
  if (!graphics)
    return;

  // process a new graphic from the source feed to create a new AlertConditionData
  auto handleGraphicAt = [this, graphics, target](int index)
  {
    if (!graphics)
      return;

    Graphic* newGraphic = graphics->at(index);
    if (!newGraphic)
      return;

    GraphicAlertSource* source = new GraphicAlertSource(newGraphic);
    AlertConditionData* newData = createData(source, target);
    addData(newData);
  };

  // connect to the graphicAdded to add condition data for any new graphics
  connect(graphics, &GraphicListModel::graphicAdded, this, handleGraphicAt);

  // add condition data for all of the graphics which are in the overlay to begin with
  const int count = graphics->rowCount();
  for (int i = 0; i < count; ++i)
    handleGraphicAt(i);
}

/*!
  \brief Destructor.
 */
AlertCondition::~AlertCondition()
{
  emit noLongerValid();
}

/*!
  \brief Returns the \l AlertLevel of the condition.
 */
AlertLevel AlertCondition::level() const
{
  return m_level;
}

/*!
  \brief Sets the \l AlertLevel foro the condition to \a level.
 */
void AlertCondition::setLevel(AlertLevel level)
{
  if (level == m_level)
    return;

  m_level = level;
}

/*!
  \brief Returns the name of the condition.
 */
QString AlertCondition::name() const
{
  return m_name;
}

/*!
  \brief Sets the \l AlertLevel foro the condition to \a level.
 */
void AlertCondition::setName(const QString& name)
{
  if (name == m_name)
    return;

  m_name = name;
}

/*!
  \brief Returns a name for the next new condition data.

  \note This will be of the form "My Condition (1)".
 */
QString AlertCondition::newConditionDataName() const
{
  return m_name + QString(" (%1)").arg(QString(m_data.count()));
}

/*!
  \brief Appends \a newData to the list of data being tracked for this condition.
 */
void AlertCondition::addData(AlertConditionData* newData)
{
  if (!newData)
    return;

  m_data.append(newData);
  AlertListModel::instance()->addAlertConditionData(newData);
}

