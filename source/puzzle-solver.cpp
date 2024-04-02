#include<iostream>
#include<vector>
#include<string.h>
#include<queue>
const int N = 200;
bool vis[N][N]; // // A*算法中检测是否走过此路径
const int n=N;// 地图的大小, 这里最大不能超过N这个常量的值

char Map[N][N];		// 输入的地图
class Position {
public:
	int x;
	int y;
	Position(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Position() {
		x = -1;
		y = -1;
	}
	bool operator==(const Position &a) {
		return (this->x == a.x) && (this->y == a.y);
	}
};
class Point {
public:
	int x, y;
	int f, g, h;
	bool operator==(const Point& pos) {
		return (pos.x == x && pos.y == y);
	}
	Point(const Position& pos) {
		x = pos.x;
		y = pos.y;
	}
	Point() {	}
	void geth(Point beginpos, Point endpos) {
		int x = std::abs(beginpos.x = endpos.x);
		int y = std::abs(beginpos.y - endpos.y);
		h = x + y;
	}
	
	void getf() {
		f = g + h;
	}
};
class TreeNode {
	
public:
	Point pos;
	TreeNode* pParent;
	std::vector<TreeNode*> pChild;
	
	
	TreeNode(Point pos) {
		this->pos = pos;
		pParent = nullptr;
	}
};
bool CanWalk(char ch[N][N], bool vis[N][N], const Point& pos)
{
	//如果越界，不能走
	if (pos.x <= 0 || pos.y <= 0 || pos.x > n || pos.y > n)
	{
		return false;
	}
	//越界
	
	if (ch[pos.x][pos.y] =='#'||ch[pos.x][pos.y]=='*'|| ch[pos.x][pos.y] == 'A')// 后面需要修改, 此处检测是否处于空地, 后续需要考虑寻路时路上的机器人
	{
		return false;
	}
	
	if (vis[pos.x][pos.y])
	{
		return false;
	}
	return true;//否则能走
}




std::vector<Position> GetPathbyPosition(Position start, Position end) {
	//返回一个vector, 其中
	//0代表向右
	//1代表向左
	//3代表向下
	//2代表向上 
	//如果需要得到两点间曼哈顿距离获取vector的size即可
	//初始化部分
	memset(vis, false, sizeof(vis));
	Point beginpos(start);
	Point endpos(end);
	TreeNode* pRoot = new TreeNode(beginpos);
	struct cmp {
		bool operator()(const TreeNode* a, const TreeNode*b) {
			return a->pos.f > b->pos.f;
		}
	};
	std::priority_queue<TreeNode*,std::vector<TreeNode*>,cmp> buff;//暂存探索过的点
	TreeNode* pCurrent = pRoot;
	TreeNode* pTemp = nullptr;
	bool isfind = false;
	//初始化结束
	std::vector<Position> Path;

	while (1) {
		
		
		for (int i = 0; i <= 3; i++) {
			pTemp = new TreeNode(pCurrent->pos);
			switch (i)
			{
				case 2://up
				pTemp->pos.x--;
				pTemp->pos.g += 1;
				break;
				case 3://down
				pTemp->pos.x++;
				pTemp->pos.g += 1;
				break;
				case 1://left
				pTemp->pos.y--;
				pTemp->pos.g += 1;
				break;
				case 0://right
				pTemp->pos.y++;
				pTemp->pos.g += 1;
				break;
				
			}
			if (CanWalk(Map, vis, pTemp->pos)) {
				pTemp->pos.geth(pTemp->pos, endpos);
				pTemp->pos.getf();
				pCurrent->pChild.push_back(pTemp);
				pTemp->pParent = pCurrent;
				buff.push(pTemp);
				
				vis[pTemp->pos.x][pTemp->pos.y] = true;
			}
			else {
				delete pTemp;
				pTemp = nullptr;
			}
		}

		if (buff.size()==0) {
			//如果寻找失败,无路可走
			return std::vector<Position>();
		}
		
		else {
			pCurrent = buff.top();
			buff.pop();//弹出该点, 说明其已经被寻找过
		}
		
		if (pCurrent->pos == endpos) {//找到了
			isfind = true;
			
			break;
		}

	}

	if (isfind) {
		while (pCurrent != nullptr) {
			Position tmp(pCurrent->pos.x, pCurrent->pos.y);
			Path.push_back(tmp);
			pCurrent = pCurrent->pParent;
		}

	}
	
	return Path;
}

std::vector<std::string>ConvertToOperationCodeByPostion(std::vector<Position> Path, std::string opCode[4] ){
	
	
	
	std::vector<std::string>anspath;
	Position startcpy = Path.back();
	Path.pop_back();
	while (!Path.empty()) {
		auto tmp = Path.back();
		Path.pop_back();
		if ((startcpy.x - tmp.x) > 0) {
			
			anspath.push_back(opCode[2]);	
		}
		else if ((startcpy.x - tmp.x) < 0) {
			anspath.push_back(opCode[3]);
		}
		else if ((startcpy.y - tmp.y) > 0) {
			anspath.push_back(opCode[1]);
		}
		else if ((startcpy.y - tmp.y) < 0) {
			anspath.push_back(opCode[0]);
		}
		startcpy = tmp;
	}
	return anspath;
}

int main(){
	
	// if not assign opCode 
	// 		use default opCode
	//	    std::string opCode[5]={'0','1','2','3'};  
	//2 means up  ,3 means down ,0 means right ,1 means left  
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> Map[i][j];
		}
	}
	Position st(19,127);
	Position ed(12,104);
	
	auto p=GetPathbyPosition(st,ed);	
	
	
	for(auto i:p){
		std::cout<<i.x<<" "<<i.y<<std::endl;
		
	}
}
