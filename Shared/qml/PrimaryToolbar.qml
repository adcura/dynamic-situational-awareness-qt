/*******************************************************************************
 *  Copyright 2012-2018 Esri
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ******************************************************************************/

import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import Esri.DSA 1.0
import QtQuick.Controls.Material 2.2

ToolBar {
    property alias toolbarLabelText: toolbarLabel.text
    property int marginWidth: 5 * scaleFactor
    property int imageWidth: 36 * scaleFactor
    property bool menuVisible
    property real scaleFactor: (Screen.logicalPixelDensity * 25.4) / (Qt.platform.os === "windows" ? 96 : 72)

    Row {
        anchors {
            fill: parent
            margins: 10 * scaleFactor
        }

        spacing: 5 * scaleFactor

        Image {
            anchors.verticalCenter: parent.verticalCenter
            width: DsaStyles.secondaryIconSize * scaleFactor
            height: width
            source: DsaResources.iconDrawer
            visible: menuVisible

            MouseArea {
                anchors.fill: parent
                onClicked: categoryToolbar.visible = !categoryToolbar.visible
            }
        }

        Label {
            id: toolbarLabel
            anchors.verticalCenter: parent.verticalCenter

            font {
                pixelSize: DsaStyles.titleFontPixelSize * scaleFactor
                family: DsaStyles.fontFamily
            }
            color: Material.foreground
        }
    }
}

