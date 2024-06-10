#include "driverEP1.h"

int processa (short int *M, int memSize) {
  unsigned short int ri, pc, a, b, c, d, r, psw;
  unsigned short int opArit, res, op1, op2;
  pc=0;

  do {
    ri=M[pc];

    switch (ri&0xF000) {
        case 0x1000:
            //LDA(x)
            a = M[ri & 0x0FFF];
            break;

        case 0x2000:
            //STA(x)
            M[ri & 0x0FFF] = a;
            break;

        case 0x3000:
            //JMP(x)
            r = M[pc+1];
            ri = ri & 0xFFF;
            break;

        case 0x4000:
            //JNZ(x)
            if(a != 0x0000){
            	r = M[pc+1];
            	ri = ri & 0xFFF;
            }
            break;

        case 0x5000:
            //RET
            r = M[pc+1];
            ri = r & 0xFFF;
            break;

        case 0x6000:
            //ARIT
            opArit = M[ri & 0x0E00];
            res = M[ri & 0x01C0];
            op1 = M[ri & 0x0038];
            op2 = M[ri & 0x0007];
            
            switch (opArit){
            	
            	case 000:
            		
            		//Põe como resultado (FFFF)h
            		break;
            		
            	case 001:
            		//Põe como resultado (0000)h
            		break;
            		
            	case 010:
            		//not(Op1)
            		break;
            		
            	case 011:
            		//and(Op1, Op2)
            		break;
            		
            	case 100:
            		//or(Op1, Op2)
            		break;
            		
            	case 101:
            		//xor(Op1, Op2)
            		break;
            		
            	case 110:
            		//add(Op1, Op2}
            		break;
            		
            	case 111:
            		//sub(Op1, Op2)
            		break;
            		
            	default:
            		break;
            }
            break;

        default:
            //NOP
            break;
      }

    pc++;
    if (pc>=memSize) pc=0;
  } while ((ri&0xF000)!=0xF000); //HALT
}
