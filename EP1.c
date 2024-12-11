#include "driverEP1.h"

int ajustaPSW(unsigned short int op1, unsigned short int op2) {
    unsigned short int PSWaux = 0x0088;

    if(op1 > op2) PSWaux = PSWaux | 0x0800;
    else if(op1 < op2) PSWaux = PSWaux | 0x2000;
    else if(op1 == op2) PSWaux = PSWaux | 0x1000;

    return PSWaux;
}

int processa(short int *M, int memSize) {
  unsigned short int ri, pc, a, b, c, d, r, psw;
  unsigned short int opArit;
  unsigned short int *res, *op1, *op2;
  unsigned short int opZerado = 0;
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
            ri = ri & 0x0FFF;
            break;

        case 0x4000:
            //JNZ(x)
            if(a != 0x0000) {
            	r = M[pc+1];
            	ri = ri & 0x0FFF;
            }
            break;

        case 0x5000:
            //RET
            r = M[pc+1];
            ri = r & 0xFFF;
            break;

        case 0x6000:
            //ARIT
            opArit = M[ri & 0x0E00]; //define qual a op a ser feita

            switch (M[ri & 0x01C0]) { //define qual o res

                case 000:
                    res = &a;
                    break;

                case 001:
                    res = &b;
                    break;

                case 010:
                    res = &c;
                    break;

                case 011:
                    res = &d;
                    break;

                case 110:
                    res = &r;
                    break;

                default:
                    break;
            }

            switch (M[ri & 0x0038]) { //define qual o op1

                case 000:
                    op1 = &a;
                    break;

                case 001:
                    op1 = &b;
                    break;

                case 010:
                    op1 = &c;
                    break;

                case 011:
                    op1 = &d;
                    break;

                case 110:
                    op1 = &r;
                    break;

                default:
                    break;
            }

            if((M[(ri & 0x0007) & 100]) == 1) { //define qual o op2
                switch (M[(ri & 0x0007) & 011]) {

                    case 00:
                        op2 = &a;
                        break;

                    case 01:
                        op2 = &b;
                        break;

                    case 10:
                        op2 = &c;
                        break;

                    case 11:
                        op2 = &d;
                        break;

                    default:
                        break;

                }
            } else op2 = &opZerado;
            
            switch (opArit) {
            	
            	case 000:
            		//Põe como resultado (FFFF)h
                    *res = 0xFFFF;
            		break;
            		
            	case 001:
            		//Põe como resultado (0000)h
                    *res = 0x0000;
            		break;
            		
            	case 010:
            		//not(Op1)
                    *res = ~(*op1);
                    psw = ajustaPSW(*op1, *op1);
            		break;
            		
            	case 011:
            		//and(Op1, Op2)
                    *res = *op1 & *op2;
                    psw = ajustaPSW(*op1, *op2);
            		break;
            		
            	case 100:
            		//or(Op1, Op2)
                    *res = *op1 | *op2;
                    psw = ajustaPSW(*op1, *op2);
            		break;
            		
            	case 101:
            		//xor(Op1, Op2)
                    *res = *op1 ^ *op2;
                    psw = ajustaPSW(*op1, *op2);
            		break;
            		
            	case 110:
            		//add(Op1, Op2}
                    *res = *op1 + *op2;
                    psw = ajustaPSW(*op1, *op2);
                    unsigned int verificaOverflow = *op1 + *op2;
                    if(verificaOverflow > 0xFFFF) psw = psw | 0x8000;
            		break;
            		
            	case 111:
            		//sub(Op1, Op2)
                    *res = *op2 - *op2;
                    psw = ajustaPSW(*op1, *op2);
                    unsigned int verificaUnderflow = *op2 - *op2;
                    if(verificaUnderflow < 0) psw = psw | 0x4000;
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

  } while ((ri&0xF000)!= 0xF000); //HALT
}