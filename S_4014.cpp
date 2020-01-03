#include <stdio.h>
#include <vector>

using namespace std;

int main(void) {

	int N, X, count = 0;
	vector<vector<int>> Map;

	scanf("%d %d", &N, &X);

	Map.assign(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			scanf("%d", &Map[i][j]);
	}

	for (int i = 0; i < N; i++) { //숫자차이가 1이 아닌경우 바로 pass
		vector<bool> slope(N);
		bool pass = true;
		int num = Map[i][0];
		
		for (int j = 1; pass && j < N; j++) {
			
			if (num - Map[i][j] == 1) {
				num = Map[i][j];
				for (int k = 0; k < X; k++, j++) {
					if (j >= N || Map[i][j] != num) {
						pass = false;
						break;
					}
					slope[j] = true;
				}
				j--;
			}
			else if(num - Map[i][j] == 0) {
				continue;
			}
			else if (num - Map[i][j] == -1) {
				for (int k = 1; k <= X; k++) {
					if (j - k < 0 || Map[i][j - k] != num || slope[j - k]) {
						pass = false;
						break;
					}
					else slope[j - k] = true;
				}
				num = Map[i][j];
			}
			else pass = false;
		}
		if (pass) count += 1;
	}

	for (int i = 0; i < N; i++) {
		vector<bool> slope(N);
		bool pass = true;
		int num = Map[0][i];

		for (int j = 1; pass && j < N; j++) {
			
			if (num - Map[j][i] == 1) {
				num = Map[j][i];
				for (int k = 0; k < X; k++, j++) {
					if (j >= N || Map[j][i] != num) {
						pass = false;
						break;
					}
					slope[j] = true;
				}
				j--;
			}
			else if(num - Map[j][i] == 0) {
				continue;
			}
			else if (num - Map[j][i] == -1) {
				for (int k = 1; k <= X; k++) {
					if (j - k < 0 || Map[j - k][i] != num || slope[j - k]) {
						pass = false;
						break;
					}
					else slope[j - k] = true;
				}
				num = Map[j][i];
			}
			else pass = false;
		}

		if (pass) count += 1;
	}

	printf("%d\n", count);

	return 0;
}