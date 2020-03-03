import QtQuick 2.0
import QtQuick.Layouts 1.10

Rectangle{
    width: 200
    height:300
    color: "beige"

    ColumnLayout{
        anchors.fill:parent
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
                text: qsTr("REGISTERS")
            }
        }

        // alineamiento tipo matriz
        Grid{
            Layout.alignment: Qt.AlignCenter
            rows: 8
            columns: 2
            spacing: 3

            Repeater{
                id: repetidor
                model:16

                Row{
                    property alias dataTexto: textoCelda.text
                    property alias colorTexto: textoCelda.color
                    spacing: 3
                    Text {text: "R" + ((index > 9)?"":"0" )+index}
                    Rectangle{
                        height: 25;  width: 60
                        color: "lightgreen" //cambiar
                        Text {
                            id: textoCelda
                            anchors.centerIn: parent
                            font.pointSize: 15
                            text: qsTr("0");

                            Behavior on color {
                                ColorAnimation {
                                    from: "red"
                                    to: "black"
                                    duration: 200
                                }
                            }
                        }
                    }
                }
            }

        }
        Connections{
            target: sc_decode
            onRegisterChanged:{
                actualizarRegs(repetidor)
            }
        }



        Rectangle{
            width: parent.width
            height: 20
            Layout.alignment: Qt.AlignBottom
            gradient: gradiente_color
        }
    }



    function actualizarRegs(matriz){
        for(var i = 0; i < 16; i++){
            if(matriz.itemAt(i).dataTexto !== "" + sc_decode.getRegister(i) ){
                matriz.itemAt(i).dataTexto = "" + sc_decode.getRegister(i)
                matriz.itemAt(i).colorTexto= "red"


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
