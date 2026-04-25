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


void WriteTable(string table[][3])
{
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
         cout << table[i][j] << ' ';

      cout << "\n";
   }
}

void ModifyTable(string table[][3], string playerCharacter, int coordinates)
{

   table[(coordinates/10)-1][(coordinates%10)-1] = playerCharacter;

   WriteTable(table);
}

int IsThreeInARow(string table[][3], string playerCharacter)
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

void RestoreTable(string table[][3])
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

void GameOver( string playerName, int player1Score, int player2Score, int playerIndex, bool isDraw)
{

   if(playerIndex == 1)
      player1Score += 1;
   else
      if(playerIndex == 2)
         player2Score += 1;

   if(!isDraw)
   {
      cout << "Jatek vege! " << playerName << " nyert \n";
   }    
   else
      cout << "Jatek vege! Dontetlen! \n";

   cout << "Jelenlegi allas: " << player1Score << ':' << player2Score << "\n";

}

bool Restart(int remainingPosition, string table[][3])
{
   string rematch;
   cout << "Visszavago (igen/nem)? \n";
   cin >> rematch;

   if(rematch == "igen")
   {
      remainingPosition = 9;
      RestoreTable(table);
      WriteTable(table);

      return true;
   }
   else
      return false;
}

void Start()
{
   string playerChoice;

   cout << "1. jatekos: add meg a felhasznalo neved: \n";
   cin >> player1Name;

   cout << "2. jatekos: add meg a felhasznalo neved: \n";
   cin >> player2Name;

   cout << player1Name << ": valaszd ki, hogy x vagy o: \n";
   cin >> playerChoice;

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

void Update()
{
   bool isGameOver = false;

   int remainingPosition = 9;
   int player1Score = 0, player2Score = 0;

   WriteTable(table);

   while(!isGameOver)
   {
      int player1Coordinate, player2Coordinate;

      cout << player1Name << " add meg a tablazatban lathato szamot \n";
      cin >> player1Coordinate;
      
      remainingPosition--;

      ModifyTable(table, player1Character, player1Coordinate);

      if(IsThreeInARow(table, player1Character))
      {
         GameOver(player1Name, player1Score, player2Score, 1, false);

         if(Restart(remainingPosition, table))
            break;
      }
      
      if(remainingPosition == 0)
      {
         GameOver(player1Name, player1Score, player2Score, 0, true);

         if(Restart(remainingPosition, table))
            break;
      }

      cout << player2Name << " add meg a tablazatban lathato szamot \n";
      cin >> player2Coordinate;

      remainingPosition--;

      ModifyTable(table, player2Character, player2Coordinate);

         
      if(IsThreeInARow(table, player2Character))
      {
         GameOver(player2Name, player1Score, player2Score, 2, false);

         if(Restart(remainingPosition, table))
            break;
      }
   }
}

int main()
{  

   Start();
   Update();

   return 0;
}