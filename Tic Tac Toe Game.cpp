#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <thread>
using namespace std;

// Represents a node in the Minimax tree
class Node 
{
public:
    vector<vector<char>> state;
    int score;
    vector<Node*> children;

    Node(vector<vector<char>> state)
    {
        this->state = state;
        score = 0;
    }
};

// Function to print the Tic Tac Toe board
void PrintBoard(const vector<vector<char>>& board)
{
    cout << "-------------\n";
    for (int i = 0; i < 3; ++i) 
    {
        cout << "| ";
        for (int j = 0; j < 3; ++j) 
        {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

// Function to check if a move is valid
bool IsValidMove(const vector<vector<char>>& board, int row, int col)
{
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
}

// Function to check if the current state of the board is a winning state
char CheckWin(const vector<vector<char>>& board) 
{
    // Check rows
    for (int i = 0; i < 3; ++i) 
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
    }

    // Check columns
    for (int j = 0; j < 3; ++j) 
    {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
            return board[0][j];
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    // Check for draw
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            if (board[i][j] == ' ')
                return ' ';
        }
    }
    return 'D'; // Draw
}

// Function to generate all possible successor states for a given player
vector<Node*> Successor(const vector<vector<char>>& state, char player)
{
    vector<Node*> successors;
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            if (state[i][j] == ' ') 
            {
                vector<vector<char>> newState = state;
                newState[i][j] = player;
                Node* newNode = new Node(newState);
                successors.push_back(newNode);
            }
        }
    }
    return successors;
}

// Minimax function to find the optimal move for the AI player
int Minimax(Node* node, char player) 
{
    char winner = CheckWin(node->state);
    if (winner != ' ')
        return (winner == 'X') ? -1 : 1; //Utility
    if (winner == 'D')
        return 0;

    vector<Node*> children = Successor(node->state, player);

    if (player == 'O') 
    { // Maximizing player
        int bestScore = numeric_limits<int>::min();
        for (Node* child : children) 
        {
            int score = Minimax(child, 'X');
            bestScore = max(bestScore, score);
        }
        return bestScore;
    }
    else 
    { // Minimizing player
        int bestScore = numeric_limits<int>::max();
        for (Node* child : children) 
        {
            int score = Minimax(child, 'O');
            bestScore = min(bestScore, score);
        }
        return bestScore;
    }
}

// Function to make a move for the AI player using Minimax algorithm
void MakeComputerMove(vector<vector<char>>& board) 
{
    Node* rootNode = new Node(board);      //  the root of the tree is the current state of the game board
    int bestScore = numeric_limits<int>::min();     
    int bestMoveRow = -1, bestMoveCol = -1;

    vector<Node*> children = Successor(rootNode->state, 'O');    

    for (Node* child : children) 
    {
        int score = Minimax(child, 'X');
        if (score > bestScore)
        {
            bestScore = score;
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    if (child->state[i][j] != board[i][j]) 
                    {
                        bestMoveRow = i;
                        bestMoveCol = j;
                    }
                }
            }
        }
    }

    board[bestMoveRow][bestMoveCol] = 'O';


}


void IdentifyPlayerMove(short& Row, short& Col)
	{
		cout << "Row? ";
		cin >> Row;
		cout << "Column? ";
		cin >> Col;
		--Row;
		--Col;
	}


void WaitSecondsBeforeComputerMakeMove(int seconds)
{
    this_thread::sleep_for(chrono::seconds(seconds));
}


void StartGame()
{
    vector<vector<char>> board =
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char currentPlayer = 'X';
    while (true)
    {
        system("cls");
        PrintBoard(board);

        if (currentPlayer == 'X')
        {
            short row, col;
            IdentifyPlayerMove(row, col);
            if (IsValidMove(board, row, col))
                board[row][col] = 'X';
            else
            {
                cout << "Invalid move! Try again.\n";
                continue;
            }
            system("cls");
        }
        else
        {
            WaitSecondsBeforeComputerMakeMove(1);
            MakeComputerMove(board);
        }

        char winner = CheckWin(board);
        if (winner != ' ')
        {
            system("cls");
            PrintBoard(board);
            if (winner == 'X')
                cout << "You win -)\n";
            else if (winner == 'O')
                {
   		  system("color 4f");
                  cout << "Computer wins!\n";
		}
            else
	    {
		system("color 6f");
                cout << "It's a draw!\n";
	    }
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}



int main() 
{
    system("color 3f");
    StartGame();

    system("pause>0");
}

