## Tic-Tac-toe
This was a challenge from the teacher. He wanted to test our coding skills. The main task was just to check whether the matrix contains 3 x/o in a row, column or diagonal. If so display x/y won, otherwise if every field is taken display "Draw".
I was the only student who built a fully playable game.

# How it works?
The code displays a message to the users, to pick a username and a character (x or o), then a table.
The players have to pick a number shown on the project window.
The code constantly checks if there are three x/o in a row/column/diagonal. In this case displays the winner, the current score and a "Rematch" message. The players have two options: to restart the game or quit. If their choice is to restart the table restores.
If every field has been occupied the game ends in a draw.

# Safety features
If the entered number's digits are bigger than 3 or less than 1 or the number is less than 0
the program asks the player to pick another number.
If the entered character is not x or o, the program asks the player to pick x or o.
