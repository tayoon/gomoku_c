#include <stdio.h>

#include <winsock2.h>



int main(void){

  //�ڑ���������N���C�A���g�[���̏��̍\���̂�p��

  struct sockaddr_in source;

  memset(&source, 0, sizeof(source));


 //�ڑ��̑҂����̐ݒ�

  source.sin_family = AF_INET;

  source.sin_port = htons(12345);

  source.sin_addr.s_addr = htonl(INADDR_ANY);



  //�\�P�b�g�ʐM�̎�t�҂�����

  WSADATA data;

  int result = WSAStartup(MAKEWORD(2, 0), &data);

  if (result < 0){

    printf("%d\n", GetLastError());

    printf("�\�P�b�g�ʐM�����G���[\n");

  }



  //�\�P�b�g�̐���

  SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (s < 0){

    printf("%d\n", GetLastError());

    printf("�\�P�b�g�����G���[\n");

  }



  //�\�P�b�g�̃o�C���h

  result = bind(s, (struct sockaddr *)&source, sizeof(source));

  if (result < 0){

    printf("%d\n", GetLastError());

    printf("�o�C���h�G���[\n");

  }



  //�\�P�b�g�ʐM�̎�t�҂��J�n

  result = listen(s, 1);

  if (result < 0){

    printf("�ڑ����G���[\n");

  }



  printf("�ڑ��J�n\n");



  //�N���C�A���g����ʐM������܂őҋ@

  SOCKET s1 = accept(s, NULL, NULL);

  if (s1 < 0){

    printf("�ҋ@�G���[\n");

  }



  //�N���C�A���g���瑗�M���ꂽ�f�[�^�̎�M

  char buffer[1024];  //��M�f�[�^�̃o�b�t�@�̈�

  memset(&buffer, '\0', sizeof(buffer));


  result = recv(s1, buffer, sizeof(buffer), 0);

  if (result < 0){

    printf("��M�G���[\n");

  }

  printf("%s����M���܂���", buffer);



  //�N���C�A���g�փf�[�^�𑗐M����

  char ans[] = "���M����";

  result = send(s1, ans, 10, 0);



  printf("�ڑ��I��\n");

  closesocket(s1);



  //�\�P�b�g�ʐM�̏I��

  WSACleanup();

  return 0;

}
