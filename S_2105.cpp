#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;
int dir[4][2] = { {-1, 1}, {1,1}, {1, -1}, {-1, -1} }; // right down left up
int N;

bool IsRange(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}

int main(void) {

	vector<vector<int>> Map;
	int count = -1;

	scanf("%d", &N);
	Map.assign(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			scanf("%d", &Map[i][j]);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
	
			int right = 1;
			int mx = i + right * dir[0][0];
			int my = j + right * dir[0][1];

			while (IsRange(mx,my)) {
				int down = 1;
				int mmx = mx + down * dir[1][0];
				int mmy = my + down * dir[1][1];

				while (IsRange(mmx, mmy)) {
					vector<int> list;
					bool pass = true;
					pair<int, int> now = make_pair(i, j);

					for (int k = 0; k < 2; k++) {
						for (int w = 1; w <= right; w++) {
							now.first += dir[2 * k][0];
							now.second += dir[2 * k][1];
					
							if (!IsRange(now.first, now.second) || find(list.begin(), list.end(), Map[now.first][now.second]) != list.end()) {
								pass = false;
								break;
							}
							else list.push_back(Map[now.first][now.second]);

						}
						if (!pass) break;

						for (int w = 1; w <= down; w++) {
							now.first += dir[2 * k + 1][0];
							now.second += dir[2 * k + 1][1];

							if (!IsRange(now.first, now.second) || find(list.begin(), list.end(), Map[now.first][now.second]) != list.end()){
								pass = false;
								break;
							}
							else list.push_back(Map[now.first][now.second]);
						}
						if (!pass) break;
					}

					if (pass) {
						if (count < (signed)list.size()) count = list.size();
					}

					down++;
					mmx = mx + down * dir[1][0];
					mmy = my + down * dir[1][1];
				}

				right++;
				mx = i + right * dir[0][0];
				my = j + right * dir[0][1];
			}


		}
	}

	
	printf("%d\n", count);

	return 0;
}