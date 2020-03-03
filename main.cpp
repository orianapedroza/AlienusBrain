#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include <QtWidgets/QApplication>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtCore/QDir>


#include "systemc.h"
#include <iostream>
#include <testbench.h>
#include <Fetch.h>
#include<Pipe1.h>
#include<Decode.h>
#include<Execute.h>
#include<MemoryP.h>
#include<WriteBack.h>
#include<clock.h>
#include<timer.h>

int sc_main(int argc, char *argv[]) {return 0;}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
//Aqui comienza System C

    // Variables de control para el tiempo de cada siclo del clock
//    sc_time PERIOD(10,SC_MS);
//    sc_time DELAY(10,SC_MS);
//    sc_clock clock("clock",PERIOD,0.5,DELAY,true);

    Clock clock("clock");
    engine.rootContext()->setContextProperty("sc_clock",&clock);

    // Variables de pipes y stages del MICRO
    Fetch fetch("Fetch_stage");
    engine.rootContext()->setContextProperty("sc_fetch", &fetch);

    Decode decode("Decode_stage");
    engine.rootContext()->setContextProperty("sc_decode", &decode);

    Execute execute("Execute_stage");

    MemoryP memory("MemoryP_stage");
    engine.rootContext()->setContextProperty("sc_memory", &memory);

    WriteBack WB("WriteB_stage");
    engine.rootContext()->setContextProperty("sc_writeback",&WB);

    Pipe1 pipe1("Pipe_reg");
    engine.rootContext()->setContextProperty("sc_pipe1", &pipe1);

    Pipe1 pipe2("Pipe_decode");
    engine.rootContext()->setContextProperty("sc_pipe2", &pipe2);

    Pipe1 pipe3("Pipe_execute");
    engine.rootContext()->setContextProperty("sc_pipe3", &pipe3);

    Pipe1 pipe4("Pipe_memoryP");
    engine.rootContext()->setContextProperty("sc_pipe4", &pipe4);

    Testbench test("testbench");     //esto es como un testbench

    Timer timer;
    engine.rootContext()->setContextProperty("timer", &timer);

    // Señales
    sc_signal<bool> clock_sg;
    array<sc_signal<int>, 5 > fetch_sg;
    array<sc_signal<int>, 5 > decode_sg;
    array<sc_signal<int>, 5 > execute_sg;
    array<sc_signal<int>, 5 > memory_sg;

    array<sc_signal<int>, 5 > pipe1_sg;
    array<sc_signal<int>, 5 > pipe2_sg;
    array<sc_signal<int>, 5 > pipe3_sg;
    array<sc_signal<int>, 5 > pipe4_sg;

    sc_signal<int> reg_dir_data;
    sc_signal<int> reg_data;
    sc_signal<bool> reg_band;
    sc_signal<int> pcplus4_out;

    clock(clock_sg);

    //Salidas de fetch
    fetch.opcode(fetch_sg[0]);
    fetch.op1(fetch_sg[1]);
    fetch.op2(fetch_sg[2]);
    fetch.op3(fetch_sg[3]);
    fetch.pcplus4(fetch_sg[4]);
    fetch.nextpc(pcplus4_out);

    //Entradas de pipe1
    pipe1.opcode_in(fetch_sg[0]);
    pipe1.op1_in(fetch_sg[1]);
    pipe1.op2_in(fetch_sg[2]);
    pipe1.op3_in(fetch_sg[3]);
    pipe1.pcplus4_in(fetch_sg[4]);

    //Entradas de testbench para prueba de salida de fetch
    test.fetch1(fetch_sg[0]);
    test.fetch2(fetch_sg[1]);
    test.fetch3(fetch_sg[2]);
    test.fetch4(fetch_sg[3]);


    //Salidas del pipe1
    pipe1.opcode_out(pipe1_sg[0]);
    pipe1.op1_out(pipe1_sg[1]);
    pipe1.op2_out(pipe1_sg[2]);
    pipe1.op3_out(pipe1_sg[3]);
    pipe1.pcplus4_out(pipe1_sg[4]);

    //Entradas de testbench para prueba de salida de pipe1
    test.pipe1_1(pipe1_sg[0]);
    test.pipe1_2(pipe1_sg[1]);
    test.pipe1_3(pipe1_sg[2]);
    test.pipe1_4(pipe1_sg[3]);

    //Entradas de decode desde salida de pipe1
    decode.opcode_in(pipe1_sg[0]);
    decode.op1_in(pipe1_sg[1]);
    decode.op2_in(pipe1_sg[2]);
    decode.op3_in(pipe1_sg[3]);
    decode.pcplus4_in(pipe1_sg[4]);
    decode.dir_dat(reg_dir_data);
    decode.dat(reg_data);
    decode.band(reg_band);

    //Salidas de decode
    decode.opcode_out(decode_sg[0]);
    decode.op1_out(decode_sg[1]);
    decode.op2_out(decode_sg[2]);
    decode.op3_out(decode_sg[3]);
    decode.pcplus4_out(decode_sg[4]);

    //Entradas de pipe2
    pipe2.opcode_in(decode_sg[0]);
    pipe2.op1_in(decode_sg[1]);
    pipe2.op2_in(decode_sg[2]);
    pipe2.op3_in(decode_sg[3]);
    pipe2.pcplus4_in(decode_sg[4]);

    //Salida pipe2
    pipe2.opcode_out(pipe2_sg[0]);
    pipe2.op1_out(pipe2_sg[1]);
    pipe2.op2_out(pipe2_sg[2]);
    pipe2.op3_out(pipe2_sg[3]);
    pipe2.pcplus4_out(pipe2_sg[4]);

    //Entrada de testbench desde salida de decode
    test.decode[0](decode_sg[0]);
    test.decode[1](decode_sg[1]);
    test.decode[2](decode_sg[2]);
    test.decode[3](decode_sg[3]);
    test.reg_dir_data(reg_dir_data);
    test.reg_data(reg_data);
    test.reg_band(reg_band);

    //Entrada de testbench desde salida de pipe2
    test.pipe2[0](pipe2_sg[0]);
    test.pipe2[1](pipe2_sg[1]);
    test.pipe2[2](pipe2_sg[2]);
    test.pipe2[3](pipe2_sg[3]);


    //Entrada execute
    execute.opcode_in(pipe2_sg[0]);
    execute.op1_in(pipe2_sg[1]);
    execute.op2_in(pipe2_sg[2]);
    execute.op3_in(pipe2_sg[3]);
    execute.pcplus4_in(pipe2_sg[4]);

    //salidas execute
    execute.opcode_out(execute_sg[0]);
    execute.op1_out(execute_sg[1]);
    execute.op2_out(execute_sg[2]);
    execute.op3_out(execute_sg[3]);
    execute.pcplus4_out(execute_sg[4]);

    //Entrada
    pipe3.opcode_in(execute_sg[0]);
    pipe3.op1_in(execute_sg[1]);
    pipe3.op2_in(execute_sg[2]);
    pipe3.op3_in(execute_sg[3]);
    pipe3.pcplus4_in(execute_sg[4]);

    //Salidas
    pipe3.opcode_out(pipe3_sg[0]);
    pipe3.op1_out(pipe3_sg[1]);
    pipe3.op2_out(pipe3_sg[2]);
    pipe3.op3_out(pipe3_sg[3]);
    pipe3.pcplus4_out(pipe3_sg[4]);

    //Entradas de testbench desde salida de execute
    test.execute[0](execute_sg[0]);
    test.execute[1](execute_sg[1]);
    test.execute[2](execute_sg[2]);
    test.execute[3](execute_sg[3]);

    //Entrada de testbench desde salida de pipe3
    test.pipe3[0](pipe3_sg[0]);
    test.pipe3[1](pipe3_sg[1]);
    test.pipe3[2](pipe3_sg[2]);
    test.pipe3[3](pipe3_sg[3]);

    //Entrada memory
    memory.opcode_in(pipe3_sg[0]);
    memory.op1_in(pipe3_sg[1]);
    memory.op2_in(pipe3_sg[2]);
    memory.op3_in(pipe3_sg[3]);
    memory.pcplus4_in(pipe3_sg[4]);

    //salidas memory
    memory.opcode_out(memory_sg[0]);
    memory.op1_out(memory_sg[1]);
    memory.op2_out(memory_sg[2]);
    memory.op3_out(memory_sg[3]);
    memory.pcplus4_out(memory_sg[4]);

    //Entrada p4
    pipe4.opcode_in(memory_sg[0]);
    pipe4.op1_in(memory_sg[1]);
    pipe4.op2_in(memory_sg[2]);
    pipe4.op3_in(memory_sg[3]);
    pipe4.pcplus4_in(memory_sg[4]);

    //Salidas
    pipe4.opcode_out(pipe4_sg[0]);
    pipe4.op1_out(pipe4_sg[1]);
    pipe4.op2_out(pipe4_sg[2]);
    pipe4.op3_out(pipe4_sg[3]);
    pipe4.pcplus4_out(pipe4_sg[4]);

    //Entradas de testbench desde salida de execute
    test.memory[0](memory_sg[0]);
    test.memory[1](memory_sg[1]);
    test.memory[2](memory_sg[2]);
    test.memory[3](memory_sg[3]);

    //Entrada de testbench desde salida de pipe4
    test.pipe4[0](pipe4_sg[0]);
    test.pipe4[1](pipe4_sg[1]);
    test.pipe4[2](pipe4_sg[2]);
    test.pipe4[3](pipe4_sg[3]);

    // //Entradas del Writeback
    WB.opcode_in(pipe4_sg[0]);
    WB.op1_in(pipe4_sg[1]);
    WB.op2_in(pipe4_sg[2]);
    WB.op3_in(pipe4_sg[3]);
    WB.pcplus4_in(pipe4_sg[4]);

    //Salidas del Writeback
    WB.data_out(reg_data);
    WB.direc_out(reg_dir_data);
    WB.band_out(reg_band);
    WB.pcplus4_out(pcplus4_out);

    //Entradas de clocks
    fetch.clock(clock_sg);
    test.clock(clock_sg);
    pipe1.clock(clock_sg);
    pipe2.clock(clock_sg);
    pipe3.clock(clock_sg);
    pipe4.clock(clock_sg);
    decode.clock(clock_sg);
    execute.clock(clock_sg);
    memory.clock(clock_sg);
    WB.clock(clock_sg);

    sc_start(0, SC_NS);



//Aqui comienza QT de nuevo
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
