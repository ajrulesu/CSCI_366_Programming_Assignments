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

    string player_file = get_file_name("action_board");

    ofstream actionboard;
    actionboard.open(player_file);
    {
        cereal::JSONOutputArchive outboard(actionboard);

        vector<int> line(BOARD_SIZE,0);
        vector<vector<int>> blankboard(BOARD_SIZE, line);

        outboard(cereal::make_nvp("board", blankboard));
    }


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
}


int Client::get_result() {
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
}


string Client::render_action_board(){
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