all: mlucky 

mlucky: luckyomp.c 
	gcc luckyomp.c -std=c99 -O1 -lm -fopenmp -o mlucky

clean:
	rm -f mlucky *.o
