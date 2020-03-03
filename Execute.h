#ifndef EXECUTE_H
#define EXECUTE_H
#include <bits/stdc++.h>
#include <basics.h>
#include <systemc.h>
#include <QDebug>

using namespace std;

class Execute : sc_module
{
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

    SC_CTOR(Execute)
    {

        SC_METHOD(operation)
        sensitive << opcode_in << op3_in<< pcplus4_in;
                //sensitive << clock.pos();
    }

    private:

    void operation()
    {
        // Escribir opcode a siguiente pipe
        opcode_out.write(opcode_in.read());
        op2_out.write(op2_in.read());
        pcplus4_out.write(pcplus4_in.read());

        // Dependiendo del codigo "OPCODE" acceder a registros o bypass posiciones de memoria
        // Bypass: lo que entra sale igual.
        switch (opcode_in.read())
        {
            case STALL:
            //STALL
                // cout<< "IM in stall\n";
                op1_out.write(0);
                op3_out.write(0);
            break;
    
            case LOAD:
            //LOAD
                // cout<< "IM in load\n"; 
                op1_out.write(op1_in.read());
                op3_out.write(op3_in.read());
            break;

            case WRITE:
            //STORE
                op1_out.write(op1_in.read());
                op3_out.write(op3_in.read());
            break;

            case ADD:
            //ADD
                op1_out.write(op1_in.read() + op2_in.read());
                op3_out.write(op3_in.read());
            break;

            case SUB:
            //SUB
                op1_out.write(op1_in.read() - op2_in.read());
                op3_out.write(op3_in.read());
            break;

            case DIV:
            //DIV
                op1_out.write(op1_in.read() / op2_in.read());
                op3_out.write(op3_in.read());
            break;

            case MULT:
            //MULT
                op1_out.write(op1_in.read() * op2_in.read());
                op3_out.write(op3_in.read());
            break;

            case LESS:
            //LESS THAN
                op1_out.write(op1_in.read() < op2_in.read());
                op3_out.write(op3_in.read());
            break;

            case BRANCH:
            //BRANCH
                op1_out.write( (op1_in.read() == op2_in.read()) ?(1) :(0) );
                // if (op1_in.read() == op2_in.read()) 
                //     op1_out.write(1);
                // else 
                //     op1_out.write(0);

                op3_out.write(op3_in.read()); //esto es la posicion de pc.... writeback da esto al pc
            break;

            case NBRNCH:
//                qDebug() << "datos NBRNCH: " <<op1_in.read() << "  "<<op2_in.read()<<"\n";

                op1_out.write( (op1_in.read() == op2_in.read()) ?(0) :(1) );
                op3_out.write(op3_in.read()); //esto es la posicion de pc.... writeback da esto al pc
                break;
            case LOADS:
                //LOAD
                op1_out.write(op1_in.read());
                op3_out.write(op3_in.read());
                break;

            case WRITES:
                //STORE
                op1_out.write(op1_in.read());
                op3_out.write(op3_in.read());
                break;

            default:
                op1_out.write(0);
                op2_out.write(0);
                op3_out.write(0);
                break;

        }


    }
        

};
#endif
