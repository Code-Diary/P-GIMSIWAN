#include <stdio.h>
#include <vector>

using namespace std;

int dir[5][2] = { {0,0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; //╩С го аб ©Л

typedef struct {
	int x;
	int y;
	int num;
	int dir;
}Micro;

int main(void) {

	int N, M, K, num = 0;
	vector<Micro> List;

	scanf("%d %d %d", &N, &M, &K);

	List.resize(K);

	for (int i = 0; i < K; i++) {
		scanf("%d %d %d %d", &List[i].x, &List[i].y, &List[i].num, &List[i].dir);
	}

	while (M > 0) {
		M--;

		for (int i = 0; i < List.size(); i++) {
			int x = List[i].x + dir[List[i].dir][0];
			int y = List[i].y + dir[List[i].dir][1];
			
			List[i].x = x;
			List[i].y = y;

			if (x == 0 || x == N - 1 || y == 0 || y == N - 1) {
				List[i].num /= 2;
				if (List[i].dir == 1) List[i].dir = 2;
				else if (List[i].dir == 2) List[i].dir = 1;
				else if (List[i].dir == 3) List[i].dir = 4;
				else if (List[i].dir == 4) List[i].dir = 3;
			}

		}

		for (int i = 0; i < List.size(); i++) {
			
			if (List[i].num == 0) {
				List.erase(List.begin() + i);
				i--;
				continue;
			}

			int n = List[i].num;

			for (int j = i + 1; j < List.size(); j++) {
				if ((List[i].x == List[j].x) && (List[i].y == List[j].y)) {
					if (List[i].num < List[j].num) {
						List[i].dir = List[j].dir;
						List[i].num = List[j].num;
					}
					n += List[j].num;
					List.erase(List.begin() + j);
					j--;
				}
			}

			List[i].num = n;
		}

	}
	for (int i = 0; i < List.size(); i++) {
		num += List[i].num;
	}

	printf("%d\n", num);

	return 0;
}