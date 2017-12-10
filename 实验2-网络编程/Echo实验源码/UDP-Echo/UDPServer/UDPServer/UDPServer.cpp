/* UDPServer.cpp */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include "conio.h"
#include<time.h>

#define	BUFLEN		2000                  // ��������С
#define WSVERS		MAKEWORD(2, 2)        // ָ���汾2.2 
#pragma comment(lib,"ws2_32.lib")         // ����winsock 2.2 Llibrary

/*------------------------------------------------------------------------
 * main - TCP client for DAYTIME service
 *------------------------------------------------------------------------
 */
void
main(int argc, char *argv[])
{
	char   *host = "127.0.0.1";	    /* server IP Address to connect */
	char   *service = "50510";  	    /* server port to connect       */
	struct sockaddr_in sin;	        /* an Internet endpoint address	*/
	struct sockaddr_in from;        /* sender address               */
	int    fromsize = sizeof(from);
	char   buf[BUFLEN+1];
	char   buf1[BUFLEN + 1]; /* buffer for one line of text	*/
	SOCKET	sock;		  	        /* socket descriptor	    	*/
	int	cc;			                /* recv character count		    */
	time_t	now;
	char	*pts;
    
	WSADATA wsadata;
    WSAStartup(WSVERS, &wsadata);   /* ����winsock library��WSVERSΪ����汾,wsadata����ϵͳʵ��֧�ֵ���߰汾��    */		
    sock = socket(PF_INET, SOCK_DGRAM,IPPROTO_UDP); // ����UDP�׽���, ������������Э���(family)�����ݱ��׽��֣�UDPЭ��ţ� ���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;                     // ��(����)���еĽӿڡ�
	sin.sin_port = htons((u_short)atoi(service));         // ��ָ���ӿڡ�atoi--��asciiת��Ϊint��htons -- ������(host)ת��Ϊ������(network), Ϊshort���͡� 
	bind(sock, (struct sockaddr *)&sin, sizeof(sin));     // �󶨱��ض˿ںţ��ͱ���IP��ַ)

 	while(!_kbhit()){                                    //����Ƿ��а���
	    cc = recvfrom(sock, buf, BUFLEN, 0, (SOCKADDR *)&from, &fromsize);  //���տͻ����ݡ����ؽ����ccΪ���յ��ַ�����from�н������ͻ�IP��ַ�Ͷ˿ںš�
		
		char *ssss = inet_ntoa(from.sin_addr);
		int st = (from.sin_port);
		char*sst = new char[25];
		itoa(st, sst, 10);
		
		
		if (cc == SOCKET_ERROR){
            printf("recvfrom() failed; %d\n", WSAGetLastError());
            break;
        }
        else if (cc == 0)
            break;
		else{
			buf[cc] = '\0';
			(void)time(&now);                                      // ȡ��ϵͳʱ��
			pts = ctime(&now);
			strcat(pts, ssss);
			strcat(pts, "    ");
			strcat(pts, sst);
			strcat(pts, "    ");			
			strcat(pts, buf);
			memcpy(buf1, pts, strlen(pts));
			buf1[strlen(pts)] = '\0';
			cc = sendto(sock, buf1, 1000, 0, (SOCKADDR *)&from, sizeof(from));
			
			if (cc == SOCKET_ERROR) {
				printf("����ʧ�ܣ�����ţ�%d\n", WSAGetLastError());
			}
			else {
				printf("���ͳɹ��������������...\n");
			}
			printf("%s\n", buf1);
		}
       
	}
 
	closesocket(sock);
	GlobalFree(buf);
	WSACleanup();       	          /* ж��ĳ�汾��DLL */
}



