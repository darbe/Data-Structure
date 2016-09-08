#include<iostream>
#include<vector>
#include<set>
#include<climits>
#include<sstream>
#include<fstream>

using namespace std;
class Point{

	friend bool operator==(const Point &p1, const Point &p2);
	friend bool operator!=(const Point &p1, const Point &p2);
	public:
	   	Point(int p_x, int p_y):x(p_x),y(p_y){}
		int getx(){return x;}
		int gety(){return y;}
		bool operator < (const Point & p)const{
			return x < p.x;
		}
	private:
		int x;
		int y;
};

class Vertex{
	public :
		Vertex(int nnode):nnode(nnode){
			selected = new int[nnode];
			index = new int[nnode];
			neibor = new int[nnode];
			nodes = new int[nnode];
		}
		bool operator < (const Vertex &v){
			return lefte < v.lefte;
		}
		int *selected;
		int *index;
		int *neibor;
		int *nodes;
		int leftp;
		int lefte;
		int nnode;

};

class Comp{
	public:
		bool operator()(const std::vector<Point> &points1, const std::vector<Point> &points2)const{
		    std::vector<Point>::const_iterator v1 = points1.begin();
			std::vector<Point>::const_iterator v2 = points2.begin();
			while(v1 != points1.end() && v2 != points2.end()){
				if(*v1++ != *v2++){
					return false;
				}
			}
			if(v1 != points1.end() || v2 != points2.end()){
				return false;
			}
			return true;
		}
};
void minHeapify(std::vector<Vertex>points, int i, int n){
	int left = 2 * i;
	int right = 2 * i + 1;
	int smallest  = 0;
	cout << "left " << left << "right "<< right<< endl;
	if(left <= n && points[left] < points[i]){
		smallest = left;
	}else{
		smallest = i;
	}
	if(right <= n && points[right] < points[smallest]){
		smallest = right;
	}
	if(smallest != i){
		swap(points[smallest],points[i]);
		minHeapify(points,smallest,n);
	}
}

void buildMinHeap(std::vector<Vertex> points){
	cout << "size "<< points.size()<<endl;
	for(int i = (points.size()-1)/2; i >=1 ; i--){
		cout << "i "<< i <<endl;
		minHeapify(points,i,points.size()-1);
	}
}
Vertex heapExtractMin(std::vector<Vertex>points){
	int n = points.size();
	if(n < 2){
		std::cout << "empty heap" << std::endl;
		exit(0);
	}
	Vertex min = points[1];
	points[1] = points[n];
	points.pop_back();
	minHeapify(points,1,points.size()-1);
	return min;
}
void heapDecreaseKey(std::vector<Vertex>points, int i, Vertex key,int keyval,int n){
	if(n < i){
		std:: cout << "Wrong insert "<< n <<" "<< i<< std::endl;
		exit(-1);
	}
	if(key < points[i].lefte){
		std::cout<<"new key is smaller"<<std::endl;
	}
	points[i].lefte = keyval;
	while(i > 1 && points[i] < points[i/2]){
		swap(points[i],points[i/2]);
		i /= 2;
	}
}


void minHeapInsert(std::vector<Vertex>points, Vertex key){
	int keyval = key.lefte;
	cout << "insert "<< keyval << endl;
	key.lefte = INT_MAX;
	points.push_back(key);
	heapDecreaseKey(points,points.size(),key,keyval,points.size()-1);
}
bool emptyHeap(std::vector<Vertex>points){
	if(points.size() == 1){
		return true;
	}
	return false;
}



bool operator==(const Point &p1, const Point &p2){
		return p1.x == p2.x && p1.y == p2.y;
}
bool operator!=(const Point &p1, const Point &p2){
		return !(p1 == p2);
}
class Matrix{
	friend ostream &operator<<(ostream &os, const Matrix &matrix);
	friend istream& operator>>(istream &is,   Matrix &m);
	friend Matrix operator^(const Matrix &m1, const Matrix &m2);
	friend bool candidatePoint(const Matrix &m1, const Matrix &m2, Matrix mmxor,std::vector<int> &points, std::set<int> &c);
	public:
		Matrix(int r, int c):N(r),M(c){
			matrix = new int*[N];
			for(int i = 0; i < N; i++){
				matrix[i] = new int[M];
			}
		}


