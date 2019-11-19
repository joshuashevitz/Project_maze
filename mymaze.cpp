//maze program
//Joshua Shevitz
//9/23/19

#include <iostream>
#include <stack>

constexpr auto N = 20;

using namespace std;
struct node {
	int data;
	node* next;
};

class linked {

private:
	node* head;
	node* tail;
public:
	linked() {
		head = NULL;
		tail = NULL;
	}
	node* gethead() {
		return head;
	}
	void create(int n) {
		node* temp = new node;
		temp->data = n;
		temp->next = NULL;
		if (head == NULL) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			tail = tail->next;
		}
	}
	void display() {
		node* temp;
		temp = head;
		while (temp != NULL) {

			cout << "(" << temp->data << ", ";
			temp = temp->next;
			cout << temp->data << ") ";
			temp = temp->next;
		}
	}
	void createathead(int n) {
		node* temp = new node;
		temp->data = n;
		temp->next = head;
		head = temp;
	}
	void deletion(node* current, int position) {
		node* temp;
		temp = current;
		node* next;
		next = temp->next;
		if (position == 0) {
			head = current->next;
			delete current;

		}
		while (next->data != position) {
			current = current->next;
		}
		temp->next = next->next;
		delete next;


	}
};

void printmaze(int maze[20][20]) {
	int i, j;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++) {
			if (maze[i][j] == 2)
				cout << "E";
			else
				cout << maze[i][j];
		
		}
		cout << endl;
	}
}

int solarr[N][N];
int visited[N][N];

void presol(int visited[N][N]) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			visited[i][j] = 1;
		}
	}
}

bool safe(int arr[N][N], int row, int col) {
	if (row >= 0 && row < N && col >= 0 && col < N && arr[row][col] != 1) {
		return true;
	}
	else {
		return false;
	}
}

bool reachable(int arr[N][N], int sol[N][N], int row, int col) {
	if (safe(arr, row, col) == true && sol[row][col] != 0) {
		return true;
	}
	else {
		return false;
	}
}
bool stuck(int arr[N][N], int sol[N][N], int row, int col) {
	if (reachable(arr, sol, row - 1, col) == false && reachable(arr, sol, row, col-1) == false && reachable(arr, sol, row + 1, col) == false && reachable(arr, sol, row, col+1) == false) {
		return true;
	}
	else {
		return false;
	}
}

void printsol(int sol[N][N],int maze[N][N]) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (maze[i][j] == 2) {
				cout << "E" << " ";
			}
			else if (sol[i][j] == 0) {
					cout << "+" << " ";
				}
			else if (sol[i][j]==3) {
				cout << "S" << " ";
			} else{
					cout << sol[i][j] << " ";
				}
			}
			cout << endl;
	}
}
//i created 2 stacks instead of using a node 
//because it helped me visualize and track what was going on
//otherwise, would have create a node stack and pushed
//the (x,y) cordinates using that. hope this is alright.
stack<int> x;
stack <int> y;
int traverse(int maze[N][N], int solarr[N][N], int visited[N][N],  int row, int col) {
	
	x.push(row);
	y.push(col);
	
	while (!x.empty() || maze[row][col] != 2) {
		x.pop();
		y.pop();

		if (safe(maze, row, col)) {
			solarr[row][col] = 0;
			if (reachable(maze,visited, row - 1, col)) {
				visited[row - 1][col] = 0;
				x.push(row - 1);
				y.push(col);
				return traverse(maze, solarr, visited, row - 1, col);
			}
			else {
				if (reachable(maze, visited, row, col - 1)) {
					visited[row][col-1] = 0;
					x.push(row);
					y.push(col-1);
					return traverse(maze, solarr,visited,row, col - 1);
				}else {
						if (reachable(maze, visited, row + 1, col)) {
							visited[row+1][col] = 0;
							x.push(row+1);
							y.push(col);
							return traverse(maze, solarr, visited, row + 1, col);
						}
				else {
							if (reachable(maze, visited, row, col + 1)) {
								visited[row][col + 1] = 0;
								x.push(row);
								y.push(col+1);
								return traverse(maze, solarr, visited, row, col + 1);
							}
							else {
							

								solarr[row][col] = 1;
								x.pop();
								y.pop();
								
								row = x.top();
								col = y.top();
								return traverse (maze, solarr, visited, row, col);
							}
					}
				}
			}
		}
		else {
			cout << "\nthat's a wall" << endl;
			break;
		}
	 
	 
	}
	if (maze[row][col]==2) {

		cout << "\nwe're free!" << endl;
	}
	else {
		if (stuck(maze, visited, row, col) == true) {
			cout << "\nwe're trapped!" << endl;

		}
	}
	return -1;
}

	
int main() {
	linked list;

	int temp1, temp2;
	int row, col, E=2, X=3, maze[20][20] = {
	{E, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
	{1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0},
	{0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0},
	{1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
	{1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
	{0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
	{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1},
	{0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1},
	{1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0},
	{0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1},
	{1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0},
	};
	
	printmaze(maze);
	cout << "\n\nplease select starting point,\nusing 1-20 for rows and 1-20 for columns.\n\n";
	presol(solarr);
	presol(visited);
	cin >> row; 
	cin >> col;
	
	
	traverse(maze, solarr, visited, row-1, col-1);
	solarr[row-1][col-1] = X;
	printsol(solarr, maze);
	
	while (!y.empty()) {
		int temp1, temp2;
		temp1 = x.top();
		temp2 = y.top();
		x.pop();
		y.pop();
		list.createathead(temp1);
		list.createathead(temp2);
	}
	list.display(); 

	
	
	return 0;
}