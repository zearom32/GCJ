#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <cstdlib>
#include <message.h>
#include "lisp_plus_plus.h"
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

vector<LL> split_nodes(LL N, LL nodes) {
    LL step = (N - 1) / nodes + 1;
    vector<LL> ans;
    LL st = 0;
    for (LL i = 0; i <= nodes; i++) {
        ans.push_back(st);
        st = min(N, st + step);
    }
    return ans;
}

const LL master = 0;
const LL myid = MyNodeId();
const LL nodes = NumberOfNodes();
const LL N = GetLength();
const LL inf = 1LL << 32;
int main()
{
    vector<LL> index = split_nodes(N, nodes);
    LL cur = 0;
    LL minn = inf;
    for (LL i = index[myid]; i < index[myid+1]; i++) {
        char c = GetCharacter(i);
        if (c == '(') cur++; else cur--;
        minn = min(minn, cur);
    }
    PutLL(master, minn);
    PutLL(master, cur);
    Send(master);
    if (myid == master) {
        vector<LL> count_min;
        vector<LL> count_sum;
        for (int i = 0; i < nodes; i++) {
            Receive(i);
            LL k = GetLL(i);
            LL q = GetLL(i);
            if (k == inf){
                continue;
            }
            count_min.push_back(k);
            count_sum.push_back(q);
        }
        LL cur = 0;
        LL ns;
        int wrong = 0;
        for (int i = 0; i < count_min.size(); i++) {
            ns = i;
            if (cur + count_min[i] < 0) {
                wrong = 1;
                break;
            } 
            cur += count_sum[i];
        }
        
        if (!wrong) {
            if (cur == 0) {
                cout << -1 << endl;
            }else {
                cout << N << endl;
            }
        }else {
            for (LL i = index[ns]; i < index[ns+1]; i++) {
                char c = GetCharacter(i);
                if (c == '(') cur ++; else {
                    cur--;
                    if (cur < 0) {
                        cout << i <<endl;
                        return 0;
                    }
                }

            }
        }
    }
    return 0;
}
