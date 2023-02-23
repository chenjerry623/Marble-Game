// evenwins6.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Jerry Chen
// St.# : 301539072
// Email: jjc55@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough detail
// so that someone can see the exact source and extent of the borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
//
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// global variables
/*
int marbles_in_middle = -1;
int human_marbles = -1;
int computer_marbles = -1;

int player_wins = 0;
int computer_wins = 0;
*/

enum class Player {
    human,
    computer
};

struct GameState {
    int marbles_in_middle;
    int human_marbles;
    int computer_marbles;
    int player_wins;
    int computer_wins;
    Player whose_turn;
};


void welcome_screen() {
    cout << "+-----------------------+\n";
    cout << "| Welcome to Even Wins! |\n";
    cout << "+-----------------------+\n";
    cout << "Even Wins is a two-person game. You start with\n";
    cout << "27 marbles in the middle of the table.\n";
    cout << "\n";
    cout << "Players alternate taking marbles from the middle.\n";
    cout << "A player can take 1 to 4 marbles on their turn, and\n";
    cout << "turns cannot be skipped. The game ends when there are\n";
    cout << "no marbles left, and the winner is the one with an even\n";
    cout << "number of marbles.";
    cout << "\n";
}

string marbles_str(int n) {
    if (n == 1) return "1 marble";
    return to_string(n) + " marbles";
}

void choose_first_player(GameState& state) {
    for (;;) {
        cout << "\nDo you want to play first? (y/n) --> ";
        string ans;
        cin >> ans;
        if (ans == "y") {
            state.whose_turn = Player::human;
            return;
        }
        else if (ans == "n") {
            state.whose_turn = Player::computer;
            return;
        }
        else {
            cout << "\nPlease enter 'y' if you want to play first,\n";
            cout << "or 'n' if you want to play second.\n";
        }
    }
} // choose_first_player

void next_player(GameState& state) {
    // check who just had a turn and switch to the next player
    state.whose_turn = (state.whose_turn == Player::human) ? Player::computer : Player::human;
}

void print_board(GameState state) {
    cout << "\n";
    cout << " marbles in the middle: " << state.marbles_in_middle
        << " " << string(state.marbles_in_middle, '*') << "\n";
    cout << "    # marbles you have: " << state.human_marbles << "\n";
    cout << "# marbles computer has: " << state.computer_marbles << "\n";
    cout << "\n";
}

// returns true if s is an int, and false otherwise
// https://www.cplusplus.com/reference/string/stoi/
bool is_int(const string& s) {
    try {
        stoi(s); // throws an invalid_argument exception if conversion fails
        return true;
    }
    catch (...) {
        return false;
    }
}

void human_turn(GameState& state) {
    // get number in range 1 to min(4, marbles_in_middle)
    int max_choice = min(4, state.marbles_in_middle);
    cout << "It's your turn!\n";
    for (;;) {
        cout << "Marbles to take? (1 - " << max_choice << ") --> ";
        string s;
        cin >> s;
        if (!is_int(s)) {
            cout << "\n  Please enter a whole number from 1 to " << max_choice
                << "\n";
            continue;
        }

        // convert s to an int so it can be compared
        int n = stoi(s);
        if (n < 1) {
            cout << "\n  You must take at least 1 marble\n";
            continue;
        }
        if (n > max_choice) {
            cout << "\n  You can take at most " << marbles_str(max_choice)
                << "\n";
            continue;
        }

        cout << "\nOkay, taking " << marbles_str(n) << " ...\n";
        state.marbles_in_middle -= n;
        state.human_marbles += n;

        return;
    } // for
} // human_turn

/*
For my AI, I have the AI try to maintain an even number of marbles by always
 taking 4 marbles when the middle marbles is above 4, this way, the number of AI marbles will
 always be even. Once the number of middle marbles goes below 4, I have the AI take as many marbles
 as possible while still staying even, this means the game will either end with the AI taking all the remaining
 marbles and being even, or the AI will take 3 marbles, get even, and then force the player to end the game by
 taking the final marble. Although this is an effective strategy that's far better than random, it does not garuntee
 victory if the AI is playing second. The player can either go first and follow the same strategy, or only take 2 at
 a time if they're going second. This would result in the player reaching a situation where they can take the final
 "move" before the marbles run out, and thus decide whether they end the game as even or odd.
*/


