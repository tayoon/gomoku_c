//http://blog.livedoor.jp/akf0/archives/51585502.html

#include <stdio.h>

#include <winsock2.h>



int main(void) {	

	//�ڑ�����T�[�o�̏��̍\���̂�p��

	struct sockaddr_in dest;

	memset(&dest, 0, sizeof(dest));

	//�T�[�o�̏������

	char destination[] = "127.0.0.1";  //�A�h���X

	dest.sin_port = htons(12345);  //�|�[�g�ԍ�

	dest.sin_family = AF_INET;

	dest.sin_addr.s_addr = inet_addr(destination);



	//�\�P�b�g�ʐM�̏����E����

	WSADATA data;

	WSAStartup(MAKEWORD(2, 0), &data);

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);



	//�T�[�o�ւ̐ڑ�

	if (connect(s, (struct sockaddr *) &dest, sizeof(dest))) {

		printf("%s�ɐڑ��ł��܂���ł���\n", destination);

		return -1;

	}

	printf("%s�ɐڑ����܂���\n", destination);


	char msg[] = "Hello Server!";
	char buffer[1024];



	//�T�[�o�Ƀf�[�^�𑗐M

	send(s, "Hello Server!", strlen(msg), 0);



	//�T�[�o����f�[�^����M

	recv(s, buffer, 1024, 0);

	printf("�� %s\n\n", buffer);



	// Windows �ł̃\�P�b�g�̏I��

	closesocket(s);

	WSACleanup();



	return 0;

}