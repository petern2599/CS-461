#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Deck.h"
#include "Card.h"
#include "Player.h"

using namespace std;

//Functions for creating csv and txt files
void create_csv();
void write_csv(int player_hand_count, string card_0, string card_1, string card_2, string card_3, string card_4, string hand_eval, double win_percent);
void write_txt(vector<double> high_card_win_percent_vec, vector<double> pair_win_percent_vec, vector<double> two_pairs_win_percent_vec, 
vector<double> three_of_a_kind_win_percent_vec, vector<double> straight_win_percent_vec, vector<double> flush_win_percent_vec, vector<double> full_house_win_percent_vec,
vector<double> four_of_a_kind_win_percent_vec, vector<double> straight_flush_win_percent_vec, vector<double> royal_flush_win_percent_vec);

int main(){
    //Construct deck object
    Deck deck;
    //Populate deck with card objects
    deck.create_deck();
    //deck.print_deck();
    
    //Initializing variables for getting winning percentage
    double win_count {0};
    double total_count {0};
    double win_percent;

    //Create csv file
    create_csv();

    //Intialize the amount of new hands the player receives
    int player_hand_count {0};

    //Initialize card reference for csv file
    string card_0;
    string card_1;
    string card_2;
    string card_3;
    string card_4;

    //Initialize hand evaluation reference for csv file and txt file
    string hand_eval;

    //Intialize vectors for each hand evaluation winning percentages
    vector<double> high_card_win_percent_vec;
    vector<double> pair_win_percent_vec;
    vector<double> two_pairs_win_percent_vec;
    vector<double> three_of_a_kind_win_percent_vec;
    vector<double> straight_win_percent_vec;
    vector<double> flush_win_percent_vec;
    vector<double> full_house_win_percent_vec;
    vector<double> four_of_a_kind_win_percent_vec;
    vector<double> straight_flush_win_percent_vec;
    vector<double> royal_flush_win_percent_vec;

    //Initialize number of iterations 
    double number_of_iterations {1000};
    //Initialize current iteration count
    double current_iteration {0};

    //Construct player object
    int num_of_players;
    Player player;
    Player player2;
    Player player3;
    Player player4;
    Player player5;
    Player player6;
    // num_of_players = player6.get_number_of_players();
    // cout << "Number of Players: " << num_of_players << endl;
    
    //Initialize seed for random number generator
    int seed {1};
    for(int player_hand_iteratations {0}; player_hand_iteratations < 1000; player_hand_iteratations++){
        //Player object draws five cards
        player.set_hand(deck.draw_cards(seed));
        //Increment hand count
        player_hand_count++;
        //Assign current cards player has in current iteration
        card_0 = player.get_hand()[0].get_card_value() + player.get_hand()[0].get_card_suit();
        card_1 = player.get_hand()[1].get_card_value() + player.get_hand()[1].get_card_suit();
        card_2 = player.get_hand()[2].get_card_value() + player.get_hand()[2].get_card_suit();
        card_3 = player.get_hand()[3].get_card_value() + player.get_hand()[3].get_card_suit();
        card_4 = player.get_hand()[4].get_card_value() + player.get_hand()[4].get_card_suit();
        //Identify what hand the player has
        player.identify_hand();
        //Assign hand evaluation for csv and txt file
        hand_eval = player.get_hand_eval();
        
        //
        for(int iterations {0}; iterations < 1000; iterations++){
            player2.set_hand(deck.draw_cards(seed));
            player2.identify_hand();

            player3.set_hand(deck.draw_cards(seed));
            player3.identify_hand();

            player4.set_hand(deck.draw_cards(seed));
            player4.identify_hand();

            player5.set_hand(deck.draw_cards(seed));
            player5.identify_hand();

            player6.set_hand(deck.draw_cards(seed));
            player6.identify_hand();
            
            string result2 = player.compare_hands(player2.get_hand(),player2.get_hand_code());
            total_count++;
            //cout << result2 << endl;

            string result3 = player.compare_hands(player3.get_hand(),player3.get_hand_code());
            total_count++;
            //cout << result3 << endl;

            string result4 = player.compare_hands(player4.get_hand(),player4.get_hand_code());
            total_count++;
            // cout << result4 << endl;

            string result5 = player.compare_hands(player5.get_hand(),player5.get_hand_code());
            total_count++;
            // cout << result5 << endl;

            string result6 = player.compare_hands(player6.get_hand(),player6.get_hand_code());
            total_count++;
            // cout << result6 << endl;

            
            if(result2 == "Win"){
                win_count++;
            }
            if(result3 == "Win"){
                win_count++;
            }
            if(result4 == "Win"){
                win_count++;
            }
            if(result5 == "Win"){
                win_count++;
            }
            if(result6 == "Win"){
                win_count++;
            }


            //Set cards to be available for drawing
            deck.reset_cards(player2.get_hand());
            deck.reset_cards(player3.get_hand());
            deck.reset_cards(player4.get_hand());
            deck.reset_cards(player5.get_hand());
            deck.reset_cards(player6.get_hand());
            //Clear the player's hand
            player2.clear_hand();
            player3.clear_hand();
            player4.clear_hand();
            player5.clear_hand();
            player6.clear_hand();

            //Increment seed for completely different random number generation
            seed++;
        }

        //Get winning percentage
        win_percent = win_count/total_count;

        //Assign win percentage to appropriate hand evaluation
        switch(player.get_hand_code()){
            case 1:{
                pair_win_percent_vec.push_back(win_percent);
                break;
            }
            case 2:{
                two_pairs_win_percent_vec.push_back(win_percent);
                break;
            }
            case 3:{
                three_of_a_kind_win_percent_vec.push_back(win_percent);
                break;
            }
            case 4:{
                straight_win_percent_vec.push_back(win_percent);
                break;
            }
            case 5:{
                flush_win_percent_vec.push_back(win_percent);
                break;
            }
            case 6:{
                full_house_win_percent_vec.push_back(win_percent);
                break;
            }
            case 7:{
                four_of_a_kind_win_percent_vec.push_back(win_percent);
                break;
            }
            case 8:{
                straight_flush_win_percent_vec.push_back(win_percent);
                break;
            }
            case 9:{
                royal_flush_win_percent_vec.push_back(win_percent);
                break;
            }
            default:{
                high_card_win_percent_vec.push_back(win_percent);
                break;
            }
        }

        //Write information into csv file
        write_csv(player_hand_count, card_0, card_1, card_2, card_3, card_4, hand_eval, win_percent);
        //Reset cards from player's hand into deck
        deck.reset_cards(player.get_hand());
        //Clear player's hand
        player.clear_hand();
        //Reset stuff for calculating win percentage
        win_count = 0;
        win_percent = 0;
        total_count = 0;
        //Keeping track of progression
        // current_iteration++;
        // cout << "Progress: " << (current_iteration/number_of_iterations) * 100 << "%" << endl;
    }
    //Write txt file of the winning percentages for each hand evaluation
    write_txt(high_card_win_percent_vec, pair_win_percent_vec, two_pairs_win_percent_vec, three_of_a_kind_win_percent_vec, 
    straight_win_percent_vec, flush_win_percent_vec, full_house_win_percent_vec, four_of_a_kind_win_percent_vec, 
    straight_flush_win_percent_vec, royal_flush_win_percent_vec);

    cout << endl;
    return 0;
}

