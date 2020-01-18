#ifndef FETCH
#define FETCH
#include <systemc.h>
#include <bits/stdc++.h>
 
using namespace std;

class Fetch : sc_module
{
    public:
        // Instruction
        sc_out <int> opcode;
        
        // 1st Operand
        sc_out <int> op1;

        // 2st Operand
        sc_out <int> op2;

        // Clock Signal
        sc_in  <bool> clock;

        int file_size = 0;

        // Program Counter
        int PC=0;

        // Instruction Register
        ifstream  reg_inst;

        int repetitions = 0;

        SC_CTOR(Fetch)
        { 
            // On every positive cycle of clock execute "operation" method
            SC_METHOD(operation)
                sensitive<<clock.pos();

        
            reg_inst.open("DISCO_DURO.txt",ios::in);
            // Move to end of file
            reg_inst.seekg(0,reg_inst.end);
            // Store actual position
            file_size = reg_inst.tellg();
            // Return to file beggining
            reg_inst.seekg(0,reg_inst.beg);
        }

    private:

        void operation ()
        {
            // If file is open and ok
            if(reg_inst.good()){
                
                // Calculate position of new line
                int pos = PC*17*sizeof(char);
                
                // If calculated position < File size
                if (pos < file_size)
                {
                    // Move to pos(PC)
                    reg_inst.seekg(pos);
                    
                    string line,opcode1,opcode2,opcode3;
                    
                    // Read instruction
                    getline(reg_inst,line);

                    // Separate instruction and operands
                    opcode1=line.substr(0,4);
                    opcode2=line.substr(4,6);
                    opcode3=line.substr(10,6);

                    // Increment PC for new clock ahead
                    PC++;
                
                    // Write results
                    opcode.write(stoi(opcode1,0,2));
                    // cout << stoi(opcode1,0,2) << " ";
                    op1.write(stoi(opcode2,0,2));
                    // cout << stoi(opcode2,0,2) << " ";
                    op2.write(stoi(opcode3,0,2));    
                    // cout << stoi(opcode3,0,2) << " \n";      
                }
                // If Calculated position is > file size stall cpu (needs to be stopped somewhere else)
                else
                {   
                    if(repetitions <= 4)
                    {
                        opcode.write(0);
                        // cout << "0";
                        op1.write(0);
                        // cout << "0";
                        op2.write(0); 
                        // cout << "0\n";
                        repetitions++;               
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
};

#endif