#include<iostream>
using namespace std;

class Player
{
    char symbol;
    string playerType;

    public:
        Player(char symbol, string type)
        {
            this->symbol = symbol;
            this->playerType = type;
        };

        void makeAMove(char grid[3][3], bool used_choices[9])
        {
            int choice;

            if(playerType == "player")
            {
                do
                {
                    cout << "Where do you want to play (1-9) : ";
                    cin >> choice;
                } while((choice < 1 || choice > 9) || used_choices[choice-1]);
            }
            else
            {
                do
                {
                    choice = rand()%9+1;
                } while (used_choices[choice-1]);
            }

            used_choices[choice-1] = true;

            switch(choice)
            {
                case 1:
                    grid[0][0] = this->symbol;
                    break;
                
                case 2:
                    grid[0][1] = this->symbol;
                    break;

                case 3:
                    grid[0][2] = this->symbol;
                    break;
                
                case 4:
                    grid[1][0] = this->symbol;
                    break;
                
                case 5:
                    grid[1][1] = this->symbol;
                    break;

                case 6:
                    grid[1][2] = this->symbol;
                    break;
                
                case 7:
                    grid[2][0] = this->symbol;
                    break;
                
                case 8:
                    grid[2][1] = this->symbol;
                    break;

                case 9:
                    grid[2][2] = this->symbol;
                    break;
                
                default:
                    break;
            }
        }

        bool Won(char grid[3][3])
        {
            return checkRows(grid) || checkColumns(grid) || checkDiagonals(grid);
        }
    
    private:
        bool checkRows(char grid[3][3])
        {
            return ((grid[0][0] == symbol && grid[0][1] == symbol && grid[0][2] == symbol) ||
            (grid[1][0] == symbol && grid[1][1] == symbol && grid[1][2] == symbol) ||
            (grid[2][0] == symbol && grid[2][1] == symbol && grid[2][2] == symbol));
        }

        bool checkColumns(char grid[3][3])
        {
            return ((grid[0][0] == symbol && grid[1][0] == symbol && grid[2][0] == symbol) ||
            (grid[0][1] == symbol && grid[1][1] == symbol && grid[2][1] == symbol) ||
            (grid[0][2] == symbol && grid[1][2] == symbol && grid[2][2] == symbol));
        }

        bool checkDiagonals(char grid[3][3])
        {
            return ((grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol) ||
            (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol));
        }
};

void displayGrid(char grid[3][3]) {
    for(int i = 1; i <= 17; i++)
    {
        for (int j = 1; j <= 17; j++)
        {
            if((j%3 == 0 && i%3 == 0) && (j%6 != 0 && i%6 != 0))
            {
                cout << grid[i/6][j/6] << ' ';
                continue;
            }

            if(j%6 == 0)    cout << '|';
            else    cout << ' ';

            if(i%6 == 0)    cout << '_';
            else    cout << ' ';
        }
        cout << endl;
    }
}

bool isGameComplete(char grid[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(grid[i][j] == ' ')
                return false;
        }
    }
    return true;
}

int main()
{
    Player player1('X', "player");
    Player player2('O', "computer");
    unsigned short int player_turn = 1;
    bool used_choices[9] = {false, false, false, false, false, false, false, false, false};
    char grid[3][3] =  {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}};

    srand(time(0));
    displayGrid(grid);

    do{
        if(player_turn == 1)
        {
            player1.makeAMove(grid, used_choices);
            displayGrid(grid);
            if(player1.Won(grid))
            {
                cout << "!!! PLAYER 1 WON !!!\n";
                break;
            }
            player_turn = 2;
        }
        else
        {
            player2.makeAMove(grid, used_choices);
            displayGrid(grid);
            if(player2.Won(grid))
            {
                cout << "!!! PLAYER 2 WON !!!\n";
                break;
            }
            player_turn = 1;
        }
    }while(!isGameComplete(grid)); 

    return 0;
}