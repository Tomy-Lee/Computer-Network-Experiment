#include <stdio.h> 
#include<iostream>
#include <string.h>
#include <stdlib.h>
#include <Winsock2.h> 
int main() { 
    char buffer[1024] = "\0";
	SOCKET socket1; 
	WSADATA wsaData;      //Socket的版本信息 
    if (WSAStartup(MAKEWORD(2,2),&wsaData)) {       //调用Windows Sockets DLL 
          printf("init error\n"); 
          WSACleanup(); 
          return 0; 
    } 
    
	struct sockaddr_in server; 
	int len =sizeof(server);       //服务器地址长度 
	
	server.sin_family = AF_INET;        //AF_INET地址族
	server.sin_port = htons(22222);                           ///server的监听端口 
	server.sin_addr.s_addr = inet_addr("192.168.199.208");           ///server的地址 

	socket1 = socket(AF_INET, SOCK_DGRAM, 0);     //创建套接字

	for(int i = 0; i < 1000; i++) { 
        itoa(i, buffer, 10);
		printf(" message %d : %s\n", i, buffer); 
       if (sendto(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, len) != SOCKET_ERROR) {      //参数中sockaddr_in转化sockaddr 
         	//Sleep(10); 
         	//if (recvfrom(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, &len) != SOCKET_ERROR) 
           // printf("rece from server:%s\n",buffer); 
     	} 
     	else {
     		printf("send failed!\n");	
     	}
     } 
    closesocket(socket1);       //关闭套接字 
    WSACleanup();               //终止使用Windows Sockets DLL  
    return 0;
}
