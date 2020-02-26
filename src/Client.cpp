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


void Client::initialize(unsigned int player, unsigned int board_size){
    this->player = player;
    string num = to_string(player);
    string player_file = "player_";
    player_file.append(num);
    player_file.append(".action_board.json");
    ofstream actionboard;
    actionboard.open(player_file);
//    for(int i=0; i<board_size; i++) {
//        for (int j = 0; j < board_size; j++) {
//            actionboard << "_";
//        }
//        actionboard << endl;
//    }
    actionboard << "{\n"
            "    \"board\": [\n"
            "        [\n"
            "            0,\n"
            "            0\n"
            "        ],\n"
            "        [\n"
            "            0,\n"
            "            0\n"
            "        ]\n"
            "    ]\n"
            "}";
    actionboard.close();
    this->initialized = true;
}


void Client::fire(unsigned int x, unsigned int y) {
    string num = to_string(this->player);
    string player_file = "player_";
    player_file.append(num);
    player_file.append(".shot.json");
    ofstream shotboard;
    shotboard.open(player_file);
    shotboard << "{\n"
                 "    \"x\": " << to_string(x) << ",\n"
                 "    \"y\": "<< to_string(y) << "\n"
                 "}";
    shotboard.close();
}


bool Client::result_available() {
}


int Client::get_result() {
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
}


string Client::render_action_board(){
}