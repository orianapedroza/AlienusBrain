#ifndef FETCH
#define FETCH
#include <systemc.h>
#include <bits/stdc++.h>
#include <QObject>

using namespace std;

class Fetch : public QObject , public sc_module
{
    Q_OBJECT

public:
    // Instruction
    sc_out <int> opcode;

    // 1st Operand
    sc_out <int> op1;

    // 2st Operand
    sc_out <int> op2;

    //3st Operand
    sc_out <int> op3;

    //pc + 4 salida
    sc_out <int> pcplus4;

    sc_in <int> nextpc;


    // Clock Signal
    sc_in  <bool> clock;

    int desp_salto=-1;
    int file_size = 0;

    // Program Counter
    int PC=-1;

    // Instruction Register
    ifstream  reg_inst;

    int repetitions = 0;

    SC_CTOR(Fetch)
    {
            // On every positive cycle of clock execute "operation" method
        SC_METHOD(operation)
        sensitive<<clock.pos();

        // Open HARD_DISK jajaja
        reg_inst.open("DISCO_DURO.txt",ios::in);
        // Move to end of file
        reg_inst.seekg(0,reg_inst.end);
        // Store actual position
        file_size = reg_inst.tellg();
        // Return to file beggining
        reg_inst.seekg(0,reg_inst.beg);
    }


signals:
    void pcChanged(int mpc);

private:
    void operation ();
};

#endif
