import QtQuick 2.0


Rectangle{
    radius: 10
    border.color: (indicador > 0.6)?"green":"red"
    border.width: 5
    property var indicador: 0.0
    property alias title: text
    gradient:life_color
    Text {
        id: text
        y:-20
        color: "white"
        text: qsTr("text")
    }

    Gradient{
        id:life_color
        GradientStop{
            position: 0.0
            color: (indicador === 0.0)?"red":"lightgreen"
        }
        GradientStop{position: indicador;color: "lightgreen"}
        GradientStop{
            position: 1.0
            color: (indicador === 1.0)?"lightgreen":"red"
        }
    }
}
