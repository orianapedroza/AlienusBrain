#ifndef PIPE1
#define PIPE1
#include <bits/stdc++.h>

class Pipe1 : sc_module
{
    public:
        sc_in <bool> clock;
        sc_in <int> opcode_in;
        sc_in <int> op1_in;
        sc_in <int> op2_in;
        sc_out <int> opcode_out;
        sc_out <int> op1_out;
        sc_out <int> op2_out;
        int opcode_saved = 0, op1_saved = 0, op2_saved = 0;
        int aux1 = 0, aux2 = 0, aux3 = 0;

        SC_CTOR(Pipe1)
        {
            SC_METHOD(operation)
                // sensitive << opcode_in << op1_in << op2_in;
                sensitive << clock.pos();
        }


    private:
    void operation()
    {
        // aux1 = opcode_saved;
        // aux2 = op1_saved;
        // aux3 = op2_saved;

        // opcode_saved = opcode_in.read();
        // op1_saved = op1_in.read();
        // op2_saved = op2_in.read();

        // opcode_out.write(aux1);
        // op1_out.write(aux2);
        // op2_out.write(aux3);

        opcode_out.write(opcode_in.read());
        op1_out.write(op1_in.read());
        op2_out.write(op2_in.read());

    }

};


#endif