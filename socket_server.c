#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 9999

main()
{
	struct sockaddr_in sockin;

	int socketfd=socket(AF_INET,SOCK_STREAM,0);
	sockin.sin_family=AF_INET;
	sockin.sin_port=htons(PORT);
	sockin.sin_addr.s_addr=htonl(INADDR_ANY);
	printf("%d\n",sizeof(sockin));
	int bindsuccess=bind(socketfd,(struct sockaddr *) &sockin,sizeof(sockin));
	if(bindsuccess)
		{
			printf("Port binding failed on addr %s and port %s",sockin.sin_addr.s_addr,sockin.sin_port);
			exit(1);
		}
	int listensuccess=listen(socketfd,128);
	if(listensuccess)
		{
			printf("Port binding failed on addr %s and port %s",sockin.sin_addr.s_addr,sockin.sin_port);
			exit(1);
		}
		struct sockaddr_in client_addr;
		int client_addr_len=0;
	int socket_tun=accept(socketfd,(struct sockaddr *) &client_addr, &client_addr_len);
	if(socket_tun==-1)
	{
		printf("error accepting connection\n");
	}
	char c[]="hello from server";
	char *buf=(char *)calloc(1000,sizeof(char));
	strcpy(buf,c);
	printf("client connected with ip address: %s\n",inet_ntoa(client_addr.sin_addr));
	//read(socket_tun,buf,1000);
	int n;
	while(1)
	{
	while((n=recv(socket_tun,buf,1000,0))>0)
	{
		printf("received %s\n",buf);
	send(socket_tun,buf,strlen(buf),0);

	send(socket_tun,&c,strlen(c),0);
	}
	}
	close(socketfd);
}
