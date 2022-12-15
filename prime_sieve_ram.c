#include <stdio.h>
#include <stdlib.h>

unsigned int TABLE_LENGTH=0;
unsigned int *table;
unsigned int start_offset=0;
unsigned int prime=0;
unsigned int q[]={0};

void output_prime(unsigned int p){
	//printf("%i,",p);
	q[0]=p;
	fwrite(q,sizeof(unsigned int),1,stdout);
}

void init_table(){
	for(unsigned int i=0;i<TABLE_LENGTH;i++){
		table[i]=i+2;
	}
}

int sieve_step(){
	unsigned int cur_prime;
	for(unsigned int i=start_offset;i<TABLE_LENGTH;i++){
		if(table[i]!=-1){
			cur_prime=table[i];
			start_offset=i;
			break;
		}
	}
	if(start_offset+cur_prime>=TABLE_LENGTH){
		return -1;
	}
	for(unsigned int i=start_offset;i<TABLE_LENGTH;i+=cur_prime){
		table[i]=-1;
	}
	return cur_prime;
}

void dump_remaining(){
	for(unsigned int i=start_offset;i<TABLE_LENGTH;i++){
		if(table[i]!=-1){
			output_prime(table[i]);
		}
	}
}

int main(int argc, char *argv[]){

	if(argc==2){
		TABLE_LENGTH=atoi(argv[1]);
	}

	table=malloc(sizeof(unsigned int)*TABLE_LENGTH);
	if(table==NULL){
		printf("LMAYO NO\n");
		exit(0);
	}
	init_table();
	while(1){
	prime=sieve_step();
	if(prime!=-1){
		output_prime(prime);
	}else{
		dump_remaining();
		break;
	}
	}
}
