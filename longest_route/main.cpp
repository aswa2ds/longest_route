#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

class vertex {
private:
	int num;
	int weight;
public:
	vertex(int n, int w) { num = n; weight = w; }
	int get_num() { return num; }
	int get_weight() { return weight; }
};

class graph{
private:
	int scale;
	vector<vertex> *dependent;
public:
	graph(int s) { scale = s; dependent = new vector<vertex>[s]; }
	void add_edge(int, int, int);
	void print();
};

int main() {
	int num;
	cin >> num;
	graph G(num);
	int src, dst, w;
	while (scanf_s("%d%d%d", &src, &dst, &w)) {
		G.add_edge(src, dst, w);
		G.print();
	}
	return 0;
}

void graph::add_edge(int src, int dst, int w) {
	vertex next(dst, w);
	dependent[src].push_back(next);
}

void graph::print() {
	for (int i = 0; i < scale; ++i) {
		cout << i << "->";
		for (unsigned j = 0; j < dependent[i].size(); ++j)
			cout << dependent[i][j].get_num() << " ";
		cout << endl;
	}
}