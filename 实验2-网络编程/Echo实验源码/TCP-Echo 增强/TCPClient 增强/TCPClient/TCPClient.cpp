/* TCPClient.cpp */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include "conio.h"

#define	BUFLEN		2000                  // ��������С
#define WSVERS		MAKEWORD(2, 0)        // ָ���汾2.0 
#pragma comment(lib,"ws2_32.lib")         // ʹ��winsock 2.0 Llibrary

/*------------------------------------------------------------------------
 * main - TCP client for TIME service
 *------------------------------------------------------------------------
 */
void
main(int argc, char *argv[])
{
	char	*host = "127.0.1.1";	    /* server IP to connect         */
	char	*service = "50510";  	    /* server port to connect       */
	struct sockaddr_in sin;	            /* an Internet endpoint address	*/
	char	buf[BUFLEN+1];   		    /* buffer for one line of text	*/
	SOCKET	sock;		  	            /* socket descriptor	    	*/
	int	cc;			                    /* recv character count		    */
	
	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata);						  //����winsock library��WSVERSΪ����İ汾��wsadata����ϵͳʵ��֧�ֵ���߰汾
	char	*pts = new char[100];

	
	
		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	  //�����׽��֣�������������Э���(family)�����׽��֣�TCPЭ��


		memset(&sin, 0, sizeof(sin));						  // ��&sin��ʼ�ĳ���Ϊsizeof(sin)���ڴ���0
		sin.sin_family = AF_INET;							  // ��������ַ��
		sin.sin_addr.s_addr = inet_addr(host);                // ���÷�����IP��ַ(32λ)
		sin.sin_port = htons((u_short)atoi(service));         // ���÷������˿ں�  

		int ret = connect(sock, (struct sockaddr *)&sin, sizeof(sin));
    while(pts!="sss")
	{ 
		scanf("%s", pts);
		int dc = send(sock, pts, strlen(pts), 0);              // �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵΪʵ�ʷ��͵��ֽ����������Է��ر�ʱ����SOCKET_ERROR��


		cc = recv(sock, buf, BUFLEN, 0);                // �ڶ�������ָ�򻺳���������������Ϊ��������С(�ֽ���)�����ĸ�����һ������Ϊ0������ֵ:(>0)���յ����ֽ���,(=0)�Է��ѹر�,(<0)���ӳ���
		if (cc == SOCKET_ERROR || cc == 0)
			printf("Error: %d.\n", GetLastError());     //����������ر��׽���sock��
		else if (cc > 0) {
			buf[cc] = '\0';	                       // ensure null-termination
			printf("%s\n", buf);                         // ��ʾ�����յ��ַ���
		}
		  
		Sleep(100);
	 }        closesocket(sock);                  
    WSACleanup();                                  // ж��winsock library
	system("pause");
    printf("���س�������...");
	getchar();										// �ȴ����ⰴ��
}
