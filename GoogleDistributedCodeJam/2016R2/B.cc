#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <cstdlib>
#include <message.h>
#include "again.h"

#define LARGE_PRIME 1000000007

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
const LL N = GetN();
int main()
{
    LL sumA = 0;
    LL sumB = 0;
    for (LL i = myid; i < N; i += nodes) {
        sumA += GetA(i);
        sumB += GetB(i);
        sumA %= LARGE_PRIME;
        sumB %= LARGE_PRIME;
    }
    PutLL(master, sumA);
    PutLL(master, sumB);
    Send(master);
    if (myid == master) {
        vector<LL> A;
        vector<LL> B;
        LL sa = 0;
        LL sb = 0;
        for (int i = 0; i < nodes; i++) {
            Receive(i);
            A.push_back(GetLL(i));
            B.push_back(GetLL(i));
        }

        for (auto k : A) sa += k;
        for (auto k :B) sb += k;
        sa = sa % LARGE_PRIME;
        sb = sb % LARGE_PRIME;
        LL ans = sa * sb % LARGE_PRIME;
        for (int i = 0; i < nodes; i++) {
            int j = nodes - i;
            if (j == nodes) j = 0;
            ans = (ans - A[i] * B[j]) % LARGE_PRIME;
        }
        ans = (ans + LARGE_PRIME) % LARGE_PRIME;
        cout << ans << endl;
    }
    return 0;
}