#include <stdio.h>
#include <vector>

using namespace std;

typedef struct {
	pair<int, int> loc;
	int length;
	int stand = 0;
}S;

typedef struct {
	pair<int, int> loc;
	int stairs_num;
	int distance;
}P;

vector<S> Stairs;
vector<P> Person;
int _time_;

int distance(int n) {
	
	return abs(Stairs[Person[n].stairs_num].loc.first - Person[n].loc.first) + abs(Stairs[Person[n].stairs_num].loc.second - Person[n].loc.second);
}

int count() {

	vector<P> C_Person = Person;
	int T= 0;
	for (int i = 0; i < C_Person.size(); i++)
		C_Person[i].distance = distance(i);

	while (C_Person.size() != 0) {
		for (int i = 0; i < C_Person.size(); i++) {
			if (C_Person[i].distance + Stairs[C_Person[i].stairs_num].length == 0) {
				Stairs[C_Person[i].stairs_num].stand -= 1;
				C_Person.erase(C_Person.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < C_Person.size(); i++) {
			if (C_Person[i].distance == 0) {
				if (Stairs[C_Person[i].stairs_num].stand == 3) continue;
				Stairs[C_Person[i].stairs_num].stand += 1;
			}
			C_Person[i].distance -= 1;
		}

		T += 1;
	}
	return T;
}

void select(int num) {

	if (num == 0) {
		int T = count();
		
		if (_time_ == -1 || _time_ > T) _time_ = T;
		return;
	}

	for (int i = 0; i < 2; i++) {
		Person[Person.size() - num].stairs_num = i;
		select(num - 1);
	}
}

int main(void) {

	int N;
	_time_ = -1;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int x;
			scanf("%d", &x);
			if (x == 1) {
				P tempt;
				tempt.loc = make_pair(i, j);
				Person.push_back(tempt);
			}
			else if (x != 0) {
				S tempt;
				tempt.loc = make_pair(i, j);
				tempt.length = x;
				Stairs.push_back(tempt);
			}
		}
	}
	select(Person.size());

	printf("%d\n", _time_);
	return 0;
}