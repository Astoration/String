#include "split.h"

using namespace std;
char** split(const char* string, const char datum){
	queue<char*> stringList;
	//절단된 문자열 포인터를 담을 Queue 리스트 생성
	int splitCount = 0;
	//문자 절단 카운트기
	char* tokenPointer = (char*)malloc(strlen(string) + 1);
	strcpy(tokenPointer, string);
	//원본 문자열의 보호를 위해 임시 문자 생성
	//원본 문자열은 상수처리되어 있기 때문에 안정성 보장, 접근 불가
	char *originalString = (char*)malloc(strlen(string) + 1);
	strcpy(originalString, string);
	//절단 전의 문자열을 기록
	tokenPointer = strtok(tokenPointer, &datum);
	while (tokenPointer){
		stringList.push(tokenPointer);
		tokenPointer = strtok(NULL, &datum);
		splitCount += 1;
	}
	//구분문자를 널문자로 치환후 절단갯수 카운팅
	if (strcmp(originalString, stringList.front()) == 0) return &originalString;
	//절단 되지 않았으면 원본문자 반환
	char** splitedString = (char**)malloc(sizeof(char*)*splitCount);
	for (int i = 0; i < splitCount; i++){
		splitedString[i] = stringList.front();
		stringList.pop();
	}
	//쌓인 리스트를 반환할 2차원 배열화
	free(originalString);
	return splitedString;
	//절단 문자 반환

}
char** split(const char* string, const char* datum){
	queue<char*> stringList;
	//절단된 문자열 포인터를 담을 Queue 리스트 생성
	unsigned int splitCount = 0;
	//문자 절단 카운트기
	size_t indexRange;
	//자를 문자 길이 카운트기
	char* standardString = (char*)malloc(sizeof(string));
	strcpy(standardString, string);
	//원본 문자 보호를 위해 임시 문자 생성
	while (true)
	{ //모든 문자를 절단할때 까지 루프
		indexRange = 0;
		while (standardString[indexRange] == '\0' ? ((splitCount == 0) ? (indexRange = 0) : false) : true){
			//문자열의 끝에 다다를때 까지 루프, 절단 되지 않았으면 절단해야할 문자열의 길이를 0으로 지정
			if (strncmp(&standardString[indexRange], datum, strlen(datum)) == 0)
				// 구분문자를 찾으면 절단해야할 문자열의 길이를 기억한채 루프 탈출
				break;
			indexRange += 1;
		}
		if (indexRange == 0)
			break;
		//절단해야할 문자가 없으면 탈출
		char* movableString = (char*)malloc(indexRange + 1);
		strncpy(movableString, standardString, indexRange);
		//새 문자열 할당후 절단할만큼 복사
		movableString[indexRange + 1] = '\0';
		stringList.push(movableString);
		//리스트에 새 문자열 추가
		splitCount += 1;
		//절단 횟수 카운팅
		if (standardString[indexRange] == '\0')
			break;
		//마지막으로 절단한 문자이면 탈출
		for (unsigned int count = 0; standardString[count + indexRange] != '\0'; count++)
			standardString[count] = standardString[(count + 1) + indexRange];
		//절단한 만큼 문자열을 당긴다
	}
	if (splitCount != 0){
		//잘린 횟수 검사
		char** splitedString = (char**)malloc(sizeof(char*)*splitCount);
		for (int i = 0; i < splitCount; i++){
			splitedString[i] = stringList.front();
			stringList.pop();
		}
		//반환할 문자열 리스트 생성
		return splitedString;
		//문자열 리스트 반환
	}
	else{
		return &standardString;
		//문자열이 잘리지 않았으면 원본문자 반환
	}
}