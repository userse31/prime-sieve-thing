#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

unsigned int TABLE_LENGTH=0;
unsigned int *b;
FILE *swap;
unsigned int start_offset=0;
unsigned int a;

unsigned int read_swap(unsigned int pos){
	rewind(swap);
	fseek(swap,pos*sizeof(unsigned int),SEEK_SET);
	fread(b,sizeof(unsigned int),1,swap);
	return b[0];
}

void write_swap(unsigned int pos, unsigned int x){
	rewind(swap);
	fseek(swap,pos*sizeof(unsigned int),SEEK_SET);
	b[0]=x;
	fwrite(b,sizeof(unsigned int),1,swap);
}

void output_prime(unsigned int p){
	//printf("%i,",p);
	b[0]=p;
	fwrite(b,sizeof(unsigned int),1,stdout);
}

unsigned int sieve_step(){
	unsigned int cur_prime;
	for(unsigned int i=start_offset;i<TABLE_LENGTH;i++){
		a=read_swap(i);//disk access is slow! Avoid duplicates.
		if(a!=-1){
			cur_prime=a;
			start_offset=i;
			break;
		}
	}
	if(start_offset+cur_prime>=TABLE_LENGTH){
		return -1;
	}
	for(unsigned int i=start_offset;i<TABLE_LENGTH;i+=cur_prime){
		write_swap(i,-1);
	}
	return cur_prime;
}

void dump_remaining(){
	for(int i=start_offset;i<TABLE_LENGTH;i++){
		a=read_swap(i);
		if(a!=-1){
			output_prime(a);
		}
	}
}

void run_sieve(){
	a=0;
	while(1){
		a=sieve_step();
		if(a==-1){
			dump_remaining();
			break;
		}else{
			output_prime(a);
		}
	}
}

int main(int argc, char *argv[]){
	//create the swap file table thing.
	if(argc==2){
		TABLE_LENGTH=atoi(argv[1]);
	}
	char *command=malloc(sizeof(char)*512);
	snprintf(command,512,"dd if=/dev/zero of=./tmp bs=1 count=%i status=none",atoi(argv[1])*sizeof(unsigned int));
	system(command);
	swap=fopen("./tmp","r+");
	TABLE_LENGTH=atoi(argv[1]);
	free(command);
	//init the table
	b=malloc(sizeof(unsigned int));
	for(unsigned int i=0;i<TABLE_LENGTH;i++){
		b[0]=i+2;
		fwrite(b,sizeof(unsigned int),1,swap);
	}
	
	run_sieve();

	/*for(int i=0;i<TABLE_LENGTH;i++){
		printf("%i\n",read_swap(i));
	}*/
}
