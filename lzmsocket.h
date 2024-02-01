#include <WinSock2.h>

SOCKET init() {
	WSADATA wsaData = { 0 };
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return SOCKET_ERROR;
	}
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == SOCKET_ERROR) {
		return SOCKET_ERROR;
	}
	return s;
}
bool init_server(SOCKET s, int port) {
	SOCKADDR_IN serv_addr = { 0 };
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(s, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
		return false;
	}
	if (listen(s, 5) == SOCKET_ERROR) {
		return false;
	}
	return true;
}
bool connect_server(SOCKET s, char addr[], int port){
	SOCKADDR_IN serv_addr = { 0 };
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.S_un.S_addr = inet_addr(addr);
	if (connect(s, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == INVALID_SOCKET) {
		return false;
	}
	return true;
}
SOCKET getclient(SOCKET s,SOCKADDR_IN *client_addr) {
	SOCKET client;
	int len = sizeof(SOCKADDR);
	client = accept(s, (SOCKADDR*)client_addr, &len);
	if (client == INVALID_SOCKET) {
		return SOCKET_ERROR;
	}
	return client;
}
int getlasterror() {
	return WSAGetLastError();
}
bool sendmsg(SOCKET s, char buf[], int size) {
	if (send(s, buf, size, 0) == SOCKET_ERROR) {
		return false;
	}
	return true;
}
bool getmsg(SOCKET s, char buf[], int size) {
	if (recv(s, buf, size, 0) == SOCKET_ERROR) {
		return false;
	}
	return true;
}
char* getip(SOCKADDR_IN addr) {
	return inet_ntoa(addr.sin_addr);
}
bool cleansocket(){
	return !WSACleanup();
}