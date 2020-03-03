#ifndef DECODE
#define DECODE
#include <bits/stdc++.h>
#include <basics.h>
#include <systemc.h>
#include <QObject>

using namespace std;

class Decode : public QObject, public sc_module
{
    Q_OBJECT
public:
    // Clock input
    sc_in <bool> clock;

    //IN
    sc_in <int> opcode_in;
    sc_in <int> op1_in;
    sc_in <int> op2_in;
    sc_in <int> op3_in;
    sc_in <int> pcplus4_in;

    //Lo que recibira en el write back
    sc_in <int> dir_dat;
    sc_in <int> dat;
    sc_in <bool> band;

    //OUT
    sc_out <int> opcode_out;
    sc_out <int> op1_out;
    sc_out <int> op2_out;
    sc_out <int> op3_out;
    sc_out <int> pcplus4_out;

    // Data registers
    array< int, 64 > dat_register;

    SC_CTOR(Decode)
    {
        // set initial memory 0,op1,op2,op3
        for(auto &a: this->dat_register)
            a = 0;

//        dat_register[1] = 21;
//        dat_register[2] = 12;


        SC_METHOD(operation)
        sensitive << opcode_in << op1_in << op2_in << band << dat << dir_dat << pcplus4_in ;
        //sensitive << clock.pos();
    }

signals:
    void registerChanged();
public slots:
    Q_INVOKABLE int getRegister(int pos);
    Q_INVOKABLE void setRegister(int pos, int data);

private:

    void operation();

};
#endif
