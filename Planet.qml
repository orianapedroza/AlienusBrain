import QtQuick 2.0

Image {
    id: root
    source: "./content/images/Planeta_green.png"
    property alias place: place_img.source
    property alias discovered: place_img.visible
    Image {
        anchors.fill: parent
        id: place_img
        source: "./content/images/Restaurant.png"
        visible: false
    }
}
