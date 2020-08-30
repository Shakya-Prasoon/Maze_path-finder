#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

struct Position //stores the position of movement
{
    int R, C;
};

void ReadMap(char maze[][81], int i, ifstream& in)//reads the map from file
{
    for (int k = 0; k < i; k++)
    {
        in.getline(maze[k], 80);
    }
}

void Print(char maze[][81], int i, int j, ofstream &out)
{
    //to make count of how many times function has been called
    static int original = 0;
    if (original == 0)//if this is the first count then print this
    {
        out << i << " " << j << endl;
    }
    original++;//increase count
    for (int k = 0; k < i; k++)//prints the whole map
    {
        for (int l = 0; l < j; l++)
        {
            if (maze[k][l] == '@')
                out << " " << flush;
            else
                out << maze[k][l] << flush;
        }
        out << endl;
    }
    out << endl << endl;
}

//this finds the route and makes the next move
bool Find_N_Place (char maze[][81], int i, int j, struct Position& pos)
{
    if (maze[pos.R - 1][pos.C] == ' ' && pos.R >= 0 && pos.R < i && pos.C >=0
        && pos.C < j)
    {
        maze[pos.R - 1][pos.C] = '#';
        pos.R--;
        return true;
    }
    else if (maze[pos.R][pos.C + 1] == ' '  && pos.R >= 0 && pos.R < i
             && pos.C >=0 && pos.C < j)
    {
        maze[pos.R][pos.C + 1] = '#';
        pos.C++;
        return true;
    }
    else if (maze[pos.R + 1][pos.C] == ' ' && pos.R >= 0 && pos.R < i
             && pos.C >=0 && pos.C < j)
    {
        maze[pos.R + 1][pos.C] = '#';
        pos.R++;
        return true;
    }
    else if (maze[pos.R][pos.C - 1] == ' ' && pos.R >= 0 && pos.R < i
             && pos.C >=0 && pos.C < j)
    {
        maze[pos.R][pos.C - 1] = '#';
        pos.C--;
        return true;
    }
    else
        return false;
}

void GoBack (char maze[][81], struct Position& pos)//if no route found go back
{
    maze[pos.R][pos.C] = '@';//put '@' if it's a dead end
    if (maze[pos.R - 1][pos.C] == '#')
    {
        pos.R -= 1; //reduces row count by 1
    }
    else if (maze[pos.R][pos.C + 1] == '#')
    {
        pos.C += 1;//increases column count by 1
    }
    else if (maze[pos.R + 1][pos.C] == '#')
    {
        pos.R += 1;//increases row count by 1
    }
    else
    {
        pos.C -= 1;//reduce column count by 1
    }
}

void Solve(char maze[][81], int i, int j, struct Position& pos, ofstream &out)
{
    if(!Find_N_Place(maze, i, j, pos))//searches the route and make movement
    {
        GoBack(maze, pos);//if no route found then go back
    }
    if (pos.R == (i - 1) && pos.C == (j - 1))//if exit found then print maze
    {
        Print(maze, i, j, out);
        exit(0);
    }
    else
        Solve(maze, i, j, pos, out);//if not the end... call the function again
}

int main(int argc, char *argv[])
{
    if (argc < 3){  //checks if there is enough parameters or not
        cout << "Not enough parameters!! " << endl;
        return -1;
    }
    ifstream in;
    ofstream out;
    in.open(argv[1]);   //open input file
    if(!in){
        cout << "Problem while opening the input file." << endl;
        return -1;
    }
    out.open(argv[2]);      //open output file
    if(!out){
        cout << "Problem while opening the output file." << endl;
        return -1;
    }
    Position pos; //create struct named pos
    char maze[24][81];//create maze
    int i, j;   //to store the size of maze

    char maze_size[6]; //to store the first line which has the maze's size
    in.getline(maze_size, 6);//read the line from file
    char* i1 = strtok(maze_size, " \n");
    char* j1 = strtok(nullptr, "\n ");
    i = atoi(i1);
    j = atoi(j1);

    ReadMap(maze, i, in);
    Print(maze, i, j, out);
    pos.R = pos.C = 0;  //sets row and col to 0 and 0 respectively
    maze[0][0] = '#';//sets first position as "#"
    Solve(maze, i, j, pos, out);//calls the solve function
    //if the maze could not be solved then print this
    out << "could not find the path." << flush;
    return 0;
}
