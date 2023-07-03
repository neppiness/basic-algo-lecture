// Authored by : scsc3204
// Co-authored by : -
// http://boj.kr/733f180c3916445487d98cf58621713e
#include <bits/stdc++.h>
using namespace std;

int m, n, seq;
bool has_inf_edge;

char b[22][22];
int dist[22][22];
int adj[12][12]; // adj[u][v] = cost from u to v
pair<int, int> coord[12];

queue<pair<int, int>> q;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int solve() {
  if (seq == 1) return 0;
  if (has_inf_edge) return -1;

  vector<int> perm(seq - 1);
  for (int i = 0; i < perm.size(); i++)
    perm[i] = i + 1;

  int ans = 0x7f7f7f7f;
  do {
    int tot = adj[0][perm[0]];
    for (int i = 1; i < perm.size(); i++)
      tot += adj[perm[i - 1]][perm[i]];
    ans = min(ans, tot);
  } while (next_permutation(perm.begin(), perm.end()));
  return ans;
}

bool oob(int x, int y) {
  return (x >= n || x < 0 || y >= m || y < 0);
}

void bfs(int cur) {
  for (int i = 0; i < n; i++)
    fill(dist[i], dist[i] + m, -1);

  auto [x, y] = coord[cur];
  dist[x][y] = 0;
  q.push(coord[cur]);
  while (!q.empty()) {
    auto [cx, cy] = q.front(); q.pop();
    for (int dir = 0; dir < 4; dir++) {
      int nx = cx + dx[dir];
      int ny = cy + dy[dir];
      if (oob(nx, ny)) continue;
      if (dist[nx][ny] != -1) continue;
      if (b[nx][ny] == 'x') continue;
      dist[nx][ny] = dist[cx][cy] + 1;
      q.push({nx, ny});
    }
  }
}

void setedges() {
  for (int cur = 0; cur < seq; cur++) {
    bfs(cur);
    for (int nxt = cur + 1; nxt < seq; nxt++) {
      auto [nx, ny] = coord[nxt];
      adj[cur][nxt] = dist[nx][ny];
      adj[nxt][cur] = dist[nx][ny];
      if (dist[nx][ny] == -1) has_inf_edge = 1;
    }
  }
}

void getinput() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c; cin >> c;
      b[i][j] = c;
      if (c == '.') continue;
      if (c == 'o') coord[0] = {i, j};
      if (c == '*') coord[seq++] = {i, j};
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> m >> n;
  while (m != 0 || n != 0) {
    seq = 1; has_inf_edge = 0;
    getinput();
    setedges();
    cout << solve() << '\n';
    cin >> m >> n;
  }
}
/*
pair<int, int> coord 배열: 13번째 줄
- 로봇 청소기와 더러운 방의 행, 열 값을 기록한다.

getinput() 함수: 74-84번째 줄
- 방의 정보를 받는다. 0에는 로봇 청소기의 위치를 저장하고,
  seq를 늘려가면서 더러운 칸 위치를 저장한다.

setedges() 함수: 62-72번째 줄
- 0부터 seq 미만의 위치를 시점으로 bfs를 수행한다.
  이를 통해 더러운 칸 또는 로봇 청소기 위치까지의 최단 거리를 계산한다.
- 이후 계산한 최단 거리를 adj 배열에 인접 행렬 형태로 저장한다(67-68번째 줄).
- 이 과정에서 dist가 -1인 지점이 있다면 닿을 수 없는 위치에 있는 것이므로
  has_inf_edge 변수를 1로 만들어준다.

bfs(int) 함수: 41-60번째 줄
- dist 함수를 -1로 초기화 해 visit 여부도 확인할 수 있도록 설정한다(42-43번째 줄).
- bfs를 수행하는 위치를 coord 배열에서 인덱싱 하여 시점으로 잡고 bfs를 수행한다(45번째 줄).

solve() 함수: 19-35번째 줄
- 더러운 칸이 10칸 보다 적다는 것만 언급되어 있기 때문에, 예외 처리를 위해
  더러운 칸이 없는 경우, 즉 seq 값이 증가하지 않고 1인 경우에는 0을 반환한다(20번째 줄).
- 닿을 수 없는 위치가 있다면 has_inf_edge = 1이므로, 이를 확인하고 -1을 반환한다(21번째 줄).
- 순열을 구성할 perm 벡터를 seq - 1 크기만큼 선언하고,
  1부터 seq - 1까지 값을 perm 벡터에 할당한다(23-25번째 줄).
- next_permutation을 활용해 모든 순열에 대해서 인접 행렬을 활용해 이동 비용을 확인한다.
  계산된 값을 ans과 비교하며 최솟값을 기록한 뒤 모든 순열에 대한 확인 후 ans을 반환한다(27-34번째 줄).
*/