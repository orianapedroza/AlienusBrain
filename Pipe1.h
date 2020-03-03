#ifndef PIPE1
#define PIPE1
#include <bits/stdc++.h>
#include <systemc.h>
#include <QObject>


class Pipe1 : public QObject, public sc_module
{
    Q_OBJECT
    public:
        sc_in <bool> clock;
        sc_in <int> opcode_in;
        sc_in <int> op1_in;
        sc_in <int> op2_in;
        sc_in <int> op3_in;
        sc_in <int> pcplus4_in;
        sc_out <int> opcode_out;
        sc_out <int> op1_out;
        sc_out <int> op2_out;
        sc_out <int> op3_out;
        sc_out <int> pcplus4_out;


         int opcode_saved = 0, op1_saved = 0, op2_saved = 0,op3_saved = 0,pcplus4_saved=0;
        // int aux1 = 0, aux2 = 0, aux3 = 0;

        SC_CTOR(Pipe1)
        {
            SC_METHOD(operation)
                // sensitive << opcode_in << op1_in << op2_in;
                sensitive << clock.pos();

            emit this->pipeChanged(
            opcode_saved,
            op1_saved,
            op2_saved,
            op3_saved,
            pcplus4_saved);
        }
    signals:
        void pipeChanged(int opcode, int op1, int op2, int op3,int pcplus4);

    private:
        void operation();


};


#endif
