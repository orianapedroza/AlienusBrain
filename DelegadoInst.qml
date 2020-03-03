import QtQuick 2.12
import QtQuick.Layouts 1.3
import "Utilidades.js" as Utils

//Reglas de como se debe ver cada elemento de la lista
Component {
//    color: "transparent"
    Item {
//        property alias assem: item.asssembler
        id: item
        height: 20
        width: parent.width
        x:8

//        property bool assembler: false
        Row{
            Text {
                width: 35
                font.bold: true
                font.pointSize: 12
                verticalAlignment: Text.AlignBottom
                text: " " + line + " "
            }
            Text {
                font.bold: true
                font.pointSize: 9
                verticalAlignment: Text.AlignVCenter
                width: 70
                text: assembler ?Utils.toAssembler(opcode) :opcode
            }
            Text {
                width: 45
                text: assembler ?parseInt(operand1,2):operand1
                font.bold: true
                font.pointSize: 10
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                width: 45
                text: assembler ?parseInt(operand2,2):operand2
                font.bold: true
                font.pointSize: 10
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                width: 45
                text: assembler ?parseInt(destination,2): destination
                font.bold: true
                font.pointSize: 10
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
