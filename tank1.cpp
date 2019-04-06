#include<iostream>
#include<windows.h> 
#include<conio.h>
using namespace std;
DWORD WINAPI com(PVOID ptank);
DWORD WINAPI attack(PVOID ptank);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CRITICAL_SECTION  cs;
class zidan *qzd;
class tank *ptan;
template<class T>
class toz
{
	T* head;
	public:
		toz()
		{
			head = NULL;
		}
		void push(T& d)
		{
			d.next = head;
			head = &d;
		}
		T* pop(const T& d)
		{
				T* p = head;
				if(*head == d)
				{
					head = head -> next;
					return p;
				}
				while(p)
				{
					if(*(p -> next) == d)
					{
						T* p2;
						p2 = p -> next;
						p -> next = p -> next -> next;
						return p2;
					}
					p = p -> next;
				}
				return NULL;				
		}
		T* gethead()
		{
			return head;
		}
};
toz<tank> bomp;
toz<zidan> bing;
void gotoxy(int x, int y)
{
    COORD pos = {x,y};
    
    SetConsoleCursorPosition(hConsole, pos);

}

void Hide_Cursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
    SetConsoleCursorInfo(hConsole, &cursor_info);
}

void SetColor(int color)
{
    SetConsoleTextAttribute(hConsole, color);
}

