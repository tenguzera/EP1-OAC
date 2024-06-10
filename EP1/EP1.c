#include "driverEP1.h"

int processa (short int *M, int memSize) {
  unsigned short int ri, pc, a, b, c, d, r, psw;
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
            printf("STA\n");
            M[ri & 0x0FFF] = a;
            break;

        case 0x3000:
            //JMP(x)
            printf("JMP\n");
            break;

        case 0x4000:
            //JNZ(x)
            printf("JNZ\n");
            break;

        case 0x5000:
            //RET
            printf("RET\n");
            break;

        case 0x6000:
            //ARIT
            printf("ARIT\n");
            break;

        default:
            //NOP
            break;
      }

    pc++;
    if (pc>=memSize) pc=0;
  } while ((ri&0xF000)!=0xF000); //HALT
}