	private:
		int N;
		int M;
		int **matrix;
	
};
ostream& operator<<(ostream &os,  const Matrix &m){
	for(int i = 0; i < m.N; i++){
		for(int j = 0; j < m.M; j++){
			os << m.matrix[i][j] << " " ;
		}
		os  << std::endl;
	}
	return os;
}

istream& operator>>(istream &is,   Matrix &m){
	for(int i = 0; i < m.N; i++){
		for(int j = 0; j < m.M; j++){
			is >> m.matrix[i][j] ;
		}
	}
	return is;
}

Matrix operator^(const Matrix &m1, const Matrix &m2){
	Matrix tmp = Matrix(m1.N,m2.M);
	for(int i =0; i < tmp.N; i++){
		for(int j = 0; j < tmp.M; j++){
			tmp.matrix[i][j] = m1.matrix[i][j] ^ m2.matrix[i][j];
		}
	}
	return tmp;
}

bool candidatePoint(const Matrix &m1, const Matrix &m2, const Matrix mxor, std::vector<int> &points,std::set<int> &c){
	bool iszero = true;
	for(int i =0; i < m1.N; i++){
		for(int j = 0; j < m1.M; j++){
			if(m1.matrix[i][j] &  mxor.matrix[i][j]){
				iszero = false;
				//cout << i << j << endl;
				points.push_back(i * m1.M + j);
				c.insert(i *m1.M + j);
			}
		}
	}
	if(iszero){
		for(int i =0; i < m2.N; i++){
			for(int j = 0; j < m2.M; j++){
				if(m2.matrix[i][j] &  mxor.matrix[i][j]){
					points.push_back(i * m2.M +j);
					c.insert(i * m2.M + j);
				}
			}
		}
	}
	return iszero;
}

void print(Point & p){	
	cout << p.getx()<< " "<<p.gety()<<endl;
}

int partition(int *nums, int p, int r, int*nums2){
	int x = nums[r];
	int i = p-1;
	for(int j = p; j < r; j++){
		if(nums[j] >= x){
			i++;
			swap(nums[i],nums[j]);
			swap(nums2[i],nums2[j]);
		}
	}
	swap(nums[i+1],nums[r]);
	swap(nums2[i+1],nums2[r]);
	return i+1;
}
void quickSort(int *nums, int p ,int r,int *nums2){
	if(p < r){
		int q = partition(nums,p,r,nums2);
		quickSort(nums,p,q-1,nums2);
		quickSort(nums,q+1,r,nums2);
	}
}
int totalkneibor(int *neibor, int k, int *nodes, int *selected,int nnode){
	//for(int i = 0; i < nnode; i++){
//		cout<< "i " << i<<"n "<< nodes[i]<<endl;
//	}
	quickSort(neibor,0,nnode-1,nodes);
//	for(int i = 0; i < nnode; i++){
//		cout<< "i " <<i<< "n "<< nodes[i]<<endl;
//	}
	int total = 0;
	for(int i = 0; i < nnode; i++){
		if(selected[nodes[i]] == 0 && k > 0){
			total += neibor[i];
			k--;
			if(k <= 0){
				break;
			}
		}
	}
	return total;
}
bool validbranch(int *neibor, int k, int e, int *nodes, int *selected,int nnode){
	int t = totalkneibor(neibor,k,nodes,selected,nnode);
	cout << "t " << t<< "e "<< e<<endl;
	return t >= e;
}
inline int max(int &a, int &b){
	return a > b ? a : b;
}
inline int min(int &a, int &b){
	return a <= b ? a : b;
}
int extractset(std::vector<Matrix>& matrixes,int P,std::set<std::vector<int>> &s){
	//std::set<Point>siglepoint; 
	int i, j;
	std::set<int> countpoints;
	for(i = 0; i < P-1; i++){
		for(j = i+1; j < P; j++){
			Matrix mxor = matrixes[i]^matrixes[j];
			vector<int>points;
			cout << "-------"<< endl;
			cout << mxor;
			cout << endl;
			cout << "---------"<<endl;
			candidatePoint(matrixes[i],matrixes[j],mxor,points,countpoints);
	//		if(points.size() == 1){
	//			siglepoint.insert(points[0]);
	//		}else if(points.size() > 1){
				s.insert(points);
	//		}
		}
	}
	if(countpoints.size() == 0){
		return -1;
	}
	std::set<int>::iterator s_it = countpoints.end();
	int nnode = *(--s_it)+1;
	//int nnode = find[countpoints.size()-1]+1;
	cout << nnode << endl;
	return nnode;
/*
	int **graph = new int*[nnode];
	int *neibor = new int[nnode];
	int *selected = new int[nnode];
	int *nodes = new int[nnode];
	for(i = 0 ; i < nnode; i++){
		graph[i] = new int[nnode];
	}
	for(i = 0 ; i < nnode; i++){
		neibor[i] = 0;
		selected[i] = 0;
		nodes[i] = i;
	}
	for(i = 0; i < nnode; i++){
		for(j = 0; j < nnode; j++){
			graph[i][j] = 0;
		}
	}
	int e = 0;
	int k = 2;
	std::set<vector<int>>::iterator points_it = s.begin();
	while(points_it != s.end()){
		const std::vector<int> &tmp_points = *points_it;
		for(i = 0 ; i < tmp_points.size(); i++){
			for(j = i+1; j < tmp_points.size(); j++){
				int a = tmp_points[i];
				int b = tmp_points[j];
				graph[min(a,b)][max(a,b)] = 1;
				e ++;
				neibor[a]++;
				neibor[b]++;
			}
		}
		points_it++;
	}
	*/
//	bool flag = validbranch(neibor,k,e,nodes,selected,nnode);
//	if(!flag){
//		return;
//	}
	
	//for(i = 0; i < nnode; i++){
	//	for(j = 0; j < nnode; j++){
	//		cout << i << " "<< j << " "<< graph[i][j]<< endl;
	//	}
//	}	
			

	/*std::set<vector<Point>>::iterator points_it = s.begin();
	bool isdelete = false;
	while(points_it != s.end()){
		isdelete = false;
		const std::vector<Point> &tmp_points = *points_it;
		std::vector<Point>::const_iterator point_it = tmp_points.begin();
		while(point_it != tmp_points.end()){
			if(siglepoint.find(*point_it) != siglepoint.end()){
				points_it = s.erase(points_it);
				isdelete = true;
				break;
			}
			point_it++;
		}
		if(!isdelete){
			points_it++;
		}
	}*/
}
void adjustIndex(int *nodes, int *indexs,int nnode)	{
	for(int i = 0; i < nnode;i++){
		indexs[nodes[i]] = i;
	}
}

