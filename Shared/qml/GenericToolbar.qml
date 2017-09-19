import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.1

ToolBar {
    property alias toolbarLabelText: toolbarLabel.text
    signal menubuttonClicked();

    RowLayout {
        anchors.fill: parent

        Image {
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
                margins: 5
            }
            source: "qrc:/Resources/icons/xhdpi/drawer_large.png"
            width: 36
            height: width

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    // emit clicked
                }
            }
        }

        Label {
            id: toolbarLabel
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        Image {
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
                margins: 5
            }
            source: "qrc:/Resources/icons/xhdpi/menu_large.png"
            width: 36
            height: width

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    // emit clicked
                }
            }
        }
    }
}

