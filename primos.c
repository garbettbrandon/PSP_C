#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// 1 proceso
void primo(int first_parameter, int end_parameter){
	int divisor;
	int es_primos;
	
	while(end_parameter> first_parameter){
		es_primos=1;
		int valorActual=first_parameter;
		for(divisor=2;first_parameter>divisor;divisor++){
			if(valorActual%divisor==0){
				es_primos=0;
				break;
			}
		}
		if(es_primos){
			printf("\n%d", valorActual);
		}
	first_parameter++;
	}
}

// 2 procesos
void main(){
	int i;
	pid_t pid;
	char buffer[30];
	
	pid=fork();//se crea el proceso hijo
	
	switch(pid){
		case -1://ERROR
			printf("NO SE HA PODIDO CREAR HIJO...");
			exit(-1);
			break;
		case 0://HIJO
			primo(100000,150000);
			exit(0);
			break;
		default://PADRE
			wait(NULL);
			primo(150001,200000);
			break;				
	}
}

// 4 procesos

void main(){
	int i,n=4,cont=0;
	int primI=100000;
	int primF=200000;	
	
	for(i=0;i<n;i++){
		if(fork()==0){
			imprimePrimos(primI+n,primF,n);
			printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
			exit(0);
		}
	}
	for(i=0;i<n;i++){
		wait(NULL);
	}
	return 0;
}

int imprimePrimos(ini, fin, n){
	int cont,j,i;
	for(i=ini;i<=fin;i=i+n){
		cont=0;
		for(j=1; j<=i; j++){
	    	if(i%j==0)
				cont++;
		}
		if(cont==2){
			printf("%d\t ",i);
		}
	}
	return 0;
}