void computer_turn(GameState& state) {
    cout << "It's the computer's turn ...\n";
    int max_choice = min(4, state.marbles_in_middle);
    int numTake = 0;
    // when more than 4 marbles are available, just try to keep own marbles even
    if (state.marbles_in_middle > 4)
    {
        numTake = 4;
    }
    
    //once the marbles are under 4, take the highest possible even # if you have even and an odd # if you have odd
    else if (state.marbles_in_middle == 4)
    {

        
        if (state.computer_marbles % 2 == 0)
        {
            numTake = 4;
        }
        else
        {
            numTake = 3;
        }
    }

    else if (state.marbles_in_middle == 3)
    {
        if (state.computer_marbles % 2 == 0)
        {
            numTake = 2;
        }
        else
        {
            numTake = 3;
        }
    }

    else if (state.marbles_in_middle == 2)
    {
        if (state.computer_marbles % 2 == 0)
        {
            numTake = 2;
        }
        else
        {
            numTake = 1;
        }
    }

    else if (state.marbles_in_middle == 1)
    {
        numTake = 1;
    }

    cout << "Computer takes " << numTake << " ...\n";
    state.marbles_in_middle -= numTake;
    state.computer_marbles += numTake;
}

void game_over(GameState& state) {
    cout << "\n";
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
        << "!! All the marbles are taken: Game Over !!\n"
        << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";

    print_board(state);

    if (state.human_marbles % 2 == 0) {
        cout << "You are the winner! Congratulations!\n";
        state.player_wins += 1;
    }
    else {
        // generates random number and decides the taunt based on it
        srand(time(NULL));
        int rNum = rand() % 5;
        if (rNum == 0)
        {
            cout << "The computer wins: tremble before it's mighty brain!\n";
        }

        else if (rNum == 1)
        {
            cout << "The computer wins: hold this L nerd!\n";
        }

        else if (rNum == 2)
        {
            cout << "The computer wins: RIP BOZO!\n";
        }

        else if (rNum == 3)
        {
            cout << "The computer wins: what are you going to do, cry?\n";
        }

        else if (rNum == 4)
        {
            cout << "The computer wins: just give up already xD \n";
        }

        state.computer_wins++;
    }

    cout << "Statistics" << endl;
    cout << "total games: " << state.player_wins + state.computer_wins << endl;
    cout << "human wins: " << state.player_wins << endl;
    cout << "computer wins: " << state.computer_wins << endl;
}

void play_game(GameState& state) {
    // initialize the game state
    state.marbles_in_middle = 27;
    state.human_marbles = 0;
    state.computer_marbles = 0;

    print_board(state);

    for (;;) {
        if (state.marbles_in_middle == 0) {
            game_over(state);
            return;
        }
        else if (state.whose_turn == Player::human) {
            human_turn(state);
            print_board(state);
            next_player(state);
        }
        else if (state.whose_turn == Player::computer) {
            computer_turn(state);
            print_board(state);
            next_player(state);
        }
    } // for
} // play_game

int main() {

    struct GameState state;

    state.marbles_in_middle = -1;
    state.human_marbles = -1;
    state.computer_marbles = -1;
    state.player_wins = 0;
    state.computer_wins = 0;

    srand(time(NULL));

    welcome_screen();

    for (;;) {
        choose_first_player(state);

        play_game(state);

        // ask if the user if they want to play again
        cout << "\nWould you like to play again? (y/n) --> ";
        string again;
        cin >> again;

        if (again == "y") {
            cout << "\nOk, let's play again ...\n";
        }
        else {
            cout << "\nOk, thanks for playing ... goodbye!\n";
            return 0;
        }
    } // for
} // main
