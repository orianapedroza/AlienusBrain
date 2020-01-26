#ifndef DECODE
#define DECODE
#include <bits/stdc++.h>
#include <basics.h>

using namespace std;

class Decode : sc_module
{
  public:
    // Clock input
    sc_in <bool> clock;

    //IN
    sc_in <int> opcode_in;
    sc_in <int> op1_in;
    sc_in <int> op2_in;
    sc_in <int> op3_in;

    //Lo que recibira en el write back
    sc_in <int> dir_dat;
    sc_in <int> dat;
    sc_in <bool> band;

    //OUT
    sc_out <int> opcode_out;
    sc_out <int> op1_out;
    sc_out <int> op2_out;
    sc_out <int> op3_out;

    // Data registers
    array< int, 64 > dat_register;

    SC_CTOR(Decode)
    {
        // set initial memory
        dat_register[2] = 12;
        dat_register[1] = 21;

        SC_METHOD(operation)
                // sensitive << opcode_in << op1_in << op2_in;
                sensitive << clock.pos();
    }

    private:

    void operation()
    {
        // Cuando writeBack esta activo
        if(band.read())
        {
            // Escribir en el registro en la pos = dir_dat, contenido de dat desde writeback 
            dat_register[ dir_dat.read() ] = dat.read();
        }

        // Escribir opcode a siguiente pipe
        opcode_out.write(opcode_in.read());

        // Dependiendo del codigo "OPCODE" acceder a registros o bypass posiciones de memoria
        switch (opcode_in.read())
        {
            case STALL:
            //STALL
                // cout<< "IM in stall\n";
                op1_out.write(0);
                op2_out.write(0);
                op3_out.write(0);
            break;
    
            case LOAD:
            //LOAD
                // cout<< "IM in load\n"; 
                op1_out.write(op1_in.read());
                op2_out.write(0);
                op3_out.write(op3_in.read());
            break;

            case WRITE:
            //STORE
                op1_out.write(op1_in.read());
                op2_out.write(0);
                op3_out.write(op3_in.read());
            break;

            case ADD:
            //ADD
                op1_out.write(dat_register[op1_in.read()]);
                op2_out.write(dat_register[op2_in.read()]);
                op3_out.write(op3_in.read());
            break;

            case SUB:
            //SUB
                op1_out.write(dat_register[op1_in.read()]);
                op2_out.write(dat_register[op2_in.read()]);
                op3_out.write(op3_in.read());
            break;

            case DIV:
            //DIV
                op1_out.write(dat_register[op1_in.read()]);
                op2_out.write(dat_register[op2_in.read()]);
                op3_out.write(op3_in.read());
            break;

            case MULT:
            //MULT
                op1_out.write(dat_register[op1_in.read()]);
                op2_out.write(dat_register[op2_in.read()]);
                op3_out.write(op3_in.read());
            break;

            case LESS:
            //LESS THAN
                op1_out.write(dat_register[op1_in.read()]);
                op2_out.write(dat_register[op2_in.read()]);
                op3_out.write(op3_in.read());
            break;

            case BRANCH:
            //BRANCH
                op1_out.write(dat_register[op1_in.read()]);
                op2_out.write(dat_register[op2_in.read()]);
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