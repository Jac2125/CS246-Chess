#include "../headers/Computer.h"
#include "../headers/Board.h"

Computer::Computer(char Colour) : Players(Colour) {}

pair<pair<int, int>, pair<int, int>> Computer::L1_GetMove(Board &CH_Board) const {
    
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> My_legal_Moves = CH_Board.getLegalMoves(colour);
    int randomIndex = std::rand() % My_legal_Moves.size();
    return My_legal_Moves[randomIndex];
}

pair<pair<int, int>, pair<int, int>> Computer::L2_GetMove(Board &CH_Board) const {
        vector<pair<pair<int, int>, pair<int, int>>> My_legal_Moves = CH_Board.getLegalMoves(colour);
        vector<pair<pair<int, int>, pair<int, int>>> capturingMoves;

        for (const pair<pair<int, int>, pair<int, int>>& move : My_legal_Moves) {
            char srcPiece = CH_Board.pieceAt(move.first.first, move.first.second)->second->getName();
            map<pair<int, int>, unique_ptr<Piece>>::iterator destPieceIter = CH_Board.pieceAt(move.second.first, move.second.second);
            char destPiece = destPieceIter != CH_Board.end() ? destPieceIter->second->getName() : ' ';

            int Move_Valid = CH_Board.move(move.first, move.second);
            if (Move_Valid == 0) { 
                if (destPiece != ' ') {
                    capturingMoves.push_back(move);
                } else if (CH_Board.inCheck(colour == 'b' ? *CH_Board.wKing : *CH_Board.bKing)) {
                    capturingMoves.push_back(move);
                }
            }

            CH_Board.remove(move.second);
            CH_Board.add(move.first, srcPiece);
            if (destPiece != ' ') {
                CH_Board.add(move.second, destPiece);
            }
        }

        if (!capturingMoves.empty()) {
            int randomIndex = rand() % capturingMoves.size();
            return capturingMoves[randomIndex];
        }

        return L1_GetMove(CH_Board);
}


pair<pair<int, int>, pair<int, int>> Computer::L3_GetMove(Board &CH_Board) const {
    vector<pair<pair<int, int>, pair<int, int>>> My_legal_Moves = CH_Board.getLegalMoves(colour);
    vector<pair<pair<int, int>, pair<int, int>>> capturingMoves;
    vector<pair<pair<int, int>, pair<int, int>>> checkingMoves;
    vector<pair<pair<int, int>, pair<int, int>>> avoidingCaptureMoves;

        for (auto move : My_legal_Moves) {
            char srcPiece = CH_Board.pieceAt(move.first.first, move.first.second)->second->getName();
            map<pair<int, int>, unique_ptr<Piece>>::iterator destPieceIter = CH_Board.pieceAt(move.second.first, move.second.second);
            char destPiece = destPieceIter != CH_Board.end() ? destPieceIter->second->getName() : ' ';

            int Move_Valid = CH_Board.move(move.first, move.second);
            if (Move_Valid == 0) {
                if (destPiece != ' ') {
                    capturingMoves.push_back(move);
                } else if (CH_Board.inCheck(colour == 'b' ? *CH_Board.wKing : *CH_Board.bKing)) {
                    checkingMoves.push_back(move);
                } else {
                    bool avoidsCapture = true;
                    bool UnderThreat = false;

                    for (auto oppMove : CH_Board.getLegalMoves(colour == 'b' ? 'w' : 'b')) {
                        if (oppMove.second == move.first) {
                            UnderThreat = true;
                            break;
                        }
                    }

                    if (UnderThreat) {
                        for (auto oppMove : CH_Board.getLegalMoves(colour == 'b' ? 'w' : 'b')) {
                            if (oppMove.second == move.second) {
                                avoidsCapture = false;
                                break;
                            }
                        }

                        if (avoidsCapture) {
                            avoidingCaptureMoves.push_back(move);
                        }
                    }
                }
            }

            CH_Board.remove(move.second);
            CH_Board.add(move.first, srcPiece);
            if (destPiece != ' ') {
                CH_Board.add(move.second, destPiece);
            }
        }

        if (!checkingMoves.empty()) {
            int randomIndex = rand() % checkingMoves.size();
            return checkingMoves[randomIndex];
        }

        if (!capturingMoves.empty()) {
            int randomIndex = rand() % capturingMoves.size();
            return capturingMoves[randomIndex];
        }

        if (!avoidingCaptureMoves.empty()) {
            int randomIndex = rand() % avoidingCaptureMoves.size();
            return avoidingCaptureMoves[randomIndex];
        }

        return L1_GetMove(CH_Board);
}
