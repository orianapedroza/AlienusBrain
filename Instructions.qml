import QtQuick 2.0
import QtQuick.Layouts 1.10
//Como se vera la lista

Rectangle{
    width: 250
    height:300
    color: "beige"

    ColumnLayout{
        anchors.fill: parent
        Rectangle{
            width: parent.width
            height: 40
            Layout.alignment: Qt.AlignTop
            gradient: gradiente_color
            Text {
                anchors.centerIn: parent
                color: "white"
                font.bold: true
                font.pointSize: 15
                text: qsTr("INSTRUCTIONS")
            }
        }
        DelegadoInst{
            id: delegado
            property bool assembler: false
        }
        ListView{
            id: listaIns
            model: ModeloIns{}
            delegate: delegado
            width: parent.width
            height: parent.height - 60
            Layout.alignment: Qt.AlignCenter
            clip: true
            highlight: Rectangle { color: "yellow"; radius: 5 }
            Connections{
                target: sc_fetch
                onPcChanged:{
                    listaIns.currentIndex =mpc;
                }
            }



        }
        Rectangle{
            width: parent.width
            height: 20
            Layout.alignment: Qt.AlignBottom
            gradient: gradiente_color

            MouseArea{
                anchors.fill: parent
                onPressed: {
                   delegado.assembler = !delegado.assembler
                }

            }
        }
}
    Gradient{
        id: gradiente_color
        GradientStop{position: 0.0; color: "#074e67"}
        GradientStop{position: 0.5; color: "#001440"}
        GradientStop{position: 1.0; color: "#074e67"}
    }


}

