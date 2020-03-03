#ifndef MEMORYP
#define MEMORYP
#include <bits/stdc++.h>
#include <basics.h>
#include <systemc.h>
#include <QObject>

using namespace std;

class MemoryP : public QObject,public sc_module
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

        //OUT
        sc_out <int> opcode_out;
        sc_out <int> op1_out;
        sc_out <int> op2_out;
        sc_out <int> op3_out;
        sc_out <int> pcplus4_out;

        // Data registers
        array< int, 64 > dat_memory;//64 de precision

        SC_CTOR(MemoryP)
        {
            for(int i = 0; i < 64; i++)
                dat_memory[i] = 0;

            SC_METHOD(operation)
            sensitive << opcode_in << op1_in << op2_in << pcplus4_in;
                   // sensitive << clock.pos();
        }
    signals:
        void memoryChanged();

    public slots:
        Q_INVOKABLE int getMemory(int pos);
        Q_INVOKABLE void setMemory(int pos,int data);

    private:

        void operation();
};

#endif
