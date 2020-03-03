import QtQuick 2.0

Rectangle{
//    color:"blue"
//    border.color: "red"
    border.width: 10

    Image {
        id:fetch
        source: "./content/images/fetch1.png"
        height: 600
        width: 600
        y:375
        x:-40
        Text {
            id: pc_texto
            text: qsTr("0")
            font.pointSize: 25
            x:240
            y:290
            font.bold: true
            Connections{
                target: sc_fetch
                onPcChanged:{
                    pc_texto.text = "" + mpc
                    pc_texto.color = "red"
                }
            }
            Behavior on color { //comportamiento

                ColorAnimation {
                    from: "red"
                    to: "black"
                    duration: 500 // 1/2 time clock
                }
            }
        }
        Text {
            id:pc4_texto
            text: qsTr("0")
            x:285
            y:420
            font.pointSize: 25

            Connections{
                target: sc_writeback
                onNextPcChanged: {
                    pc4_texto.text = nextPC;
                    pc4_texto.color = "red";
                }
            }

            Behavior on color {


                ColorAnimation {
                    from: "red"
                    to: "black"
                    duration: 500
                }
            }


        }
    }

    Image {
        id:pipe_1
        source: "./content/images/pipe1.png"
        height: 800
        width: 800
        y:120
        x:45

        Text {
            id: p1_opcode
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:45
        }
        Text {
            id: p1_op1
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:135
        }
        Text {
            id: p1_op2
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:235
        }
        Text {
            id: p1_op3
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:335
        }
        Text {
            id: p1_pc_plus_4
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:515
        }
        Connections{
            target: sc_pipe1
            onPipeChanged: {
                p1_opcode.text =  "" + opcode
                p1_op1.text = "" + op1
                p1_op2.text = "" + op2
                p1_op3.text = "" + op3
                p1_pc_plus_4.text = "" + pcplus4
            }
        }
    }

    Image {
        id: pipe_2
        source: "./content/images/pipe2.png"
        height: 800
        width: 800
        y:120
        x:430
        Text {
            id: p2_opcode
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:45
        }
        Text {
            id: p2_op1
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:135
        }
        Text {
            id: p2_op2
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:235
        }
        Text {
            id: p2_op3
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:335
        }
        Text {
            id: p2_pc_plus_4
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:515
        }
        Connections{
            target: sc_pipe2
            onPipeChanged: {
                p2_opcode.text = "" + opcode
                p2_op1.text = "" + op1
                p2_op2.text = "" + op2
                p2_op3.text = "" + op3
                p2_pc_plus_4.text = "" + pcplus4
            }
        }
        //pipe 3
        Text {
            id: p3_opcode
            text: qsTr("0")
            font.pointSize: 25
            x:610
            y:45
        }
        Text {
            id: p3_op1
            text: qsTr("0")
            font.pointSize: 25
            x:610
            y:135
        }
        Text {
            id: p3_op2
            text: qsTr("0")
            font.pointSize: 25
            x:610
            y:235
        }
        Text {
            id: p3_op3
            text: qsTr("0")
            font.pointSize: 25
            x:610
            y:335
        }
        Text {
            id: p3_pc_plus_4
            text: qsTr("0")
            font.pointSize: 25
            x:610
            y:515
        }
        Connections{
            target: sc_pipe3
            onPipeChanged: {
                p3_opcode.text = "" + opcode
                p3_op1.text = "" + op1
                p3_op2.text = "" + op2
                p3_op3.text = "" + op3
                p3_pc_plus_4.text = "" + pcplus4
            }
        }
    }

    Image {
        id: pipe_4
        source: "./content/images/pipe4.png"
        height: 800
        width: 800
        y:120
        x:1055
        Text {
            id: p4_opcode
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:45
        }
        Text {
            id: p4_op1
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:135
        }
        Text {
            id: p4_op2
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:235
        }
        Text {
            id: p4_op3
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:335
        }
        Text {
            id: p4_pc_plus_4
            text: qsTr("0")
            font.pointSize: 25
            x:355
            y:515
        }
        Connections{
            target: sc_pipe4
            onPipeChanged: {
                p4_opcode.text = "" + opcode
                p4_op1.text = "" + op1
                p4_op2.text = "" + op2
                p4_op3.text = "" + op3
                p4_pc_plus_4.text = "" + pcplus4
            }
        }
    }
    Registers{
        x:496
        y:170
    }

    Memory{
        x:1130
        y:170
    }
    Instructions{
        x:30
        y: 148
    }
}
