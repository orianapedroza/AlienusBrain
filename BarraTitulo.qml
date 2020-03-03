import QtQuick 2.0

Rectangle{
    property alias  titulo: texto_titulo
    color: "#001440"

    Text {

        id: texto_titulo
        text: qsTr("text")
        anchors.centerIn: parent
        color: "white"
        font.pointSize: 40
    }



}
