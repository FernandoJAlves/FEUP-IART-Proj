# FEUP-IART

## Compilation and Execution

    1) Open the terminal/cmd on the project's directory.

    2) To compile the project run on the terminal:
        
        @bash: make

    3) Run the project by typing:
        
        @bash: run


## How to play

    When executing the program you will be presented with 3 game mode options in the main menu:

    1) Human Player - Where you can play the game after choosing the level desired.
   
    2) Bot Player - Where you can see the bot solving the game puzzles with a specific search method.
    
    3) Leave Game - Where you can simply leave the game.


### Human Game Mode

    Exemple map
    X X X X X X X
    X a X       X
    X   X   X   X
    X   X   X   X
    X   X   X   X
    X     b   A X
    X X X X X X X

    - When playing in this mode you can select a robot(that will be represented with a char e.g. 'a') and 
    the direction which he can move(a-left, s-down, d-right, w-up) to reach the objective which is its uppercase letter,
    in this case for 'a' is the cell 'A'.
    - For instance, in the 'Example Map' if you type 'as' you select the robot 'a' and tell him to move down until he
    finds an obstacle, which can be a wall or another robot.

    Exemple map after play:'as'
    X X X X X X X
    X   X       X
    X   X   X   X
    X   X   X   X
    X   X   X   X
    X a   b   A X
    X X X X X X X

    -You can quit a current game by typing 'qq' or 'QQ'.
    -You can also request an help move from the game by typing 'hh' or 'HH'.


### Bot Game Mode

    -In this mode after selecting the game level and the search method to use you can check the bot 
    solving the puzzle and some statistics such as the number of steps, the nodes expanded in the game tree
    and the time needed to reach that puzzle solution.
    -In the search methods 'Greedy-Search' and 'A*' you can also choose an heuristic to use from the five possible.
