all:
	gcc prime_sieve_ram.c -o prime_sieve_ram
	gcc prime_sieve_disk.c -o prime_sieve_disk
	gcc prime_read.c -o prime_read
