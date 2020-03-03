import QtQuick 2.0


Rectangle{
    color: "transparent"
    property int felicidad: sc_memory.getMemory(3)*0.4+sc_memory.getMemory(4)*0.2+sc_memory.getMemory(5)*0.4
    property int bio: 0
    property int cult: 0
    property int emo: 0

    Image {
        id: feliz
        anchors.fill:parent
        source: "./content/images/Alien_happy.png"
        visible: (felicidad>=75)?true:false
    }

    Image {
        id:molesto
        anchors.fill: parent
        source: "./content/images/Alien_mad.png"
        visible: (felicidad<25)?true:false
    }

    Image{
        id:triste
        anchors.fill: parent
        source: "./content/images/Alien_sad.png"
        visible: (felicidad>=25 && felicidad<50)?true:false

    }

    Image{
        id:neutral
        anchors.fill: parent
        source: "./content/images/Alien_neutral.png"
        visible: (felicidad>=50 && felicidad<75)?true:false

    }
    Termometer{
        x : parent.width
        width: 40
        height: parent.height
        title.text: "Felicidad"
        indicador: felicidad/100
    }
    Termometer{
        x : parent.width +50
        y : (parent.height*0.2)
        width: 40
        height: parent.height-(parent.height*0.2)
        title.text: "B"
        indicador: bio/100
    }
    Termometer{
        x : parent.width + 100
        y : (parent.height*0.2)
        width: 40
        height: parent.height-(parent.height*0.2)
        title.text: "C"
        indicador: cult/100
    }
    Termometer{
        x : parent.width + 150
        y : (parent.height*0.2)
        width: 40
        height: parent.height-(parent.height*0.2)
        title.text: "E"
        indicador: emo/100
    }



}
