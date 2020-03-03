#ifndef WRITEBACK
#define WRITEBACK
#include <bits/stdc++.h>
#include <basics.h>
#include <systemc.h>
#include <QObject>

using namespace std;

class WriteBack :public QObject, public  sc_module
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
        sc_out <int> data_out; //Dato
        sc_out <int> direc_out; //Direccion
        sc_out <bool> band_out;  //Enable
        sc_out <int> pcplus4_out;

        SC_CTOR(WriteBack)
        {
            SC_METHOD(operation)
                    sensitive << clock.pos();
//            sensitive << opcode_in << op1_in << op2_in;
        }

    signals:
        void nextPcChanged(int nextPC);

    private:

        void operation();

};

#endif
