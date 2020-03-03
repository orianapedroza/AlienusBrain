#include <Decode.h>
#include <QDebug>

void Decode:: operation(){
    // Cuando writeBack esta activo
    if(band.read())
    {
        // Escribir en el registro en la pos = dir_dat, contenido de dat desde writeback
//        qDebug() << "datos de WB: " <<  dir_dat.read() << "    " << dat.read() <<"\n";
            dat_register[ dir_dat.read() ] = dat.read();
            emit this->registerChanged();
    }

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
        op1_out.write(op1_in.read());
        op2_out.write(0);
        op3_out.write(op3_in.read());
        break;

    case WRITE:
        //STORE
        op1_out.write(this->dat_register.at(op1_in.read()));
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
    case NBRNCH:
        op1_out.write(dat_register[op1_in.read()]);
        op2_out.write(dat_register[op2_in.read()]);
        op3_out.write(op3_in.read());
        break;

    case LOADS:
        //Nuevo LOAD para suma op1 y op2
        op1_out.write(op1_in.read() + op2_in.read());
        op2_out.write(0);
        op3_out.write(op3_in.read());
        break;

    case WRITES:
        //STORE
        op1_out.write(this->dat_register.at(op1_in.read() + op2_in.read()));
        op2_out.write(0);
        op3_out.write(op3_in.read());
        break;

    default:
        op1_out.write(0);
        op2_out.write(0);
        op3_out.write(0);

        break;
    }
}
int Decode:: getRegister(int pos){

    return this->dat_register[pos];

}
void Decode:: setRegister(int pos, int data){

    this->dat_register[pos] = data;
    emit this->registerChanged();
}
