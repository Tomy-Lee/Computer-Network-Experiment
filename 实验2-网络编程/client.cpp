#include <stdio.h> 
#include<iostream>
#include <string.h>
#include <stdlib.h>
#include <Winsock2.h> 
int main() { 
    char buffer[1024] = "\0";
	SOCKET socket1; 
	WSADATA wsaData;      //Socket�İ汾��Ϣ 
    if (WSAStartup(MAKEWORD(2,2),&wsaData)) {       //����Windows Sockets DLL 
          printf("init error\n"); 
          WSACleanup(); 
          return 0; 
    } 
    
	struct sockaddr_in server; 
	int len =sizeof(server);       //��������ַ���� 
	
	server.sin_family = AF_INET;        //AF_INET��ַ��
	server.sin_port = htons(22222);                           ///server�ļ����˿� 
	server.sin_addr.s_addr = inet_addr("192.168.199.208");           ///server�ĵ�ַ 

	socket1 = socket(AF_INET, SOCK_DGRAM, 0);     //�����׽���

	for(int i = 0; i < 1000; i++) { 
        itoa(i, buffer, 10);
		printf(" message %d : %s\n", i, buffer); 
       if (sendto(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, len) != SOCKET_ERROR) {      //������sockaddr_inת��sockaddr 
         	//Sleep(10); 
         	//if (recvfrom(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, &len) != SOCKET_ERROR) 
           // printf("rece from server:%s\n",buffer); 
     	} 
     	else {
     		printf("send failed!\n");	
     	}
     } 
    closesocket(socket1);       //�ر��׽��� 
    WSACleanup();               //��ֹʹ��Windows Sockets DLL  
    return 0;
}
