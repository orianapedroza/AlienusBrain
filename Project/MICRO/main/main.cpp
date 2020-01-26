#include "systemc.h"
#include <iostream>
#include <Fetch.h>
#include<Pipe1.h>
#include<Decode.h>
#include<Execute.h>

using namespace std;

class aux: sc_module
{
    private:
    void ops()
    {
        // Tabla de salida
        cout<<" | PIPE1 | PIPE2 | PIPE3 |\n";
        cout<<" | I | O | I | O | I | O |\n";

        cout<<" | "<< fetch1.read()<<" | "<< pipe1_1.read();
        cout<<" | "<< decode[0].read() << " | "<< pipe2[0].read();
        cout<<" | "<< execute[0].read() << " | "<< pipe3[0].read() << " |\n";
        
        cout<<" | "<< fetch2.read()<<" | "<< pipe1_2.read();
        cout<<" | "<< decode[1].read() << " | "<< pipe2[1].read();
        cout<<" | "<< execute[1].read() << " | "<< pipe3[1].read() << " |\n";       
        
        cout<<" | "<< fetch3.read()<<" | "<< pipe1_3.read();
        cout<<" | "<< decode[2].read() << " | "<< pipe2[2].read();
        cout<<" | "<< execute[2].read() << " | "<< pipe3[2].read() << " |\n";

        cout<<" | "<< fetch4.read()<<" | "<< pipe1_4.read();
        cout<<" | "<< decode[3].read() << " | "<< pipe2[3].read();
        cout<<" | "<< execute[3].read() << " | "<< pipe3[3].read() << " |\n";
    
    }

    public:
    SC_CTOR(aux){
        SC_METHOD(ops)
            sensitive << clock.pos() ;
            // sensitive << fetch1;
    }

    // Entradas del fetch
    sc_in<int> fetch1;
    sc_in<int> fetch2;
    sc_in<int> fetch3; 
    sc_in <int> fetch4;

    // Entradas del pipe1
    sc_in<int> pipe1_1;
    sc_in<int> pipe1_2;
    sc_in<int> pipe1_3;
    sc_in <int> pipe1_4;

    // Entradas del decode
    array<sc_in <int>, 4> decode;

    // Entradas del execute stage (ALU)
    array<sc_in <int>, 4> execute;

    // Entradas del pipe2
    array<sc_in <int>, 4> pipe2;

    // Entradas del pipe3
    array<sc_in <int>, 4> pipe3;
    
    // Salidas del pipe2 (solo para compilar, se deben conectar a writeback)
    sc_out <int> reg_dir_data;
    sc_out <int> reg_data;
    sc_out <bool> reg_band;

    // Entrada de reloj
    sc_in<bool> clock;
};


int sc_main(int argc, char* argv[])
{
    // Variables de control para el tiempo de cada siclo del clock
    sc_time PERIOD(10,SC_NS);
    sc_time DELAY(10,SC_NS);
    sc_clock clock("clock",PERIOD,0.5,DELAY,true);

    // Variables de pipes y stages del MICRO
    Fetch fetch("Fetch_stage"); 
    Decode decode("Decode_stage");
    Execute execute("Execute_stage");
    Pipe1 pipe1("Pipe_reg");
    Pipe1 pipe2("Pipe_decode");
    Pipe1 pipe3("Pipe_execute");
    aux test("testbench");     //esto es como un testbench YOLO!!!!!
    
    // Señales
    array<sc_signal<int>, 4 > fetch_sg; 
    array<sc_signal<int>, 4 > pipe1_sg;
    array<sc_signal<int>, 4 > decode_sg;
    array<sc_signal<int>, 4 > execute_sg;
    array<sc_signal<int>, 4 > pipe2_sg;
    array<sc_signal<int>, 4 > pipe3_sg;

    sc_signal<int> reg_dir_data;
    sc_signal<int> reg_data;
    sc_signal<bool> reg_band;

    //Salidas de fetch
    fetch.opcode(fetch_sg[0]);
    fetch.op1(fetch_sg[1]);
    fetch.op2(fetch_sg[2]);
    fetch.op3(fetch_sg[3]);

    //Entradas de pipe1
    pipe1.opcode_in(fetch_sg[0]);
    pipe1.op1_in(fetch_sg[1]);
    pipe1.op2_in(fetch_sg[2]);
    pipe1.op3_in(fetch_sg[3]);

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
    decode.dir_dat(reg_dir_data);
    decode.dat(reg_data);
    decode.band(reg_band);

    //Salidas de decode
    decode.opcode_out(decode_sg[0]);
    decode.op1_out(decode_sg[1]);
    decode.op2_out(decode_sg[2]);
    decode.op3_out(decode_sg[3]);

    //Entradas de pipe2
    pipe2.opcode_in(decode_sg[0]);
    pipe2.op1_in(decode_sg[1]);
    pipe2.op2_in(decode_sg[2]);
    pipe2.op3_in(decode_sg[3]);

    //Salida pipe2
    pipe2.opcode_out(pipe2_sg[0]);
    pipe2.op1_out(pipe2_sg[1]);
    pipe2.op2_out(pipe2_sg[2]);
    pipe2.op3_out(pipe2_sg[3]);


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

    //salidas execute
    execute.opcode_out(execute_sg[0]);
    execute.op1_out(execute_sg[1]);
    execute.op2_out(execute_sg[2]);
    execute.op3_out(execute_sg[3]);

    //Entrada
    pipe3.opcode_in(execute_sg[0]);
    pipe3.op1_in(execute_sg[1]);
    pipe3.op2_in(execute_sg[2]);
    pipe3.op3_in(execute_sg[3]);

    //Salidas
    pipe3.opcode_out(pipe3_sg[0]);
    pipe3.op1_out(pipe3_sg[1]);
    pipe3.op2_out(pipe3_sg[2]);
    pipe3.op3_out(pipe3_sg[3]);

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



    //Entradas de clocks
    fetch.clock(clock);
    test.clock(clock);
    pipe1.clock(clock);
    pipe2.clock(clock);
    pipe3.clock(clock);
    decode.clock(clock);
    execute.clock(clock);

    sc_start();
    return 0;
}
