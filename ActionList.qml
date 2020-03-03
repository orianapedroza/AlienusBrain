import QtQuick 2.0

Rectangle{
    property alias list: actions
    color:"purple"
//    property alias index: actions

    Component{
        id:delegate
        Item{
            id:item
            height: 25
            width:parent.width
            Row{
                spacing: 8
                Text {
                    id: action
                    width: 75
                    text:"  " + act_text
                    font.pointSize: 15
                    font.bold: true
                }
                Text {
                    id:biologic
                    text: bio_text + "  "
                    font.pointSize: 15
                    font.bold: true
                }
                Text {
                    id: culture
                    text: cul_text
                    font.pointSize: 15
                    font.bold: true
                }
            }
            MouseArea{
                anchors.fill: parent
                hoverEnabled: false
                onPressed:{
                    actions.currentIndex = index
                    actions.activiti = actions.model.get(index).act_text
                    actions.biological = actions.model.get(index).bio_text
                    actions.cultural = actions.model.get(index).cul_text
                }
            }
        }
    }



    Column{
        anchors.fill: parent
        Rectangle{
            border.color: "white"
            height: 20
            width: parent.width

            Row{
                anchors.fill: parent
                spacing: 10
                Text { text:" Accion";font.pointSize:14; font.bold: true}
                Text {text: "Bio"; font.pointSize:14; font.bold: true}
                Text {text: "Cult"; font.pointSize:14; font.bold: true}
            }
        }
        ListView {
            height: parent.height - 20
            id: actions
            property var activiti: 0
            property var biological: 0
            property var cultural: 0

            width: parent.width
            delegate: delegate
            focus: true
            highlight: Rectangle{
                color: "lightgreen"
                radius: 5
            }
            model:ListModel{
                ListElement{act_text:"pollo"; bio_text:40;cul_text:20}
                ListElement{act_text:"carne"; bio_text:50;cul_text:20}
            }
        }
    }



}
