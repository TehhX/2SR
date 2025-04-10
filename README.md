# Two Suits and a Royal (2SR)
This is a CLI based implementation of my game Two Suits and a Royal (2SR) made in C++. It allows playing against another player, a CPU, or to simulate n trials between two CPU's given some parameters.

## Game Rules
* This game takes two players and a standard 52-card deck of cards (jokerless)
* Both players pick a primary and secondary suit (Hearts, diamonds, spades or clubs) and a Royal (Jack, Queen, King).
* Both players take turns drawing cards until one of them reaches 300 points, or until the deck is exhausted.
* If the deck is exhausted, the player with the most points is declared the winner.
* The players then tally up their points according to the following table:

|                    |   Unchosen Suit |  Secondary Suit |    Primary Suit |
|-------------------:|----------------:|----------------:|----------------:|
|        **Numeral** | CV (Card Value) |           2x CV |           4x CV |
| **Unchosen Royal** |              10 |              20 |              40 |
|   **Chosen Royal** |              50 |             100 |             200 |

Score is automatically tracked by this program, but if you play by hand you will need a scoresheet or similar.

## Compiling
This program uses CMake to compile and run for the most compatability. The CMakeLists.txt file is in the root folder, and handles the whole program. It is sufficient to run cmake from there when building. If using VSCode, the [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension is reccomended, but not required.

## Running
Execute the output file using either ``` ./2SR ``` or ``` 2SR.exe ``` (assuming a file name of 2SR) in your terminal, appending the amount of trials you want to run followed by the amount of real players. An example execution in the Windows command line is as follows: ``` C:\2SR\build> 2SR.exe 100 0 ```. This runs 100 trials with no real players.

## Reading the Logger Output
A log file (log.csv) will be output on program completion that contains the entire game's events, including cards drawn, scores, as well as total moves, and average moves per trial. It can be opened in a text editor, or spreadsheet editor like Excel or LibreOffice Calc.

## Logger Output Format
The output log.csv will have the following format:

|  TotalMoves  |  AverageMoves  |           |                 |
|:------------:|:--------------:|:---------:|:---------------:|
|      tm      |       am       |           |                 |
| **RoundNum** |    **Suit**    | **Value** | **TotalPoints** |
|      t       |       s        |     v     |        tp       |
|     ...      |      ...       |    ...    |       ...       |
