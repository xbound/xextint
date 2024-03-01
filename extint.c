#include "extint.h"
//#define USE_LIBC
size_t extint_add(uint64_t *buf,uint64_t addend){
	uint64_t *restrict p=buf;
	do {
		addend=((*(p++)+=addend)<addend);
	}while(addend);
	return p-buf;
}
size_t extint_add2(uint64_t *buf,const uint64_t *addend_buf,size_t size){
	uint64_t *restrict p=buf;
	size_t s,r=0;
	while(size--){
		s=extint_add(p,*(addend_buf++))+(p-buf);
		if(s>r)r=s;
		++p;
	}
	return r;
}
size_t extint_sub(uint64_t *buf,uint64_t subtractor){
	uint64_t *restrict p=buf;
	do {
		subtractor=((*(p++)-=subtractor)>subtractor);
	}while(subtractor);
	return p-buf;
}
size_t extint_sub2(uint64_t *buf,const uint64_t *subtractor_buf,size_t size){
	uint64_t *restrict p=buf;
	size_t s,r=0;
	while(size--){
		s=extint_sub(p,*(subtractor_buf++))+(p-buf);
		if(s>r)r=s;
		++p;
	}
	return r;
}
size_t extint_mul(uint64_t *buf,size_t size,uint32_t factor,uint64_t *workspace){
	//uint32_t carry=0;
	uint32_t *restrict p;
	uint32_t *restrict wp;
	union {
		uint64_t v;
		size_t size;
	} un;
	size_t size32=size<<1,csize32;
	for(p=(uint32_t *)buf,wp=(uint32_t *)workspace;
			(p-(uint32_t *)buf)<size32;
			++p,++wp){
		un.v=((uint64_t)*p)*factor;
		*p=un.v&0xfffffffful;
		*wp=(un.v>>32ul);
	}
	csize32=size32;
	for(p=(uint32_t *)buf,wp=(uint32_t *)workspace;
			(wp-(uint32_t *)workspace)<csize32;
			++p,++wp){
		if(!*wp)continue;
		//un.size=((p-(uint32_t *)buf+1)>>1)+extint_add((uint64_t *)(p+1),*wp);
		un.size=p-(uint32_t *)buf;
		if(((uintptr_t)p)&7)
		//if(un.size&1)
			un.size=(un.size>>1)+1+
				extint_add((uint64_t *)(p+1),*wp);
		else {
			*wp=((p[1]+=*wp)<*wp);
			if(*wp){
			un.size=(un.size>>1)+1+
				extint_add((uint64_t *)(p+2),*wp);
			}else continue;
		}
		if(un.size>size){
			size=un.size;
			size32=size<<1;
		}
	}
	return size;
}
size_t extint_mul2(uint64_t *buf,size_t bufsize,const uint64_t *factor_buf,size_t factor_size,uint64_t *workspace){
	uint32_t *restrict p=(uint32_t *)buf;
	uint32_t *restrict fbuf=(uint32_t *)factor_buf;
	uint64_t *pa=workspace+bufsize,
		 *wsp=workspace+bufsize*2+1,
		 *endp=buf+bufsize+factor_size;
	size_t i=(factor_size<<1);
	extint_copy(workspace,buf,bufsize);
	extint_zero(buf,bufsize+factor_size);
	while(i--){
		extint_zero(pa,wsp-pa);
		extint_copy(pa,workspace,bufsize);
		if(extint_mul(pa,bufsize,*(fbuf++),wsp)>bufsize)
			extint_add2((uint64_t *)p,pa,bufsize+1);
		else
			extint_add2((uint64_t *)p,pa,bufsize);
		++p;
	}
	while(--endp>buf){
		if(*endp)break;
	}
	return endp-buf+1;
}
size_t extint_div(uint64_t *buf,size_t size,uint32_t divisor,uint32_t *mod){
	uint32_t *p=(uint32_t *)(buf+size);
	uint64_t v;
	size_t rsize=0;
	uint32_t backup=0;
	*(uint32_t *)p=0;
	do {
		--p;
		v=*(uint64_t *)p/divisor;
		if(!v)continue;
		//extint_sub((uint64_t *)p,v*divisor);
		*(uint64_t *)p-=v*divisor;
		//*(uint64_t *)p%=divisor;
		((uint32_t *)p)[1]=backup;
		//extint_add((uint64_t *)qp,v);
		//*(uint32_t *)qp=v;
		backup=v;
		if(!rsize)rsize=(p-(uint32_t *)buf)+1;
	}while(p>(uint32_t *)buf);
	*mod=*(uint32_t *)buf;
	*(uint32_t *)buf=backup;
	if(rsize)
		return (rsize+1)>>1;//+1+1
	else return 0;
}
void extint_copy(uint64_t *dst,const uint64_t *src,size_t size){
#ifndef USE_LIBC
	do
		*(dst++)=*(src++);
	while(--size);
#else
	__builtin_memcpy(dst,src,size*sizeof(uint64_t));
#endif
}
void extint_zero(uint64_t *buf,size_t size){
#ifndef USE_LIBC
	do
		*(buf++)=0ul;
	while(--size);
#else
	__builtin_memset(buf,0,size*sizeof(uint64_t));
#endif
}
void extint_mirror(char *buf,size_t size){
	char *out=buf+size-1,swapbuf;
	while(out>buf){
		swapbuf=*out;
		*out=*buf;
		*buf=swapbuf;
		--out;
		++buf;
	}
}
size_t extint_ascii(uint64_t *buf,size_t size,const char *chars,uint32_t system,char *outbuf){
	//size_t s;
	//uint64_t *m,*q,*swapbuf;
	uint32_t mod,ds=system,dsn,n=1;
	char *out=outbuf;
	//extint_copy(workspace,buf,size);
	/*extint_zero(workspace+size,size);
	m=workspace;
	q=m+size;
	do {
		s=extint_div(m,size,system,q);
		*(out++)=chars[*m];
		*m=0;
		swapbuf=m;
		m=q;
		q=swapbuf;
	}while(s);*/
	for(;;){
		dsn=ds*system;
		if(dsn>ds&&!(dsn%ds)){
			ds=dsn;
			++n;
		}
		else break;
	}
	//__builtin_printf("%u\n",ds);
	for(;;){
		size=extint_div(buf,size,ds,&mod);
		if(size){
			for(dsn=n;dsn;--dsn){
				*(out++)=chars[mod%system];
				mod/=system;
			}
		}else {
			while(mod){
				*(out++)=chars[mod%system];
				mod/=system;
			}
			break;
		}
	}
	*out=0;
	size=out-outbuf;
	return size;
}
