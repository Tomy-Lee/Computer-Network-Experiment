/* TCPClient.cpp */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include "conio.h"

#define	BUFLEN		2000                  // 缓冲区大小
#define WSVERS		MAKEWORD(2, 0)        // 指明版本2.0 
#pragma comment(lib,"ws2_32.lib")         // 使用winsock 2.0 Llibrary

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
	WSAStartup(WSVERS, &wsadata);						  //加载winsock library。WSVERS为请求的版本，wsadata返回系统实际支持的最高版本
	char	*pts = new char[100];

	
	
		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	  //创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议


		memset(&sin, 0, sizeof(sin));						  // 从&sin开始的长度为sizeof(sin)的内存清0
		sin.sin_family = AF_INET;							  // 因特网地址簇
		sin.sin_addr.s_addr = inet_addr(host);                // 设置服务器IP地址(32位)
		sin.sin_port = htons((u_short)atoi(service));         // 设置服务器端口号  

		int ret = connect(sock, (struct sockaddr *)&sin, sizeof(sin));
    while(pts!="sss")
	{ 
		scanf("%s", pts);
		int dc = send(sock, pts, strlen(pts), 0);              // 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值为实际发送的字节数，出错或对方关闭时返回SOCKET_ERROR。


		cc = recv(sock, buf, BUFLEN, 0);                // 第二个参数指向缓冲区，第三个参数为缓冲区大小(字节数)，第四个参数一般设置为0，返回值:(>0)接收到的字节数,(=0)对方已关闭,(<0)连接出错
		if (cc == SOCKET_ERROR || cc == 0)
			printf("Error: %d.\n", GetLastError());     //出错。其后必须关闭套接字sock。
		else if (cc > 0) {
			buf[cc] = '\0';	                       // ensure null-termination
			printf("%s\n", buf);                         // 显示所接收的字符串
		}
		  
		Sleep(100);
	 }        closesocket(sock);                  
    WSACleanup();                                  // 卸载winsock library
	system("pause");
    printf("按回车键继续...");
	getchar();										// 等待任意按键
}
