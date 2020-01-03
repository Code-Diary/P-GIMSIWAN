#include <stdio.h>
#include <vector>

using namespace std;
int start[4] = { 0 }; //0 1 2 3 4 5 6 7

void rotation(int num, int dir) {
	if (start[num] + dir == -1) start[num] = 7;
	else start[num] = (start[num] + dir) % 8;
}
int main(void) {

	int K, score = 0;
	vector<vector<int>> magnet;
	magnet.assign(4, vector<int>(8));

	scanf("%d", &K);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++)
			scanf("%d", &magnet[i][j]);
	}

	for (int i = 0; i < K; i++) {
		int num, dir;
		bool rotate[4] = { false };

		scanf("%d %d", &num, &dir);

		for (int j = num - 1; j > 0; j--) {
			if (magnet[j][(start[j] + 6) % 8] == magnet[j - 1][(start[j - 1] + 2) % 8]) break;
			rotate[j - 1] = true;
		}
		for (int j = num - 1; j < 3; j++) {
			if (magnet[j][(start[j] + 2) % 8] == magnet[j + 1][(start[j + 1] + 6) % 8]) break;
			rotate[j + 1] = true;
		}
		rotate[num - 1] = true;

		for (int j = 0; j < 4; j++) {
			if (rotate[j]) rotation(j, pow(-1, abs(num - j)) * dir);
		}
	}
	for (int i = 0; i < 4; i++) {
		score += magnet[i][start[i]] * pow(2, i);
	}


	printf("%d\n", score);

	return 0;
}