#include <string>
#include <iostream>
#include <sstream>
#include "../headers/Board.h"
#include "../headers/Computer.h"
#include "../headers/Players.h"

int main(){
    std::string command;
    bool blackTurn{false};
    bool currPlaying{false};
    bool blackIsComputer{false};
    bool whiteIsComputer{false};
    int whiteLevel = 0;
    int blackLevel = 0;
    Board b{};
    Players whitePlayer{'w'}; 
    Players blackPlayer{'b'};
    Computer blackComp{'b'};
    Computer whiteComp{'w'};
    std::cout << "Enter the Commands" << std::endl;
    while (std::cin >> command) {
        std::pair<int, int>src;
        std::pair<int, int>dest;
        if(currPlaying){
            if(blackTurn && blackIsComputer){
                if(blackLevel == 1){
                    pair<pair<int, int>, pair<int, int>> gen = whiteComp.L1_GetMove(b);
                    src = gen.first;
                    dest = gen.second;
                }
                if(blackLevel == 2){
                    pair<pair<int, int>, pair<int, int>> gen = whiteComp.L2_GetMove(b);
                    src = gen.first;
                    dest = gen.second;
                }
                if(blackLevel == 3){
                    pair<pair<int, int>, pair<int, int>> gen = whiteComp.L3_GetMove(b);
                    src = gen.first;
                    dest = gen.second;
                }
                b.move(src, dest);
            }
            if(!blackTurn && whiteIsComputer){
                if(whiteLevel == 1){
                    pair<pair<int, int>, pair<int, int>> gen = whiteComp.L1_GetMove(b);
                    src = gen.first;
                    dest = gen.second;
                }
                if(whiteLevel == 2){
                    pair<pair<int, int>, pair<int, int>> gen = whiteComp.L2_GetMove(b);
                    src = gen.first;
                    dest = gen.second;
                }
                if(whiteLevel == 2){
                    pair<pair<int, int>, pair<int, int>> gen = whiteComp.L3_GetMove(b);
                    src = gen.first;
                    dest = gen.second;
                }
            }

        }

        if (!currPlaying && command == "game" ) {
            b.init();
            std::cout << b << endl;
            std::string white,black;
            std::cin >> white >> black;
            if(white == "human"){
                cout << "White is a human player" << endl;
            }else{
                for(char c : black){
                    if(isdigit(c)) whiteLevel = c - '0';
                }
                std::cout << white << whiteLevel << std::endl;
                whiteIsComputer = true; 
            }

            if(black == "human"){
                cout << "Black is a human player" << endl;
            }else{
                for(char c : black){
                    if(isdigit(c)) blackLevel = c - '0';
                }
                std::cout << black << " " << blackLevel << std::endl;
                blackIsComputer = true;
            }
            currPlaying = true;
        }else if( command == "move"){
            
            std::string coord;
            char srcCol, destCol; //it is a char but we change it to int using enum
            int srcRow, destRow;
            std::cin >> srcCol >> srcRow >> destCol >> destRow;
            std::pair<int, int>src{srcRow, srcCol - 'a' + 1};
            std::pair<int, int>dest{destRow, destCol - 'a' + 1};
            int result = b.move(src, dest);
            if(result == -1){
                cout << "Enter the correct move" << endl;
                cout << "Current Player is: " << b.whoseTurn() << endl;
            }
            cout << b << endl;

            if(b.promotionAvailable()){
                cout << "Promotion Available for " << b.whoseTurn() <<endl;
                cout << "Enter the Piece **Lower case for Black and Capital Case for White**" << endl;
                char p;
                while(std::cin >> p){
                    if(islower(p) && blackTurn){
                        if(p == 'q' || p == 'r' || p == 'n' || p == 'b'){
                                b.promote(p);
                                break;
                        }
                    }
                    if((isupper(p) && !blackTurn)){
                        if(p == 'Q' || p == 'R' || p == 'N' || p == 'B'){
                                b.promote(p);
                                break;
                        }
                    }
                    cout << "Enter the correct character for " << b.whoseTurn() <<endl;
                }

            }

            int winner = b.getWinner();
            if(winner == 0){
                cout << "Stealmate" << endl;
                currPlaying = false;
            }
            if(winner == 1){
                cout << "Checkmate! White wins" << endl;
                if(!whiteIsComputer) whitePlayer.win();
                else whiteComp.win();
                currPlaying = false;
            }
            if(winner == 2){
                cout << "Checkmate! Black wins" << endl;
                if(!blackIsComputer) blackPlayer.win();
                else blackComp.win();
                blackPlayer.win();
                currPlaying = false;
            }else{
                if(b.inCheck(*b.bKing)) cout << "Black is in Check" << endl;
                if(b.inCheck(*b.wKing)) cout << "White is in Check" << endl;
            }
            if(result == 0) blackTurn = !blackTurn;
        }
        else if (currPlaying && command == "resign") {
            //black resign increase white's score
            if(blackTurn){
                std::cout << "Black Resigns" << std::endl;
                whitePlayer.win();
            }else if(!blackTurn){ //white resign increase black's score
                std::cout << "White Resign" << std::endl;
                blackPlayer.win();
            } 
            currPlaying = false;
        }
        else if (!currPlaying && command == "setup") {
            std::string option;
            bool done = false;
            while(!done && std::cin >> option){
                if(option == "+"){
                    int srcRow;
                    char c,srcCol;
                    std::cin >> c >> srcCol >> srcRow;
                    std::pair<int, int>src{srcRow, srcCol - 'a' + 1};
                    std::cout << src.first << " " << src.second << " " << c << std::endl;
                    b.add(src, c);
                    cout << b << endl;
                    //add  piece c
                }else if(option == "-"){
                    int srcRow;
                    char srcCol;
                    std::cin >> srcCol >> srcRow;
                    std::pair<int, int>src{srcRow, srcCol - 'a' + 1};
                    std::cout << src.first << " " << src.second << std::endl;
                    b.remove(src);
                    cout << b << endl;
                    //remove a piece from src
                }else if(option == "="){
                    std::string colour;
                    std::cin >> colour;
                    if(colour == "black"){
                        blackTurn = true;
                        std::cout << "Black Turn" << std::endl;
                    }else if(colour == "white"){
                        blackTurn = false;
                        std::cout << "White Turn" << std::endl;
                    }
                }else if(option == "done"){
                    bool verified = b.verifySetup();
                    if(verified){
                        done = true;
                        std::cout << "Setup done" <<std::endl;
                    }else{
                        std::cout << "Please correct the setup" <<std::endl;
                    }
                }else{
                    std::cout << "Enter the Correct Commands" << std::endl;
                    continue;
                }
            }
        }//if
        std::cout << "Enter the Commands" << std::endl;
    } // while
    //display scores
    std::cout << "Black :";
    if(blackIsComputer) std::cout << blackComp.getScore() << endl;
    else std::cout << blackPlayer.getScore() << endl;

    std::cout << "White :";
    if(whiteIsComputer) std::cout << whiteComp.getScore() << endl;
    else std::cout << whitePlayer.getScore() << endl;
}
