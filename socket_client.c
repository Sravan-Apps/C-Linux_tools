#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

void resetbuf(char *buf,int len)
{
	while(len)
		buf[--len]='\0';
}

void print_help()
{
	printf("Usage: socket_client <ip> <port>\n");
}

main(int argc,char *argv[])
{
	if(argc!=3)
	{
		print_help();
		exit(1);
	}

	int port=atoi(argv[2]);

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	struct in_addr serverip;
	int  convertsuccess=inet_pton(AF_INET,argv[1],&serverip);
	if(!convertsuccess)
	{
		printf("Error convertig server ip to nethost format %s\n",argv[1]);
		exit(2);
	}

	server_addr.sin_addr=serverip;
	//printf("Server address is %s",server_addr.sin_addr.s_addr);
	int connectfail=connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	char client_hello[]="hello from client\n";
	char *buf=(char *) calloc(1000,sizeof(char));
	int n;

	if(!connectfail)
		{
			send(sockfd,client_hello,strlen(client_hello),0);
			while((n=recv(sockfd,buf,1000,0))>0)
			{
				printf("%s",buf);
				resetbuf(buf,1000);
				read(1,buf,1000);
				send(sockfd,buf,strlen(buf),0);
				resetbuf(buf,1000);
			}

		}

		else
		{
			printf("Connect failed.\n");
			exit(3);
		}



}
