// Copyright 2016 ESRI
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
import QtQuick.Dialogs 1.2
import Esri.DSA 1.0
import Esri.ArcGISRuntime.Toolkit.Controls.CppApi 100.2

Row {
    id: reportToolRow
    spacing: 10 * scaleFactor
    visible: categoryToolbar.state === "reports"
    onVisibleChanged: state = "clear"

    states: [
        State {
            name: enemyIcon.toolName
            PropertyChanges {
                target: enemyIcon
                selected: true
            }
        },
        State {
            name: sigactIcon.toolName
            PropertyChanges {
                target: sigactIcon
                selected: true
            }
        },
        State {
            name: cotIcon.toolName
            PropertyChanges {
                target: cotIcon
                selected: true
            }
        },

        State {
            name: "clear"
            PropertyChanges {
                target: cotIcon
                selected: false
            }
            PropertyChanges {
                target: enemyIcon
                selected: false
            }
            PropertyChanges {
                target: sigactIcon
                selected: false
            }
        }
    ]

    // Enemy Tool
    ToolIcon {
        id: enemyIcon
        iconSource: DsaResources.iconCreateReport
        toolName: "Enemy"
        onToolSelected: {
            reportToolRow.state = toolName;
            console.log("send Enemy report");
        }
    }

    // SIGACT Tool
    ToolIcon {
        id: sigactIcon
        iconSource: DsaResources.iconCreateReport
        toolName: "SIGACT"
        onToolSelected: {
            reportToolRow.state = toolName;
            console.log("send SIGACT report");
        }
    }

    // CoT Tool
    ToolIcon {
        id: cotIcon
        iconSource: DsaResources.iconCreateReport
        toolName: "CoT"
        onToolSelected: {
            reportToolRow.state = toolName;
            console.log("send CoT report");
        }
    }
}