int nextNode(int *selected, int *nodes, int nnode){
	for(int i = 0; i < nnode; i++){
		cout << "i "<< i<< "node[i] "<<nodes[i]<< "select[] "<<selected[nodes[i]]<<endl;
		if(selected[nodes[i]] == 0){
			return nodes[i];
		}
	}
	return -1;
}
Vertex Left(Vertex curv,int nextindex,int nnode,int ** graph){
	Vertex left(nnode);
	left.leftp = curv.leftp - 1;
	left.lefte = curv.lefte;
	for(int i = 0; i < nnode; i++){
		left.index[i] = curv.index[i];
		left.selected[i] = curv.selected[i];
		left.neibor[i] = curv.neibor[i];
		left.nodes[i] = curv.nodes[i];
	}
	int total = 0;
	int i,j;
	for(int i = 0; i < nnode; i++){
		if(nextindex < i && left.selected[i] != 1 && graph[nextindex][i] == 1){
			total++;
			left.neibor[left.index[i]]--;
		}else if(nextindex > i && left.selected[i] != 1 && graph[i][nextindex] == 1){
			total++;
			left.neibor[left.index[i]]--;
		}
	}
	left.selected[nextindex] = 1;
	left.neibor[left.index[nextindex]] = 0;
	quickSort(left.neibor,0,nnode-1,left.nodes);
	adjustIndex(left.nodes,left.index,nnode);
	return left;
}

Vertex Right(Vertex curv,int nextindex,int nnode,int **graph){
	Vertex right(nnode);
	right.leftp = curv.leftp - 1;
	right.lefte = curv.lefte;
	for(int i = 0; i < nnode; i++){
		right.index[i] = curv.index[i];
		right.selected[i] = curv.selected[i];
		right.neibor[i] = curv.neibor[i];
		right.nodes[i] = curv.nodes[i];
	}
	right.selected[nextindex] = -1;
	return right;
}

