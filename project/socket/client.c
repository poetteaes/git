/**************************************
 * socket test
 * client
 * created by CAO Fei
 * date: 2018-04-29
 *************************************/
 
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <unistd.h> 
#include <errno.h> 
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  

#define PORT 28111  /*port*/
#define BUF_LEN 1024

/*

struct sockaddr
{
	sa_family_t sin_family;
	char sa_date[];
	；
	：
}


#include<netinet/in.h>
struct in_addr
{
	in_addr_t s_addr;   //IPV4 addr
}

struct sockaddr_in
{
	sa_family_t sin_family;
	in_port_t sin_port;
	struct in_addr sin_addr;
}


因特网地址结构sockaddr_in需要转化为通用的地址结构sockaddr;
地址和端口需要转换为网络字节序(整数转为网络字节序：htonl htons;   点分十进制文本转为二进制网络字节序：inet_addr inet_pton);

*/


/*client*/
int main(void)
{
	int ret;
	int clientSocket;
	char buf[BUF_LEN]={0};
	
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	
	memset(&serverAddr, 0x00, sizeof(serverAddr));
	memset(&clientAddr, 0x00, sizeof(clientAddr));
	
	/*clientSocket*/
	clientSocket = socket(AF_INET, SOCK_STREAM, 0); /*int socket（int domain , int type , int protocol)*/
	if(clientSocket == -1)
	{
		printf("socket() error: %s\n", strerror(errno));
		return -1;
	}
	printf("socket() success.\n");
	
	
	/*Convert server IP and PORT*/
	serverAddr.sin_family = AF_INET;                           /*ipv4*/
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");       /*in_addr_t inet_addr(const char *ip)*/  
	serverAddr.sin_port = htons(PORT);                         /*uint16_t  htons(uint16_t hostshort)*/
    printf("server ip and port is 127.0.0.1: %d\n", PORT);
	
	/*connect*/
	/* int connect (int sockfd, struct sockaddr *serv_addr, socketlen_t addrlen)*/
	ret = connect(clientSocket, (struct sockaddr *)(&serverAddr), (socklen_t)(sizeof(serverAddr)) );   
	if(ret == -1)
	{
		printf("connect() error: %s\n", strerror(errno));
		return -1;
	}
	printf("connect() success. connected\n");
	
	/*send*/
	printf("Begin to communicate\n");
	while(1)
	{
		memset(buf, 0x00, sizeof(buf));
		printf("client: ");
		fflush(stdin);
		if(fgets(buf, sizeof(buf)-1, stdin) == NULL)
		{
			printf("fgets() encounters an error or EOF\n");
			fflush(stdin);
			break;
		}
		fflush(stdin);
		
		/*size_t send(int sockfd, const void *buf, size_t nbytes, int flags);*/
		
		/*send*/
		ret = send(clientSocket, buf, sizeof(buf)-1, 0);
		if(ret == -1)  
        {  
            printf("send() error: %s\n", strerror(errno));
	    	return -1;
        }
		
		
		if(memcmp(buf, "exit", 4) == 0) 
		{
			/*stop*/
			printf("close connection.\n");
			close(clientSocket);
			break;
		}
		
		/*recv*/
		memset(buf, 0x00, sizeof(buf));
		if(recv(clientSocket, buf, sizeof(buf)-1, 0) <0 )  /*ssize_t recv( int sockfd, void *buf, size_t nbytes,  int flags)*/
		{
			 printf("recv() error: %s\n", strerror(errno));
			 close(clientSocket);
			 break;
		}
		printf("server: %s", buf);
		
		if(memcmp(buf, "exit", 4) == 0 || memcmp(buf, "kill", 4) == 0) 
		{
			/*stop*/
			printf("close connection.\n");
			close(clientSocket);
			break;
		}

	}
	
	
	return 0;
}
