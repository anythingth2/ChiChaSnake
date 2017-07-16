

#include "iostream"
#include <windows.h>
#include <conio.h>




void setup();
void loop();


class Window {
public: int Window::width;
public:  int Window::height;
public :Window::Window(){}
public: Window::Window(int w,int h) {
	width = w;
	height = h;
}
		//TODO implement gotoxy()
public: static void Window::gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}
		//TODO implement wherex()
public: static int Window::wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD  result;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
	))
		return -1;
	return result.X;
}
		//TODO implement wherey()
public: static int Window::wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD  result;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
	))
		return -1;
	return result.Y;
}
};

class IO {
public: static const char UP = 'w';
public: static const char RIGHT = 'd';
public: static const char DOWN = 's';
public: static const char LEFT = 'a';

public:static int input() {
	char inputChar = getch();
	switch (inputChar) {
	case UP:
		return 1;
	case RIGHT:
		return 2;
	case DOWN:
		return 3;
	case LEFT:
		return 4;
	default:
		return 0;
	}

}

public:static void output(int x, int y) {
	Window::gotoxy(x, y);
	print(true);
}

public:static void clear(int x, int y) {
	Window::gotoxy(x, y);
	print(false);
}
	   //TODO implement print() to turnON or turnOFF pixelbrite bit
public:static void print(bool b) {
	//TODO random color bit while moving
	char ch = b ? rand()%('z'-'A')+'A' : ' ';
	std::cout << ch;
}

public:static bool isKeyboardHit() {
	return kbhit();
}

};
class Energy {
public:int x[10];
public:int y[10];
public:int numberEnergy;
public:static const int maxEnergy = 10;
public:Energy(int num) {
	numberEnergy = num;


}
public:void createRandomEnergy(Window window) {
	int xrand = rand() % window.width;
	int yrand = rand() % window.height;

	x[numberEnergy - 1] = xrand;
	y[numberEnergy - 1] = yrand;

	if (numberEnergy < 10 - 1)
		numberEnergy++;

	IO::output(xrand, yrand);

}

public:bool isEatEnergy(int xpos, int ypos) {
	for (int i = 0; i < numberEnergy; i++) {
		if (xpos == x[i] && ypos == y[i]) {

			numberEnergy--;
			for (int j = i; j<numberEnergy - i; j++)
			{
				x[j - 1] = x[j];
				y[j - 1] = y[j];
			}
			IO::clear(xpos, ypos);
			return true;
		}
	}
	return false;
}
};
class Snake {
	
public:int x, y;
public: int dir;
public:int length;
public:Window window;
public:Snake::Snake(int xpos, int ypos, int direction,int lengthlong,Window windowss) {
	x = xpos;
	y = ypos;
	dir = direction;
	length = lengthlong;
	window = windowss;
}
public:static const int UP = 1;
public:static const int RIGHT = 2;
public:static const int DOWN = 3;
public:static const int LEFT = 4;


public:void go(int inputDir) {
	switch (inputDir) {
	case Snake::UP:
		IO::clear(x, y);
		if(--y<0)
			y = window.height-1;
		IO::output(x, y);
		break;
	case Snake::RIGHT:
		IO::clear(x, y);
		if (++x > window.width)
			x = 0;
		IO::output(x, y);
		break;
	case Snake::DOWN:
		IO::clear(x, y);
		if (++y > window.height)y = 0;
		IO::output(x, y);
		break;
	case Snake::LEFT:
		IO::clear(x, y);
		if (--x < 0)
			x = window.width - 1;
		IO::output(x, y);
		break;
	default:
		break;
	}
	
	
}
};



Window window(10, 10);
Snake snake(0, 0, Snake::DOWN,3,window);
//TODO initilize size window

Energy energy(1);
int main()
{
	setup();
	while (true)
		loop();

	return 0;
}


void setup() {
	
	energy.createRandomEnergy(window);
}

void loop() {

	if (IO::isKeyboardHit()) {
		int inputDir = IO::input();

		if (inputDir == snake.dir) {
			//do nothing
		}
		else {
			switch (inputDir)
			{
			case Snake::UP:
				snake.dir = inputDir;
				break;
			case Snake::RIGHT:
				snake.dir = inputDir;
				break;
			case Snake::DOWN:
				snake.dir = inputDir;
				break;
			case Snake::LEFT:
				snake.dir = inputDir;
				break;
			default:
				break;
			}
		}
	}

	snake.go(snake.dir);
	if (energy.isEatEnergy(snake.x, snake.y)) {
		energy.createRandomEnergy(window);
		energy.createRandomEnergy(window);
	};

	Sleep(100);//TODO implement timetick
}




