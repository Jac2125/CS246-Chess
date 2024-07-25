#include <string>
#include <iostream>
#include <sstream>
#include "../headers/Board.h"

int main(){
    std::string command;
    bool blackTurn{false};
    bool currPlaying{false};
    Board b{};
    while (std::cin >> command) {
        if (command == "game" ) {
            std::string white,black;
            std::cin >> white >> black;
            if(white == "human"){
                //do initialization?
                std::cout << white << std::endl;
            }else{
                int level;
                for(char c : black){
                    if(isdigit(c)) level = c - '0';
                }
                std::cout << white << level << std::endl;
                //do init computer
            }

            if(black == "human"){
                //do initialization?
                std::cout << black << std::endl;
            }else{
                int level;
                for(char c : black){
                    if(isdigit(c)) level = c - '0';
                }
                std::cout << black << " " << level << std::endl;
                //do init computer
                
            }
            currPlaying = true;
        }
        else if (currPlaying && command == "resign") {
            //
            if(blackTurn) std::cout << "Black Resign" << std::endl;//black resign increase white's score
            if(!blackTurn) std::cout << "White Resign" << std::endl;//white resign increase black's score
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
                    done = true;
                    std::cout << "done" <<std::endl;
                }
            }
        }//if
        blackTurn = currPlaying? !blackTurn : blackTurn;
    } // while
    //display scores
}
