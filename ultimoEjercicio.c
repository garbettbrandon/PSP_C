#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(void){
	int fd[2];
	int fd1[2];
	pid_t pid;
	int num=-1;
	int suma=0;
	pipe(fd);
	pipe(fd1);
	pid=fork();

	switch(pid){
		case -1: //ERROR
			printf("NO SE HA PODIDO CREAR HIJO...");
			exit(-1);
		case 0: //HIJO 
			for(int i=0; i<2;i++){
				printf("SOY HIJO\n");
				read(fd[0],&num,sizeof(num));//HIJO LEE PIPE
				printf("%d\n",num);
				suma=suma+num;
				printf("la suma es %d \n",suma);
				if(i==1){
					write(fd1[1],&suma,sizeof(suma));
					printf("Hago la suma y salgo\n");
					exit(0);
				}
			}
			break;
		default: //PADRE 	
			printf("PADRE\n");
			for(int i=0; i<2;i++){
				close(fd[0]);
				printf("Número aleatorio: %d\n",i);
				num=rand()%21;
				write(fd[1],&num,sizeof(num));//PADRE ESCRIBE
				}

			wait(NULL);//Espera a que el hijo acabe
			break;
			read(fd[1],&suma,sizeof(suma));
			printf("La suma es: %d\n",suma);
			}
	return 0;
}