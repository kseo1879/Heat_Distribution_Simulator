CC=gcc 
CFLAGS=-Wall -Werror -std=gnu11 -fsanitize=address -fopenmp -g
.PHONY: clean


firewall: ./firewall.c
	$(CC) $(CFLAGS) $^ -o $@

test_2d:
	time ./firewall 2d

test_3d:
	time ./firewall 3d

clean:
	rm -f *.o
	rm -f firewall