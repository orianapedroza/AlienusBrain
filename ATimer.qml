import QtQuick 2.0

Item{
    id: root
    property alias timer: m_timer
    property alias tick: angles_div
    property int ang: 0
    signal timesUp()

    Rectangle{
        id:minimo
        width: 75
        height: 25
        color: "white"
        radius: 5
        y:220
        x:25
        TextInput{
            anchors.centerIn: parent
            id: min_text
            anchors.fill: parent
        }


    }

    Rectangle{
        id:maximo
        width:75
        height: 25
        color: "white"
        radius: 5
        x:110
        y:220
        TextInput{
            anchors.centerIn: parent
            id: max_text
            anchors.fill: parent
        }
    }
    Rectangle{
        width:75
        height: 25
        y:250
        x:25
        color: "lightgray"
        radius: 5
        Text{
            text: "Set Interval"
        }

        MouseArea{
            anchors.fill: parent
            onPressed: {
                m_timer.interval = calculateRandom(parseInt(min_text.text),parseInt(max_text.text))
                interval.text = m_timer.interval
                root.ang = 0
            }
        }
    }

    Rectangle{
        width:75
        height: 25
        color: "white"
        radius: 5
        x:110
        y:250
        Text{
            anchors.centerIn: parent
            id: interval
            anchors.fill: parent
        }
    }





    Image{
    source: "./content/images/clock-night.png"
    }

    Timer {
        id: m_timer
        interval: 100; running: false; repeat: true;
        onTriggered: {
            root.timesUp()
            root.ang = 0
            m_timer.interval = calculateRandom(parseInt(min_text.text),parseInt(max_text.text))
            interval.text = m_timer.interval
//            angles_div.running = false
//            angles_div.running = true

        }
    }

    Timer {
        id: angles_div
        interval: m_timer.interval / 12 ; running: m_timer.running; repeat: true;
        onTriggered: {
            root.ang = root.ang + 30
        }
    }


    Image {
        id: aguja
        source: "./content/images/hour.png"
        x: 92.5; y: 27
        opacity: 0.5
        transform: Rotation {
            id: secondRotation
            origin.x: 7.5; origin.y: 73
            angle: root.ang
            Behavior on angle {
                SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
            }
        }
    }
    function calculateRandom(min,max)
    {
        return min + Math.floor(Math.random() * Math.floor(max-min))
    }
}
