#include <MemoryP.h>

void MemoryP :: operation(){
    // Escribir opcode a siguiente pipe
    opcode_out.write(opcode_in.read());
    pcplus4_out.write(pcplus4_in.read());
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
        op1_out.write(dat_memory[op1_in.read()]);//Leo lo que tengo en m.p
        op2_out.write(0);
        op3_out.write(op3_in.read());
        break;

    case WRITE:
        //STORE
        dat_memory[op3_in.read()] = op1_in.read();//Traigo de mi cache y escribo en m.p
        op1_out.write(0);
        op2_out.write(0);
        op3_out.write(0);
        break;

    case ADD:
        //ADD
        op1_out.write(op1_in.read());
        op2_out.write(op2_in.read());
        op3_out.write(op3_in.read());
        break;

    case SUB:
        //SUB
        op1_out.write(op1_in.read());
        op2_out.write(op2_in.read());
        op3_out.write(op3_in.read());
        break;

    case DIV:
        //DIV
        op1_out.write(op1_in.read());
        op2_out.write(op2_in.read());
        op3_out.write(op3_in.read());
        break;

    case MULT:
        //MULT
        op1_out.write(op1_in.read());
        op2_out.write(op2_in.read());
        op3_out.write(op3_in.read());
        break;

    case LESS:
        //LESS THAN
        op1_out.write(op1_in.read());
        op2_out.write(op2_in.read());
        op3_out.write(op3_in.read());
        break;

    case BRANCH:
        //BRANCH
        op1_out.write(op1_in.read());
        op2_out.write(op2_in.read());
        op3_out.write(op3_in.read());
        break;

    case NBRNCH:
        op1_out.write(op1_in.read());
        op2_out.write(op2_in.read());
        op3_out.write(op3_in.read());
        break;

    case LOADS:
        //LOAD
        // cout<< "IM in load\n";
        op1_out.write(dat_memory[op1_in.read()]);//Leo lo que tengo en m.p
        op2_out.write(0);
        op3_out.write(op3_in.read());
        break;

    case WRITES:
        //STORE
        dat_memory[op3_in.read()] = op1_in.read();//Traigo de mi cache y escribo en m.p
        emit this->memoryChanged();
        op1_out.write(0);
        op2_out.write(0);
        op3_out.write(0);
        break;

    default:
        op1_out.write(0);
        op2_out.write(0);
        op3_out.write(0);

        break;

    }

}

int MemoryP::getMemory(int pos)
{
    return this->dat_memory[pos];

}

void MemoryP::setMemory(int pos, int data)
{
    this->dat_memory[pos]=data;
    emit this->memoryChanged();
}
