#include <stdio.h>
#include <stdlib.h>

int main(){
	int result=0;
	int *b=malloc(sizeof(unsigned int));
	while(1){
		result=fread(b,sizeof(unsigned int),1,stdin);
		if(result==0){
			break;
		}
		printf("%i,",b[0]);
	}
	printf("\n");
}
