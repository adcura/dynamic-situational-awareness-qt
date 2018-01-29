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

#include "AlertTarget.h"

using namespace Esri::ArcGISRuntime;

AlertTarget::AlertTarget(QObject* parent):
  QObject(parent)
{

}

AlertTarget::~AlertTarget()
{
  emit noLongerValid();
}