#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
void calfact(uint64_t base,uint32_t system){
	mpz_t n;
	mpz_init(n);
	fputs("evaluating\n",stderr);
	mpz_set_ui(n,1);
	for(uint64_t i=2;i<=base;++i){
		mpz_mul_ui(n,n,i);
	}
	fputs("to ascii\n",stderr);
	fprintf(stdout,"%s\n",mpz_get_str(NULL,system,n));
	mpz_clear(n);
}
void calpow(uint64_t base,uint64_t pow,uint32_t system){
	mpz_t n;
	mpz_init(n);
	fputs("evaluating\n",stderr);
	mpz_ui_pow_ui(n,base,pow);
	fputs("to ascii\n",stderr);
	fprintf(stdout,"%s\n",mpz_get_str(NULL,system,n));
	mpz_clear(n);
}
int main(int argc,char **argv){
	uint32_t system=10;
	switch(argc){
	case 1:
		puts("pow base exp\npow base");
		break;
	case 2:
		calfact(atoi(argv[1]),system);
		break;
	case 3:
		calpow(atoi(argv[1]),atoi(argv[2]),system);
		break;
	}
}
