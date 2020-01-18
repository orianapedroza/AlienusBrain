#include "systemc.h"
#include <iostream>
#include <Fetch.h>
#include<Pipe1.h>
using namespace std;

class aux: sc_module
{
    private:
    void ops()
    {
        cout<<" | PIPE1 |\n";
        cout<<" | I | O |\n";
        cout<<" | "<< fetch1.read()<<" | "<< pipe1_1.read() << " |\n";
        cout<<" | "<< fetch2.read()<<" | "<< pipe1_2.read() << " |\n";
        cout<<" | "<< fetch3.read()<<" | "<< pipe1_3.read() << " |\n";
    
    }

    public:
    SC_CTOR(aux){
        SC_METHOD(ops)
            sensitive << clock.pos() ;
            // sensitive << fetch1;
    }

    sc_in<int> fetch1;
    sc_in<int> fetch2;
    sc_in<int> fetch3;

    sc_in<int> pipe1_1;
    sc_in<int> pipe1_2;
    sc_in<int> pipe1_3;

    sc_in<bool> clock;
};


int sc_main(int argc, char* argv[])
{
    sc_time PERIOD(10,SC_NS);
    sc_time DELAY(10,SC_NS);
    sc_clock clock("clock",PERIOD,0.5,DELAY,true);

    Fetch fetch("Fetch_stage");
    Pipe1 pipe1("Pipe_reg");
    aux test("testbench");
    array<sc_signal<int>, 3 > fetch_sg; 
    array<sc_signal<int>, 3 > pipe1_sg; 

    fetch.opcode(fetch_sg[0]);
    fetch.op1(fetch_sg[1]);
    fetch.op2(fetch_sg[2]);

    pipe1.opcode_in(fetch_sg[0]);
    pipe1.op1_in(fetch_sg[1]);
    pipe1.op2_in(fetch_sg[2]);

    test.fetch1(fetch_sg[0]);
    test.fetch2(fetch_sg[1]);
    test.fetch3(fetch_sg[2]);

    pipe1.opcode_out(pipe1_sg[0]);
    pipe1.op1_out(pipe1_sg[1]);
    pipe1.op2_out(pipe1_sg[2]);

    test.pipe1_1(pipe1_sg[0]);
    test.pipe1_2(pipe1_sg[1]);
    test.pipe1_3(pipe1_sg[2]);

    fetch.clock(clock);
    test.clock(clock);
    pipe1.clock(clock);

    sc_start();
    // cout << "Hello World!" << endl;
    return 0;
}
