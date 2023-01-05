#include <iostream>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <cmath>
using namespace std;
char header[6][42];

char maze[24][70];
void maze_show();
void calculate_score();
void load();
void movepack_man();
void moveHeroLeft();
void moveHeroRight();
void moveHeroUp();
void moveHeroDown();
void gotoxy(int x, int y);
void ghost1_moveup();
void ghost_move();
void printScore();
void gameover();
int ghostDirection();
bool ghostMovementRand();
bool move_down = false;
bool move_up = true;
void lives_counter();
void lives_show();

int px = 9;  
int py = 31; 
int score = 0;

int ghostX_2 = 2; 
int ghostY_2 = 28;

int ghostX = 19;
int ghostY = 25;
// vertical movement.............................
int ghostX_1 = 12; // move UpDown
int ghostY_1 = 2;
bool move_up_1();
bool move_down_1();
bool gostmovement_vertical();
char previousItem = ' ';
char previousItem_Vertical = ' ';
bool gameRunning_vertical = true;
bool temp = false;
//_______________
//*************
// horizontol moovement
int ghostX_3 = 15; // horizontolly move
int ghostY_3 = 22;
char previousItem_horizontol = ' ';
int turn_horizontol = 0;
bool temp_horizontol = false;
bool gostmovement_horizontol();
bool move_left_3();
bool move_right_3();
bool gameRunning_horizontol = true;

//************
//-----------chasing ghoast-------------------------
bool ghost_chase();
int distance(int p_x, int p_y, int g_x, int g_y);
float directionG[4] = {1, 1, 1, 1};
int small_idx();
char previousItem_chase = ' ';
bool gameRunning_chasing = true;
//-----------------------------------------------
bool gameRunning = true;
int lives = 3;
int turn = 0;
char p;
int main()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
	
	 p = 2;
//system("color 3");
    load();
    bool gameplay = true;
    system("CLS");
    maze_show();
    gotoxy(py, px);
    cout << p;

    while (lives > 0)
    {
        Sleep(200);

        gotoxy(py, px);

        printScore();
        lives_show();
        if (gameRunning == false || gameRunning_vertical == false || gameRunning_horizontol == false || gameRunning_chasing == false)
        {
            lives_counter();
            lives_show();
        }

        gameRunning_vertical = gostmovement_vertical();
        gameRunning_horizontol = gostmovement_horizontol();
        gameRunning_chasing = ghost_chase();
        gameRunning = ghostMovementRand();

        if (GetAsyncKeyState(VK_LEFT))
        {
            moveHeroLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveHeroRight(); 
        }
        if (GetAsyncKeyState(VK_UP))
        {
            moveHeroUp(); 
                   }
        if (GetAsyncKeyState(VK_DOWN))
        {
            moveHeroDown();
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gameRunning = false; 
        }
    }


    system("cls");
    cout<<"\n";
    cout<<"\n";
    cout<<"------------------ Your Secore -----------------"<<endl;
    cout<<"\n";
    cout<<"\t\t\t\t"<<score<<endl;
    cout<<"\n";
    cout<<"\n";
    gameover();
    
}

//--------------------------------------------------------

