#include "myfile.h"
SOCKET Connection;

void ClientHandler() {
	char msg[256];
	while (true) {
		recv(Connection, msg, sizeof(msg), NULL);
		cout << msg << endl;
	}
	WSACleanup();
	closesocket(Connection);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Ошибка " << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "Ошибка!Соединение с сервером было потеряно.\n";
		return 1;
	}
	cout << "Подключение выполнено!\n";

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	char msg1[256];
	while (true) {
		cin.getline(msg1, sizeof(msg1));
		send(Connection, msg1, sizeof(msg1), NULL);
		Sleep(10);
	}
	
	return 0;
}