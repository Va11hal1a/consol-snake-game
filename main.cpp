#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <stdio.h>

using namespace std;
//using namespace std::basic_ifstream;

const int _SIZE = 30;
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
	vec2():x(0), y(0){
	}
};

class snake{
public:
	vec2 head;
	vec2* body;
	vec2 direct;
	static const int _size = 20;
	int dinamic_size;
	snake(): head(_SIZE / 2, _SIZE / 2), direct(1, 0){
		body = new vec2[_SIZE];
		dinamic_size = 0;
	}
	void trace_to_display(display* disp){
		disp ->set(head.x, head.y, '@');
		for(int i = 0; i < dinamic_size; i++){
			disp -> set((body + i) -> x, (body + i) -> y, '*');
		}
	}
	void add_last(){
		int x, y; 
		if(dinamic_size >= 1){ x = body[dinamic_size - 1].x; y = body[dinamic_size - 1].y;}
		else {x = head.x; y = head.y;}
		body[dinamic_size].x =  x - direct.x;
		body[dinamic_size].y =  y - direct.y;
		dinamic_size++;
	}
	void move(){
		vec2* temp = new vec2[_size];
		for(int i = 0; i < dinamic_size; i++){
			temp[i] = body[i];
		}
		this -> body[0] = head;
		this -> head = vec2(head.x + direct.x, head.y + direct.y);
		for(int i = 1; i < dinamic_size; i++){
			body[i] = temp[i - 1];
	    }
		delete temp;
	}
	void dispose(){
		delete body;
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
	if(x+1 >= _SIZE || y+1 >= _SIZE || x < 0 || y < 0) return;
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

void controller(snake* snk){
	if(_kbhit()){
		char a = getch();
		switch(a){
		case 'd':
			snk -> direct = vec2(1, 0);
			break;
		case 'a':
			snk -> direct = vec2(-1, 0);
			break;
		case 's':
			snk -> direct = vec2(0, 1);
			break;
		case 'w':
			snk -> direct = vec2(0, -1);
			break;
		}
	}
}

class food_gen{
public:
	vec2 apple_pos;
	void check(snake* snk){
		if(snk -> head.x == apple_pos.x && snk -> head.y == apple_pos.y){
			generate();
			snk -> add_last();
		}
	}
	void generate(){
		do{
		apple_pos = vec2(rand() % _SIZE + 1, rand() % _SIZE + 1);
		}while(apple_pos.x >= _SIZE || apple_pos.y >= _SIZE || apple_pos.x <= 0 || apple_pos.y <= 0);
	}
	void draw(display* disp_handler){
		disp_handler -> set(apple_pos.x, apple_pos.y, '#');
	}
};

void start_menu(){

}

void save(){
	ofstream FILE;
	FILE.open("D:\data/saves/savemng.txt");
}

void load(){
	ifstream FILE("D:/data/saves/savemng.txt");
	if(!FILE.is_open()){
		cout << "Данного файла не существует";
	}
}

int main(){
	setlocale(LC_ALL, "rus");
	save();
	snake snk = snake();
	system("pause");
	food_gen fg = food_gen();
	snk.add_last();
	snk.add_last();
	snk.add_last();
	snk.add_last();
	fg.generate();
	display a;
	while(true){
	  controller(&snk);
	  a.begin();
	  snk.move();
	  snk.trace_to_display(&a);
	  fg.draw(&a);
	  fg.check(&snk);
	  a.push_buffer();
	  Sleep(500);
	  a.clr();
	}
	return 0;
	snk.dispose();
}