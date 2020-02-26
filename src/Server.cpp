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
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
    file->seekg(0, file->end);
    int pos = file->tellg();
    return pos;
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){

    //open files as filestream
    ifstream p1;
    p1.open (p1_setup_board, ifstream::in);
    ifstream p2;
    p2.open(p2_setup_board, ifstream::in);

    //get length of files
    unsigned int p1size= get_file_length(&p1);
    unsigned int p2size = get_file_length(&p2);

    //compare to board size, accounting for newline chars
    int board_length = pow(board_size, 2) + board_size-1;

    if(!(board_length==p1size && board_length==p2size)){
        throw __error();
    }

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {

}


int Server::process_shot(unsigned int player) {
   return NO_SHOT_FILE;
}