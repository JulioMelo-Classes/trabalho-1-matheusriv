/*!
 *  @mainpage Keno
 *  @authors Matheus Rivaldo da Silva
 *  @date 2021
 *  @version 1.0
 *
 *  @file KenoMain.cpp
 *  @brief Main Function
 *
 *  File with the main function
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "KenoBet.hpp"
#include "OtherFunctions.hpp"

using namespace std;

//! The main function
//! @param argc - number of command line arguments
//! @param argv - list of command-line arguments, used to read the bet    file name
//! @return 0 if success, 1 if not
int main(int argc, char *argv[]) {
    string aposta_filename;

    if(argc == 1){ 
        cerr << "Sem arquivo, jogando com o arquivo default de apostas" << endl;
        aposta_filename = "bet_01.dat";
    }
    else
        aposta_filename = argv[1];

    cout << ">>> Lendo arquivo de apostas [data/" << aposta_filename << "], por favor aguarde..." << endl;
    cout << "----------------------------------------------" << endl;

    ifstream arqDados("data/"+aposta_filename);
    if(arqDados.bad()) {
        cerr << "ERRO, o arquivo não foi aberto" << endl;
        exit(1);
    }
    cout << ">>> Aposta lida com sucesso!" << endl;


}