import QtQuick
import QtLocation
import QtPositioning

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Tesla infotainment")


    Rectangle{
        id: bottomBar
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        color: "black"
        height: parent.height / 12


        Image {
            id: carIcon
            anchors{
                left: parent.left
                leftMargin: 30
                verticalCenter: parent.verticalCenter
            }
            height: parent.height * .85
            fillMode: Image.PreserveAspectFit
            source: "qrc:/ui/assets/car-icon.png"
        }
    }


    Rectangle{
        id: leftScreen
        anchors {
            left: parent.left
            bottom: bottomBar.top
            top: parent.top

        }
        color: "white"
        width: parent.width * 1/3

        Image {
            id: car
            anchors.centerIn: parent
            width: parent.width * 0.95
            fillMode: Image.PreserveAspectFit
            source: "qrc:/ui/assets/car.png"
        }
    }


    Rectangle{
        id: rightScreen

        anchors{
            top: parent.top
            bottom: bottomBar.top
            right: parent.right
        }

        Plugin{
            id: mapPlugin
            name: "osm"
        }

        Map{
            anchors.fill: parent
            plugin: mapPlugin
            center: QtPositioning.coordinate(59.91,10.75)
            zoomLevel: 14
        }

        color: "orange"
        width: parent.width * 2/3
    }

}



