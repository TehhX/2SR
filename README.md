# Two Suits and a Royal (2SR)

This is a CLI based implementation of my game Two Suits and a Royal (2SR) made in C++. It allows playing against another player, a CPU, or to simulate n trials between two CPU's given some parameters.

## Game Rules

* This game takes two players and a standard 52-card deck of cards (jokerless)
* Both players pick a primary and secondary suit (Hearts, diamonds, spades or clubs) and a Royal (Jack, Queen, King).
* Both players take turns drawing cards until one of them reaches 600 points, or until the deck is exhausted.
* If the deck is exhausted, the player with the most points is declared the winner.
* The players then tally up their points according to the following table:

|                    |   Unchosen Suit |  Secondary Suit |    Primary Suit |
|-------------------:|----------------:|----------------:|----------------:|
|        **Numeral** |      Card Value |   2x Card Value |   4x Card Value |
| **Unchosen Royal** | Same as Numeral | Same as Numeral | Same as Numeral |
|   **Chosen Royal** |              25 |              75 |             150 |

Score is automatically tracked by this program, but if you play by hand you will need a scoresheet or similar.

## Compiling and running

This program uses CMake to compile and run for the most compatability. The CMakeLists.txt file is in the root folder, and handles the whole program. It is sufficient to run cmake from there when building.
