#include <Fetch.h>

void Fetch::operation() {

    // If file is open and ok
    if(reg_inst.good()){

        int next=nextpc.read();

        bool cond1= (PC>5);
        bool cond2=(desp_salto==-1);
        bool cond3=(PC<=(file_size/17)+4);

        if(desp_salto>4)desp_salto=-1;

        if (cond1 and cond2 and cond3 and (PC!=next))
        {
            this->PC = next;
            desp_salto++;
            repetitions = 0;

        }else{
            PC++;
            if(desp_salto>-1) desp_salto++;
        }
        // Calculate position of new line
        int pos = PC*21*sizeof(char);

        // If calculated position < File size
        if (pos < file_size)

        {
            // Move to pos(PC)
            reg_inst.seekg(pos);

            string line,opcode1,opcode2,opcode3,opcode4;

            // Read instruction
            getline(reg_inst,line);

            // Separate instruction and operands
            opcode1=line.substr(0,4);
            opcode2=line.substr(4,5);
            opcode3=line.substr(9,5);
            opcode4=line.substr(14,6);

            emit this->pcChanged(this->PC);
            // Increment PC for new clock ahead
            //PC++;
            pcplus4.write(PC+5);

            // Write results
            opcode.write(stoi(opcode1,0,2));
            // cout << stoi(opcode1,0,2) << " ";
            op1.write(stoi(opcode2,0,2));
            // cout << stoi(opcode2,0,2) << " ";
            op2.write(stoi(opcode3,0,2));
            // cout << stoi(opcode3,0,2) << " \n";
            op3.write(stoi(opcode4,0,2));
        }
        // If Calculated position is > file size stall cpu (needs to be stopped somewhere else)
        else
        {
            if(repetitions <= 6)
            {
                opcode.write(0);
                // cout << "0";
                op1.write(0);
                // cout << "0";
                op2.write(0);
                // cout << "0\n";
                op3.write(0);
                pcplus4.write(PC+5);
                repetitions++;

                emit this->pcChanged(this->PC);
            }
            else{
                sc_stop();
            }
        }
    }

    // If file is bad end simulation
    else
    {
        sc_stop();
    }

}
