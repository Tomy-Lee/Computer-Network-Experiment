/* TCPServer.cpp - main */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <time.h>
#include "conio.h"
#include <string.h>

#define	WSVERS	MAKEWORD(2, 0)
#define	BUFLEN		2000 
#pragma comment(lib,"ws2_32.lib")  //ʹ��winsock 2.2 library
/*------------------------------------------------------------------------
 * main - Iterative TCP server for TIME service
 *------------------------------------------------------------------------
 */
void
main(int argc, char *argv[]) 
/* argc: �����в��������� ���磺C:\> TCPServer 8080 
                     argc=2 argv[0]="TCPServer",argv[1]="8080" */
{
	struct	sockaddr_in fsin;	    /* the from address of a client	  */
	SOCKET	msock, ssock;		    /* master & slave sockets	      */
	WSADATA wsadata; 
	char	*service = "50510";
	struct  sockaddr_in sin;	    /* an Internet endpoint address		*/
    int	    alen;			        /* from-address length		        */
	char	*pts;			        /* pointer to time string	        */
	time_t	now;			        /* current time			            */
	int dc;
	char	buf[BUFLEN + 1];
	WSAStartup(WSVERS, &wsadata);						// ����winsock library��WSVERSָ������ʹ�õİ汾��wsadata����ϵͳʵ��֧�ֵ���߰汾
	msock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	// �����׽��֣�������������Э���(family)�����׽��֣�TCPЭ��
	
												// ���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET

	memset(&sin, 0, sizeof(sin));						// ��&sin��ʼ�ĳ���Ϊsizeof(sin)���ڴ���0
	sin.sin_family = AF_INET;							// ��������ַ��(INET-Internet)
	sin.sin_addr.s_addr = INADDR_ANY;					// ��������(�ӿڵ�)IP��ַ��
	sin.sin_port = htons((u_short)atoi(service));		// �����Ķ˿ںš�atoi--��asciiת��Ϊint��htons--������������(host to network��s-short 16λ)
	bind(msock, (struct sockaddr *)&sin, sizeof(sin));  // �󶨼�����IP��ַ�Ͷ˿ں�

	 listen(msock, 5);                                  // ��������Ϊ5������������У����ѵ������������������еȴ�����

    while(!_kbhit()){ 		                                   // ����Ƿ��а���,���û�������ѭ����ִ��
		alen = sizeof(struct sockaddr);                         // ȡ����ַ�ṹ�ĳ���
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen); // ����������������������������������������󲢽������ӣ����ظ����ӵ��׽��֣����򣬱���䱻����ֱ�����зǿա�fsin�����ͻ���IP��ַ�Ͷ˿ں�

		char *ssss = inet_ntoa(fsin.sin_addr);
		int st = (fsin.sin_port);
		char*sst = new char[25];
		itoa(st, sst, 10);

		dc = recv(ssock, buf, BUFLEN, 0);                // �ڶ�������ָ�򻺳���������������Ϊ��������С(�ֽ���)�����ĸ�����һ������Ϊ0������ֵ:(>0)���յ����ֽ���,(=0)�Է��ѹر�,(<0)���ӳ���
		if (dc == SOCKET_ERROR || dc == 0)
			printf("Error: %d.\n", GetLastError());     //����������ر��׽���sock��
		else if (dc > 0) {
			buf[dc] = '\0';	                       // ensure null-termination

		}

		(void)time(&now);                                      // ȡ��ϵͳʱ��
		pts = ctime(&now); // ��ʱ��ת��Ϊ�ַ���
		strcat(pts, ssss);
		strcat(pts, "    ");
		strcat(pts, sst);
		strcat(pts, "    ");
		strcat(pts, buf);

		int cc = send(ssock, pts, strlen(pts), 0);              // �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵΪʵ�ʷ��͵��ֽ����������Է��ر�ʱ����SOCKET_ERROR��
		printf("%s\n", pts);                                      // ��ʾ���͵��ַ���
		
		Sleep(100);
     } (void)closesocket(ssock);
    (void) closesocket(msock);                                 // �رռ����׽���
     WSACleanup();                                             // ж��winsock library

}

