#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma comment(lib,"libmysql.lib")
#include <mysql.h>

#include"global.h"
#include"server.h"
#include"tcp.h"
#include"cmd.h"
#include"ui.h"
#include"user.h"

HANDLE heartbeat_tid;

static DWORD WINAPI heartbeat_th(LPVOID arg){
	while(1){
		Sleep(1000);
		uiheartbeat();
		userheartbeat();
	}
}
int mysql_test(void)
{
	//connection params
	//FILE *file;
	char *host = "127.0.0.1";
	char *user = "root";
	char *pass = "123456";
	char *db = "host";
	int res;
	//sock
	MYSQL sock;
	MYSQL_RES *results;
	MYSQL_ROW record;
	mysql_init(&sock);

	//connection
	if (mysql_real_connect(&sock, host, user, pass, db, 0, NULL, 0)){
		printf("connection ok!");
		
		res=mysql_query(&sock,"insert into hostview values(50,'ggjhg',6,'dsdd','dsadd','dasdh',123,'dsadf',12,23,'dadd',123);");
		if(!res){
			printf("succs");
		} else{
			printf("insert fail\n");
		}

	} else {
		printf("connection fail: ");
	}

	printf("succeed");


	mysql_close(&sock);

	return EXIT_SUCCESS;

}
int main(int argc, char *argv[])
{
	char * msg;
	port = 6000;
	if(argc > 1) port = atoi(argv[1]);
	mysql_test();
	uiinit();
	userinit();

	server_bind(port, 20, do_ui, NULL);
	tcp_server_bind(2012, 20, do_cmd_tcp, NULL);

	heartbeat_tid=CreateThread(NULL, 0, heartbeat_th, NULL, 0, NULL);

	do_cmd_stdin();

	return 0;
}
