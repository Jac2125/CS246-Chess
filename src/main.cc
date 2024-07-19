#include <string>
#include <iostream>
#include <sstream>

int main(){
    std::string command;
    bool blackTurn{false};
    bool currPlaying{false};
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
            std::cout << src.first << " " << src.second << std::endl;
            std::cout << dest.first << " " << dest.second << std::endl;
            //move using two pairs
        }
        else if (!currPlaying && command == "setup") {
            std::string option;
            std::cin >> option;
            bool done = false;
            while(!done){
                if(option == "+"){
                    int srcRow;
                    char c,srcCol;
                    std::cin >> c >> srcCol >> srcRow;
                    std::pair<int, int>src{srcRow, srcCol - 'a' + 1};
                    std::cout << src.first << " " << src.second << " " << c << std::endl;
                    //add  piece c
                }else if(option == "-"){
                    int srcRow;
                    char srcCol;
                    std::cin >> srcCol >> srcRow;
                    std::pair<int, int>src{srcRow, srcCol - 'a' + 1};
                    std::cout << src.first << " " << src.second << std::endl;
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