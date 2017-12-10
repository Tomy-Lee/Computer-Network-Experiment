/* UDPClient.cpp */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>

#define	BUFLEN		2000                  // 缓冲区大小
#define WSVERS		MAKEWORD(2, 2)        // 指明版本2.2 
#pragma comment(lib,"ws2_32.lib")         // 加载winsock 2.2 Llibrary

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
    WSAStartup(WSVERS, &wsadata);       /* 启动某版本Socket的DLL        */	

    sock = socket(PF_INET, SOCK_DGRAM,IPPROTO_UDP);

	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons((u_short)atoi(service));    //atoi：把ascii转化为int. htons：主机序(host)转化为网络序(network), s--short
	toAddr.sin_addr.s_addr = inet_addr(host);           //如果host为域名，需要先用函数gethostbyname把域名转化为IP地址
	

	memset(buf,' ',1000);  //fill 1000 bytes with 'e'
	buf[1000] = '\0';
	scanf("%s", pts);                                      // 把时间转换为字符串
    memcpy(buf,pts,strlen(pts));

	cc = sendto(sock, buf, 1000, 0,(SOCKADDR *)&toAddr, sizeof(toAddr));
    if (cc == SOCKET_ERROR){
        printf("发送失败，错误号：%d\n", WSAGetLastError());
     }
	else{
		printf("发送成功，按任意键继续...\n");
        cc = recvfrom(sock, buf, BUFLEN, 0, (SOCKADDR *)&toAddr, &toAddrsize);  //接收客户数据。返回结果：cc为接收的字符数，from中将包含客户IP地址和端口号。
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

	
	WSACleanup();       	          /* 卸载某版本的DLL */  

	getchar();

}
