#include <iostream>

using namespace std;

const int _SIZE = 20;
const int _BORDER_WIDTH = 1;
const char WALL = '#';

class display{
public:
	char buffer[_SIZE][_SIZE];
	void begin();
	void push_buffer();
	void set(int x, int y, char s);
	void clr();
};

struct vec2{
	int x, y;
public:
	vec2(int x, int y){
		this -> x = x;
		this -> y = y;
	}
};

class snake{
public:
	vec2 head;
	vec2* body;
	vec2 direct;
	static const int _size = 20;
	int dinamic_size;
	snake(): head(_SIZE / 2, _SIZE / 2), direct(0, 1){
		body = (vec2*) malloc(_size);
		dinamic_size = 0;
	}
	void trace_to_display(display* disp){
		disp ->set(head.x, head.y, '@');
		for(int i = 0; i < dinamic_size; i++){
			disp -> set((body + i) -> x, (body + i) -> y, '*');
		}
	}
	void add_last(){
		dinamic_size++;
		int x = (body + dinamic_size - 1) -> x;
		int y = (body + dinamic_size - 1) -> y;
		(body + dinamic_size) -> x = x - direct.x;
		(body + dinamic_size) -> y = y - direct.y;
	}
};

void display::begin(){
	for(int x = 0; x < _SIZE; x++){
		for(int y = 0; y < _SIZE; y++){
			buffer[x][y] = ' ';
		}
	}
}

void display::clr(){
	system("cls");
}

void display::set(int x, int y, char s){
	if(x+1 >= _SIZE || y+1 >= _SIZE) return;
	buffer[x+1][y+1] = s;
}

void display::push_buffer(){
	for(int y = 0; y < _SIZE + _BORDER_WIDTH * 2; y++){
		for(int x = 0; x < _SIZE + _BORDER_WIDTH * 2; x++){
			if(x < _BORDER_WIDTH || x > _SIZE || y < _BORDER_WIDTH || y > _SIZE){
				cout << WALL;
			}
			else if(x < _SIZE && y < _SIZE) cout << buffer[x][y];
			else cout << " ";
		}
		cout << "" << endl;
	}
}


int main(){
	snake snk = snake();
	snk.add_last();
	snk.add_last();
	display a;
	while(true){
	a.begin();
	a.set(0,0,'a');
	snk.trace_to_display(&a);
	a.push_buffer();
	a.clr();
	}
	return 0;
}