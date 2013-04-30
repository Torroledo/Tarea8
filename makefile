t0.3.txt: gauss.out parabola.out 
	./gauss.out 
	./parabola.out 
gauss.out: gauss.c 
	cc -o gauss.out gauss.c -lm 
parabola.out: parabola.c
	cc -o parabola.out parabola.c -lm 
clean:
	rm -f *.txt
	rm -f *.out