int greedy(int *neibor, int *nodes,int k,int e,int **graph,int nnode){
	Vertex v(nnode);
	v.leftp = k;
	v.lefte = e;
	for(int i = 0; i < nnode; i++){
		v.selected[i] = 0;
		v.index[i] = 0;
		v.neibor[i] = neibor[i];
		v.nodes[i] = nodes[i];
	//	cout << "i "<< i<< "node[i] "<<v.nodes[i]<<endl;
	}

	/*****free()*******/

	adjustIndex(v.nodes,v.index,nnode);
	vector<Vertex> vnodes;
	vnodes.push_back(v);
	vnodes.push_back(v);
	buildMinHeap(vnodes);

	cout << " k " << k << "e "<<e<< endl;
	while(!emptyHeap(vnodes)){
		Vertex curv = heapExtractMin(vnodes);
		if(curv.lefte == 0){
			return k-curv.leftp;
		}
		int nextindex = nextNode(curv.selected,curv.nodes,nnode);
		if(nextindex != -1){
			Vertex left = Left(curv,nextindex,nnode,graph);
			Vertex right = Right(curv,nextindex,nnode,graph);
			if(validbranch(left.neibor,left.leftp,left.lefte,left.nodes,left.selected,nnode)){
				minHeapInsert(vnodes,left);
			}
			if(validbranch(right.neibor,right.leftp,right.lefte,right.nodes,right.selected,nnode)){
				minHeapInsert(vnodes,right);
			}
	cout << "*******3*"<<endl;
		}
	}
	return -1;
}

void setGraph(std::set<vector<int>>& s, int **&graph, int* &neibor, int* &selected,int* &nodes,int &e,int nnode){
	graph = new int*[nnode];
	neibor = new int[nnode];
	selected = new int[nnode];
	nodes = new int[nnode];
	int i ,j;
	for(i = 0 ; i < nnode; i++){
		graph[i] = new int[nnode];
	}
	for(i = 0 ; i < nnode; i++){
		neibor[i] = 0;
		selected[i] = 0;
		nodes[i] = i;
	}
	for(i = 0; i < nnode; i++){
		for(j = 0; j < nnode; j++){
			graph[i][j] = 0;
		}
	}
	std::set<vector<int>>::iterator points_it = s.begin();
	while(points_it != s.end()){
		const std::vector<int> &tmp_points = *points_it;
		for(i = 0 ; i < tmp_points.size(); i++){
			for(j = i+1; j < tmp_points.size(); j++){
				int a = tmp_points[i];
				int b = tmp_points[j];
				graph[min(a,b)][max(a,b)] = 1;
				e++;
				neibor[a]++;
				neibor[b]++;
			}
		}
		points_it++;
	}
}
int init(std::vector<Matrix> &matrixes){
	int N, M , P;
	int i,j;
	//ifstream map_file("map_file");
	//ifstream input("input");
	//string text;
	//getline(input,text);
	//istringstream stream(text);
	//stream >> N >> M >> P;
	//cout << "N "<< N << "M "<<M<< "P " << P<<endl;
	//getline(input,text);
	std::cin >> N >> M >> P;
	for(i = 0; i < P; i++){
		Matrix m = Matrix(N,M);
	//	getline(input,text);
	//	istringstream stream(text);
	//	stream >> m;
	//	cout << m<<endl;	
		std::cin >> m;
		matrixes.push_back(m);
		//getline(input,text);
	}
	std::cout << std::endl;
	return P;
}
int minPoint(){
	int k=1;
	std::vector<Matrix> matrixes;
	int P = init(matrixes);
	std::set<std::vector<int>> s;
	int nnode = extractset(matrixes,P,s);
	if(nnode == -1){
		return 0;
	}
	int **graph;
	int *neibor;
	int *selected;
	int *nodes;
	int edges = 0;
	
	setGraph(s,graph,neibor,selected,nodes,edges,nnode);
	for(int i = 0; i < nnode; i++){
		for(int j = 0; j < nnode; j++){
			cout << i << " "<< j << " "<< graph[i][j]<< endl;
		}
	}
	s.clear();
	bool flag = validbranch(neibor,k,edges,nodes,selected,nnode);
	if(!flag){
		return -1;
	}
    
	int diffpoint = greedy(neibor,nodes,k,edges,graph,nnode);
	cout << "min point is diffpoints" <<endl;
	return diffpoint;

}







int main(){
	minPoint();
}
