#include "extint.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
void calpow(uint64_t base,uint64_t pow,uint32_t system){
	size_t outlen=(size_t)((double)pow*(log(base)/log(system)))+1,s,s2;
	char *out=malloc(outlen+1);
	uint64_t *p=malloc((pow+1)*sizeof(uint64_t));
	uint64_t *p1=malloc((pow+1)*sizeof(uint64_t));
	uint64_t *p2=malloc((pow+1)*sizeof(uint64_t));
	uint64_t *ws=malloc(((pow+1)*3+1)*sizeof(uint64_t));
	memset(p,0,(pow+1)*sizeof(uint64_t));
	memset(p2,0,(pow+1)*sizeof(uint64_t));
	fputs("evaluating\n",stderr);
	s=extint_add(p,base);
	s2=extint_add(p2,1);
	for(uint64_t i=pow;i;i>>=1){
		if(i&1){
			s2=extint_mul2(p2,s2,p,s,ws);
			if(i==1)break;
		}
		memcpy(p1,p,(s)*sizeof(uint64_t));
		//printf("i=%lu,s=%zu,s2=%zu\n",i,s,s2);
		s=extint_mul2(p,s,p1,s,ws);
	}
	fputs("to ascii\n",stderr);
	//exit(0);
	outlen=extint_ascii(p2,s2,"0123456789abcdefg",system,out);
	//fputs("mirroring ascii\n",stderr);
	extint_mirror(out,outlen);
	fwrite(out,1,outlen,stdout);
	fwrite("\n",1,1,stdout);
	free(out);
	free(p);
	free(p1);
	free(p2);
	free(ws);
}
void calfact(uint64_t base,uint32_t system){
	size_t outlen=(size_t)((double)base*(log(base)/log(system)))+1,s;
	char *out=malloc(outlen+1);
	uint64_t *p=malloc((base+1)*sizeof(uint64_t));
	uint64_t *ws=malloc((base+1)*sizeof(uint64_t));
	memset(p,0,(base+1)*sizeof(uint64_t));
	fputs("evaluating\n",stderr);
	s=extint_add(p,1);
	//while(base>1){
	for(uint64_t i=2;i<=base;++i){
		s=extint_mul(p,s,i,ws);
	}
	fputs("to ascii\n",stderr);
	outlen=extint_ascii(p,s,"0123456789abcdefg",system,out);
	//fputs("mirroring ascii\n",stderr);
	extint_mirror(out,outlen);
	fwrite(out,1,outlen,stdout);
	fwrite("\n",1,1,stdout);
	free(out);
	free(p);
	free(ws);
}
void calpow_old(uint64_t base,uint64_t pow,uint32_t system){
	size_t outlen=(size_t)((double)pow*(log(base)/log(system)))+1,s;
	char *out=malloc(outlen+1);
	uint64_t *p=malloc((pow+1)*sizeof(uint64_t));
	uint64_t *ws=malloc((pow+1)*sizeof(uint64_t));
	memset(p,0,(pow+1)*sizeof(uint64_t));
	fputs("evaluating\n",stderr);
	s=extint_add(p,1);
	//while(base>1){
	for(uint64_t i=0;i<pow;++i){
		s=extint_mul(p,s,base,ws);
	}
	fputs("to ascii\n",stderr);
	outlen=extint_ascii(p,s,"0123456789abcdefg",system,out);
	//fputs("mirroring ascii\n",stderr);
	extint_mirror(out,outlen);
	fwrite(out,1,outlen,stdout);
	fwrite("\n",1,1,stdout);
	free(out);
	free(p);
	free(ws);
}
void calfactsum(uint64_t base,uint32_t system){
	size_t outlen=(size_t)((double)base*(log(base)/log(system)))+1,s,s1,s2;
	char *out=malloc(outlen+1);
	uint64_t *p=malloc((base+1)*sizeof(uint64_t));
	uint64_t *sum=malloc((base+2)*sizeof(uint64_t));
	uint64_t *ws=malloc((base+1)*sizeof(uint64_t));
	memset(p,0,(base+1)*sizeof(uint64_t));
	memset(sum,0,(base+2)*sizeof(uint64_t));
	fputs("evaluating\n",stderr);
	s=extint_add(p,1);
	//while(base>1){
	s1=extint_add(sum,1);
	for(uint64_t i=2;i<=base;++i){
		s=extint_mul(p,s,i,ws);
		s2=extint_add2(sum,p,s);
		if(s2>s1)s1=s2;
	}
	fputs("to ascii\n",stderr);
	outlen=extint_ascii(sum,s1,"0123456789abcdefg",system,out);
	//fputs("mirroring ascii\n",stderr);
	extint_mirror(out,outlen);
	fwrite(out,1,outlen,stdout);
	fwrite("\n",1,1,stdout);
	free(out);
	free(p);
	free(sum);
	free(ws);
}
int main(int argc,char **argv){
	uint32_t system=16;
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
