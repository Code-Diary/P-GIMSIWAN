#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

bool compare(int a, int b) {
	return a > b;
}
int main() {

	int N, K;
	char * inputStr;
	int digit[28]; //숫자 하나씩 저장
	int *number;

	scanf("%d %d", &N, &K);

	inputStr = (char*)malloc(sizeof(char)* (N+1));
	number = (int*)malloc(sizeof(int)* N);
	memset(number, 0, sizeof(int)* N);
	scanf("%s", inputStr); //문자열 입력 받음
	
	for (int i = 0; i < N; i++) {
		char tempt = inputStr[i];
		digit[i] = (int)strtol(&tempt, NULL, 16);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= N / 4; j++) {
			number[i] += pow(16, (N / 4) - j) * digit[(i + j - 1) % N];
		}
	}

	sort(number, number + N,compare);
	
	if (K == 1) {
		printf("#%d\n", number[0]);
	}
	else {
		int j = 1;

		for (int i = 1; i < N; i++)
		{
			if (number[i] != number[i - 1]) {
				j++;
				if (j == K) {
					printf("#%d\n", number[i]);
					break;
				}
			}
		}
	}
	
	free(inputStr);
	free(number);

	return 0;
}