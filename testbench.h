#ifndef TESTBENCH_H
#define TESTBENCH_H
#include "systemc.h"
#include <iostream>
#include <Fetch.h>
#include<Pipe1.h>
#include<Decode.h>
#include<Execute.h>
#include<MemoryP.h>
#include<WriteBack.h>

using namespace std;

class Testbench : public sc_module
{

public:

    SC_CTOR(Testbench){
        SC_METHOD(operation)
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

    // Entradas del ALU a Memoria Principal
    array<sc_in <int>, 4> memory;

    // Entradas del pipe2
    array<sc_in <int>, 4> pipe2;

    // Entradas del pipe3
    array<sc_in <int>, 4> pipe3;

    // Entradas de la salida de memoria
    array<sc_in <int>, 4> pipe4;

    // Salidas del pipe2 (solo para compilar, se deben conectar a writeback)
    sc_in <int> reg_dir_data;
    sc_in <int> reg_data;
    sc_in <bool> reg_band;

    // Entrada de reloj
    sc_in<bool> clock;

private:
    void operation();

};

#endif // TESTBENCH_H
