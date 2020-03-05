//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "common.hpp"
#include "Client.hpp"

Client::~Client() {
}

template<class Archive>

void Client::serialize(Archive & archive)
{
    int x, y, z;
    archive( x, y, z ); // serialize things by passing them to the archive
}

void Client::initialize(unsigned int player, unsigned int board_size) {
    this->player = player;

    string actionboard = get_file_name("action_board");

    ofstream actionstream;
    actionstream.open(actionboard);

    cereal::JSONOutputArchive outboard(actionstream);

    vector<int> line(BOARD_SIZE,0);
    vector<vector<int>> blankboard(BOARD_SIZE, line);

    outboard(cereal::make_nvp("board", blankboard));



    this->initialized = true;
}


void Client::fire(unsigned int x, unsigned int y) {
    string player_file = get_file_name("shot");

    ofstream shotboard;
    shotboard.open(player_file);

    cereal::JSONOutputArchive outboard(shotboard);
    outboard(CEREAL_NVP(x), CEREAL_NVP(y));

}


bool Client::result_available() {
    string resultboard = get_file_name("result");
    ifstream resultstream;
    resultstream.open(resultboard);
    if(resultstream.good())
        return true;
    else
        return false;
}


int Client::get_result() {
    //open result file
    string resultboard = get_file_name("result");
    ifstream resultstream;
    resultstream.open(resultboard);
    cereal::JSONInputArchive resultarchive(resultstream);
    int result;

    //receive result
    resultarchive(result);

    //handle bad results
    if(result!= HIT && result!= MISS && result!= OUT_OF_BOUNDS)
        throw ClientException("Bad Result!");

    //remove player_#.result.json
    const char * rm = resultboard.c_str();
    remove(rm);

    return result;

}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
    //open player_#.action_board.json as input
    string actionboard = get_file_name("action_board");
    ofstream oActionstream;
    ifstream iActionstream;
    iActionstream.open(actionboard);
    cereal::JSONInputArchive inboard(iActionstream);

    //receive action_board as 2D vector
    vector<vector<int>> board;
    inboard(board);
    iActionstream.close();

    //place result at coordinates in action_board
    vector<int> row = board.at(y);
    row.at(x) = result;
    board.at(y) = row;

    //write 2D vector back to player_#.action_board.json
    {
        oActionstream.open(actionboard);
        cereal::JSONOutputArchive outboard(oActionstream);
        outboard(cereal::make_nvp("board", board));
    }
    oActionstream.close();
}


string Client::render_action_board(){
    //open player_#.action_board.json as input
    string actionboard = get_file_name("action_board");
    ifstream iActionstream;
    iActionstream.open(actionboard);
    cereal::JSONInputArchive inboard(iActionstream);

    //receive action_board as 2D vector
    vector<vector<int>> board;
    inboard(board);
    iActionstream.close();

    string result;

    for(int i=0; i<board.size(); i++) {
        vector<int> row = board.at(i);
        for (int j = 0; j<row.size(); j++){
            result.append(to_string(row.at(j)));
        }
        result.append("\n");
    }

    return result;
}

string Client::get_file_name(string board){
    string num = to_string(this->player);
    string player_file = "player_";
    player_file.append(num);
    player_file.append(".");
    player_file.append(board);
    player_file.append(".json");
    return player_file;
}