class tank 
{
	int x;
	int y;
	int exe;
	int level;
	int speed;
	int fullblood;
	int blood;
	int fire;
	int defense;
	int life;
	char dir;
	char dired;
	int cop;  //0£ºcom; 1:1p; 2:2p;  
	int money;
	int fullexe;
	public:
		tank* next;
		friend class zidan;
		tank()
		{
			x = 0;
			y = 0;
			dir = 's';
			dired = dir;
			level = 0;
			exe = 0;
			fullexe = 1;
			life = 1;
			fullblood = 1;
			blood = fullblood;
			money = 0;
			fire = 1;
			defense = 0;
			speed = 1;
			cop = 0;
			bomp.push(*this);
		}
		tank(int a, int b, char c, int d, int e)
		{
			x = a;
			y = b;
			dir = c;
			dired = dir;
			level = d;
			exe = 0;
			fullexe = 1;
			fullexe += level;
			life = 1;
			fullblood = 1;
			fullblood += 1 + level / 5;
			blood = fullblood;
			money = 0;
			fire = 1;
			fire += 1 + level / 4;
			defense = 0;
			defense += level / 5;
			speed = 1;
			speed += 1 + level / 5;
			cop = e;
			bomp.push(*this);
			if(cop)
			{
				pprint();
			}
			else
			{
				HANDLE ctank = CreateThread(NULL, 0, com, this, 0, NULL);
			}
		}
		tank(const tank& b)
		{
			x = b.x;
			y = b.y;
			dir = b.dir;
			dired = dir;
			level = b.level;
			exe = b.exe;
			fullexe = b.fullexe;
			money = b.money;
			life = b.life;
			fullblood = b.fullblood;
			blood = b.fullblood;
			fire = b.fire;
			defense = b.defense;
			speed = b.speed;;
			cop = b.cop;
			bomp.push(*this);
			if(cop)
			{
				pprint();
			}
			else
			{
				HANDLE ctank = CreateThread(NULL, 0, com, this, 0, NULL);
			}
		}
		~tank()
		{
		}
		void lvu()
		{
			exe ++;
			if(exe == fullexe)//fullexe += level / 2;
			{
				fullexe += level;
				life += level / 6;
				fullblood += 1 + level / 5;
				blood = fullblood;
				fire += 1 + level / 4;
				defense += 1 + level / 5;
				speed += 1 + level / 5;
				exe = 0;
			}
			
		}
		void gj(const tank& a)
		{
			int df = a.fire - defense;
			if(df < 0)
			{
				df = 0;
			}
			blood -= 1 + df;
			if(blood < 0)
			{
				life --;
			}
			
		}
		void dele()
		{
			if(cop)
			{
				if(dir == 'w' || dir == 'W')
		{
			gotoxy(x, y - 1);
			cout << " " ;
			gotoxy(x - 2, y);
			cout << "     "; 
			gotoxy(x - 2, y + 1);
			cout << "     ";
		}
		if(dir == 's' || dir == 'S')
		{
			gotoxy(x - 2, y - 1);
			cout << "     ";
			gotoxy(x - 2, y);
			cout << "     "; 
			gotoxy(x, y + 1);
			cout << " " ;
		}
		if(dir == 'd' || dir == 'D')
		{
			gotoxy(x - 2, y - 1);
			cout << "   " ;
			gotoxy(x - 2, y);
			cout << "     ";
			gotoxy(x - 2, y + 1);
			cout << "   ";
		}
		if(dir == 'a' || dir == 'A')
		{
			gotoxy(x , y - 1);
			cout << "   " ;
			gotoxy(x - 2, y);
			cout << "     ";
			gotoxy(x, y + 1);
			cout << "   ";
		}
//		LeaveCriticalSection(&cs);
	}
	else
	{
		EnterCriticalSection(&cs);
	if(dir == 'w' || dir == 'W')
	{
		gotoxy(x, y - 1);
		cout << " " ;
		gotoxy(x, y);
		cout << " "; 
	}
	if(dir == 's' || dir == 'S')
	{
		gotoxy(x, y);
		cout << " " ;
		gotoxy(x , y + 1);
		cout << " "; 
	}
	if(dir == 'a' || dir == 'A')
	{
		gotoxy(x, y);
		cout << " " ;
		gotoxy(x - 2, y);
		cout << " "; 
	}
	if(dir == 'd' || dir == 'D')
	{
		gotoxy(x, y);
		cout << " " ;
		gotoxy(x + 2, y);
		cout << " "; 
	}
	LeaveCriticalSection(&cs);
	}
			
		}
		void showmsg()
		{
			EnterCriticalSection(&cs);
			gotoxy(65, 0);
			cout << "player:";
			gotoxy(65, 2);
			cout << "life: " << life;
			gotoxy(65, 3);
			cout << "blood: " << blood << " / " << fullblood;
			gotoxy(65, 5);
			cout << "level: " << level;
			gotoxy(65, 6);
			cout << "exe: " << exe << " / " << fullexe;
			gotoxy(65, 7);
			cout << " money: " << money;
			LeaveCriticalSection(&cs);
		}
		void pmove()
		{
			EnterCriticalSection(&cs);
			if((dir == 'w' || dir == 'W') && y >= 2)
			{
		if(dired != 'w' || dired != 'W')
		{
			gotoxy(x - 1, y - 1);
			cout << " ¡ü ";
			gotoxy(x - 3, y);
			cout << " ¨Š¡ò¨‡ " ;
			gotoxy(x - 2, y + 1);
			cout << "¨Š©Ü¨‡";
		}
		if(dired == 'w' || dired == 'W')
		{
			y --;
			gotoxy(x, y - 1);
			cout << "¡ü" ;
			gotoxy(x - 2, y);
			cout << "¨Š¡ò¨‡"; 
			gotoxy(x - 2, y + 1);
			cout << "¨Š©Ü¨‡";
			gotoxy(x - 1, y + 2);
			cout << "    ";
		}
		dired = 'w';
	}
	if((dir == 's' || dir == 'S') && y <= 21)
	{
		if(dired != 's' || dired != 'S')
		{
			gotoxy(x - 2, y - 1);
			cout << "¨Š©Ô¨‡";
			gotoxy(x - 2, y);
			cout << "¨Š¡ò¨‡"; 
			gotoxy(x - 1, y + 1);
			cout << " ¡ý " ;
		}
		if(dired == 's' || dired == 'S')
		{
			y ++;
			gotoxy(x, y + 1);
			cout << "¡ý" ;
			gotoxy(x - 2, y);
			cout << "¨Š¡ò¨‡"; 
			gotoxy(x - 2, y - 1);
			cout << "¨Š©Ô¨‡";
			gotoxy(x - 1, y - 2);
			cout << "    ";
		}
		dired = 's';
	}
	if((dir == 'a' || dir == 'A') && x >= 4)
	{
		if(dired != 'a' || dired != 'S')
		{
			gotoxy(x - 1, y - 1);
			cout << " ¨x¨x" ;
			gotoxy(x - 2, y);
			cout << "¡û¡ò©Ì";
			gotoxy(x - 1, y + 1);
			cout << " ¨‰¨‰";
		}
		if(dired == 'a' || dired == 'A')
		{
			x --;
			gotoxy(x , y - 1);
			cout << "¨x¨x" ;
			gotoxy(x - 2, y);
			cout << "¡û¡ò©Ì";
			gotoxy(x, y + 1);
			cout << "¨‰¨‰";
			for( int i = -1; i <= 1; i ++)
			{
				gotoxy(x + 5, y + i);
				cout << ' ';
			}
		}
		dired = 'a';
	}
	if((dir == 'd' || dir == 'D') && x <= 60)
	{
		if(dired != 'd' || dired != 'D')
		{
			gotoxy(x - 2, y - 1);
			cout << "¨x¨x " ;
			gotoxy(x - 2, y);
			cout << "©Ä¡ò¡ú";
			gotoxy(x - 2, y + 1);
			cout << "¨‰¨‰ ";
		}
		if(dired == 'd' || dired == 'D')
		{
			x ++;
			gotoxy(x - 2, y - 1);
			cout << "¨x¨x" ;
			gotoxy(x - 2, y);
			cout << "©Ä¡ò¡ú";
			gotoxy(x - 2, y + 1);
			cout << "¨‰¨‰";
			for( int i = -1; i <= 1; i ++)
			{
				gotoxy(x - 5, y + i);
				cout << ' ';
			}
		}
		dired = 'd';
	}
	LeaveCriticalSection(&cs);
}
void cmove()
{
	EnterCriticalSection(&cs);
	if((dir == 'w' || dir == 'W') && y >= 2)
	{
		if(dired != 'w' || dired != 'W')
		{
			if(dired == 's' || dired == 'S')
			{
				gotoxy(x, y - 1);
				cout << "¡ü" ;
				gotoxy(x , y + 1);
				cout << " "; 
			}
			if(dired == 'a' || dired == 'A')
			{
				gotoxy(x, y - 1);
				cout << "¡ü" ;
				gotoxy(x - 2, y);
				cout << " "; 
			}
			if(dired == 'd' || dired == 'D')
			{
				gotoxy(x, y - 1);
				cout << "¡ü" ;
				gotoxy(x + 2, y);
				cout << " "; 
			}
		}
		if(dir == 'w' || dir == 'W')
		{
			y --;
			gotoxy(x, y - 1);
			cout << "¡ü" ;
			gotoxy(x, y);
			cout << "¡ò"; 
			gotoxy(x, y + 1);
			cout << ' ';
		}
		dired = 'w';
	}
	if((dir == 's' || dir == 'S') && y <= 21)
	{
		if(dired != 's' || dired != 'S')
		{
			if(dired == 'w' || dired == 'W')
			{
				gotoxy(x, y + 1);
				cout << "¡ý" ;
				gotoxy(x , y - 1);
				cout << " "; 
			}
			if(dired == 'a' || dired == 'A')
			{
				gotoxy(x, y + 1);
				cout << "¡ý" ;
				gotoxy(x - 2, y);
				cout << " "; 
			}
			if(dired == 'd' || dired == 'D')
			{
				gotoxy(x, y + 1);
				cout << "¡ý" ;
				gotoxy(x + 2, y);
				cout << " "; 
			}
		}
		if(dir == 's' || dir == 'S')
		{
			y ++;
			gotoxy(x, y + 1);
			cout << "¡ý" ;
			gotoxy(x, y);
			cout << "¡ò"; 
			gotoxy(x, y - 1);
			cout << ' ';
		}
		dired = 's';
	}
	if((dir == 'a' || dir == 'A') && x >= 5)
	{
		if(dired != 'a' || dired != 'S')
		{
			if(dired == 'w' || dired == 'W')
			{
				gotoxy(x - 2, y);
				cout << "¡û" ;
				gotoxy(x , y - 1);
				cout << " "; 
			}
			if(dired == 's' || dired == 'S')
			{
				gotoxy(x - 2, y);
				cout << "¡û" ;
				gotoxy(x, y + 1);
				cout << " "; 
			}
			if(dired == 'd' || dired == 'D')
			{
				gotoxy(x - 2, y);
				cout << "¡û" ;
				gotoxy(x + 2, y);
				cout << " "; 
			}
		}
		if(dired == 'a' || dired == 'A')
		{
			x --;
			gotoxy(x, y);
			cout << "¡ò" ;
			gotoxy(x - 2, y);
			cout << "¡û"; 
			gotoxy(x + 2, y);
			cout << ' ';
		}
		dired = 'a';
	}
	if((dir == 'd' || dir == 'D') && x <= 45)
	{
		if(dired != 'a' || dired != 'S')
		{
			if(dired == 'w' || dired == 'W')
			{
				gotoxy(x + 2, y);
				cout << "¡ú" ;
				gotoxy(x , y - 1);
				cout << " "; 
			}
			if(dired == 's' || dired == 'S')
			{
				gotoxy(x + 2, y);
				cout << "¡ú" ;
				gotoxy(x, y + 1);
				cout << " "; 
			}
			if(dired == 'a' || dired == 'A')
			{
				gotoxy(x + 2, y);
				cout << "¡ú" ;
				gotoxy(x - 2, y);
				cout << " "; 
			}
		}
		if(dired == 'd' || dired == 'D')
		{
			x ++;
			gotoxy(x, y);
			cout << "¡ò" ;
			gotoxy(x + 2, y);
			cout << "¡ú"; 
			gotoxy(x - 2, y);
			cout << ' ';
		}
		dired = 'd';
	}
	LeaveCriticalSection(&cs);
}
void cprint()
{
	EnterCriticalSection(&cs);
	if(dir == 'w' || dir == 'W')
	{
		gotoxy(x, y - 1);
		cout << "¡ü" ;
		gotoxy(x, y);
		cout << "¡ò"; 
	}
	if(dir == 's' || dir == 'S')
	{
		gotoxy(x, y);
		cout << "¡ò" ;
		gotoxy(x , y + 1);
		cout << "¡ý"; 
	}
	if(dir == 'a' || dir == 'A')
	{
		gotoxy(x, y);
		cout << "¡ò" ;
		gotoxy(x - 2, y);
		cout << "¡û"; 
	}
	if(dir == 'd' || dir == 'D')
	{
		gotoxy(x, y);
		cout << "¡ò" ;
		gotoxy(x + 2, y);
		cout << "¡ú"; 
	}
	LeaveCriticalSection(&cs);
}
void pprint()
{
//	EnterCriticalSection(&cs);
	if(dir == 'w' || dir == 'W')
		{
			gotoxy(x, y - 1);
			cout << "¡ü" ;
			gotoxy(x - 2, y);
			cout << "¨Š¡ò¨‡"; 
			gotoxy(x - 2, y + 1);
			cout << "¨Š©Ü¨‡";
		}
		if(dir == 's' || dir == 'S')
		{
			gotoxy(x - 2, y - 1);
			cout << "¨Š©Ô¨‡";
			gotoxy(x - 2, y);
			cout << "¨Š¡ò¨‡"; 
			gotoxy(x, y + 1);
			cout << "¡ý" ;
		}
		if(dir == 'd' || dir == 'D')
		{
			gotoxy(x - 2, y - 1);
			cout << "¨x¨x" ;
			gotoxy(x - 2, y);
			cout << "©Ä¡ò¡ú";
			gotoxy(x - 2, y + 1);
			cout << "¨‰¨‰";
		}
		if(dir == 'a' || dir == 'A')
		{
			gotoxy(x , y - 1);
			cout << "¨x¨x" ;
			gotoxy(x - 2, y);
			cout << "¡û¡ò©Ì";
			gotoxy(x, y + 1);
			cout << "¨‰¨‰";
		}
//		LeaveCriticalSection(&cs);
	}
	void ai(const tank& player)
	{
		if(x < player.x)
		{
			dir = 'D';
			cmove();
		}
		if(x > player.x)
		{
			dir = 'A';
			cmove();
		}
		if(y > player.y)
		{
			dir = 'W';
			cmove();
		} 
		if(y < player.y)
		{
			dir = 'S';
			cmove();
		}
		if(x == player.x || y == player.y)
		{
			HANDLE pao = CreateThread(NULL, 0, attack, this, 0, NULL);
		}
	}
	void action()
	{
		char act;
		int th = 1;
		showmsg();
		while(life > 0)
		{
			
			act = getch();
			if(act == 'j' || act == 'J')
			{
				if(th % 2)
				{
					HANDLE pao = CreateThread(NULL, 0, attack, this, 0, NULL);
				}
				th ++;
			}
			else
			{
				dir = act;
				pmove();
			}
		}
		dele();
	} 
	const bool operator==( const tank& a )
	{
		if(x == a.x && y == a.y && dir == a.dir && level == a.level)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	//const bool operator==( const zidan& a )
//	{
//		if((x - 1 == a.x || x + 1 == a.x) && (y - 1 == a.y || y == a.y || y + 1 == a.y) || x == a.x && (y - 1 == a.y || y + 1 == a.y))
//		{
//			return 1;
//		}
//		else
//		{
//			return 0;
//		}
//	}
	int getx()
	{
		return x;
	}
	int gety()
	{
		return y;
	}
	char getdir()
	{
		return dir;
	}
	int getcop()
	{
		return cop;
	}
	int getspeed()
	{
		return speed;
	}
	int getblood()
	{
		return blood;
	}
	int getlife()
	{
		return life;
	}
	int getcio()
	{
		return cop;
	}
}player1(30, 20, 'w', 100, 1);


class zidan
{
	int x;
	int y;
	char dir;
	tank tk;
	int sp;
	int yw;
	public:
		friend class tank;
		zidan* next;
		zidan()
		{
			x = 0;
			y = 0;
			dir = 'w';
			sp = 0;
			yw = 0;
			bing.push(*this);
		}
		zidan(tank& d)
		{
			x = d.getx();
			y = d.gety();
			dir = d.getdir();
			tk = d;
			sp = 101 - tk.speed;
			yw = 1;
			bing.push(*this);
		}
		const bool operator==( const tank& a )
	{
		if((a.x - 1 == x || a.x + 1 == x) && (a.y - 1 == y || a.y == y || a.y + 1 == y) || x == a.x && (a.y - 1 == y || a.y + 1 == y))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	tank gettank()
	{
		return tk;
	}
	void checktank()
		{
				tank* p = bomp.gethead();
				while(p)
				{
					if(*this == *p)
					{
						bomp.pop(*p);
						p -> gj(tk);
						tk.lvu();
						player1.showmsg();
						yw = 0;
						break;
					}
					p = p -> next;
				}				
		}
		const bool operator==( const zidan& a )
		{
			if(x == a.x && y == a.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		void fly()
		{
			if(dir == 'w' || dir == 'W')
		{
			y -= 2;
			while(y >= 0 && yw)
			{
				EnterCriticalSection(&cs);
				gotoxy(x, y --);
				cout << "¡Ñ" ;
				if(y != tk.gety() - 3)
				{
					gotoxy(x, y + 2);
					cout << ' ';
				}
				if(y < 1)
				{
					gotoxy(x, y + 1);
					cout << ' ';
				}
				checktank();
				if(yw == 0)
				{
					gotoxy(x, y);
					cout << ' ';
				}
				LeaveCriticalSection(&cs);
				Sleep(sp);
			}
		}
		if(dir == 's' || dir == 'S')
		{
			y += 2;
			while(y <= 23 && yw)
			{
				EnterCriticalSection(&cs);
				gotoxy(x, y ++);
				cout << "¡Ñ" ;
				if(y != tk.gety() + 3)
				{
					gotoxy(x, y - 2);
					cout << ' ';
				}
				if(y > 23)
				{
					gotoxy(x, y - 1);
					cout << ' ';
				}
				checktank();
				if(yw == 0)
				{
					gotoxy(x, y);
					cout << ' ';
				}
				LeaveCriticalSection(&cs);
				
				Sleep(sp);
			}
		}
		if(dir == 'd' || dir == 'D')
		{
			x += 4;
			while(x <= 60 && yw)
			{
				EnterCriticalSection(&cs);
				gotoxy(x, y);
				cout << "¡Ñ" ;
				if(x != tk.getx() + 4)
				{
					gotoxy(x - 1, y);
					cout << ' ';
				}
				x += 1;
				if(x > 60)
				{
					gotoxy(x - 1, y);
					cout << ' ';
				}
				checktank();
				if(yw == 0)
				{
					gotoxy(x, y);
					cout << ' ';
				}
				LeaveCriticalSection(&cs);
				
				Sleep(sp);
			}
		}
		if(dir == 'a' || dir == 'A')
		{
			x -= 4;
			while(x >= 0 && yw)
			{
				EnterCriticalSection(&cs);
				gotoxy(x, y);
				cout << "¡Ñ" ;
				if(x != tk.getx() - 4)
				{
					gotoxy(x + 2, y);
					cout << ' ';
				}
				x -= 1;
				if(x < 0)
				{
					gotoxy(x + 1, y);
					cout << ' ';
				}
				checktank();
				if(yw == 0)
				{
					gotoxy(x, y);
					cout << ' ';
				}
				LeaveCriticalSection(&cs);
				
				Sleep(sp);
			}
		}
		}
};
DWORD WINAPI com(PVOID ptank)
{
	tank *com = (tank*)ptank;
	com -> cprint();
	while(com -> getlife() > 0)
	{
		com -> ai(player1);
//		com -> showmsg();
		Sleep(1000);
	}
	return 0;
}
DWORD WINAPI attack(PVOID ptank)
{
	tank* tk = (tank*)ptank;
	zidan zd(*tk);
//	zd.gettank().cprint();
	zd.fly();
	//int s;
//	int b;
//	int sl = 100;	
		//if(tk -> getdir() == 'w' || tk -> getdir() == 'W')
//		{
//			s = tk -> gety() - 2;
//			b = tk -> getx();
//			while(s >= 0)
//			{
//				EnterCriticalSection(&cs);
//				gotoxy(b, s --);
//				cout << "¡Ñ" ;
//				if(s != tk -> gety() - 3)
//				{
//					gotoxy(b, s + 2);
//					cout << ' ';
//				}
//				if(s < 1)
//				{
//					gotoxy(b, s + 1);
//					cout << ' ';
//				}
//				LeaveCriticalSection(&cs);
//				_sleep(sl);
//			}
//		}
//		if(tk -> getdir() == 's' || tk -> getdir() == 'S')
//		{
//			s = tk -> gety() + 2;
//			b = tk -> getx();
//			while(s <= 23)
//			{
//				EnterCriticalSection(&cs);
//				gotoxy(b, s ++);
//				cout << "¡Ñ" ;
//				if(s != tk -> gety() + 3)
//				{
//					gotoxy(b, s - 2);
//					cout << ' ';
//				}
//				if(s > 23)
//				{
//					gotoxy(b, s - 1);
//					cout << ' ';
//				}
//				LeaveCriticalSection(&cs);
//				
//				_sleep(sl);
//			}
//		}
//		if(tk -> getdir() == 'd' || tk -> getdir() == 'D')
//		{
//			s = tk -> getx() + 4;
//			b = tk -> gety();
//			while(s <= 60)
//			{
//				EnterCriticalSection(&cs);
//				gotoxy(s, b);
//				cout << "¡Ñ" ;
//				if(s != tk -> getx() + 4)
//				{
//					gotoxy(s - 1, b);
//					cout << ' ';
//				}
//				s += 1;
//				if(s > 60)
//				{
//					gotoxy(s - 1, b);
//					cout << ' ';
//				}
//				LeaveCriticalSection(&cs);
//				
//				_sleep(sl);
//			}
//		}
//		if(tk -> getdir() == 'a' || tk -> getdir() == 'A')
//		{
//			s = tk -> getx() - 4;
//			b = tk -> gety();
//			while(s >= 0)
//			{
//				EnterCriticalSection(&cs);
//				gotoxy(s, b);
//				cout << "¡Ñ" ;
//				if(s != tk -> getx() - 4)
//				{
//					gotoxy(s + 2, b);
//					cout << ' ';
//				}
//				s -= 1;
//				if(s < 0)
//				{
//					gotoxy(s + 1, b);
//					cout << ' ';
//				}
//				LeaveCriticalSection(&cs);
//				
//				_sleep(sl);
//			}
//		}
	return 0;
}
//y <= 24; x <= 79
void showside()
{
	gotoxy(0, 0);
	for(int i = 0; i <= 47; i ++)
	{
		cout << '#';
	}
	gotoxy(0, 22);
	for(int i = 0; i <= 47; i ++)
	{
		cout << '#';
	}
	for(int i = 1; i < 22; i ++)
	{
		gotoxy(0, i);
		cout << '#';
		gotoxy(47, i);
		cout << '#';
	}
}
int main()
{
	Hide_Cursor();
	InitializeCriticalSection (&cs);
//	showside();
	tank com(10, 10, 's', 0, 0);
	tank com2(40, 10, 's', 0, 0);
	//tank* p = bomp.gethead();
//	while(p)
//	{
//		if(p -> getcop())
//		{
//			p -> pprint();
//		}
//		else
//		{
//			p -> cprint();
//		}
//		p = p -> next;
//	}
	player1.action();
	getch();
	DeleteCriticalSection (&cs);
	return 0;
}
