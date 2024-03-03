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
$ time ./pow 3 1000000 > 3p1000000.txt
evaluating
to ascii

real	0m36.833s
user	0m36.690s
sys	0m0.016s
$ time ./pow_gmp 3 100000000 > 3p100000000_gmp.txt
evaluating
to ascii

real	0m10.581s
user	0m9.955s
sys	0m0.568s
```
