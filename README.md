# Sudoku-app-C-and-Qt-DEFINITION OF DONE MVP

This is a classic sudoku app developed using C++ and will adhere the following basic outline:
    - Basic sudoku (everyone's favourite game), 9x9 cells.
    - The game will support three difficulties, easy/medium/hard.
    - It will accept input via the keyboard and mouse.
    - Each cell will can be marked with a digit from 1-9.


RULES OF GAME
    - The goal of sudoku is to completely fill a field comprised of 9x9 cells each accepting a single digit. 
    - Each row, column and square should be comprised of each digit between 1-9. 
    - A digit can NOT appear twice or else the player loses/have done it incorrectly. 
    - The player has infinte amount of tries and can erase previously filled in numbers. 

TECHNICAL ASPECT OF GAME
    C++ standard and build   
    - Built using C++20, CMake project.
    - Versioning semantic 0.1.0 for MVP.
    GUI 
    - QT 6 (Widgets)
        Pros: Native look great text rendering, high-DPI, easy menys/dialogs, first-class packaging tools.
        Packaging: (windeployqt for windows)

PROJECT STRUCTURE
    /app    -> main(), DI/Wiring, settings, resources
    /core   -> pure C++: Board, Rules, Solver, Generator, Gamestate, Persistance
    /ui     -> widgets/views, input handeling, rendering
    /assets -> fonts, icons 

This project uses the Qt framework under the LGPL license

TO BE INCLUDED IN FUTURE:
    - The player should be able to save the current state and then reopen and continue upon closing. 
    - Unit tests: GoogleTest, /tests  -> unit + property tests.
