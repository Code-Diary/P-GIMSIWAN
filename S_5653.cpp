#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

typedef struct {
	int status = -1; // -1: x , 0: 비활성, 1: 활성, 2 : 죽은
	int time = 0; // 비활성후 지난 시간
	int x = 0; // 생명력
}cell;

vector<vector<cell>> map;
int N, M, K; // N = 세로, M = 가로, K = 시간
int startPos, L;
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
queue<pair<int, int>> ActiveCell;
queue<pair<int, int>> WaitCell;

int main(void) {

	int count;
	scanf("%d %d %d", &N, &M, &K);
	L = 2 *K + 50;
	map.assign(L, vector<cell>(L));
	startPos = K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i + startPos][j + startPos].x);
			if (map[i + startPos][j + startPos].x != 0) {
				map[i + startPos][j + startPos].status = 0;
				WaitCell.push(make_pair(i + startPos, j + startPos));
			}
		}
	}

	while (K > 0) {
		K--;

		pair<int, int> rear;
		pair<int, int> Act_rear;
		pair<int, int> front;
		bool empty = true;

		if (!WaitCell.empty()) rear = WaitCell.back();
		if (!ActiveCell.empty()) Act_rear = ActiveCell.back();
		else empty = false;

		while (!WaitCell.empty()) {
			front = WaitCell.front();
			WaitCell.pop();

			map[front.first][front.second].time++;
			if (map[front.first][front.second].x == map[front.first][front.second].time) {
				map[front.first][front.second].status = 1;
				ActiveCell.push(make_pair(front.first, front.second));
			}
			else WaitCell.push(make_pair(front.first, front.second));
			if (front == rear) break;
		}

		while (empty && !ActiveCell.empty()) { // 위 while문에서 빈 active queue에 추가된 경우 예외처리
			front = ActiveCell.front();
			ActiveCell.pop();
			map[front.first][front.second].time++;

			if (map[front.first][front.second].time == map[front.first][front.second].x + 1) {
			
				for (int d = 0; d < 4; d++) {
					int dx = front.first + dir[d][0];
					int dy = front.second + dir[d][1];

					if (map[dx][dy].time == 0) {//주변에 존재 하지 않으면
						if (map[dx][dy].status == -1) {
							map[dx][dy].status = 0;
							WaitCell.push(make_pair(dx, dy));
						}
						if (map[dx][dy].x < map[front.first][front.second].x)
							map[dx][dy].x = map[front.first][front.second].x;
					}
				}
			}
			if (map[front.first][front.second].time < map[front.first][front.second].x * 2)
				ActiveCell.push(make_pair(front.first, front.second));


			if (front == Act_rear) break;
		}

	}
	
	count = WaitCell.size() + ActiveCell.size();
	printf("%d\n",count);
	return 0;

}