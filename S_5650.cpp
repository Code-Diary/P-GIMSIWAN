#include <stdio.h>
#include <vector>

using namespace std;

vector<vector<int>> Map;
int s;
int dir[4][2] = { {-1,0},{0,1},{0,-1},{1,0} };

int main(void) {

	pair<int, int> wormhole[11];
	int Max = -1;

	for (int i = 0; i <= 10; i++)	
		wormhole[i] = make_pair(-1, -1);

	scanf("%d", &s);

	Map.assign(s, vector<int>(s));

	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			scanf("%d", &Map[i][j]);
			if (Map[i][j] >= 6 && Map[i][j] <= 10) {
				if (wormhole[Map[i][j]] == wormhole[0]) wormhole[Map[i][j]] = make_pair(i, j);
				else wormhole[Map[i][j] - 5] = make_pair(i, j);
			}

		}
	}
	
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			if (Map[i][j] != 0) continue; //���� ��ġ�� ������� �ƴҰ�� pass

			for (int w = 0; w < 4; w++) { // 0 -> ��, 1-> ��, 2-> ��, 3-> ��

				pair<int, int> start = make_pair(i, j);
				pair<int, int> pos = start;
				int d = w;
				int count = 0;

				pos = make_pair(pos.first + dir[d][0], pos.second + dir[d][1]);

				if (pos.first < 0 || pos.second < 0 || pos.first >= s || pos.second >= s) { //���� �ε��� ���
					d = 3 - d;
					count += 1;
					pos = make_pair(pos.first + dir[d][0], pos.second + dir[d][1]);
				}

				while (pos != start && Map[pos.first][pos.second] != -1) { //��ġ�� start�ų� blackhole�� ��� ����

					int status = Map[pos.first][pos.second];

					switch (status) {
						case 0:
							break;
						case 1:
							if (d == 0 || d == 1)
								d = 3 - d;
							else d = d - 2;
							count += 1;
							break;
						case 2:
							if (d == 1 || d == 3)
								d = 3 - d;
							else d = d + 1;
							count += 1;
							break;
						case 3:
							if (d == 2 || d == 3)
								d = 3 - d;
							else d = d + 2;
							count += 1;
							break;
						case 4:
							if (d == 0 || d == 2)
								d = 3 - d;
							else d = d - 1;
							count += 1;
							break;
						case 5:
							d = 3 - d;
							count += 1;
							break;
						case 6:
						case 7:
						case 8:
						case 9:
						case 10:
							if (pos == wormhole[status]) pos = wormhole[status - 5];
							else pos = wormhole[status];
							break;
						default:
							break;
					}

					pos = make_pair(pos.first + dir[d][0], pos.second + dir[d][1]);

					if (pos.first < 0 || pos.second < 0 || pos.first >= s || pos.second >= s) { //���� �ε��� ���
						d = 3 - d;
						count += 1;
						pos = make_pair(pos.first + dir[d][0], pos.second + dir[d][1]);
					}

				}

				if (Max == -1 || (Max != -1 && Max < count)) Max = count;
			}

		}
	}
	
	printf("%d\n", Max);
	return 0;
}