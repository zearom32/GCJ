# Again

* 题意

给定一段时间复杂度很高的代码，优化这段代码。
本题是个数学题，基本就是求和 a[i]*b[j], 0 <= i,j < N 且 (i+j) % nodes != 0

* Solution

可以求它的补集，sum(a[i]*b[j]), (i+j) % nodes == 0