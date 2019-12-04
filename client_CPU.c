#include <stdio.h>
#include <winsock2.h>

int main(void) {	

	//接続するサーバの情報の構造体を用意

	struct sockaddr_in dest;

	memset(&dest, 0, sizeof(dest));

	//サーバの情報を入力

	printf("アドレス：");
	char destination[128];
	scanf("%s", destination);

	//char destination[] = "172.29.15.40";  //アドレス

	printf("ポート番号：");
	char str[128];
	scanf("%s", str);

	dest.sin_port = htons(atoi(str));  //ポート番号

	dest.sin_family = AF_INET;

	dest.sin_addr.s_addr = inet_addr(destination);

	//ソケット通信の準備・生成

	WSADATA data;

	WSAStartup(MAKEWORD(2, 0), &data);

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);



	//サーバへの接続

	if (connect(s, (struct sockaddr *) &dest, sizeof(dest))) {

		printf("%sに接続できませんでした\n", destination);

		return -1;

	}

	printf("%sに接続しました\n", destination);

while(1){
	char buffer[1024];

	//サーバからデータを受信
	

	recv(s, buffer, 1024, 0);

	printf("→ %s\n\n", buffer);

	//char msg[] = "Hello Server!";
	printf("サーバに送信する文字列を入力してください\n");
	char msg[128];
	scanf("%s", msg);

	//サーバにデータを送信

	//send(s, "Hello Server!", strlen(msg), 0);
	send(s, msg, strlen(msg), 0);

}

	// Windows でのソケットの終了

	closesocket(s);

	WSACleanup();

	return 0;

}