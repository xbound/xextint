#include <stdint.h>
#include <stddef.h>
size_t extint_add(uint64_t *buf,uint64_t addend);
size_t extint_add2(uint64_t *buf,const uint64_t *addend_buf,size_t size);
size_t extint_sub(uint64_t *buf,uint64_t subtractor);
size_t extint_sub2(uint64_t *buf,const uint64_t *subtractor_buf,size_t size);
size_t extint_mul(uint64_t *buf,size_t size,uint32_t factor,uint64_t *workspace);
size_t extint_mul2(uint64_t *buf,size_t bufsize,const uint64_t *factor_buf,size_t factor_size,uint64_t *workspace);
size_t extint_div(uint64_t *buf,size_t size,uint32_t divisor,uint32_t *mod);
void extint_copy(uint64_t *dst,const uint64_t *src,size_t size);
void extint_zero(uint64_t *buf,size_t size);
void extint_mirror(char *buf,size_t size);
size_t extint_ascii(uint64_t *buf,size_t size,const char *chars,uint32_t system,char *outbuf);
