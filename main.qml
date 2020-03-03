import QtQuick 2.12
import QtQuick.Window 2.12
import QtQml.Models 2.12

Window {
    visible: true
    width: 1920
    height: 1800
    title: qsTr("---")

        BarraTitulo {
            width: parent.width
            height: 70
            titulo.text: "AlienusBrain"
        }
        ListView{
            id: root
            y:70
            x:300
            height: parent.height-70
            width: parent.width
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            highlightMoveDuration: 1000
            focus: false
            orientation: ListView.Horizontal
            boundsBehavior: Flickable.StopAtBounds

            model: ObjectModel{
                Simulation{
                    id: simulation
                    width: root.width
                    height: root.height
                }

                Micro{
                    width: root.width
                    height: root.heightt
                }
            }
        }
        BarraIzq {
            y:70
            width: 300
            height: parent.height - 70


            MasterClock{
                width: 300
                height: 300
                onStarted: {
                    simulation.start_sim.running = true
                    simulation.start_tick.running = true
                }
            }

            Rectangle{

                id:button
                width: 150
                height: 50
                y:930
                color: "lightgrey"
                Text {
                    text: qsTr("Aplicar Cambios")
                }
                MouseArea{
                    anchors.fill:parent
                    onPressed: {
                        if (simulation.index==2){
                            var biologic = parseInt(simulation.activeList.biological)
                            var currentBio = sc_memory.getMemory(0)
                            var terLugarBio = currentBio + biologic
                            console.log("food: "+biologic+" current: "+currentBio+" result: "+terLugarBio+"\n")

                            var cult = parseInt(simulation.activeList.cultural)
                            var currentCult = sc_memory.getMemory(1)
                            var terLugarCult = currentCult + cult
                            console.log("cult: "+cult+" current: "+currentCult+" result: "+terLugarCult+"\n")

                            var emotional = Math.floor(Math.random() * Math.floor(100))

                            if(terLugarBio <= 100)
                                sc_memory.setMemory(0,terLugarBio)
                            if(terLugarCult <= 100)
                                sc_memory.setMemory(1,terLugarCult)
                            sc_memory.setMemory(2,emotional)
                        }
                    }
                }
            }
        }
}
