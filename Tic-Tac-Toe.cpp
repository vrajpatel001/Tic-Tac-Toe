// Author: Vraj Patel
// Tic-Tac-Toe Game
// Single and Dual Player

#include <iostream>
#include <ctime>
#include <windows.h>
#include <climits>
#include <conio.h>
using namespace std;

char square[10] = {'L','1','2','3','4','5','6','7','8','9'};
int tictacwin=-1, player=1, flag=0;

class TextAttr
{
  friend std::ostream& operator<<(std::ostream& out, TextAttr attr)
  {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr.value);
    return out;
  }
public:
    explicit TextAttr(WORD attributes): value(attributes) {}
private:
    WORD value;
};

#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

int numrandom(int nop)
{
  srand(time(NULL));
  return (rand()%nop+1);
}

void grandomc()
{
  int fcolor = numrandom(4);
  if(fcolor==1)
    cout<<TextAttr(FOREGROUND_INTENSITY | FOREGROUND_WHITE);
  else if(fcolor==2)
    cout<<TextAttr(FOREGROUND_INTENSITY | FOREGROUND_RED);
  else if(fcolor==3)
    cout<<TextAttr(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
  else
    cout<<TextAttr(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
}

int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])

        return 1;
    else if (square[4] == square[5] && square[5] == square[6])

        return 1;
    else if (square[7] == square[8] && square[8] == square[9])

        return 1;
    else if (square[1] == square[4] && square[4] == square[7])

        return 1;
    else if (square[2] == square[5] && square[5] == square[8])

        return 1;
    else if (square[3] == square[6] && square[6] == square[9])

        return 1;
    else if (square[1] == square[5] && square[5] == square[9])

        return 1;
    else if (square[3] == square[5] && square[5] == square[7])

        return 1;
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3'
                    && square[4] != '4' && square[5] != '5' && square[6] != '6'
                  && square[7] != '7' && square[8] != '8' && square[9] != '9')

        return 0;
    else
        return -1;
}

void cleanboard()
{
    square[0]='L';
    for(int i=1;i<10;i++)
        square[i]='0'+i;
}

void board(char count)
{
    grandomc();
    system("cls");
    cout << "\n\n\tTic Tac Toe\n\n";

    if(count!='2')
        cout << "User (X)  -  Computer (O)" << endl << endl;
    else
        cout << "User 1(X)  -  User 2(O)" << endl << endl;
    cout << endl;

    cout << "     |     |     " << endl;
    cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;

    cout << "     |     |     " << endl << endl;
}

void printb(int player, int choice)
{
    grandomc();
    int check=0;
    char mark= (player%2) ? 'X' : 'O';

    if (choice == 1 && square[1] == '1')
        square[1] = mark;
    else if (choice == 2 && square[2] == '2')
        square[2] = mark;
    else if (choice == 3 && square[3] == '3')
        square[3] = mark;
    else if (choice == 4 && square[4] == '4')
        square[4] = mark;
    else if (choice == 5 && square[5] == '5')
        square[5] = mark;
    else if (choice == 6 && square[6] == '6')
        square[6] = mark;
    else if (choice == 7 && square[7] == '7')
        square[7] = mark;
    else if (choice == 8 && square[8] == '8')
        square[8] = mark;
    else if (choice == 9 && square[9] == '9')
        square[9] = mark;
    else
    {
        cout<<"Invalid move "<<endl;
        cout<<"Try again after pressing Enterkey"<<endl;
        flag=1;
        check=1;
        cin.ignore();
        cin.get();
    }
    check==0?flag=0:flag=1;
}

int ticplayer(char count)
{
    grandomc();
    int choice;
    if(count!='2')
        cout << "User, enter a number:  ";
    else
    {
        char cplay = (player%2)?'1':'2';
        cout << "User "<<cplay<<", enter a number:  ";
    }
    cin >> choice;

    while(cin.fail())
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout<<"Please enter input between 1 to 9 only"<<endl;
        cin>>choice;
    }

    printb(player, choice);
    board(count);

    return choice;
}

void ticcomp(int pchoice)
{
    int m=0;
    int checker[8];
    for(int i=1;i<10;i++)
    {
        char temp= '0'+i;
        if(square[i]==temp)
        {
            checker[m]=i;
            m++;
        }
    }
    if(m==0)
        return;
    int cpos = numrandom(m);
    printb(player,checker[cpos-1]);
    board('1');
}

void ticcontrol(char count)
{
    board(count);
    do
    {
       int pc=ticplayer(count);
       while(flag!=0)
        pc=ticplayer(count);
       tictacwin=checkwin();
       if(tictacwin!=-1)
        break;
       player++;
       if(count=='2')
       {
          ticplayer(count);
          while(flag!=0)
            pc=ticplayer(count);
          tictacwin=checkwin();
       }
       else
       {
          ticcomp(pc);
          tictacwin=checkwin();
       }
       if(tictacwin!=-1)
        break;
       player++;
    }while(true);

    board(count);
    grandomc();
    if(tictacwin==1 && count!='2')
    {
        string winner = (player%2) ? "User" : "Computer" ;
        cout<<"==>\a"<<winner<<" wins ";
    }
    else if(tictacwin==1 && count!='2')
    {
        cout<<"==>\aGame draw";
    }
    else if(tictacwin==1 && count=='2')
    {
        string winner = (player%2) ? "User 1" : "User 2" ;
        cout<<"==>\a"<<winner<<" wins ";
    }
    else
    {
        cout<<"==>\aGame draw";
    }

    cin.ignore();
    cin.get();
}

int main()
{
    do
    {
        cleanboard();
        grandomc();
        cout<<"For Dual player enter 2 else for single player anything! : ";
        ticcontrol(_getch());
        system("cls");
        grandomc();
        cout<<"If you want to play again enter 1 else anything! : "<<endl<<endl;
    }while(_getch()=='1');
    return 0;
}
