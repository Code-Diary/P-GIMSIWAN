#include <stdio.h>
#include <vector>

using namespace std;

int dir[5][2] = { {0, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, 0} };//X 상 우 하 좌

typedef struct {
	int x;
	int y;
	int c;
	int p;
}BC;

bool check(BC AP, pair<int, int> user) {
	if (abs(AP.x - user.first) + abs(AP.y - user.second) <= AP.c) return true;
	else return false;
}

int main(void) {

	int M, A, answer = 0;
	pair<int, int> userA = make_pair(1,1);
	pair<int, int> userB = make_pair(10,10);

	vector<vector<int>> Move;
	vector<BC> AP;

	scanf("%d %d", &M, &A);

	Move.assign(2, vector<int>(M));
	AP.resize(A);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < M; j++)
			scanf("%d", &Move[i][j]);
	}

	for (int i = 0; i < A; i++)
		scanf("%d %d %d %d", &AP[i].x, &AP[i].y, &AP[i].c, &AP[i].p);


	for (int i = 0;; i++) {
		//A최대 + B최대 , A2번째 + B최대, A최대 + B2
		int userAf = 0, userAs = 0, userBf = 0, userBs = 0;
		int index_a = 0, index_b = 0;

		for (int j = 0; j < A; j++) {
			if (check(AP[j], userA) && AP[j].p > userAs) {
				if (AP[j].p > userAf) {
					userAs = userAf;
					userAf = AP[j].p;
					index_a = j;
				}
				else userAs = AP[j].p;
			}
		}

		for (int j = 0; j < A; j++) {
			if (check(AP[j], userB) && AP[j].p > userBs) {
				if (AP[j].p > userBf) {
					userBs = userBf;
					userBf = AP[j].p;
					index_b = j;
				}
				else userBs = AP[j].p;
			}
		}
		int plus = 0;
		if (check(AP[index_a], userB) && check(AP[index_b], userA)) {
			if ((userAf + userBs) > (userAs + userBf)) plus = (userAf + userBs);
			else plus = (userAs + userBf);
		}
		else plus = (userAf + userBf);

		answer += plus;
		if (i == M) break;

		userA = make_pair(userA.first + dir[Move[0][i]][0], userA.second + dir[Move[0][i]][1]);	
		userB = make_pair(userB.first + dir[Move[1][i]][0], userB.second + dir[Move[1][i]][1]);
	}

	printf("%d\n", answer);


	return 0;
}