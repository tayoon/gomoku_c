#include <stdio.h>

#include <winsock2.h>



int main(void){

  //接続を許可するクライアント端末の情報の構造体を用意

  struct sockaddr_in source;

  memset(&source, 0, sizeof(source));


 //接続の待ち方の設定

  source.sin_family = AF_INET;

  source.sin_port = htons(12345);

  source.sin_addr.s_addr = htonl(INADDR_ANY);



  //ソケット通信の受付待ち準備

  WSADATA data;

  int result = WSAStartup(MAKEWORD(2, 0), &data);

  if (result < 0){

    printf("%d\n", GetLastError());

    printf("ソケット通信準備エラー\n");

  }



  //ソケットの生成

  SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (s < 0){

    printf("%d\n", GetLastError());

    printf("ソケット生成エラー\n");

  }



  //ソケットのバインド

  result = bind(s, (struct sockaddr *)&source, sizeof(source));

  if (result < 0){

    printf("%d\n", GetLastError());

    printf("バインドエラー\n");

  }



  //ソケット通信の受付待ち開始

  result = listen(s, 1);

  if (result < 0){

    printf("接続許可エラー\n");

  }



  printf("接続開始\n");



  //クライアントから通信があるまで待機

  SOCKET s1 = accept(s, NULL, NULL);

  if (s1 < 0){

    printf("待機エラー\n");

  }



  //クライアントから送信されたデータの受信

  char buffer[1024];  //受信データのバッファ領域

  memset(&buffer, '\0', sizeof(buffer));


  result = recv(s1, buffer, sizeof(buffer), 0);

  if (result < 0){

    printf("受信エラー\n");

  }

  printf("%sを受信しました", buffer);



  //クライアントへデータを送信する

  char ans[] = "送信成功";

  result = send(s1, ans, 10, 0);



  printf("接続終了\n");

  closesocket(s1);



  //ソケット通信の終了

  WSACleanup();

  return 0;

}
