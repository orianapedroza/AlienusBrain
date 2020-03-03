import QtQuick 2.0

Rectangle{
    property alias start_sim: sim_timer.timer
    property alias start_tick: sim_timer.tick
    property alias activeList: list.list
    property alias index: alien.position

    Image {
        id: root
        height: parent.height
        width: parent.width
        source: "./content/images/fondo.png"
    }

    Planet{
//        place: "./content/images/Gym.png"/
        x : 900; y:50
        height: 500
        width: 500
        discovered: true
        Termometer{
            id: p1_bio
            width: 30
            height: parent.height/3
            title.text: "B"
            x:360
        }
        Termometer{
            id: p1_cult
            width: 30
            height: parent.height/3
            title.text: "C"
            x:400
        }
        Termometer{
            id: p1_emo
            width: 30
            height: parent.height/3
            title.text: "E"
            x:440
        }
        Connections{
            target: sc_memory
            onMemoryChanged: {
                var bio = sc_memory.getMemory(0)
                var cult = sc_memory.getMemory(1)
                var emo = sc_memory.getMemory(2)

                if(bio>100){
                    sc_memory.setMemory(0,100);
                    bio = 100
                }
                if(cult>100){
                    sc_memory.setMemory(1,100);
                    cult = 100
                }
                if(emo>100){
                    sc_memory.setMemory(2,100);
                    emo = 100
                }
                if(bio<-100){
                    sc_memory.setMemory(0,-100);
                    bio = -100
                }
                if(cult<-100){
                    sc_memory.setMemory(1,-100);
                    cult = -100
                }
                if(emo<-100){
                    sc_memory.setMemory(2,-100);
                    emo = -100
                }


                p1_bio.indicador = bio/100
                p1_cult.indicador = cult/100
                p1_emo.indicador = emo/100
            }
        }
    }

    Planet{
        source: "./content/images/Planeta_purple.png"
        place: "./content/images/Gym.png"
        x : 200; y:50
        height: 500
        width: 500
        discovered: true
    }
    Planet{
        source: "./content/images/Planeta_home.png"
        place: "./content/images/House.png"
        x : 550; y:450
        height: 500
        width: 500
        discovered: true
    }

    Alien{
        id: alien
        property int position: 0
        width:300
        height: 300
//        felicidad: 50
        property var xPositions: [800,400,1100]//casa,gym,restaurant
        property var yPositions: [650,230,220]
        x: xPositions[0]
        y: yPositions[0]
    }
    Connections{
        target: sc_memory
        onMemoryChanged: {
                var bio = sc_memory.getMemory(3)
                var cult = sc_memory.getMemory(4)
                var emo = sc_memory.getMemory(5)

                if(bio>100){
                    sc_memory.setMemory(3,100);
                    bio = 100
                }
                if(cult>100){
                    sc_memory.setMemory(4,100);
                    cult = 100
                }
                if(emo>100){
                    sc_memory.setMemory(5,100);
                    emo = 100
                }
                if(bio<0){
                    sc_memory.setMemory(3,0);
                    bio = 0
                }
                if(cult<0){
                    sc_memory.setMemory(4,0);
                    cult = 0
                }
                if(emo<0){
                    sc_memory.setMemory(5,0);
                    emo = 0
                }

                alien.felicidad = bio *0.5 + cult * 0.3 + emo * 0.2
                alien.bio = bio
                alien.cult = cult
                alien.emo = emo
//            console.log("felicidad de alien  "+ alien.felicidad)
        }
    }

    ATimer{
        id:sim_timer
        onTimesUp: {
            var pos = Math.floor(3 * Math.random())
            alien.x = alien.xPositions[pos]
            alien.y = alien.yPositions[pos]
            alien.position = pos

        }
    }

    ActionList{
        id:list
        x:800
        height: 200
        width:  155
        list.model:ListModel{
            ListElement{act_text:"pollo"; bio_text:10;cul_text:20}
            ListElement{act_text:"carne"; bio_text:20;cul_text:15}
            ListElement{act_text:"arepa"; bio_text:5;cul_text:40}
            ListElement{act_text:"pepino"; bio_text:-40;cul_text:-50}
            ListElement{act_text:"brocoli"; bio_text:-70;cul_text:-30}

        }

    }

}

