#include <iostream>
using namespace std;

string player1Name, player2Name, rematch;
string playerChoice, player1Character, player2Character;

int player1Coordinate, player2Coordinate;
int player1Score = 0, player2Score = 0;

int gameOver = 0;

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
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
         if(table[i][j] == table[i][j+1] && table[i][j+1] == table[i][j+2])
            if(table[i][j] == playerCharacter)
               return 1;
         else
            if(table[j][i] == table[j][i+1] && table[j][i+1] == table[j][i+2])
               if(table[i][j] == playerCharacter)
                  return 1;
         
      if(table[i][i] == table[i][i+1] && table[1][i+1] == table[i][i+2])
         if(table[i][i] == playerCharacter)
            return 1;
      
      if(table[i][2-i] == table[i][3-i] && table[1][3-i] == table[i][4-i])
         if(table[i][i] == playerCharacter)
            return 1;
   }

   return 0;
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

void Start()
{
   cout << "1. jatekos: add meg a felhasznalo neved: \n";
   cin >> player1Name;

   cout << "2. jatekos: add meg a felhasznalo neved: \n";
   cin >> player2Name;

   cout << "1. jatekos: valaszd ki, hogy x vagy o: \n";
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
   int player1InputCount = 0, player2InputCount = 0, remainingPosition = 9;

   WriteTable(table);

   while(gameOver == 0)
   {

      cout << player1Name << " add meg a tablazatban lathato szamot \n";
      cin >> player1Coordinate;
      
      remainingPosition--;

      ModifyTable(table, player1Character, player1Coordinate);


      if(IsThreeInARow(table, player1Character) == 1)
      {
         cout << "Jatek vege!" << player1Name << " nyert \n";
         cout << "Jelenlegi allas:" << player1Score << ':' << player2Score << "\n";

         cout << "Visszavago (igen/nem)? \n";
         cin >> rematch;

         if(rematch == "igen")
         {
            remainingPosition = 9;
            RestoreTable(table);
            continue;
         }
         else
         {
            gameOver == 1;
            continue;
         }

      }
      

      cout << player2Name << " add meg a tablazatban lathato szamot \n";
      cin >> player2Coordinate;

      remainingPosition--;

      ModifyTable(table, player2Character, player2Coordinate);

         
      if(IsThreeInARow(table, player2Character) == 1)
      {
         cout << "Jatek vege!" << player2Name << " nyert \n";
         cout << "Jelenlegi allas:" << player1Score ++ << ':' << player2Score << "\n";

         cout << "Visszavago (igen/nem)? \n";
         cin >> rematch;

         if(rematch == "igen")
         {
            remainingPosition = 9;
            RestoreTable(table);
            continue;
         }
         else
         {
            gameOver == 1;
            continue;
         }

      }
      
      if(remainingPosition == 0)
      {
         cout << "Jatek vege! Dontetlen! \n";
         cout << "Jelenlegi allas:" << player1Score << ':' << player2Score++ << "\n";

         cout << "Visszavago (igen/nem)? \n";
         cin >> rematch;

         if(rematch == "igen")
         {
            remainingPosition = 9;
            RestoreTable(table);
            continue;
         }
         else
         {
            gameOver == 1;
         }
      }

   }

}

int main()
{  

   Start();
   Update();

   return 0;
}