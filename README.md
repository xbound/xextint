Compared with GMP
```
$ time ./pow 1000000 >fact1000000.txt
evaluating
to ascii

real	78m35.954s
user	78m34.913s
sys	0m0.600s
$ time ./pow_gmp 1000000 >fact1000000_gmp.txt
evaluating
to ascii

real	1m23.940s
user	1m23.917s
sys	0m0.020s
```
