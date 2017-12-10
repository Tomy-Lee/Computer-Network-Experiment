/* UDPClient.cpp */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>

#define	BUFLEN		2000                  // ��������С
#define WSVERS		MAKEWORD(2, 2)        // ָ���汾2.2 
#pragma comment(lib,"ws2_32.lib")         // ����winsock 2.2 Llibrary

void
main(int argc, char *argv[])
{
	char	*host = "127.0.0.1";	    /* server IP to connect         */
	char	*service = "50510";  	    /* server port to connect       */
	struct sockaddr_in toAddr;	        /* an Internet endpoint address	*/
	char	buf[BUFLEN+1];   		        /* buffer for one line of text	*/
	SOCKET	sock;		  	            /* socket descriptor	    	*/
	int	cc;			                    /* recv character count		    */
	char	*pts=new char [100];			        /* pointer to time string	        */
	time_t	now;			        /* current time			            */
	int   toAddrsize = sizeof(toAddr);
	WSADATA wsadata;
    WSAStartup(WSVERS, &wsadata);       /* ����ĳ�汾Socket��DLL        */	

    sock = socket(PF_INET, SOCK_DGRAM,IPPROTO_UDP);

	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons((u_short)atoi(service));    //atoi����asciiת��Ϊint. htons��������(host)ת��Ϊ������(network), s--short
	toAddr.sin_addr.s_addr = inet_addr(host);           //���hostΪ��������Ҫ���ú���gethostbyname������ת��ΪIP��ַ
	

	memset(buf,' ',1000);  //fill 1000 bytes with 'e'
	buf[1000] = '\0';
	scanf("%s", pts);                                      // ��ʱ��ת��Ϊ�ַ���
    memcpy(buf,pts,strlen(pts));

	cc = sendto(sock, buf, 1000, 0,(SOCKADDR *)&toAddr, sizeof(toAddr));
    if (cc == SOCKET_ERROR){
        printf("����ʧ�ܣ�����ţ�%d\n", WSAGetLastError());
     }
	else{
		printf("���ͳɹ��������������...\n");
        cc = recvfrom(sock, buf, BUFLEN, 0, (SOCKADDR *)&toAddr, &toAddrsize);  //���տͻ����ݡ����ؽ����ccΪ���յ��ַ�����from�н������ͻ�IP��ַ�Ͷ˿ںš�
	    if (cc == SOCKET_ERROR) {
		printf("recvfrom() failed; %d\n", WSAGetLastError());
		
	     }
	     else
	     {
			 buf[cc] = '\0';
		     printf("%s\n", buf);
	     }
	}	
	getchar();

	closesocket(sock);

	
	WSACleanup();       	          /* ж��ĳ�汾��DLL */  

	getchar();

}
