#include <stdio.h>
#include <stdlib.h>
#include <vector>


using namespace std;

int N, W, H;
vector<vector<int>> Map;
vector<vector<int>> M;
vector<vector<bool>> Visit;
vector<vector<bool>> V;
int d[4][2] = { {-1,0},{0,1},{1,0},{0,-1} }; //북 동 남 서 
int pos[4];
int Min;
bool finish = false;

int min(int a, int b);
void ready(int n);
void shoot();
void boom(int y, int x);
void arrange();
int count();


int min(int a, int b) { return a < b ? a : b; }

void ready(int n) {
	if (finish) {
		return;
	}
	if (n == 0) {
		M = Map;
		shoot();
		return;
	}
	for (int i = 0; i < W; i++) {
		pos[N - n] = i;
		ready(n - 1);
	}
}

void shoot()
{
	for (int i = 0; i < N; i++) { //N번 쏘는거
		int x = pos[i], j = 0;
		V = Visit;

		for (; j < H; j++) {
			if (M[j][x] != 0) {
				boom(j, x);
				arrange();
				if(count() == 0){
					finish = true;
					Min = 0;
					return;
				}
				break;
			}
		}
		if (j == H) continue; //해당 라인에 맞을게 없는 경우
		Min = min(Min, count());
	}
}

void boom(int y, int x) {
	V[y][x] = 1;
	int w = M[y][x] - 1;

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= w; j++) {
			int dy = y + j * d[i][0];
			int dx = x + j * d[i][1];

			if (dy >= 0 && dy < H && dx >= 0 && dx < W && !V[dy][dx] && M[dy][dx] != 0) {
				boom(dy, dx);
			}
		}
	}
	M[y][x] = 0;
}

void arrange() {

	for (int i = 0; i < W; i++) {
		for (int j = H - 1; j >= 0; j--) {
			if (M[j][i] == 0) {
				int t = 1, k = j - 1;

				for (; k >= 0; k--, t++) {
					if (M[k][i] != 0) break;
				}
				if (k < 0) break;

				for (; k >= 0; k--) {
					M[k + t][i] = M[k][i];
				}
				for (t = t - 1; t >= 0; t--)
					M[t][i] = 0;
			}
		}
	}
}
int count() {
	int count = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++)
			if (M[i][j] != 0) count++;
	}

	return count;
}
int main(void) {

	scanf("%d %d %d", &N, &W, &H);
	Min = W * H;
	Map.assign(H, vector<int>(W));
	Visit.assign(H, vector<bool>(W, false));
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++)
			scanf("%d", &Map[i][j]);
	}
	ready(N);

	printf("#%d\n", Min);

	return 0;
}