/**************************************
 * socket test
 * server
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


/*server*/
int main(void)
{
	int ret;
	int serverSocket;
	int clientSocket;
	int addrLen;
	char buf[BUF_LEN]={0};
	
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	
	memset(&serverAddr, 0x00, sizeof(serverAddr));
	memset(&clientAddr, 0x00, sizeof(clientAddr));
	
	/*serverSocket*/
	serverSocket = socket(AF_INET, SOCK_STREAM, 0); /*int socket（int domain , int type , int protocol)*/
	if(serverSocket == -1)
	{
		printf("socket() error: %s\n", strerror(errno));
		return -1;
	}
	printf("socket() success.\n");
	
	
	/*Convert IP and PORT*/
	serverAddr.sin_family = AF_INET;                  /*ipv4*/
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);   /*uint32_t  htonl(uint32_t hostlong);  INADDR_ANY: 0.0.0.0*/  
	serverAddr.sin_port = htons(PORT);                /*uint16_t  htons(uint16_t hostshort)*/

	/*bind*/
	/*int bind (int sockfd , struct sockaddr *my_addr , socketlen_t addrlen)*/
	ret = bind(serverSocket, (struct sockaddr *)(&serverAddr), (socklen_t)(sizeof(serverAddr)) );   
	if(ret == -1)
	{
		printf("bind() error: %s\n", strerror(errno));
		return -1;
	}
	printf("server bind port:[%d]\n", PORT);
	
	/*listen*/
	ret = listen(serverSocket, 128); /*int listen(int sockfd, int backlog) */
	if(ret == -1)  
    {  
        printf("listen() error: %s\n", strerror(errno));
		return -1;
    } 
	
	/*accept and recv*/
	printf("Begin to accept\n");
	while(1)
	{
		/*accept*/
		/*int accept(int sockfd, void *addr, socketlen_t *addrlen); here addr is clientAddr*/
		/*如果不关心客户端标识，可以bind(sockfd, NULL, 0)来调用；
	      否则my_addr是客户地址指针，而*addrlen要设置成一个能够存储地址长度的缓冲区长度，my_addr存储长度不超过*addrlen的地址数据 
	      如果实际长度不足，会被改更改长度
	    */
		memset(&clientAddr, 0x00, sizeof(clientAddr));
		addrLen = sizeof(clientAddr);
		clientSocket = accept(serverSocket, (struct sockaddr *)(&clientAddr), (socklen_t*)(&addrLen));
		if(clientSocket == -1)  
        {  
            printf("accept() error: %s\n", strerror(errno));
	    	return -1;
        }
		printf("Connected. client ip[%s]:port[%d]\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        printf("Begin to communicate\n");
		
		while(1)
		{
			/*recv*/
			memset(buf, 0x00, sizeof(buf));
			if(recv(clientSocket, buf, sizeof(buf)-1, 0) <0 )  /*ssize_t recv( int sockfd, void *buf, size_t nbytes,  int flags)*/
			{
				 printf("recv() error: %s\n", strerror(errno));
				 close(clientSocket);
				 break;
			}
			printf("client: %s", buf);
			
			if(memcmp(buf, "exit", 4) == 0) 
			{
				 close(clientSocket);
				 printf("close clientSocket\n");
				 break;
			}
			
			/*send*/
			fflush(stdin);
			memset(buf, 0x00, sizeof(buf));
			printf("server: ");
		    if(fgets(buf, sizeof(buf)-1, stdin) == NULL)
		    {
		    	printf("fgets() encounters an error or EOF\n");
				close(clientSocket);
		    	fflush(stdin);
		    	break;
		    }
		    fflush(stdin);
			
			send(clientSocket, buf, sizeof(buf)-1, 0);    
			if(memcmp(buf, "exit", 4) == 0 || memcmp(buf, "kill", 4)==0) 
			{
				 close(clientSocket);
				 printf("close clientSocket\n");
				 break;
			}
			
             
		}
		
		if(memcmp(buf, "kill", 4) == 0) 
		{
			 close(serverSocket);
			 printf("close serverSocket\n");
			 break;
		}
		
		
	}
	
	
	return 0;
}
