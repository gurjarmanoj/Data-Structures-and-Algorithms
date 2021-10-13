// C++ implementation to find the
// simple cycle in the given path

#include <bits/stdc++.h>
using namespace std;
#define MAXN 1005

// Declaration of the Graph
vector<vector<int> > adj(MAXN);

// Declaration of visited array
vector<bool> vis(MAXN);
int a, b;

// Function to add edges
// connecting 'a' and 'b'
// to the graph
void addedge(int a, int b)
{
	adj[a].push_back(b);
	adj[b].push_back(a);
}

// Function to detect if the
// graph contains a cycle or not
bool detect_cycle(int node, int par)
{
	// Marking the current node visited
	vis[node] = 1;
	// Traversing to the childs
	// of the current node
	// Simple DFS approach
	for (auto child : adj[node]) {
		if (vis[child] == 0) {
			if (detect_cycle(child, node))
				return true;
		}

		// Checking for a back-edge
		else if (child != par) {
			// A cycle is detected
			// Marking the end-vertices
			// of the cycle
			a = child;
			b = node;
			return true;
		}
	}
	return false;
}

vector<int> simple_cycle;

// Function to get the simple cycle from the
// end-vertices of the cycle we found from DFS
void find_simple_cycle(int a, int b)
{
	// Parent array to get the path
	vector<int> par(MAXN, -1);

	// Queue for BFS
	queue<int> q;
	q.push(a);
	bool ok = true;
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		vis[node] = 1;
		for (auto child : adj[node]) {
			if (node == a && child == b)
				// Ignoring the direct edge
				// between a and b
				continue;

			if (vis[child] == 0) {
				// Updating the parent array
				par[child] = node;

				if (child == b) {
					// If b is reached,
					// we've found the
					// shortest path from
					// a to b already
					ok = false;
					break;
				}
				q.push(child);
				vis[child] = 1;
			}
		}
		// If required task is done
		if (ok == false)
			break;
	}

	// Cycle starting from a
	simple_cycle.push_back(a);
	int x = b;

	// Until we reach a again
	while (x != a) {
		simple_cycle.push_back(x);
		x = par[x];
	}
}

// Driver Code
int main()
{

	// Creating the graph
	addedge(1, 2);
	addedge(2, 3);
	addedge(3, 4);
	addedge(4, 1);
	addedge(1, 3);

	if (detect_cycle(1, -1) == true) {
		// If cycle is present

		// Resetting the visited array
		// for simple cycle finding
		vis = vector<bool>(MAXN, false);
		find_simple_cycle(a, b);

		// Printing the simple cycle
		cout << "A simple cycle: ";
		for (auto& node : simple_cycle) {
			cout << node << " => ";
		}
		cout << a;
		cout << "\n";
	}
	else {
		cout << "The Graph doesn't "
			<< "contain a cycle.\n";
	}

	return 0;
}
