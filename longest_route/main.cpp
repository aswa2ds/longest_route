#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>

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
	vector<int> topo;
	graph(int s) { scale = s; dependent = new vector<vertex>[s]; }
	void add_edge(int, int, int);
	void print();
	void topological(int, bool*);
	void longest_route();
};

int main() {
	int num;
	cin >> num;
	graph G(num);
	bool *in_topo = new bool[num];
	memset((void*)in_topo, 0, num * sizeof(bool));
	int src, dst, w;
	while (scanf_s("%d%d%d", &src, &dst, &w) != EOF) {
		G.add_edge(src, dst, w);
	}
	//G.print();
	G.topological(0, in_topo);
	/*for (unsigned i = 0; i < G.topo.size(); ++i)
		cout << G.topo[i];
	cout << endl;*/
	G.longest_route();
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

void graph::topological(int u, bool* in) {
	in[u] = true;
	for (unsigned i = 0; i < dependent[u].size(); ++i) {
		int v = dependent[u][i].get_num();
		if (in[v] == false) 	topological(v, in);
	}
	topo.push_back(u);
}

void graph::longest_route() {
	int *length = new int[scale];
	memset((void*)length, 0, scale * sizeof(int));
	for (int i = scale - 1; i >= 0; --i) {
		int u = topo[i];
		for (int j = 0; j < dependent[u].size(); ++j) {
			int v = dependent[u][j].get_num();
			int w = dependent[u][j].get_weight();
			length[v] = (length[v] < length[u] + w) ? length[u] + w : length[v];
		}
	}
	cout << "I have read the rules about plagiarism punishment" << endl;
	for (int i = 1; i < scale; ++i)
		cout << length[i] << " ";
	cout << endl;
}