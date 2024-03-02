#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
void calfact(uint64_t base,uint32_t system){
	//size_t outlen=(size_t)((double)base*(log(base)/log(system)))+1,s;
	//char *out=malloc(outlen+1);
	//uint64_t *p=malloc((base+1)*sizeof(uint64_t));
	//uint64_t *ws=malloc((base+1)*sizeof(uint64_t));
	//memset(p,0,(base+1)*sizeof(uint64_t));
	mpz_t n;
	mpz_init(n);
	fputs("evaluating\n",stderr);
	mpz_set_ui(n,1);
	//while(base>1){
	for(uint64_t i=2;i<=base;++i){
		mpz_mul_ui(n,n,i);
	}
	fputs("to ascii\n",stderr);
	//outlen=extint_ascii(p,s,"0123456789abcdefg",system,out);
	//fputs("mirroring ascii\n",stderr);
	//extint_mirror(out,outlen);
	fprintf(stdout,"%s\n",mpz_get_str(NULL,system,n));
	mpz_clear(n);
}

int main(int argc,char **argv){
	uint32_t system=10;
/*	switch(argc){*/
/*	case 1:*/
/*		puts("pow base exp\npow base");*/
/*		break;*/
/*	case 2:*/
		calfact(atoi(argv[1]),system);
/*		break;*/
/*	case 3:*/
/*		calpow(atoi(argv[1]),atoi(argv[2]),system);*/
/*		break;*/
/*	}*/
}
