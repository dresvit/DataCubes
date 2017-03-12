#include <cstdio>
#include <cstring>

const int maxn = 105;           //最大view数
const int maxm = 10005;         //最大边数

struct AdjList {                //邻接表，用于保存cube lattice
	int y;                      //当前有向边指向的结点
	int next;                   //下一条边
} edge[maxm];

int n;                          //view总数
int m;                          //有向边总数
int K;                          //要选择的view数目（不算top view）
int currentView;                //当前选择的view
int totEdge;                    //邻接表总边数
int head[maxn];                 //邻接表中每个结点的起始边
int S[maxn];                    //要选择的view的集合
int totCover[maxn];             //每个view覆盖的view数目
int coverList[maxn][maxn];      //记录每个view覆盖的view
long long cost[maxn];           //每个view的代价
long long currentCost[maxn];    //每个view对应的S中的代价最小的view的代价
bool isroot[maxn];              //判断当前view是不是top view
bool selected[maxn];            //判断当前view是否已被选择
bool covered[maxn][maxn];       //判断某个view是否覆盖了另一个view
bool hasEdge[maxn][maxn];       //判断是否有重边
FILE *fp;                       //文件指针

//添加从x到y的有向边
void addEdge(int x, int y) {
	totEdge++;
	edge[totEdge].y = y;
	edge[totEdge].next = head[x];
	head[x] = totEdge;
}

//找出x覆盖的所有view
void findCoveredView(int x) {
	if (!covered[currentView][x]) {
		covered[currentView][x] = true;
		coverList[currentView][++totCover[currentView]] = x;
	}
	for (int i = head[x]; i; i = edge[i].next)
		findCoveredView(edge[i].y);
}

//计算benefit
long long calcBenefit(int x) {
	long long result = 0;
	for (int i = 1; i <= totCover[x]; i++) {
		if (currentCost[coverList[x][i]] > cost[x])
			result += currentCost[coverList[x][i]] - cost[x];
	}
	return result;
}

//更新每个view对应的S中的代价最小的view的代价
void update(int x) {
	for (int i = 1; i <= totCover[x]; i++) {
		if (currentCost[coverList[x][i]] > cost[x])
			currentCost[coverList[x][i]] = cost[x];
	}
}

//初始化
void initialize() {
	totEdge = 0;
	memset(head, 0, sizeof(head));
	memset(totCover, 0, sizeof(totCover));
	memset(isroot, true, sizeof(isroot));
	memset(selected, false, sizeof(selected));
	memset(covered, false, sizeof(covered));
	memset(hasEdge, false, sizeof(hasEdge));
}

//输入数据
void inputdata() {
	int x, y;
	fscanf(fp, "%d", &n);
	for (int i = 1; i <= n; i++) {
		fscanf(fp, "%d", &x);
		fscanf(fp, "%lld", &cost[x]);
	}
	fscanf(fp, "%d", &m);
	for (int i = 1; i <= m; i++) {
		fscanf(fp, "%d%d", &x, &y);
		if (!hasEdge[x][y]) {
			hasEdge[x][y] = true;
			addEdge(x, y);
			isroot[y] = false;
		}
	}
}

//求解主过程
void solve() {
	int root;
	long long benefit, maxBenefit;
	
	for (int i = 1; i <= n; i++) {
		currentView = i;
		findCoveredView(i);
	}
	
	for (int i = 1; i <= n; i++)
		if (isroot[i]) {
			root = i;
			break;
		}
	
	S[0] = root;
	selected[root] = true;
	for (int i = 1; i <= n; i++)
		currentCost[i] = cost[root];
	
	//贪心算法主过程
	for (int i = 1; i <= K; i++) {
		maxBenefit = -1;
		currentView = 0;
		for (int j = 1; j <= n; j++)
			if (!selected[j]) {
				benefit = calcBenefit(j);
				if (maxBenefit < benefit) {
					maxBenefit = benefit;
					currentView = j;
				}
			}
		S[i] = currentView;
		selected[currentView] = true;
		update(currentView);
	}
}

//输出答案
void outputdata() {
	printf("%d", S[0]);
	for (int i = 1; i <= K; i++)
		printf(" -> %d", S[i]);
	printf("\n");
}

int main(int argc, char *argv[]) {
	if (argc < 5) {
		printf("Error!\n");
		return 1;
	}
	fp = NULL;
	K = -1;
	for (int i = 1; i < 5; i += 2) {
		if (strcmp(argv[i], "-f") == 0) {
			fp = fopen(argv[i + 1], "r");
		} else
		if (strcmp(argv[i], "-k") == 0) {
			sscanf(argv[i + 1], "%d", &K);
		} else {
			printf("Error!\n");
			return 1;
		}
	}
	if (fp == NULL || K < 0) {
		printf("Error!\n");
		return 1;
	}
	initialize();
	inputdata();
	solve();
	outputdata();
	fclose(fp);
	return 0;
}

