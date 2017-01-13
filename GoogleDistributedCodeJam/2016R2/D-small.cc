#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <cstdlib>
#include <message.h>
#include "asteroids.h"
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const LL master = 0;
const LL myid = MyNodeId();
LL nodes = NumberOfNodes();

const LL height = GetHeight();
const LL width = GetWidth();

vector<LL> split_nodes(LL N, LL& nodes) {
    LL step = (N - 1) / nodes + 1;
    vector<LL> ans;
    LL st = 0;
    for (LL i = 0; i <= nodes; i++) {
        ans.push_back(st);
        st = min(N, st + step);
    }
    for (LL i = 0; i <= nodes; i++){
        if (ans[i] == ans[i+1]) {
            nodes = i;
            break;
        }
    }
    return ans;
}

const LL inf = 1LL << 40;

int main()
{
    /*
    vector<LL> index = split_nodes(height, nodes);

    for (int i = index[myid];  i < index[myid+1]; i++) {

    }
*/

    if (myid == master) {
        vector<LL> row(width);
        vector<LL> tmp = row;
        vector<LL> val = row;
        for (LL i = 0; i < height + 1; i++) {
            for (LL j = 0; j < width; j++) {
                LL v;
                char c;
                if (i == height) {
                    c = '0';
                }else 
                    c = GetPosition(i,j);
                if (c == '#') {
                    tmp[j] = v = -inf;
                } else {
                    v = c - '0';
                    if (row[j] == -inf) tmp[j] = -inf; else tmp[j] = row[j] + v;
                    if (j > 0 && row[j-1] != -inf && val[j] != -inf) tmp[j] = max(tmp[j], v + row[j-1] + val[j]);
                    if (j < width-1 && row[j+1] != -inf && val[j] != -inf) tmp[j] = max(tmp[j], v + row[j+1] + val[j]);
                }
                val[j] = v;
            }
            row = tmp;
           // for (auto k:row) if (k == -inf) cout << -1; else cout << k;
          //  cout << endl;
        }

        LL ans = -inf;
        for (auto k:row) {
            ans = max(ans, k);
        }
        if (ans > 0) {
            cout << ans <<endl;
        } else cout << -1 << endl;
    }

    return 0;
}