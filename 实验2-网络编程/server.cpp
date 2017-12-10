#include <stdio.h> 
#include <Winsock2.h> 
int main() { 
    int count = 0;
	SOCKET socket1; 
	WSADATA wsaData;                //Socket�İ汾��Ϣ  
    if (WSAStartup(MAKEWORD(2,2),&wsaData)) {           //����Windows Sockets DLL 
          printf("init error\n"); 
          WSACleanup(); 
          return 0; 
    } 
    
    printf("server activited\n"); 
    
	struct sockaddr_in local; 
	struct sockaddr_in from; 
	int fromlen =sizeof(from);                   //�ͻ��˵�ַ���� 
	
	local.sin_family=AF_INET; 
	local.sin_port=htons(22222);                //�����˿� 
	local.sin_addr.s_addr=INADDR_ANY;          //���� 
	
	socket1=socket(AF_INET,SOCK_DGRAM,0);     //�����׽���
	bind(socket1,(struct sockaddr*)&local,sizeof(local)); 
	while (1) { 
		char buffer[1024]="\0"; 
		printf("waiting for receiving message\n"); 
		if (recvfrom(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&from, &fromlen) != SOCKET_ERROR) {     //������sockaddr_inת��sockaddr
			printf("Received datagram from %s : %s\n", inet_ntoa(from.sin_addr), buffer);     //inet_ntoa()�����͵�ַת���ɵ��ʮ���� 
			count++;
			printf("You have received %d messgaes.\n\n", count);
			//sendto(socket1, buffer, sizeof(buffer), 0, (struct sockaddr*)&from, fromlen);         //��cilent����Ϣ 
		} 
	} 
	closesocket(socket1);           //�ر��׽��� 
	WSACleanup();                  //��ֹʹ��Windows Sockets DLL 
	return 0;   
} 
