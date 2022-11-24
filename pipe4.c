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
			while(num!=17){
				read(fd[0],&num,sizeof(num));//HIJO LEE PIPE
				printf("%s\n",num);
				
				if(num==17){
					read(fd1[0],&suma,sizeof(suma))
				}
			}
			break;
		default: //PADRE 	
			while(num!=17){
				close(fd[0]);
				num=rand()%21;
				suma=suma+num;
				write(fd[1],&num,sizeof(num));//PADRE ESCRIBE
				if(num==17){
					write(fd[1],&suma,sizeof(suma));
				}
			}
			wait(NULL);//Espera a que el hijo acabe
			break;
	}
	return 0;
}