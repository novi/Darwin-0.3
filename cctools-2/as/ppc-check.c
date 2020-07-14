#include <stdio.h>
#include "ppc-opcode.h"

static int bits(
    unsigned long width);

static char *cond[] = { "lt", "gt", "eq", "un"};
static char *pred[] = { "+", "-" };

void
main(
int argc,
char *argv[],
char *envp[])
{
    long i, j, x, d, p, doing_jbsr;

	doing_jbsr = 0;
	p = 0;
	for(i = 0; *(ppc_opcodes[i].name) != '\0'; i++){
	    if(strcmp("jbsr", ppc_opcodes[i].name) == 0)
		continue;
	    printf("\t%s", ppc_opcodes[i].name);
	    if(IS_BRANCH_CONDITIONAL(ppc_opcodes[i].opcode)){
		p = bits(5) & 1;
		printf("%s", pred[p]);
	    }
	    if(ppc_opcodes[i].ops[0].type == NONE)
		printf("\n");
	    else
		printf("\t");
	    d = 0;
	    for(j = 0; j < 5 && ppc_opcodes[i].ops[j].type != NONE; j++){
		switch(ppc_opcodes[i].ops[j].type){
		case PCREL:
		    if(doing_jbsr)
			printf("L1");
		    else
			printf("_relitive");
		    break;
		case BADDR:
		    printf("_absolute");
		    break;
		case D:
		    printf("0x%04x(", bits(16));
		    d = 1;
		    break;
		case DS:
		    printf("0x%04x(", bits(14) << 2);
		    d = 1;
		    break;
		case SI:
		case UI:
		case HI:
		    printf("0x%04x", bits(16));
		    break;
		case GREG:
		    printf("r%d", bits(5) );
		    break;
		case G0REG:
		    printf("r%d", bits(5) | 0x1 );
		    break;
		case FREG:
		    printf("f%d", bits(5) );
		    break;
		case SGREG:
		    printf("sr%d", bits(4) );
		    break;
		case SPREG:
		    printf("%d", bits(10) );
		    break;
		case BCND:
		    printf("cr%d+%s", bits(3), cond[bits(2)] );
		    break;
		case CRF:
		case CRFONLY:
		    x = bits(3);
		    printf("cr%ld", x == 0 ? 1 : x);
		    break;
		case sh:
		    printf("%d", bits(6) );
		    break;
		case mb:
		    printf("%d", bits(6) );
		    break;
		case NUM0:
		case NUM:
		    if(j == 0 &&
		       IS_BRANCH_CONDITIONAL(ppc_opcodes[i].opcode)){
			x = bits(ppc_opcodes[i].ops[j].width);
			if(ppc_opcodes[i].ops[2].type == PCREL)
			    if(p == 0) /* + with negative disp */
				x &= 0xfffffffe; 
			    else
				x |= 1; 
			else
			    if(p == 0) /* + with positive disp */
				x |= 1; 
			    else
				x &= 0xfffffffe; 
			if(x == 20)
			    x = 0;
			printf("%ld", x);
		    }
		    else
			printf("%d", bits(ppc_opcodes[i].ops[j].width) );
		    break;
		case NONE:
		    break;
		case ZERO:
		    printf("0");
		    break;
		case JBSR:
		    printf("_long_branch_stub");
		    doing_jbsr = 1;
		    break;
		default:
		    fprintf(stderr, "Unknown parameter type\n");
		    exit(1);
		}
		if(j == 4 || ppc_opcodes[i].ops[j+1].type == NONE){
		    if(d == 1)
			printf(")\n");
		    else{
			if(doing_jbsr){
			    printf("\n");
			    printf("L1:\n");
			    doing_jbsr = 0;
			}
			else
			    printf("\n");
		    }
		}
		else{
		    if(ppc_opcodes[i].ops[j].type != D &&
		       ppc_opcodes[i].ops[j].type != DS)
			printf(",");
		}
	    }
	}
	exit(0);
}

static
int
bits(
unsigned long width)
{
     static int x = 1;

	x = (x + 1) & ((1 << width) - 1);
	return(x);
}
