#include <string>
#include <iostream>

int main(){
    std::string command;
    while (std::cin >> command) {
        if (command == "game" ) {
            std::string white,black;
            std::cin >> white >> black;
        }
        else if (command == "resign") {
            
        }
        else if (command == "move") {
            char srcCol, destCol;
            int srcRow, destRow;
            std::cin >> srcCol >> srcRow >> destCol >> destRow;
        }
        else if (command == "setup") {
            std::string option;
            std::cin >> option;
            bool done = false;
            while(!done){
                if(option == "+"){

                }else if(option == "-"){

                }else if(option == "="){

                }else if(option == "done"){
                    done = true;
                }
            }
        }//if
    } // while
  
}