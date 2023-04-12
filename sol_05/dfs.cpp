#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Point {
public:
    int x;
    int y;

    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

class MazeSolver {
public:
    const int n = 10; // 맵의 크기
    char map[10][10]; // 맵 배열
    bool visited[10][10]; // 방문 여부 체크 배열
    Point start, end; // 출발점과 도착점
    Point prev[10][10]; // 이전 위치 기록 배열

    // 생성자
    MazeSolver() {}

    // 출발점과 도착점 입력 받기
    void inputPoints() {
        cout << "출발점 입력 (x, y): ";
        cin >> start.x >> start.y;
        cout << "도착점 입력 (x, y): ";
        cin >> end.x >> end.y;
    }

    // 맵 초기화
    void initMap() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                map[i][j] = '.'; // 빈 공간으로 초기화
                visited[i][j] = false; // 방문 여부 체크 배열 초기화
            }
        }
    }

    // 장애물 개수와 위치 입력 받기
    void inputObstacles() {
        int numObstacles;
        cout << "장애물 개수: ";
        cin >> numObstacles;

        for (int i = 0; i < numObstacles; i++) {
            int obstacleX, obstacleY;
            cout << "장애물 " << i + 1 << " 위치 (x, y): ";
            cin >> obstacleX >> obstacleY;
            map[obstacleX][obstacleY] = 'X'; // 장애물 위치에 X로 표시
        }
    }

    // 출발점과 도착점 설정
    void setStartEndPoints() {
        map[start.x][start.y] = 'p';
        map[end.x][end.y] = 'e';
    }

    // BFS를 이용한 최단 경로 탐색
    bool findShortestPath() {
        queue<Point> q;
        q.push(start);
        visited[start.x][start.y] = true;
        prev[start.x][start.y] = start; // 출발점의 이전 위치는 자기 자신으로 설정

        bool foundPath = false; // 도착점에 도달했는지 여부를 체크하는 변수

        while (!q.empty()) {
            Point current = q.front();
            q.pop();

            // 도착점에 도달한 경우 종료
            if (current.x == end.x && current.y == end.y) {
                foundPath = true;
                break;
            }

            // 상하좌우로 이동
            int dx[] = { -1, 0, 1, 0 };
            int dy[] = { 0, 1, 0, -1 };

            for (int i = 0; i < 4; i++) {
                int nx = current.x + dx[i];
                int ny = current.y + dy[i];

                // 맵 범위를 벗어나는 경우
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

                // 벽이거나 이미 방문한 경우
                if (map[nx][ny] == 'X' || visited[nx][ny]) continue;

                q.push(Point(nx, ny));
                visited[nx][ny] = true;
                prev[nx][ny] = current; // 이전 위치를 현재 위치로 설정
            }
        }

        return foundPath;
    }

    // 최단 경로 출력
    void printShortestPath() {
        if (!visited[end.x][end.y]) {
            cout << "최단경로가 없습니다." << endl;
            return;
        }

        vector<Point> shortestPath;
        Point current = end;

        // 도착점에서 출발점까지의 최단 경로를 역추적하여 shortestPath 벡터에 저장
        while (!(current.x == start.x && current.y == start.y)) {
            shortestPath.push_back(current);
            current = prev[current.x][current.y];
        }

        shortestPath.push_back(start);
        reverse(shortestPath.begin(), shortestPath.end());

        // 최단 경로 출력
        cout << "최단 경로: ";
        for (const auto& point : shortestPath) {
            // 경로를 'o'로 바꿈
            map[point.x][point.y] = 'o';
        }
        cout << endl;
    }
        // 맵 출력
    void printMap() {
        cout << "맵 출력:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    MazeSolver mazeSolver;
    mazeSolver.inputPoints();
    mazeSolver.initMap();
    mazeSolver.inputObstacles();
    mazeSolver.setStartEndPoints();
    if (mazeSolver.findShortestPath()) {
        mazeSolver.printShortestPath();
        mazeSolver.setStartEndPoints();
    }
    else {
        cout << "최단경로가 없습니다." << endl;
    }
    mazeSolver.printMap(); // 맵 출력 추가
    return 0;
}

