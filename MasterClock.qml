import QtQuick 2.0
import QtCharts 2.3
import QtQuick.Controls 2.12

Rectangle {
    id: root
    color: "gray"

    signal started()

    Row{
        x: 5; y:5
        spacing: 5
        Column{
            width: 75
            spacing: 5
            Button{
                width: parent.width
                text: "Next PC"; onPressed: sc_clock.next()
            }
            Text { text: qsTr("Period:"); font.pointSize: 16}
            Rectangle {
                radius: 10
                height: root.height/8
                width: parent.width
                TextInput {
                    id: period_input
                    anchors.fill: parent
                }
            }
            Button{
                width: parent.width
                text: "Start"
                onPressed: {
                    root.started()
                    sc_clock.start(parseInt(period_input.text))
                }
            }
            Button{
                width: parent.width
                text: "Pause"; onPressed: sc_clock.pause()
            }
            Button{
                width: parent.width
                text: "Stop"; onPressed: sc_clock.stop()
            }

        }

        ChartView {
            id: chart
            property int times: 0
            property int cycles: 0
            property int period: parseInt(period_input.text)
            width: root.width - period_input.width
            height: root.height
            theme: ChartView.ChartThemeBlueCerulean
            antialiasing: true

            ValueAxis {
                id: time
                min:0
                max:2 * parseInt(period_input.text,10)
//                tickInterval: 200
//                tickCount:4
                Behavior on min {
                    NumberAnimation {duration: parseInt(period_input.text,10)/2 }
                }
                Behavior on max {
                    NumberAnimation {duration: parseInt(period_input.text,10)/2 }
                }

            }
            ValueAxis {
                id: logicState
                min: -1
                max: 2
            }
            LineSeries {
                id: lineSeries1
                name: "clock"
                axisX: time
                axisY: logicState
            }

            Connections {
                target: sc_clock
                onNewCycle: {
                    lineSeries1.append(chart.times * parseInt(period_input.text,10), 0);
                    lineSeries1.append(chart.times * parseInt(period_input.text,10), 1);
                    lineSeries1.append((chart.times * parseInt(period_input.text,10)) + parseInt(period_input.text,10) / 2, 1);
                    lineSeries1.append((chart.times * parseInt(period_input.text,10)) + parseInt(period_input.text,10) / 2, 0);
                    lineSeries1.append((chart.times * parseInt(period_input.text,10)) + parseInt(period_input.text,10), 0);
                    chart.times += 1;
                    chart.cycles +=1;
                    if(chart.cycles >= 1) {
                        time.min = (chart.times * parseInt(period_input.text,10)) - parseInt(period_input.text,10);
                        time.max = (chart.times * parseInt(period_input.text,10)-parseInt(period_input.text,10)) + 2 * parseInt(period_input.text,10);
                        chart.cycles = 0;
//                        time.applyNiceNumbers();
                    }
                }
            }

        }
    }
}
