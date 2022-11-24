#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(void){
	int fd[2];
	int fd1[2];
	pid_t pid;
	char holaHijo[]="Hola hijo,soy tu padre. \0";
	char holaPadre[]="Hola papi, soy tu hijo. \0";
	char buffer[25];
	
	pipe(fd);
	pipe(fd1);
	pid=fork();
	
	switch(pid){
		case -1: //ERROR
			printf("NO SE HA PODIDO CREAR HIJO...");
			exit(-1);
		case 0: //HIJO 
			for(int i=0;i<3;i++){
				close(fd[1]);//cierra el descriptor de entrada
				read(fd[0],buffer,sizeof(buffer));//HIJO LEE PIPE
				printf("%s\n");
				write(fd1[1],holaPadre,strlen(holaPadre));//HIJO ESCRIBE
			}
			break;
		default: //PADRE 	
			for(int i=0;i<3;i++){
				close(fd[0]);
				write(fd[1],holaHijo,strlen(holaHijo));//PADRE ESCRIBE
			}
			wait(NULL);//Espera a que el hijo acabe
			for(int i=0;i<3;i++){
				read(fd1[0],buffer,sizeof(buffer));//PADRE LEE PIPE
				printf("%s\n");				
			}
			break;
	}
	return 0;
}