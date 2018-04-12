// Copyright 2018 ESRI
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

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Window 2.2
import Esri.DSA 1.0
import Esri.ArcGISRuntime.Toolkit.Controls.CppApi 100.2

Row {
    id: reportToolRow
    property real scaleFactor: (Screen.logicalPixelDensity * 25.4) / (Qt.platform.os === "windows" ? 96 : 72)
    spacing: 10 * scaleFactor
    visible: categoryToolbar.state === "reports"
    onVisibleChanged: state = "clear"

    property alias contactState: contactIcon.toolName
    property string clearState: "clear"

    states: [
        State {
            name: contactIcon.toolName
            PropertyChanges {
                target: contactIcon
                selected: true
            }
        },

        State {
            name: clearState
            PropertyChanges {
                target: contactIcon
                selected: false
            }
        }
    ]

    // Contact Tool
    ToolIcon {
        id: contactIcon
        iconSource: DsaResources.iconCreateReport
        toolName: "Contact"
        onToolSelected: {
            if (selected) {
                reportToolRow.state = clearState;
                selected = false;
            }
            else
                reportToolRow.state = toolName;
        }

        onSelectedChanged: {
            contactReportTool.visible = selected;
        }
    }
}