void gotoxy(int x, int y) 
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void load()
{
    fstream file;
    file.open("SimpleFrame.txt", ios::in);
    string line;
    for (int i = 0; i < 24; i++)
    {
        getline(file, line);
        for (int j = 0; j < 71; j++)
        {
            maze[i][j] = line[j];
        }
    }
    file.close();
}
void printScore()
{
    gotoxy(74, 3);
    cout << " Score > > > >---  " << score << endl
         << endl;
}
void maze_show()
{

    for (int i = 0; i < 24; i++)
    {

        for (int j = 0; j < 70; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }

    cout<< endl;
}
void calculate_score()
{
    score++;
}
void lives_counter()
{
    lives--;
}
void lives_show()
{
    gotoxy(75, 4);
    cout << "Remaining lives:" << lives;
  
}
void moveHeroLeft() 
{
    if ((maze[px][py - 1] == ' ') || maze[px][py - 1] == '.' || maze[px][py - 1] == '*')
    {
        maze[px][py] = ' ';

        gotoxy(py, px);
        cout << " ";
        if (maze[px][py - 1] == '.') 
        {
               calculate_score();
        }
        else
        {
            if(maze[px][py - 1] == '*')
            {
                lives = lives + 1;
            }
        }
        maze[px][py - 1] = 'P';
        py = py - 1;
        gotoxy(py, px);
        cout << p;
    }
}
void moveHeroRight()
{
    if (maze[px][py + 1] == ' ' || maze[px][py + 1] == '*' || maze[px][py + 1] == '.' )
    {
        maze[px][py] = ' ';
        gotoxy(py, px);
        cout << " ";
        if (maze[px][py + 1] == '.')
        {
            calculate_score();
        }
        else
        {
            if(maze[px][py + 1] == '*')
            {
                lives = lives + 1;
            }
        }
        maze[px][py + 1] = 'P';
        py = py + 1;
        gotoxy(py, px);
        cout << p;
    }
}

void moveHeroUp()
{
    if ((maze[px - 1][py] == ' ') || maze[px - 1][py] == '.' || maze[px - 1][py] == '*')
    {
        maze[px][py] = ' ';
        gotoxy(py, px);
        cout << " ";
        if (maze[px - 1][py] == '.')
        {
            calculate_score();
        }
        else
        {
            if(maze[px - 1][py] == '*')
            {
                lives = lives + 1;
            }
        }
        maze[px - 1][py] = 'P';
        px = px - 1;
        gotoxy(py, px);
        cout << p;
    }
}
void moveHeroDown()
{

    if ((maze[px + 1][py] == ' ') || maze[px + 1][py] == '.' || maze[px + 1][py] == '*' )
    {
        maze[px][py] = ' ';
        gotoxy(py, px);
        cout << " ";

        if (maze[px + 1][py] == '.')
        {
            calculate_score();
        }
        else
        {
            if(maze[px + 1][py] == '*')
            {
                lives = lives + 1;
            }
        }
        maze[px + 1][py] = 'P';
        px = px + 1;
        gotoxy(py, px);
        cout << p;
    }
}

int ghostDirection()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}
bool ghostMovementRand()
{
    int value = ghostDirection();
    if (value == 1)
    {
       
        if (maze[ghostX][ghostY - 1] == ' ' || maze[ghostX][ghostY - 1] == '.' || maze[ghostX][ghostY - 1] == 'P')
        {
            maze[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            cout << previousItem;
            ghostY = ghostY - 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << "G";
        }
    }
    if (value == 2)
    {

        if (maze[ghostX][ghostY + 1] == ' ' || maze[ghostX][ghostY + 1] == '.' || maze[ghostX][ghostY + 1] == 'P')
        {
            maze[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            cout << previousItem;
            ghostY = ghostY + 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << "G";
        }
    }
    if (value == 3)
    {
      
        if (maze[ghostX - 1][ghostY] == ' ' || maze[ghostX - 1][ghostY] == '.' || maze[ghostX - 1][ghostY] == 'P')
        {
            maze[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            cout << previousItem;
            ghostX = ghostX - 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << "G";
        }
    }
    if (value == 4)
    {

        if (maze[ghostX + 1][ghostY] == ' ' || maze[ghostX + 1][ghostY] == '.' || maze[ghostX + 1][ghostY] == '.')
        {
            maze[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            cout << previousItem;
            ghostX = ghostX + 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << "G";
        }
    }
    return 1;
}
//
bool gostmovement_vertical()
{
    if (turn == 0)
    {
        temp = move_down_1();
        return temp;
    }
    if (turn == 1)
    {
        temp = move_up_1();
        return temp;
    }
}
bool move_up_1()
{
    if (maze[ghostX_1 - 1][ghostY_1] == ' ' || maze[ghostX_1 - 1][ghostY_1] == '.' || maze[ghostX_1 - 1][ghostY_1] == 'P')
    {

        maze[ghostX_1][ghostY_1] = previousItem_Vertical;
        gotoxy(ghostY_1, ghostX_1);
        cout << previousItem_Vertical;
        ghostX_1 = ghostX_1 - 1;
        previousItem_Vertical = maze[ghostX_1][ghostY_1];
        maze[ghostX_1][ghostY_1] = 'G';
        gotoxy(ghostY_1, ghostX_1);
        cout << "G";
    }
    if (ghostX_1 == 2)
    {
        previousItem_Vertical = ' ';
        turn = 0;
    }
    if (previousItem_Vertical != 'P')
    {

        return true;
    }
}
bool move_down_1()
{
    if (maze[ghostX_1 + 1][ghostY_1] == ' ' || maze[ghostX_1 + 1][ghostY_1] == '.' || maze[ghostX_1 + 1][ghostY_1] == 'P')
    {

        maze[ghostX_1][ghostY_1] = previousItem_Vertical;
        gotoxy(ghostY_1, ghostX_1);
        cout << previousItem_Vertical;
        ghostX_1 = ghostX_1 + 1;
        previousItem_Vertical = maze[ghostX_1][ghostY_1];
        maze[ghostX_1][ghostY_1] = 'G';
        gotoxy(ghostY_1, ghostX_1);
        cout << "G";
    }
    if (ghostX_1 == 22)
    {
        previousItem_Vertical = ' ';
        turn = 1;
    }
    if (previousItem_Vertical != 'P')
    {
        return true;
    }
}


bool gostmovement_horizontol()
{

    if (turn_horizontol == 0)
    {
        temp_horizontol = move_right_3();
        return temp_horizontol;
    }
    if (turn_horizontol == 1)
    {
        temp_horizontol = move_left_3();
        return temp_horizontol;
    }
}

bool move_right_3()
{
    if (maze[ghostX_3][ghostY_3 + 1] == ' ' || maze[ghostX_3][ghostY_3 + 1] == '.' || maze[ghostX_3][ghostY_3 + 1] == 'P')
    {

        maze[ghostX_3][ghostY_3] = previousItem_horizontol;
        gotoxy(ghostY_3, ghostX_3);
        cout << previousItem_horizontol;
        ghostY_3 = ghostY_3 + 1;
        previousItem_horizontol = maze[ghostX_3][ghostY_3];
        maze[ghostX_3][ghostY_3] = 'G';
        gotoxy(ghostY_3, ghostX_3);
        cout << "G";
    }
    if (maze[ghostX_3][ghostY_3 + 1] == '|')
    {
        previousItem_horizontol = ' ';
        turn_horizontol = 1;
    }
    if (previousItem_horizontol != 'P')
    {

        return true;
    }
}
bool move_left_3()
{
    
    if (maze[ghostX_3][ghostY_3 - 1] == ' ' || maze[ghostX_3][ghostY_3 - 1] == '.' || maze[ghostX_3][ghostY_3 - 1] == 'P')
    {

        maze[ghostX_3][ghostY_3] = previousItem_horizontol;
        gotoxy(ghostY_3, ghostX_3);
        cout << previousItem_horizontol;
        ghostY_3 = ghostY_3 - 1;
        previousItem_horizontol = maze[ghostX_3][ghostY_3];
        maze[ghostX_3][ghostY_3] = 'G';
        gotoxy(ghostY_3, ghostX_3);
        cout << "G";
    }
    if (ghostY_3 == 2)
    {
        previousItem_horizontol = ' ';
        turn_horizontol = 0;
    }
    if (previousItem_horizontol != 'P')
    {

        return true;
    }
}
bool ghost_chase()

{

    directionG[0] = distance(px, py, ghostX_2, ghostY_2 + 1);
    directionG[1] = distance(px, py, ghostX_2, ghostY_2 - 1);
    directionG[2] = distance(px, py, ghostX_2 + 1, ghostY_2);
    directionG[3] = distance(px, py, ghostX_2 - 1, ghostY_2);
    int small_distance = small_idx();
    if (small_distance == 0)
    {
        

        if (maze[ghostX_2][ghostY_2 + 1] == ' ' || maze[ghostX_2][ghostY_2 + 1] == '.' || maze[ghostX_2][ghostY_2 + 1] == 'P')
        {
            maze[ghostX_2][ghostY_2] = previousItem_chase;
            gotoxy(ghostY_2, ghostX_2);
            cout << previousItem_chase;
            ghostY_2 = ghostY_2 + 1;
            previousItem_chase = maze[ghostX_2][ghostY_2];
            if (previousItem_chase == 'P')
            {
                return false;
            }
            maze[ghostX_2][ghostY_2] = 'G';
            gotoxy(ghostY_2, ghostX_2);
            cout << "G";
        }
        return true;
    }

    if (small_distance == 1)
    {
        
        if (maze[ghostX_2][ghostY_2 - 1] == ' ' || maze[ghostX_2][ghostY_2 - 1] == '.' || maze[ghostX_2][ghostY_2 - 1] == 'P')
        {
            maze[ghostX_2][ghostY_2] = previousItem_chase;
            gotoxy(ghostY_2, ghostX_2);
            cout << previousItem_chase;
            ghostY_2 = ghostY_2 - 1;
            previousItem_chase = maze[ghostX_2][ghostY_2];
            if (previousItem_chase == 'P')
            {
                return false;
            }
            maze[ghostX_2][ghostY_2] = 'G';
            gotoxy(ghostY_2, ghostX_2);
            cout << "G";
        }
        return true;
    }
    if (small_distance == 2)
    {
        if (maze[ghostX_2 + 1][ghostY_2] == ' ' || maze[ghostX_2 + 1][ghostY_2] == '.' || maze[ghostX_2 + 1][ghostY_2] == 'P')
        {
            maze[ghostX_2][ghostY_2] = previousItem_chase;
            gotoxy(ghostY_2, ghostX_2);
            cout << previousItem_chase;
            ghostX_2 = ghostX_2 + 1;
            previousItem_chase = maze[ghostX_2][ghostY_2];
            if (previousItem_chase == 'P')
            {
                return false;
            }
            maze[ghostX_2][ghostY_2] = 'G';
            gotoxy(ghostY_2, ghostX_2);
            cout << "G";
        }
        return true;
    }
    if (small_distance == 3)
    {

        if (maze[ghostX_2 - 1][ghostY_2] == ' ' || maze[ghostX_2 - 1][ghostY_2] == '.' || maze[ghostX_2 - 1][ghostY_2] == 'P')
        {
            maze[ghostX_2][ghostY_2] = previousItem_chase;
            gotoxy(ghostY_2, ghostX_2);
            cout << previousItem_chase;
            ghostX_2 = ghostX_2 - 1;
            previousItem_chase = maze[ghostX_2][ghostY_2];
            if (previousItem_chase == 'P')
            {
                return false;
            }
            maze[ghostX_2][ghostY_2] = 'G';
            gotoxy(ghostY_2, ghostX_2);
            cout << "G";
        }
        return true;
    }
}
int distance(int p_x, int p_y, int g_x, int g_y)
{
    int d = sqrt(pow((g_x - p_x), 2) + (pow((g_y - p_y), 2)));
    return d;
}
int small_idx()
{
    int small = directionG[0];
    int s_idx = 0;
    for (int i = 1; i < 4; i++)
    {
        if (directionG[i] < small)
        {
            small = directionG[i];
            s_idx = i;
        }
    }

    return s_idx;
}

void gameover()
{
    system("color 4");
  cout<<"           _______                         _______                 "<<endl;                         
  cout<<"          |     __|.---.-.--------.-----. |       |.--.--.-----.----."<<endl;
  cout<<"          |    |  ||  _  |        |  -__| |   -   ||  |  |  -__|   _|"<<endl;
  cout<<"          |_______||___._|__|__|__|_____| |_______| \___/|_____|__| "<<endl;
  cout<<"                                                                    "<<endl;
}