#include <Pipe1.h>

void Pipe1 :: operation(){
    // aux1 = opcode_saved;
    // aux2 = op1_saved;
    // aux3 = op2_saved;

    // opcode_saved = opcode_in.read();
    // op1_saved = op1_in.read();
    // op2_saved = op2_in.read();

    // opcode_out.write(aux1);
    // op1_out.write(aux2);
    // op2_out.write(aux3);
    emit this->pipeChanged(opcode_in.read(), op1_in.read(), op2_in.read(), op3_in.read(),pcplus4_in.read());

    opcode_out.write(opcode_in.read());
    op1_out.write(op1_in.read());
    op2_out.write(op2_in.read());
    op3_out.write(op3_in.read());
    pcplus4_out.write(pcplus4_in.read());


}