void create_csv(){
    fstream fout;

    fout.open("Poker_Result.csv", ios::out | ios::app);
    fout << "Hand" << "," << "Card 1" << "," << "Card 2" << "" << "," << "Card 3" << "" << "," << "Card 4" << "" << "," << "Card 5" << ",";
    fout << "Hand_Evaluated" << "," << "Winning Percentage" << "\n";
}

void write_csv(int player_hand_count, string card_0, string card_1, string card_2, string card_3, string card_4, string hand_eval, double win_percent){\
    fstream fout;
    fout.open("Poker_Result.csv", ios::out | ios::app);
    fout << player_hand_count << "," << card_0 << "," << card_1 << "" << "," << card_2 << "" << "," << card_3 << "" << "," << card_4 << ",";
    fout << hand_eval << "," << win_percent << "\n";
}

void write_txt(vector<double> high_card_win_percent_vec, vector<double> pair_win_percent_vec, vector<double> two_pairs_win_percent_vec, 
vector<double> three_of_a_kind_win_percent_vec, vector<double> straight_win_percent_vec, vector<double> flush_win_percent_vec, vector<double> full_house_win_percent_vec,
vector<double> four_of_a_kind_win_percent_vec, vector<double> straight_flush_win_percent_vec, vector<double> royal_flush_win_percent_vec){
    ofstream fout;
    fout.open("Poker_Result.txt");
    fout << "============ Poker Monte Carlo Simulation ============\n";
    
    if(high_card_win_percent_vec.size() != 0){
        double sum {0.0};
        for(int index {0}; index < high_card_win_percent_vec.size(); index++){
            sum += high_card_win_percent_vec[index];
        }
        fout << "\nPlayer's hand is evaluated as High Card " << high_card_win_percent_vec.size() << " times." << endl;
        fout << "Average win percentage for High Card is: " << sum / high_card_win_percent_vec.size() << endl;
    }
    else{
        fout << "There was no occurrence of evaluating player's hand as High Card..." << endl;
    }
    
    if(pair_win_percent_vec.size() != 0){
        double sum {0.0};
        for(int index {0}; index < pair_win_percent_vec.size(); index++){
            sum += pair_win_percent_vec[index];
        }
        fout << "\nPlayer's hand is evaluated as Pair " << pair_win_percent_vec.size() << " times." << endl;
        fout << "Average win percentage for Pair is: " << sum / pair_win_percent_vec.size() << endl;
    }
    else{
        fout << "\nThere was no occurrence of evaluating player's hand as Pair..." << endl;
    }

    if(two_pairs_win_percent_vec.size() != 0){
        double sum {0.0};
        for(int index {0}; index < two_pairs_win_percent_vec.size(); index++){
            sum += two_pairs_win_percent_vec[index];
        }
        fout << "\nPlayer's hand is evaluated as Two Pairs " << two_pairs_win_percent_vec.size() << " times." << endl;
        fout << "Average win percentage for Two Pairs is: " << sum / two_pairs_win_percent_vec.size() << endl;
    }
    else{
        fout << "\nThere was no occurrence of evaluating player's hand as Two Pairs..." << endl;
    }

    if(three_of_a_kind_win_percent_vec.size() != 0){
        double sum {0.0};
        for(int index {0}; index < three_of_a_kind_win_percent_vec.size(); index++){
            sum += three_of_a_kind_win_percent_vec[index];
        }
        fout << "\nPlayer's hand is evaluated as Three-of-a-Kind " << three_of_a_kind_win_percent_vec.size() << " times." << endl;
        fout << "Average win percentage for Three-of-a-Kind is: " << sum / three_of_a_kind_win_percent_vec.size() << endl;
    }
    else{
        fout << "\nThere was no occurrence of evaluating player's hand as Three-of-a-Kind..." << endl;
    }

    if(straight_win_percent_vec.size() != 0){
        double sum {0.0};
        for(int index {0}; index < straight_win_percent_vec.size(); index++){
            sum += straight_win_percent_vec[index];
        }
        fout << "\nPlayer's hand is evaluated as Straight " << straight_win_percent_vec.size() << " times." << endl;
        fout << "Average win percentage for Straight is: " << sum / straight_win_percent_vec.size() << endl;
    }
    else{
        fout << "\nThere was no occurrence of evaluating player's hand as Straight..." << endl;
    }

    if(flush_win_percent_vec.size() != 0){
        double sum {0.0};
        for(int index {0}; index < flush_win_percent_vec.size(); index++){
            sum += flush_win_percent_vec[index];
        }
        fout << "\nPlayer's hand is evaluated as Flush " << flush_win_percent_vec.size() << " times." << endl;
        fout << "Average win percentage for Flush is: " << sum / flush_win_percent_vec.size() << endl;
    }
    else{
        fout << "\nThere was no occurrence of evaluating player's hand as Flush..." << endl;
    }

    if(full_house_win_percent_vec.size() != 0){
        double sum {0.0};
        for(int index {0}; index < full_house_win_percent_vec.size(); index++){
            sum += full_house_win_percent_vec[index];
        }
        fout << "\nPlayer's hand is evaluated as Full House " << full_house_win_percent_vec.size() << " times." << endl;
        fout << "Average win percentage for Full House is: " << sum / full_house_win_percent_vec.size() << endl;
    }
    else{
        fout << "\nThere was no occurrence of evaluating player's hand as Full House..." << endl;
    } 

    if(four_of_a_kind_win_percent_vec.size() != 0){
        double sum {0.0};
        for(int index {0}; index < four_of_a_kind_win_percent_vec.size(); index++){
            sum += four_of_a_kind_win_percent_vec[index];
        }
        fout << "\nPlayer's hand is evaluated as Four-of-a-Kind " << four_of_a_kind_win_percent_vec.size() << " times." << endl;
        fout << "Average win percentage for Four-of-a-Kind is: " << sum / four_of_a_kind_win_percent_vec.size() << endl;
    }
    else{
        fout << "\nThere was no occurrence of evaluating player's hand as Four-of-a-Kind..." << endl;
    }

    if(straight_flush_win_percent_vec.size() != 0){
        double sum {0.0};
        for(int index {0}; index < straight_flush_win_percent_vec.size(); index++){
            sum += straight_flush_win_percent_vec[index];
        }
        fout << "\nPlayer's hand is evaluated as Straight Flush " << straight_flush_win_percent_vec.size() << " times." << endl;
        fout << "Average win percentage for Straight Flush is: " << sum / straight_flush_win_percent_vec.size() << endl;
    }
    else{
        fout << "\nThere was no occurrence of evaluating player's hand as Straight Flush..." << endl;
    }

    if(royal_flush_win_percent_vec.size() != 0){
        double sum {0.0};
        for(int index {0}; index < royal_flush_win_percent_vec.size(); index++){
            sum += royal_flush_win_percent_vec[index];
        }
        fout << "\nPlayer's hand is evaluated as Royal Flush " << royal_flush_win_percent_vec.size() << " times." << endl;
        fout << "Average win percentage for Royal Flush is: " << sum / royal_flush_win_percent_vec.size() << endl;
    }
    else{
        fout << "\nThere was no occurrence of evaluating player's hand as Royal Flush..." << endl;
    }
    fout << "======================================================\n";
    fout.close();
}