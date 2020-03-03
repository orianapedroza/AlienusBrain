#include <WriteBack.h>
#include <QDebug>


void WriteBack :: operation(){

    switch (opcode_in.read())
    {
    case STALL:
        //STALL
        // cout<< "IM in stall\n";

        data_out.write(0);
        direc_out.write(0);
        band_out.write(0);
        pcplus4_out.write(pcplus4_in.read());
        emit nextPcChanged(pcplus4_in.read());
        break;

    case LOAD:
        //LOAD
//        qDebug() <<  "datos salida WB: " << op3_in.read() <<"  "<< op1_in.read() << "\n";
        data_out.write(op1_in.read());
        direc_out.write(op3_in.read());
        band_out.write(1);
        pcplus4_out.write(pcplus4_in.read());
        emit nextPcChanged(pcplus4_in.read());
        break;

    case WRITE:
        //STORE
//        qDebug() <<  "datos salida WB: " << op3_in.read() <<"  "<< op1_in.read() << "\n";
        data_out.write(0);
        direc_out.write(0);
        band_out.write(0);
        pcplus4_out.write(pcplus4_in.read());
        emit nextPcChanged(pcplus4_in.read());
        break;

    case ADD:
        //ADD
//        cout << "datos salida WB: " << op3_in.read() <<"  "<< op1_in.read() << "\n";
//        qDebug() <<  "datos salida WB: " << op3_in.read() <<"  "<< op1_in.read() << "\n";
        band_out.write(1);
        data_out.write(op1_in.read());
        direc_out.write(op3_in.read());
        pcplus4_out.write(pcplus4_in.read());
        emit nextPcChanged(pcplus4_in.read());
        break;

    case SUB:
        //SUB
//        qDebug() <<  "datos salida WB: " << op3_in.read() <<"  "<< op1_in.read() << "\n";
        data_out.write(op1_in.read());
        direc_out.write(op3_in.read());
        band_out.write(1);
        pcplus4_out.write(pcplus4_in.read());
        emit nextPcChanged(pcplus4_in.read());
        break;

    case DIV:
        //DIV
        data_out.write(op1_in.read());
        direc_out.write(op3_in.read());
        band_out.write(1);
        pcplus4_out.write(pcplus4_in.read());
        emit nextPcChanged(pcplus4_in.read());
        break;

    case MULT:
        //MULT
        data_out.write(op1_in.read());
        direc_out.write(op3_in.read());
        band_out.write(1);
        pcplus4_out.write(pcplus4_in.read());
        emit nextPcChanged(pcplus4_in.read());
        break;

    case LESS:
        //LESS THAN
        data_out.write(op1_in.read());
        direc_out.write(op3_in.read());
        band_out.write(1);
        pcplus4_out.write(pcplus4_in.read());
        emit nextPcChanged(pcplus4_in.read());
        break;

    case BRANCH:
    case NBRNCH:
        //BRANCH
        if(op1_in.read())
        {
            pcplus4_out.write(op3_in.read());
            emit nextPcChanged(op3_in.read());
        }else {
            pcplus4_out.write(pcplus4_in.read());
            emit nextPcChanged(pcplus4_in.read());
        }

        data_out.write(op1_in.read());
        direc_out.write(op3_in.read());
        band_out.write(0);
        break;

    case LOADS:
        //LOAD
        //        qDebug() <<  "datos salida WB: " << op3_in.read() <<"  "<< op1_in.read() << "\n";
        data_out.write(op1_in.read());
        direc_out.write(op3_in.read());
        band_out.write(1);
        pcplus4_out.write(pcplus4_in.read());
        emit nextPcChanged(pcplus4_in.read());
        break;

    case WRITES:
        //STORE
        //        qDebug() <<  "datos salida WB: " << op3_in.read() <<"  "<< op1_in.read() << "\n";
        data_out.write(0);
        direc_out.write(0);
        band_out.write(0);
        pcplus4_out.write(pcplus4_in.read());
        emit nextPcChanged(pcplus4_in.read());
        break;

    default:
        data_out.write(0);
        direc_out.write(0);
        band_out.write(0);
        pcplus4_out.write(pcplus4_in.read());
        emit nextPcChanged(pcplus4_in.read());
        break;

    }


}
