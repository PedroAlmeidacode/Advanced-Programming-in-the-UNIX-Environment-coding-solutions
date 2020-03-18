
#include "/home/pedro/Desktop/auxilios/apue.h"



int my_dup(int oldfd, int newfd){

	int n = newfd; // guarda posicao do novo ddescritor desejada 

	/*se um dos dois argumentos 
	contem uma posição inváida*/
	if(oldfd < 0 || newfd < 0 ){
		perror("calling dup2");
		return -1;
	}

	/*se a posicao desejada a duplicar o 
	descritor contem a mesma posicao do antigo*/
	if(oldfd == newfd) return newfd;

	/*se a posicaoa a colorcar o novo descritor 
	ja tiver um inserido*/
	if(fcntl(newfd, F_GETFD) != -1 || errno != EBADF) close(newfd);

	int fd = dup(oldfd);
	int previous[20];
	int i=0;

	while(fd!= n)
	{
	previous[i] = fd; // coloca em previous a posicao onde criou o descritor 
	fd = dup(oldfd); // cria o descritor novamente sendo que ja nao pode colocar em previous pois esta ocupado 
	i++;
	}

	//faz close aos descritores utilizados erradamente que estavam livres de incio
	for(int j =0; j < i; j++){
		close(previous[j]);
	}

	return newfd;	

}
