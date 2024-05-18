#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

int max_y = INT_MIN, max_x = INT_MIN, min_y = INT_MAX, min_x = INT_MAX;

int n;

vector<pair<int, int> > p;

bool check(int x, int y){
	for(int i = 0; i < n - 1; ++i){
		if(x == p[i].first && x == p[i + 1].first){
			if(p[i].second < p[i + 1].second && y >= p[i].second && y <= p[i + 1].second) return false;
			if(y <= p[i].second && y >= p[i + 1].second) return false;
		}
		if(y == p[i].second && y == p[i + 1].second){
			if(p[i].first < p[i + 1].first && x >= p[i].first && x <= p[i + 1].first) return false;
			if(x <= p[i].first && x >= p[i + 1].first) return false;
		}
	}
	return true;
}

void bfs(int start_x, int start_y) {
    queue<pair<pair<int, int>, int> > q; // pair of coordinates and distance
    set<pair<int, int> > visited;

    q.push(pair<pair<int, int>, int>(pair<int, int>(start_x, start_y), 1));
    visited.insert(pair<int, int>(start_x, start_y));

    while (!q.empty()) {
    	pair<int, int> curr(q.front().first);
    	int cnt = q.front().second;
    	int x = curr.first, y = curr.second;
    	
        q.pop();

        if (x > max_x || x < min_x || y > max_y || y < min_y) continue;
        
        if (curr == p[0]) {
        	cout<<cnt<<endl;
            exit(1);
        }
        
        if (!check(x, y)) continue;

        pair<int, int> next(x + 1, y);

        if (visited.find(next) == visited.end()) {
            q.push(pair<pair<int, int>, int>(next, cnt + 1));
            visited.insert(next);
        }
        next = pair<int, int>(x - 1, y);

        if (visited.find(next) == visited.end()) {
            q.push(pair<pair<int, int>, int>(next, cnt + 1));
            visited.insert(next);
        }
        next = pair<int, int>(x, y + 1);

        if (visited.find(next) == visited.end()) {
            q.push(pair<pair<int, int>, int>(next, cnt + 1));
            visited.insert(next);
        }
        next = pair<int, int>(x, y - 1);

        if (visited.find(next) == visited.end()) {
            q.push(pair<pair<int, int>, int>(next, cnt + 1));
            visited.insert(next);
        }
    }
}

int main() {
    ifstream in("gyvatele.txt");
    in >> n;
    
    p.resize(n);
    
    for (int i = 0; i < n; ++i) {
        in >> p[i].first >> p[i].second;

        max_y = max(max_y, p[i].second + 1);
        min_y = min(min_y, p[i].second - 1);
        max_x = max(max_x, p[i].first + 1);
        min_x = min(min_x, p[i].first - 1);
    }
    
    in.close();

    bfs(p[n - 1].first, p[n - 1].second - 1);
    bfs(p[n - 1].first - 1, p[n - 1].second);
    bfs(p[n - 1].first + 1, p[n - 1].second);
    bfs(p[n - 1].first, p[n - 1].second + 1);

    return 0;
}

