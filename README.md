# FiveChess
A small Gobang Fivechess game based on VS2010.

For more, please see [doc](https://github.com/Hzwcode/FiveChess/tree/master/doc).

- alpha-beta剪枝算法伪代码：

```
double	alphabeta(int depth, double alpha, double beta, State s) {
	/* 计算局面s的最优值 */
	int i;
	double t;
	if (depth == 0) {
		return evaluate(p);    /* 叶节点 */
	}
	State c[w] = get_child_state(s);
	if(极大点) {
		for(i = 0; i < w; i++) {
			t = alphabeta(depth - 1; alpha, beta, c[i]);
			if(t > alpha) {
				if(t>beta) {
					return t;
				}
				else {
					alpha = t;
				}
			}
		}
		return alpha;
	}

	else {
		/* 极小点 */
		for(i = 0; i < w; i++) {
			t = alphabeta(depth - 1; alpha, beta, c[i]);
			if(t < beta) {
				if(t > alpha) {
					return t;
				}
				else {
					beta = t;
				}
			}
		}
		reutn beta
	}
}
```
