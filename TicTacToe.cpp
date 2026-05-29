#include <iostream>
using namespace std;

string player1Name, player2Name;
string player1Character, player2Character;

string table[3][3] =
   {
   "11", "12", "13",
   "21", "22", "23",
   "31", "32", "33"
   };

//This method displays the table on the console.
void writeTable(string table[][3])
{
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
         cout << table[i][j] << ' ';

      cout << "\n";
   }
}

/*
This method modifies the table on the player's input. 
If the given coordinates are out of range or this field already contains an x or o
the method calls itself.
*/
void modifyTable(string table[][3], string playerCharacter, int coordinates)
{
   if(coordinates/10 <= 3 && coordinates % 10 <= 3 && coordinates > 0)
      if(table[(coordinates/10)-1][(coordinates%10)-1] != "o" && table[(coordinates/10)-1][(coordinates%10)-1] != "x")
      {
         table[(coordinates/10)-1][(coordinates%10)-1] = playerCharacter;
         writeTable(table);
      }     
      else
      {
         cout << "This field is already occupied! Try another! \n";
         cin >> coordinates;
         modifyTable(table, playerCharacter, coordinates);
      }
   else
   {
      cout << "Out of range! Try again! \n";
      cin >> coordinates;
         modifyTable(table, playerCharacter, coordinates);
   }
}

/*
This method checks if in table are three x or o characters in the same a row, column or diagonal. 
If there are returns a true value.
*/
int isThreeInARow(string table[][3], string playerCharacter)
{
   bool isThreeInARow = true;
   int ok = 0;

   for(int i = 0; i < 3; i++)
   {
      ok = 0;
      for(int j = 0; j < 3; j++)
         if(table[i][j] != playerCharacter)
         {
            ok--;
            break;
         }
      if(ok == 0)
         return isThreeInARow;
   }

   for(int i = 0; i < 3; i++)
   {
      ok = 0;
      for(int j = 0; j < 3; j++)
         if(table[j][i] != playerCharacter)
         {
         ok--;
         break;
         }

      if(ok == 0)
         return isThreeInARow;
   }
        
   ok = 0;

   for(int j = 0; j < 3; j++)
   {
      if(table[j][j] != playerCharacter)
      {
            ok--;
            continue;
      }
      
   }
   
   if(ok == 0)
      return isThreeInARow;

   ok = 0;

   for(int j = 0; j < 3; j++)
   {
      if(table[j][2-j] != playerCharacter)
      {
            ok--;
            continue;
      }   
   }

   if(ok == 0)
      return isThreeInARow;

   return false;
}

//This method is called when the game is over, but the players want a replay. Restores the modified table.
void restoreTable(string table[][3])
{
   string originalTable[3][3] = 
   {
   "11", "12", "13",
   "21", "22", "23",
   "31", "32", "33"
   };

   for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
         table[i][j] = originalTable[i][j];
}

/*
This method is called when one of the players wins 
or when the game ends in a draw.
Displays a game over message and the current score.
*/
void gameOver(string playerName, int& player1Score, int& player2Score, int playerIndex, bool isDraw)
{

   if(playerIndex == 1)
      player1Score += 1;
   else
      if(playerIndex == 2)
         player2Score += 1;

   if(!isDraw)
   {
      cout << "Game over! " << playerName << " won! \n";
   }    
   else
      cout << "Game over! Draw! \n";

   cout << "Current score: " << player1Score << ':' << player2Score << "\n";

}

/*
When the game is over displays a "Rematch?" message. If the answer is "yes"
calls the restoreTable() method, then displays a cleared table. 
It sets the remainingPosition variable to 9 and returns a true value.
Otherwise case returns false.
*/
bool rematch(int& remainingPosition, string table[][3])
{
   string rematch;
   cout << "Want a rematch (yes/no)? \n";
   cin >> rematch;

   if(rematch == "yes")
   {
      restoreTable(table);
      writeTable(table);
      remainingPosition = 9;
      return true;
   }
   else
      return false;
}

/*
This method is called at the start of the game.
Asks the players to set a username and a character to play with (x or o).
*/
void start()
{
   string playerChoice;

   cout << "Player 1: choose your username: \n";
   cin >> player1Name;

   cout << "Player 2: choose your username: \n";
   cin >> player2Name;

   cout << player1Name << ": choose a character (x or o): \n";
   cin >> playerChoice;

   while(playerChoice != "x" && playerChoice != "o")
   {
      cout << "You have chosen an invalid character. Please choose between x or o! \n";
      cin >> playerChoice;
   }

   if(playerChoice == "x")
   {
      player1Character = 'x';
      player2Character = 'o';
   }
   else
   {
      player1Character = 'o';
      player2Character = 'x';
   }
}

/*
This method manages the entire gameflow.
Until the game is over asks the players to make a move. 
At every input reduces the remainingPosition's value,
calls the modifyTable and isThreeInARow() methods. If isThreeInARow() 
returns true the rematch() method is called. If it returns true the game
continues, otherwise ends.
If the remainingPosition reaches 0 the game ends in a draw. The rematch() is called again.
*/
void update()
{
   bool isGameOver = false;

   int remainingPosition = 9;
   int player1Score = 0, player2Score = 0;

   writeTable(table);

   while(!isGameOver)
   {
      int player1Coordinate, player2Coordinate;

      cout << player1Name << " choose a number shown on the screen \n";
      cin >> player1Coordinate;
      
      remainingPosition--;

      modifyTable(table, player1Character, player1Coordinate);

      if(isThreeInARow(table, player1Character))
      {
         gameOver(player1Name, player1Score, player2Score, 1, false);

         if(!(rematch(remainingPosition, table)))
            break;
      }
      
      if(remainingPosition == 0)
      {
         gameOver(player1Name, player1Score, player2Score, 0, true);

         if(!(rematch(remainingPosition, table)))
            break;
      }

      cout << player2Name << " choose a number shown on the screen \n";
      cin >> player2Coordinate;

      remainingPosition--;

      modifyTable(table, player2Character, player2Coordinate);

         
      if(isThreeInARow(table, player2Character))
      {
         gameOver(player2Name, player1Score, player2Score, 2, false);

         if(!(rematch(remainingPosition, table)))
            break;
      }

      if(remainingPosition == 0)
      {
         gameOver(player1Name, player1Score, player2Score, 0, true);

         if(!(rematch(remainingPosition, table)))
            break;
      }
   }
}

int main()
{  

   start();
   update();

   return 0;
}
