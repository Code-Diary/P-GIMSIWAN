#include <stdio.h>
#include <vector>

using namespace std;

typedef struct {
	int x;
	int y;
	int d;
	int k;
}atom;

int dir[4][2] = { {0,1},{0,-1},{-1,0},{1,0} };
vector<vector<int>> map;
vector<atom> list;

int main(void)
{
	map.assign(4001, vector<int>(4001));
	int N;
	int energy = 0;
	scanf("%d", &N);

	list.resize(N);

	for (int i = 0; i < N; i++) {
		scanf("%d %d %d %d", &list[i].x, &list[i].y, &list[i].d, &list[i].k);
		list[i].x *= 2;
		list[i].y *= 2;
	}

	while(list.size()> 1){

		for (int i = 0; i < list.size(); i++) {
			int dx = list[i].x + dir[list[i].d][0];
			int dy = list[i].y + dir[list[i].d][1];

			if (dx < -2000 || dx > 2000 || dy < -2000 || dy > 2000) {
				list.erase(list.begin() + i);
				i--;
				continue;
			}
			
			map[dx + 2000][dy + 2000] += list[i].k;
			list[i].x = dx;
			list[i].y = dy;
		}

		for (int i = 0; i < list.size();) {
			if (list[i].k != map[list[i].x + 2000][list[i].y + 2000]) {
				for (int j = i + 1; j < list.size();) {
					if (list[i].x == list[j].x && list[i].y == list[j].y) {
						energy += list[j].k;
						list.erase(list.begin() + j);
					}
					else j++;
				}
				energy += list[i].k;
				map[list[i].x + 2000][list[i].y + 2000] = 0;
				list.erase(list.begin() + i);
			}
			else{
				map[list[i].x + 2000][list[i].y + 2000] = 0;
				i++;
			}
		}
	}

	printf("%d\n", energy);
	
	return 0;
}