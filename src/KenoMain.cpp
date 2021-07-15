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

/*
Avaliação
Processamento do Arquivo de Entrada: 1
Execução correta: 1
Interfcace Textual: 1
Documentação: 1
Compilação automatizada: 1
Organização em src, include, build, data: 1

Comentários
- Acho que você poderia ter feito uma melhor divisão das funcionalidades, especialmente
a parte de impressão da interface textual, talvez a parte de validadação também pudesse
ficar melhor encapsulada em uma classe.
- A indentação do arquivo KenoBet.cpp ficou estranha, não sei se foi intencional, mas
não vou penalizar já que a diferença é um tab a mais.
- O arquivo OtherFunctions ficou ok, embora o nome não seja muito feliz, se vc tirasse aquela
função "invalidCharacters" ele ficaria apenas responsável pelo quicksort, aí o nome ficaria melhor.
Ainda assim a organização dele poderia usar um pouco mais de C++ através de funções estáticas
ou de um namespace.
*/

//! Main function - não é necessário =)
//! @param argc number of command line arguments
//! @param argv list of command-line arguments, used to read the bet    file name
//! @return 0 if success, 1 if not
int main(int argc, char *argv[]) {

    string aposta_filename; // <! Creates string to store file name
    KenoBet bet;  // <! Creates KenoBet object

    vector<vector<float>> payoff_table = {
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
        cerr << "Sem arquivo, jogando com o arquivo default de apostas." << endl;
        aposta_filename = "bet_01.dat";
    }
    else
        aposta_filename = argv[1];

    // Show message from reading the file
    cout << ">>> Lendo arquivo de apostas [data/" 
    << aposta_filename << "], por favor aguarde..." << endl;
    PrintLine(58);

    // Open file
    ifstream arqDados("../data/"+aposta_filename);
    if(!arqDados){
        cerr << ">>>> ERRO, o arquivo não foi aberto" << endl;
        exit(1);
    } 

    /* stringstream is a convenient way to manipulate strings and an easy
       way to convert strings of digits into ints, floats or doubles. */
    stringstream strStream;            // Create a stringstream
    strStream << arqDados.rdbuf();     // Read the file
    string bet_data = strStream.str(); // String holds the content of the file
    arqDados.close();                  // Close opened file

    // Check file for invalid characters
    if(InvalidCharacters(bet_data)){
          cerr << ">>>> ERRO, o arquivo possui caracteres inválidos." << endl;
          exit(1);
    } 

    float IC; // <! Initial Credit
    int NR;   // <! Number of Rounds
    strStream >> IC; // IC float data type, initial credit
    bet.set_IC(IC);
    strStream >> NR; // NR int data type, number of rounds
    bet.set_NR(NR);
    bet.set_FC(bet.get_IC());                // Final Credit
    bet.set_wage(bet.get_IC()/bet.get_NR()); // Set Wage by Round

    // If wage = 0
    if(bet.get_IC() <= 0){
        cerr << ">>>> ERRO! Você não pode apostar com crédito inicial zerado!\n";
        exit(1);
    }
    // If number of rounds = 0
    if(bet.get_NR() <= 0){
        cerr << ">>>> ERRO! Número de rodadas inválido!\n";
        exit(1);
    }
    
    int count=0;  // <! auxiliary int
    // Read information till the end of the file.
    while(!strStream.eof()){
        int num;
        strStream >> num;
        // If conditions of add number are invalid, exit.
        if(bet.add_number(num) == false){ 
            cerr << ">>>> ERRO! Os números escolhidos são repetidos ou inválidos.\n";
            exit(1);
        }
        // If quantity of numbers is greater than 15, exit.
        if(count>15){
            cerr << ">>>> ERRO! A quantidade de números escolhidos é inválida.\n";
            exit(1);
        }
        ++count;
    }
    // If spots values are invalid
    if(bet.get_spots().size() == 0) {
        cerr << ">>>> ERRO! Sua aposta é inválida!\n";
        exit(1);
    }


    // Show sucess message
    cout << ">>> Aposta lida com sucesso!" << endl;

    // Show message with bet information 
    cout << "\tVocê apostará um total de $" << bet.get_IC() 
    << " créditos.\n" << "\tJogará um total de " << bet.get_NR() 
    << " rodadas, apostando $"
    << bet.get_IC()/bet.get_NR() << " créditos por rodada." << endl;

    // Show vector with the player's bet.
    cout << "\tSua aposta tem " << bet.size(); 
    if(bet.size() == 1) cout << " número. Ele é "; 
    else                cout << " números. Eles são ";
    // Print the vector with the spots the player has picked.
    set_of_numbers_type vspots = bet.get_spots();
    bet.print_vector(vspots, vspots.size());
    cout << endl;

    // Print Payoff Table
    bet.print_payofftable(payoff_table);

    // Rounds
    for(int IndexRound=1; IndexRound<=bet.get_NR(); IndexRound++) {
        // Creates vector with random numbers without repetition
        set_of_numbers_type random_vector = bet.generate_random();

        cout << "\t";
        PrintLine(58);
        cout << "\t Esta é a rodada #" << IndexRound << " de " << bet.get_NR()
          << ", sua aposta é $" << bet.get_wage() << ". Boa Sorte!" 
          << endl;
        
        cout << "\tOs números sorteados são: ";
        // Print the random numbers vector
        bet.print_vector(random_vector, random_vector.size());
        cout << endl;

        // Create vector with spots that match the hits.
        set_of_numbers_type vector_hits = bet.get_hits(random_vector);

        // Get the payout rate from the payoff table
        bet.set_PayoffValue( payoff_table[bet.size()-1][vector_hits.size()] );
        // Calculates the Current Value
        bet.set_CurrentValue( bet.get_wage() * bet.get_PayoffValue() );
        // Updates FC, the final credit
        bet.set_FC( (bet.get_CurrentValue() - bet.get_wage()) );

        if(vector_hits.size() <= 1) cout << "\n\tVocê acertou o número "; 
        else                        cout << "\n\tVocê acertou os números ";
        bet.print_vector(vector_hits, vector_hits.size());
        cout << ", um total de " << vector_hits.size() << " hits de "
          << bet.size() << ".\n\tSua taxa de retorno é " 
          << bet.get_PayoffValue() << ", assim você sai com: $" 
          << bet.get_CurrentValue() << ".\n"
          << "\tVocê possui um total de: $" << bet.get_FC() << " créditos." << endl;
    }

    cout << ">>> Fim das rodadas!" << endl;
    PrintLine(58);
    cout << endl;

    // Calculates the difference between FC and IC, the spent cash.
    bet.set_SC( bet.get_FC() - bet.get_IC() );

    // Show Final Message
    cout << "======= Sumário =======\n"
    << ">>> Você gastou um total de $" << bet.get_IC() << " créditos." << endl;
    if(bet.get_SC() == 0){ 
        cout << ">>> Você não ganhou créditos!" << endl;
    }
    else if(bet.get_SC() > 0){ 
        cout << ">>> Hooray! Você ganhou $" << bet.get_SC() << " créditos!"
        << endl;
    }
    else{ 
        cout << ">>> Você perdeu $" << -bet.get_SC() << " créditos." << endl;
    }
    cout << ">>> Você está saindo do jogo com um total de $" << bet.get_FC() << " créditos.\n" << endl;

    return 0;


}