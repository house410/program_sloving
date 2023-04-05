#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int SIZE = 10; // 그리드의 크기

struct Point { // 좌표를 나타내는 구조체
    int x, y, dist; // x좌표, y좌표, 시작점으로부터의 거리
    bool operator<(const Point& other) const {
        return dist > other.dist;
    }
};

// 현재 위치의 이웃들을 반환하는 함수
vector<Point> getNeighbors(int grid[][SIZE], int x, int y) {
    vector<Point> neighbors;
    int dx[] = { 0, 0, 1, -1 };
    int dy[] = { 1, -1, 0, 0 };
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && grid[nx][ny] != 1) {
            neighbors.push_back({ nx, ny, 1 });
        }
    }
    return neighbors;
}

// 시작점에서 도착점까지의 최단 경로를 구하는 함수
vector<Point> bfs(int grid[][SIZE], Point start, Point end) {
    priority_queue<Point> pq;
    vector<vector<bool>> visited(SIZE, vector<bool>(SIZE, false)); // 방문 여부 저장
    vector<vector<Point>> prev(SIZE, vector<Point>(SIZE, { -1, -1, -1 })); // 경로 역추적을 위한 이전 좌표 저장
    pq.push(start);

    while (!pq.empty()) {
        Point current = pq.top();
        pq.pop();
        if (current.x == end.x && current.y == end.y) { // 도착점에 도달한 경우
            break;
        }
        if (visited[current.x][current.y]) { // 이미 방문한 경우
            continue;
        }
        visited[current.x][current.y] = true;
        vector<Point> neighbors = getNeighbors(grid, current.x, current.y); // 현재 위치의 이웃들
        for (Point neighbor : neighbors) {
            if (!visited[neighbor.x][neighbor.y]) { // 이웃이 아직 방문하지 않은 경우
                pq.push({ neighbor.x, neighbor.y, current.dist + neighbor.dist }); // 이웃을 우선순위 큐에 추가
                prev[neighbor.x][neighbor.y] = current; // 이웃의 이전 좌표를 현재 좌표로 갱신
            }
        }
    }

    vector<Point> shortestPath;
    Point current = end;
    while (current.x != -1 && current.y != -1) { // 경로 역추적
        shortestPath.push_back(current);
        current = prev[current.x][current.y];
    }
    reverse(shortestPath.begin(), shortestPath.end());

    return shortestPath;
}

int main() {
    int grid[SIZE][SIZE] = {
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 2}
    };
    Point start = { 0, 0 };
    Point end = { 9, 9 };
    vector<Point> shortestPath = bfs(grid, start, end);
    for (int i = 0; i < shortestPath.size(); i++) {
        cout << "(" << shortestPath[i].x << ", " << shortestPath[i].y << ") ";
    }
    cout << endl;

    //맵출력
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                cout << ". ";
            }
            else if (grid[i][j] == 1) {
                cout << "X ";
            }
            else if (grid[i][j] == 2) {
                cout << "E ";
            }
            else {
                bool inPath = false;
                for (int k = 0; k < shortestPath.size(); k++) {
                    if (shortestPath[k].x == i && shortestPath[k].y == j) {
                        cout << "P ";
                        inPath = true;
                        break;
                    }
                }
                if (!inPath) {
                    cout << ". ";
                }
            }
        }
        cout << endl;
    }
    return 0;
} 
