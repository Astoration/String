#include "split.h"

using namespace std;
char** split(const char* string, const char datum){
	queue<char*> stringList;
	//���ܵ� ���ڿ� �����͸� ���� Queue ����Ʈ ����
	int splitCount = 0;
	//���� ���� ī��Ʈ��
	char* tokenPointer = (char*)malloc(strlen(string) + 1);
	strcpy(tokenPointer, string);
	//���� ���ڿ��� ��ȣ�� ���� �ӽ� ���� ����
	//���� ���ڿ��� ���ó���Ǿ� �ֱ� ������ ������ ����, ���� �Ұ�
	char *originalString = (char*)malloc(strlen(string) + 1);
	strcpy(originalString, string);
	//���� ���� ���ڿ��� ���
	tokenPointer = strtok(tokenPointer, &datum);
	while (tokenPointer){
		stringList.push(tokenPointer);
		tokenPointer = strtok(NULL, &datum);
		splitCount += 1;
	}
	//���й��ڸ� �ι��ڷ� ġȯ�� ���ܰ��� ī����
	if (strcmp(originalString, stringList.front()) == 0) return &originalString;
	//���� ���� �ʾ����� �������� ��ȯ
	char** splitedString = (char**)malloc(sizeof(char*)*splitCount);
	for (int i = 0; i < splitCount; i++){
		splitedString[i] = stringList.front();
		stringList.pop();
	}
	//���� ����Ʈ�� ��ȯ�� 2���� �迭ȭ
	free(originalString);
	return splitedString;
	//���� ���� ��ȯ

}
char** split(const char* string, const char* datum){
	queue<char*> stringList;
	//���ܵ� ���ڿ� �����͸� ���� Queue ����Ʈ ����
	unsigned int splitCount = 0;
	//���� ���� ī��Ʈ��
	size_t indexRange;
	//�ڸ� ���� ���� ī��Ʈ��
	char* standardString = (char*)malloc(sizeof(string));
	strcpy(standardString, string);
	//���� ���� ��ȣ�� ���� �ӽ� ���� ����
	while (true)
	{ //��� ���ڸ� �����Ҷ� ���� ����
		indexRange = 0;
		while (standardString[indexRange] == '\0' ? ((splitCount == 0) ? (indexRange = 0) : false) : true){
			//���ڿ��� ���� �ٴٸ��� ���� ����, ���� ���� �ʾ����� �����ؾ��� ���ڿ��� ���̸� 0���� ����
			if (strncmp(&standardString[indexRange], datum, strlen(datum)) == 0)
				// ���й��ڸ� ã���� �����ؾ��� ���ڿ��� ���̸� �����ä ���� Ż��
				break;
			indexRange += 1;
		}
		if (indexRange == 0)
			break;
		//�����ؾ��� ���ڰ� ������ Ż��
		char* movableString = (char*)malloc(indexRange + 1);
		strncpy(movableString, standardString, indexRange);
		//�� ���ڿ� �Ҵ��� �����Ҹ�ŭ ����
		movableString[indexRange + 1] = '\0';
		stringList.push(movableString);
		//����Ʈ�� �� ���ڿ� �߰�
		splitCount += 1;
		//���� Ƚ�� ī����
		if (standardString[indexRange] == '\0')
			break;
		//���������� ������ �����̸� Ż��
		for (unsigned int count = 0; standardString[count + indexRange] != '\0'; count++)
			standardString[count] = standardString[(count + 1) + indexRange];
		//������ ��ŭ ���ڿ��� ����
	}
	if (splitCount != 0){
		//�߸� Ƚ�� �˻�
		char** splitedString = (char**)malloc(sizeof(char*)*splitCount);
		for (int i = 0; i < splitCount; i++){
			splitedString[i] = stringList.front();
			stringList.pop();
		}
		//��ȯ�� ���ڿ� ����Ʈ ����
		return splitedString;
		//���ڿ� ����Ʈ ��ȯ
	}
	else{
		return &standardString;
		//���ڿ��� �߸��� �ʾ����� �������� ��ȯ
	}
}