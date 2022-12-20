#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
int n, mx = 0;
vector<int>arr;

//print
void show() {
    for (int i = 0; i < n * n; i++) {
        int y = i % n;
        cout << arr[i] << ' ';
        if (y == n - 1)cout << '\n';
    }
    cout << '\n';
}
// 랜덤한 곳에 숫자 추가
void addition() {
    int tmp = n * n;
    while (1) {
        int num = rand() % tmp;
        if (!arr[num]) {
            arr[num] = 2;
            break;
        }
    }
}

void init() {
    srand((unsigned int)time(NULL));
    arr.resize(n * n, 0);
    addition();
    addition();
}
// 더 이상 움직일 수 없는지 확인
bool check() {
    int tmp = n * n;
    for (int i = 0; i < tmp; i++) {
        if (i + n < tmp) {
            if (arr[i + n] == arr[i]) return true;
        }
        if (i + 1 < tmp && (i + 1) / n == i / n) {
            if (arr[i + 1] == arr[i])return true;
        }
    }
    return false;
}

void sw(int k) {
    //right
    int tmp = n * n;
    queue<int>que;
    // 오른쪽
    if (k) {
        for (int i = tmp - 1; i >= 0; i--) {
            if (arr[i]) {
                que.push(arr[i]);
                arr[i] = 0;
            }
            if (i % n == 0) {
                int j = i + n - 1;
                while (!que.empty()) {
                    int t = que.front();
                    que.pop();
                    if (arr[j] == 0)arr[j] = t;
                    else if (arr[j] == t) {
                        arr[j--] = 2 * t;
                    }
                    else {
                        arr[--j] = t;
                    }
                }
            }
            mx = max(arr[i], mx);
        }
    }
    //왼쪽
    else {
        for (int i = 0; i <= tmp - 1; i++) {
            if (arr[i]) {
                que.push(arr[i]);
                arr[i] = 0;
            }
            if (i % n == n - 1) {
                int j = i - n + 1;
                while (!que.empty()) {
                    int t = que.front();
                    que.pop();
                    if (arr[j] == 0)arr[j] = t;
                    else if (arr[j] == t) {
                        arr[j++] = 2 * t;
                    }
                    else {
                        arr[++j] = t;
                    }
                }
            }
            mx = max(arr[i], mx);
        }
    }
}

void transpose() {
    int tmp = n * n;
    int k = n - 1;
    for (int i = 0; i < tmp; i+=(n+1)) {
        for (int j = i + 1;j<=i+k; j++) {
            int x = j / n, y = j % n;
            swap(arr[x * n + y], arr[y * n + x]);
        }
        k--;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    init();
    int tmp = n * n;
    while (check()) {

        //1 동작
        //2 랜덤 추가
        show();
        char x; cin >> x;

        switch (x) {
        case 'w':case'W':
            transpose();
            sw(0);
            transpose();
            break;

        case 'a':case'A':
            // 왼
            sw(0);
            break;
        case 'd':case'D':
            //오른
            sw(1);
            break;
        case 's':case'S':
            transpose();
            sw(1);
            transpose();
            break;
        default:
            continue;
            break;
        }
        if (mx == 2048) {
            cout << "GOOD";
            break;
        }
        show();
        addition();
    }
}
