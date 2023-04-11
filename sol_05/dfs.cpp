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

int main() {
    const int n = 10; // 맵의 크기
    char map[n][n]; // 맵 배열
    bool visited[n][n]; // 방문 여부 체크 배열
    Point start, end; // 출발점과 도착점
    Point prev[n][n]; // 이전 위치 기록 배열

    // 출발점과 도착점 입력 받기
    cout << "출발점 입력 (x, y): ";
    cin >> start.x >> start.y;
    cout << "도착점 입력 (x, y): ";
    cin >> end.x >> end.y;

    // 맵 초기화
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            map[i][j] = '.'; // 빈 공간으로 초기화
            visited[i][j] = false; // 방문 여부 체크 배열 초기화
        }
    }

    // 장애물 개수와 위치 입력 받기
    int numObstacles;
    cout << "장애물 개수: ";
    cin >> numObstacles;

    for (int i = 0; i < numObstacles; i++) {
        int obstacleX, obstacleY;
        cout << "장애물 " << i + 1 << " 위치 (x, y): ";
        cin >> obstacleX >> obstacleY;
        map[obstacleX][obstacleY] = 'X'; // 장애물 위치에 X로 표시
    }

    // 출발점과 도착점 설정
    map[start.x][start.y] = 'p';
    map[end.x][end.y] = 'e';

    // BFS를 이용한 최단 경로 탐색
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
            // 맵 범위를 벗어나는 경우 스킵
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                continue;
            }

            // 벽인 경우 스킵
            if (map[nx][ny] == 'X') {
                continue;
            }

            // 방문하지 않은 경우 큐에 추가하고 방문 여부 체크
            if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push(Point(nx, ny));
                prev[nx][ny] = current; // 이전 위치 기록
            }
        }
    }

    // 도착점에서부터 역으로 출발점까지의 경로 출력
    if (!visited[end.x][end.y]) {
        cout << "최단 경로가 없습니다." << endl;
        // 맵 출력
        cout << endl << "맵 출력:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "최단 경로: ";
        Point current = end;
        while (!(current.x == start.x && current.y == start.y)) {
            map[current.x][current.y] = 'o'; // 경로에 해당하는 위치에 *로 표시
            current = prev[current.x][current.y];
        }
        map[start.x][start.y] = 'p'; // 출발점에 다시 p로 표시
        map[end.x][end.y] = 'e';

        // 맵 출력
        cout << endl << "맵 출력:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}

