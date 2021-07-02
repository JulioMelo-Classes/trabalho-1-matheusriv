/*!
 *  @mainpage Keno
 *  @authors Matheus Rivaldo da Silva
 *  @version 1.0
 *
 *  @file KenoMain.cpp
 *  @brief Keno Main Function
 *
 *  File with the driver program
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

//! Main function
//! @param argc number of command line arguments
//! @param argv list of command-line arguments, used to read the bet    file name
//! @return 0 if success, 1 if not
int main(int argc, char *argv[]) {

    string aposta_filename; // <! Creates string to store file name
    string line;
    float IC;     // <! Initial Credit
    int NR;       // <! Number of Rounds
    int count=0;  // <! auxiliary int
    KenoBet bet;  // <! Creates KenoBet object

    vector<vector<float>> payofftable = {
        {0, 3},
        {0, 1, 9},
        {0, 1, 2, 16},
        {0, 0.5, 2, 6, 12},
        {0, 0.5, 1, 3, 15, 50},
        {0, 0.5, 1, 2, 3, 30, 75},
        {0, 0.5, 0.5, 1, 6, 12, 36, 100},
        {0, 0.5, 0.5, 1, 3, 6, 19, 90, 720},
        {0, 0.5, 0.5, 1, 2, 4, 8, 20, 80, 1200},
        {0, 0, 0.5, 1, 2, 3, 5, 10, 30, 600, 1800},
        {0, 0, 0.5, 1, 1, 2, 6, 15, 25, 180, 1000, 3000},
        {0, 0, 0, 0.5, 1, 2, 4, 24, 72, 250, 500, 2000, 4000},
        {0, 0, 0, 0.5, 0.5, 3, 4, 5, 20, 80, 240, 500, 3000, 6000},
        {0, 0, 0, 0.5, 0.5, 2, 3, 5, 12, 50, 150, 500, 1000, 2000, 7500},
        {0, 0, 0, 0.5, 0.5, 1, 2, 5, 15, 50, 150, 300, 600, 1200, 2500, 10000}
        };

    // Check command line arguments
    if(argc == 1){ 
        cerr << "Sem arquivo, jogando com o arquivo default de apostas" << endl;
        aposta_filename = "bet_01.dat";
    }
    else
        aposta_filename = argv[1];

    // Show message from reading the file
    cout << ">>> Lendo arquivo de apostas [data/" 
    << aposta_filename << "], por favor aguarde...\n"
    << "--------------------------------------------------------" << endl;

    // Open file
    ifstream arqDados(aposta_filename);
    if(arqDados.bad()){
        cerr << ">>>>ERRO, o arquivo não foi aberto" << endl;
        exit(1);
    } 

    /* stringstream is a convenient way to manipulate strings and an easy
       way to convert strings of digits into ints, floats or doubles. */
    stringstream strStream;
    strStream << arqDados.rdbuf(); // read the file
    string bet_data = strStream.str(); // str holds the content of the file
    arqDados.close(); // close opened file

    // Check file for invalid characters
    for(int i=0;i<bet_data.size();i++){
        if((bet_data[i]>=33 && bet_data[i]<=45) ||
            (bet_data[i]==47) ||
            (bet_data[i]>=58 && bet_data[i]<=126)){
                cerr << ">>>> ERRO, o arquivo possui caracteres estranhos.\n";
                exit(1);
        }
    }

    // stringstream() : This is an easy way to convert strings of digits into ints, floats or doubles.
    strStream >> IC;      // IC float data type, initial credit
    strStream >> NR;      // NR int data type, number of rounds
    float FC = IC;        // <! Final Credit
    bet.set_wage(IC/NR);  // <! Set Wage by Round

    // If wage = 0
    if(IC == 0 || IC < 0){
        cerr << ">>>> ERRO! Você não pode apostar com crédito inicial zerado!\n";
        exit(1);
    }
    // If number of rounds = 0
    if(NR == 0 || NR < 0 || NR > 15){
        cerr << ">>>> ERRO! Número de rodadas inválido!\n";
        exit(1);
    }
    // Read information till the end of the file.
    while(!strStream.eof()){
        ++count;
        int num;
        strStream >> num;
        // If conditions of add number are invalid, exit.
        if(bet.add_number(num) == false){ 
            cerr << ">>>> ERRO! Os números escolhidos são repetidos ou inválidos.\n";
            exit(1);
        }
        if(count>NR){
            // If number of numbers are bigger than number of rounds, exit.
            cerr << ">>>> ERRO! A quantidade de números escolhidos é maior que o número de rodadas.\n";
            exit(1);
        }
    }
    // If spots values are invalid
    if(bet.get_spots().size() == 0) {
        cerr << ">>>> ERRO! Sua aposta é inválida!\n";
        exit(1);
    }

    // Show sucess message
    cout << ">>> Aposta lida com sucesso!" << endl;

    // Show message with bet information 
    cout << "    Você apostará um total de $" << IC << " créditos." << endl;
    cout << "    Jogará um total de " << NR << " rodadas, apostando $"
    << IC/NR << " créditos por rodada." << endl;

    // Show vector with the player's bet.
    cout << "    Sua aposta tem " << bet.size(); 
    if(bet.size() == 1) cout << " número. Ele é [ "; 
    else                cout << " números. Eles são [ ";
    for(auto i : bet.get_spots()) 
        cout << i << " ";
    cout << "]." << endl;

    // Print Payoff Table
    printPayoffTable(payofftable, NR, bet.size());

    // Rounds
    for(int I=1; I<=NR; I++) {
        set_of_numbers_type random_numbers = bet.generateRandom();

        cout << "\t--------------------------------------------------------\n"
            << "\t Esta é a rodada #" << I << " de " << NR
            << ", sua aposta é $" << bet.get_wage() << ". Boa Sorte!" 
            << endl;
        
        // Show random generated numbers
        cout << "\tOs números sorteados são: [ ";
        for(auto i : random_numbers)
            cout << i << " ";
        cout << "]" << endl;

        // Create vector with spots that match the hits.
        set_of_numbers_type numbers_hits = bet.get_hits(random_numbers);

        float taxa_retorno = payofftable[bet.size()-1][numbers_hits.size()];
        float valor_agora = bet.get_wage() * taxa_retorno;
        FC += valor_agora - bet.get_wage();

        cout << "\n\tVocê acertou o(s) número(s) [ ";
        for(auto i : numbers_hits)
            cout << i << " ";
        cout << "], um total de " << numbers_hits.size() << " hits de "
        << bet.size() << ".\n\tSua taxa de retorno é " << taxa_retorno
        << ", assim você sai com: $" << valor_agora << ".\n"
        << "\tVocê possui um total de: $" << FC << " créditos." << endl;
    }

    cout << ">>> Fim das rodadas!\n"
    << "--------------------------------------------------------\n" << endl;

    // Calculates the difference between FC and IC.
    float difference = FC - IC;

    // Show Final Message
    cout << "======= Sumário =======\n"
    << ">>> Você gastou um total de $" << IC << " créditos." << endl;
    if(difference >= 0){ 
        cout << ">>> Hooray! você ganhou $" << difference
        << " créditos!" << endl;
    }
    else{ 
        cout << ">>> Você perdeu $" << -difference << " créditos." << endl;
    }
    cout << ">>> Você está saindo do jogo com um total de $" << FC << " créditos.\n" << endl;

    return 0;


}