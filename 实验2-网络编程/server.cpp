#include <stdio.h> 
#include <Winsock2.h> 
int main() { 
    int count = 0;
	SOCKET socket1; 
	WSADATA wsaData;                //Socket的版本信息  
    if (WSAStartup(MAKEWORD(2,2),&wsaData)) {           //调用Windows Sockets DLL 
          printf("init error\n"); 
          WSACleanup(); 
          return 0; 
    } 
    
    printf("server activited\n"); 
    
	struct sockaddr_in local; 
	struct sockaddr_in from; 
	int fromlen =sizeof(from);                   //客户端地址长度 
	
	local.sin_family=AF_INET; 
	local.sin_port=htons(22222);                //监听端口 
	local.sin_addr.s_addr=INADDR_ANY;          //本机 
	
	socket1=socket(AF_INET,SOCK_DGRAM,0);     //创建套接字
	bind(socket1,(struct sockaddr*)&local,sizeof(local)); 
	while (1) { 
		char buffer[1024]="\0"; 
		printf("waiting for receiving message\n"); 
		if (recvfrom(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&from, &fromlen) != SOCKET_ERROR) {     //参数中sockaddr_in转化sockaddr
			printf("Received datagram from %s : %s\n", inet_ntoa(from.sin_addr), buffer);     //inet_ntoa()将整型地址转化成点分十进制 
			count++;
			printf("You have received %d messgaes.\n\n", count);
			//sendto(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&from, fromlen);         //给cilent发信息 
		} 
	} 
	closesocket(socket1);           //关闭套接字 
	WSACleanup();                  //终止使用Windows Sockets DLL 
	return 0;   
} 
