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
    while (std::cin >> command) {
        if (command == "game" ) {
            std::string white,black;
            std::cin >> white >> black;
            if(white == "human"){
                //do initialization?
                std::cout << white << std::endl;
            }else{
                for(char c : black){
                    if(isdigit(c)) whiteLevel = c - '0';
                }
                std::cout << white << whiteLevel << std::endl;
                whitePlayer = Computer('w');
                whiteIsComputer = true; 
                //do init computer
            }

            if(black == "human"){
                //do initialization?
                std::cout << black << std::endl;
            }else{
                for(char c : black){
                    if(isdigit(c)) blackLevel = c - '0';
                }
                std::cout << black << " " << blackLevel << std::endl;
                //do init computer
                blackPlayer = Computer('b');
                blackIsComputer = true;
            }
            currPlaying = true;
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
        else if (currPlaying && command == "move") {
            char srcCol, destCol; //it is a char but we change it to int using enum
            int srcRow, destRow;
            std::cin >> srcCol >> srcRow >> destCol >> destRow;
            std::pair<int, int>src{srcRow, srcCol - 'a' + 1};
            std::pair<int, int>dest{destRow, destCol - 'a' + 1};
            b.move(src, dest);
            cout << b << endl;
            int winner = b.getWinner();
            if(winner == 0){
                cout << "Stealmate" << endl;
                currPlaying = false;
            }
            if(winner == 1){
                cout << "Checkmate! White wins" << endl;
                whitePlayer.win();
                currPlaying = false;
            }
            if(winner == 2){
                cout << "Checkmate! Black wins" << endl;
                blackPlayer.win();
                currPlaying = false;
            }
            blackTurn = currPlaying? !blackTurn : blackTurn;
            //move using two pairs
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
                        std::cout << "done" <<std::endl;
                    }else{
                        std::cout << "Please correct the setup" <<std::endl;
                    }
                }
            }
        }//if
        
    } // while
    //display scores
}
