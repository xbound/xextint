#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <signal.h>
volatile sig_atomic_t run=1,show=0;
void sh(int sig){
	run=0;
}
void usr(int sig){
	show=1;
}
void cale(uint64_t pow,uint32_t system){
	uint64_t i,s;
	int inf=(pow==UINT64_MAX);
	mpq_t e,n,a,a2;
	mpz_t er,ee,d;
	mpq_inits(n,e,a,a2,NULL);
	mpq_set_ui(e,2,1);
	mpq_set_ui(n,1,1);
	mpq_set_ui(a,1,1);
	mpq_set_ui(a2,1,1);
	fputs("evaluating\n",stderr);
	for(i=2;(i<=pow+1||inf)&&run;++i){
		mpq_add(a,a,a2);
		mpq_div(n,n,a);
		mpq_add(e,e,n);
		if(show){
			uint64_t ci=i;
			double dig=0;
			while(--ci>1){
				dig+=log((double)ci);
			}
			fprintf(stderr,"%lu digits\n",(uint64_t)(dig/log((double)system))+1);
			show=0;
		}
	}
	mpq_canonicalize(e);
	mpz_inits(er,ee,d,NULL);
	mpz_set(er,&e->_mp_num);
	mpz_set(ee,&e->_mp_den);
	mpq_clears(n,e,a,a2,NULL);
	mpz_div(d,er,ee);
	double dig=0;
	while(--i>1){
		dig+=log((double)i);
	}
	i=(uint64_t)(dig/log((double)system))+2;
	fprintf(stderr,"%lu digits before . to ascii\n",i-1);
	char *p;
	gmp_asprintf(&p,"%Zd",d);
	fprintf(stdout,"%s.",p);
	free(p);

	while(--i){
		mpz_submul(er,d,ee);
		mpz_mul_ui(er,er,10);
		mpz_div(d,er,ee);
		s=gmp_asprintf(&p,"%Zd",d);
		fwrite(p,1,s,stdout);
		free(p);
	}
	fwrite("\n",1,1,stdout);
	mpz_clears(er,ee,d,NULL);
}
int main(int argc,char **argv){
	uint32_t system=10;
	signal(SIGINT,sh);
	signal(SIGTERM,sh);
	signal(SIGUSR1,usr);
	cale(argv[1]?atol(argv[1]):UINT64_MAX,system);
}
