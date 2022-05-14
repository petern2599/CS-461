#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include "Card.h"

/*
    This is a class for creating players and mainly deal with Poker mechanics
*/
class Player{
private:
    // Hand of card objects (typically 5 objects)
    std::vector<Card> hand;
    // Used for switch cases to identify what hand evaluation the player's hand is identified as
    int hand_code;
    // String version of evaluated hand for logging in .csv file
    std::string hand_eval;
    // Vector of card values from A to K
    std::vector<std::string> card_value_A1_vec { "A", "2", "3", "4", "5", "6" ,"7", "8", "9", "10", "J", "Q", "K"};
    // Vector of card values as a key values that correlates to A through K
    std::vector<double> key_A1_vec {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 10.1, 10.2, 10.3}; 
    // Vector of card values from 2 to A
    std::vector<std::string> card_value_A11_vec {"2", "3", "4", "5", "6" ,"7", "8", "9", "10", "J", "Q", "K", "A"}; 
    // Vector of card values as a key values that correlates to 2 through A
    std::vector<double> key_A11_vec {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 10.1, 10.2, 10.3, 11}; 
    // Vector of card suits from S to H
    std::vector<std::string> card_suit_vec {"S", "C", "D", "H"}; 
    // Vector of card values as a key values that correlates to S through H
    std::vector<double> key_suit_vec {0.01, 0.02, 0.03, 0.04};
    // A static class member to know how many players exist
    static int number_of_players;

public:
    //Methods:
    // For copying cards from deck to the player
    void set_hand(std::vector<Card> hand_vec);
    // Getting the player's hand
    std::vector<Card> get_hand();
    // Getting the hand code for evaluated hand
    int get_hand_code();
    // Get string version of evaluated hand
    std::string get_hand_eval();
    // Clear player's hand of all cards
    void clear_hand();
    //Identifying Hand
    void identify_hand();
    // Count how many card rank in player's hand for sequence 2-A
    std::vector<int> count_card_values();
    // Count how many card rank in player's hand for sequence A-K
    std::vector<int> count_card_values2();
    // Count how many card suits in player's hand
    std::vector<int> count_card_suits();
    //Identify if hand is a royal flush
    std::tuple<int,std::vector<Card>> identify_royal_flush();
    //Identify if hand is a straight flush
    std::tuple<int,std::vector<Card>> identify_straight_flush();
    //Identify if hand is a four-of-a-kind
    std::tuple<int,std::vector<Card>> identify_four_of_a_kind();
    //Identify if hand is a full house
    std::tuple<int,std::vector<Card>> identify_full_house();
    //Identify if hand is a flush
    std::tuple<int,std::vector<Card>> identify_flush();
    //Identify if hand is a straight
    std::tuple<int,std::vector<Card>> identify_straight();
    //Identify if hand is a three-of-a-kind
    std::tuple<int,std::vector<Card>> identify_three_of_a_kind();
    //Identify if hand is a two pairs
    std::tuple<int,std::vector<Card>> identify_two_pairs();
    //Identify if hand is a pair
    std::tuple<int,std::vector<int>,std::vector<Card>> identify_pair();
    //Get the high_card since this is the last option if the ones above is not evaluated
    std::tuple<int,std::vector<Card>> get_high_card();
    // Find index of card rank of sequence 2-A in card rank counter
    int find_card_value_vec_index(std::string card_val);
    // Find index of card rank of sequence A-K in card rank counter
    int find_card_value_vec_index2(std::string card_val);
    // Find index of card suit in card suit counter
    int find_card_suit_vec_index(std::string card_suit);
    //Compare hand with a different player and determine whether the current player's hand wins or not
    std::string compare_hands(std::vector<Card> other_hand, int other_hand_code);
    //Constructor
    Player();
    //Deconstructor
    ~Player();
    //Static Methods
    static int get_number_of_players();
};

// For copying cards from deck to the player
void Player::set_hand(std::vector<Card> hand_vec){
    hand = hand_vec;
    // std::cout << "\n======================" << std::endl;
    // std::cout << "Player got a hand" << std::endl;
    // std::cout << "======================" << std::endl;
}
// Getting the player's hand
std::vector<Card> Player::get_hand(){
    return hand;
}
// Getting the hand code for evaluated hand
int Player::get_hand_code(){
    return hand_code;
}
// Get string version of evaluated hand
std::string Player::get_hand_eval(){
    return hand_eval;
}
// Clear player's hand of all cards
void Player::clear_hand(){
    hand.clear();
    hand_code = 0;
    // std::cout << "\n======================" << std::endl;
    // std::cout << "Player cleared their hand" << std::endl;
    // std::cout << "======================" << std::endl;
}

// Used to identify what type of Poker hand the player has (order is based the likelihood of that hand type occurring)
// Identified Hand Key:
// 0 - High Hand
// 1 - Pair
// 2 - Two Pair
// 3 - Three of a Kind
// 4 - Straight
// 5 - Flush
// 6 - Full House
// 7 - Four of a Kind
// 8 - Straight Flush
// 9 - Royal Flush
void Player::identify_hand(){
    std::vector<int> identity_vec;

    auto [pair_identified_hand,pair_hand_indexes, pair_hand] = identify_pair();
    identity_vec.push_back(pair_identified_hand);

    auto [two_pairs_identified_hand,two_pairs_hand] = identify_two_pairs();
    identity_vec.push_back(two_pairs_identified_hand);

    auto [three_of_a_kind_identified_hand,three_of_a_kind_hand] = identify_three_of_a_kind();
    identity_vec.push_back(three_of_a_kind_identified_hand);

    auto [straight_identified_hand, straight_hand] = identify_straight();
    identity_vec.push_back(straight_identified_hand);

    auto [flush_identified_hand, flush_hand] = identify_flush();
    identity_vec.push_back(flush_identified_hand);

    auto [full_house_identified_hand, full_house_hand] = identify_full_house();
    identity_vec.push_back(full_house_identified_hand);

    auto [four_of_a_kind_identified_hand,four_of_a_kind_hand] = identify_four_of_a_kind();
    identity_vec.push_back(four_of_a_kind_identified_hand);

    auto [straight_flush_identified_hand,straight_flush_hand] = identify_straight_flush();
    identity_vec.push_back(straight_flush_identified_hand);
    
    auto [royal_flush_identified_hand,royal_flush_hand] = identify_royal_flush();
    identity_vec.push_back(royal_flush_identified_hand);

    //Store all hand_codes in vecotr and find highest hand_code to evaluate hand as
    int identified_hand {0};
    for(auto id:identity_vec){
        //std::cout << id << std::endl;
        if(id > identified_hand){
            identified_hand = id;
        }
    }

    hand_code = identified_hand;

    // std::cout << "\n======================" << std::endl;
    // std::cout << "Hand Recognized: "<< std::endl;
    switch(identified_hand){
        case 1:{
            // std::cout << "Pair Cards: ";
            // std::cout << pair_hand[0].get_card_value() << pair_hand[0].get_card_suit() << " ";
            // std::cout << pair_hand[1].get_card_value() << pair_hand[1].get_card_suit() << " ";
            // std::cout << pair_hand[2].get_card_value() << pair_hand[2].get_card_suit() << " ";
            // std::cout << pair_hand[3].get_card_value() << pair_hand[3].get_card_suit() << " ";
            // std::cout << pair_hand[4].get_card_value() << pair_hand[4].get_card_suit() << std::endl;
            hand = pair_hand;
            hand_code = 1;
            hand_eval = "Pair";
            break;
        }
        case 2:{
            // std::cout << "Two Pair Cards: ";
            // std::cout << two_pairs_hand[0].get_card_value() << two_pairs_hand[0].get_card_suit() << " ";
            // std::cout << two_pairs_hand[1].get_card_value() << two_pairs_hand[1].get_card_suit() << " ";
            // std::cout << two_pairs_hand[2].get_card_value() << two_pairs_hand[2].get_card_suit() << " ";
            // std::cout << two_pairs_hand[3].get_card_value() << two_pairs_hand[3].get_card_suit() << " ";
            // std::cout << two_pairs_hand[4].get_card_value() << two_pairs_hand[4].get_card_suit() << std::endl;
            hand = two_pairs_hand;
            hand_code = 2;
            hand_eval = "Two Pairs";
            break;
        }
        case 3:{
            // std::cout << "Three-of-a-Kind Cards: ";
            // std::cout << three_of_a_kind_hand[0].get_card_value() << three_of_a_kind_hand[0].get_card_suit() << " ";
            // std::cout << three_of_a_kind_hand[1].get_card_value() << three_of_a_kind_hand[1].get_card_suit() << " ";
            // std::cout << three_of_a_kind_hand[2].get_card_value() << three_of_a_kind_hand[2].get_card_suit() << " ";
            // std::cout << three_of_a_kind_hand[3].get_card_value() << three_of_a_kind_hand[3].get_card_suit() << " ";
            // std::cout << three_of_a_kind_hand[4].get_card_value() << three_of_a_kind_hand[4].get_card_suit() << std::endl;
            hand = three_of_a_kind_hand;
            hand_code = 3;
            hand_eval = "Three-of-a-Kind";
            break;
        }
        case 4:{
            // std::cout << "Straight Cards: ";
            // std::cout << straight_hand[0].get_card_value() << straight_hand[0].get_card_suit() << " ";
            // std::cout << straight_hand[1].get_card_value() << straight_hand[1].get_card_suit() << " ";
            // std::cout << straight_hand[2].get_card_value() << straight_hand[2].get_card_suit() << " ";
            // std::cout << straight_hand[3].get_card_value() << straight_hand[3].get_card_suit() << " ";
            // std::cout << straight_hand[4].get_card_value() << straight_hand[4].get_card_suit() << std::endl;
            hand = straight_hand;
            hand_code = 4;
            hand_eval = "Straight";
            break;
        }
        case 5:{
            // std::cout << "Flush Cards: ";
            // std::cout << flush_hand[0].get_card_value() << flush_hand[0].get_card_suit() << " ";
            // std::cout << flush_hand[1].get_card_value() << flush_hand[1].get_card_suit() << " ";
            // std::cout << flush_hand[2].get_card_value() << flush_hand[2].get_card_suit() << " ";
            // std::cout << flush_hand[3].get_card_value() << flush_hand[3].get_card_suit() << " ";
            // std::cout << flush_hand[4].get_card_value() << flush_hand[4].get_card_suit() << std::endl;
            hand = flush_hand;
            hand_code = 5;
            hand_eval = "Flush";
            break;
        }
        case 6:{
            // std::cout << "Full House Cards: ";
            // std::cout << full_house_hand[0].get_card_value() << full_house_hand[0].get_card_suit() << " ";
            // std::cout << full_house_hand[1].get_card_value() << full_house_hand[1].get_card_suit() << " ";
            // std::cout << full_house_hand[2].get_card_value() << full_house_hand[2].get_card_suit() << " ";
            // std::cout << full_house_hand[3].get_card_value() << full_house_hand[3].get_card_suit() << " ";
            // std::cout << full_house_hand[4].get_card_value() << full_house_hand[4].get_card_suit() << std::endl;
            hand = full_house_hand;
            hand_code = 6;
            hand_eval = "Full House";
            break;
        }
        case 7:{
            // std::cout << "Four-of-a-Kind Cards: ";
            // std::cout << four_of_a_kind_hand[0].get_card_value() << four_of_a_kind_hand[0].get_card_suit() << " ";
            // std::cout << four_of_a_kind_hand[1].get_card_value() << four_of_a_kind_hand[1].get_card_suit() << " ";
            // std::cout << four_of_a_kind_hand[2].get_card_value() << four_of_a_kind_hand[2].get_card_suit() << " ";
            // std::cout << four_of_a_kind_hand[3].get_card_value() << four_of_a_kind_hand[3].get_card_suit() << " ";
            // std::cout << four_of_a_kind_hand[4].get_card_value() << four_of_a_kind_hand[4].get_card_suit() << std::endl;
            hand = four_of_a_kind_hand;
            hand_code = 7;
            hand_eval = "Four-of-a-Kind";
            break;
        }
        case 8:{
            // std::cout << "Straight Flush Cards: ";
            // std::cout << straight_flush_hand[0].get_card_value() << straight_flush_hand[0].get_card_suit() << " ";
            // std::cout << straight_flush_hand[1].get_card_value() << straight_flush_hand[1].get_card_suit() << " ";
            // std::cout << straight_flush_hand[2].get_card_value() << straight_flush_hand[2].get_card_suit() << " ";
            // std::cout << straight_flush_hand[3].get_card_value() << straight_flush_hand[3].get_card_suit() << " ";
            // std::cout << straight_flush_hand[4].get_card_value() << straight_flush_hand[4].get_card_suit() << std::endl;
            hand = straight_flush_hand;
            hand_code = 8;
            hand_eval = "Straight Flush";
            break;
        }
        case 9:{
            // std::cout << "Royal Flush Cards: ";
            // std::cout << royal_flush_hand[0].get_card_value() << royal_flush_hand[0].get_card_suit() << " ";
            // std::cout << royal_flush_hand[1].get_card_value() << royal_flush_hand[1].get_card_suit() << " ";
            // std::cout << royal_flush_hand[2].get_card_value() << royal_flush_hand[2].get_card_suit() << " ";
            // std::cout << royal_flush_hand[3].get_card_value() << royal_flush_hand[3].get_card_suit() << " ";
            // std::cout << royal_flush_hand[4].get_card_value() << royal_flush_hand[4].get_card_suit() << std::endl;
            hand = royal_flush_hand;
            hand_code = 9;
            hand_eval = "Royal Flush";
            break;
        }
        default:{
            auto[high_card_identified_hand, high_card_hand] = get_high_card();
            // std::cout << "High Card: " << high_card_hand[0].get_card_value() + high_card_hand[0].get_card_suit() << std::endl;
            // std::cout << std::endl;
            // std::cout << "Cards: ";
            // std::cout << high_card_hand[0].get_card_value() << high_card_hand[0].get_card_suit() << " ";
            // std::cout << high_card_hand[1].get_card_value() << high_card_hand[1].get_card_suit() << " ";
            // std::cout << high_card_hand[2].get_card_value() << high_card_hand[2].get_card_suit() << " ";
            // std::cout << high_card_hand[3].get_card_value() << high_card_hand[3].get_card_suit() << " ";
            // std::cout << high_card_hand[4].get_card_value() << high_card_hand[4].get_card_suit() << std::endl;
            hand = high_card_hand;
            hand_code = 0;
            hand_eval = "High Card";
            break;
        }

    }
    // std::cout << "======================" << std::endl;
}


// Determine the amount of card values in a player's hand using a counter in sequence 2-A
std::vector<int> Player::count_card_values(){
    // This vector is based on 'card_value_A11_vec' in terms of order of the counter
    std::vector<int> card_val_counter (13,0);
    for(int current_card{0}; current_card < hand.size(); current_card++){
        card_val_counter[find_card_value_vec_index(hand[current_card].get_card_value())]++;
    }
    return card_val_counter;
}

// Determine the amount of card values in a player's hand using a counter in sequence A-K
std::vector<int> Player::count_card_values2(){
    // This vector is based on 'card_value_A11_vec' in terms of order of the counter
    std::vector<int> card_val_counter (13,0);
    for(int current_card{0}; current_card < hand.size(); current_card++){
        card_val_counter[find_card_value_vec_index2(hand[current_card].get_card_value())]++;
    }
    return card_val_counter;
}

// Determines the amount of card suits in a player's hand using a counter
std::vector<int> Player::count_card_suits(){
    // This vector is based on 'card_value_A11_vec' in terms of order of the counter
    std::vector<int> card_suit_counter (4,0);
    for(int current_card{0}; current_card < hand.size(); current_card++){
        card_suit_counter[find_card_suit_vec_index(hand[current_card].get_card_suit())]++;
    }
    return card_suit_counter;
}

// Determines whether royal flush exists
std::tuple<int,std::vector<Card>> Player::identify_royal_flush(){
    auto [flush_exists, flush_hand] = identify_flush();
    std::vector<int> card_val_counter = count_card_values();
    std::vector<int> counter_indexes;
    // Uses card value counter for 2 through A
    for(int counter_index{8};counter_index < card_val_counter.size();counter_index++){
        if(card_val_counter[counter_index] > 0){
            counter_indexes.push_back(counter_index);
            //std::cout << counter_index << std::endl;
        }
    }
    
    bool difference_equal_one {true};
    bool royal_flush_exist {true};
    // Checks if the size of the counter indices are equal to 5, which means each card is unique and that there are not any card of the same value
    if(counter_indexes.size() != 5){
        royal_flush_exist = false;
    }

    // Checks cards are in straight order for 2-A
    for(int index{1}; index < counter_indexes.size();index++){
        if(counter_indexes[index] - counter_indexes[index-1] != 1){
            difference_equal_one = false;
        }
    }

    // If cards are not in straight order for both 2-A, straight does not exist
    if(difference_equal_one == false){
        royal_flush_exist = false;
    }
    
    
    if(flush_exists == 5 && royal_flush_exist == true){
        //Get total value of each card in hand based on key values
        int key_val_index;
        int key_suit_index;
        std::vector<double> hand_key_vec;
        for(int current_card{0}; current_card < hand.size();current_card++){
            key_val_index = find_card_value_vec_index(hand[current_card].get_card_value());
            key_suit_index = find_card_suit_vec_index(hand[current_card].get_card_suit());
            hand_key_vec.push_back(key_A11_vec[key_val_index] + key_suit_vec[key_suit_index]);
        }

        // Sort hand from greatest to least
        double max_value{0.0};
        int max_val_index {0};
        int begin_index {0};
        std::vector<Card> hand_copy = hand;
        while(begin_index < hand.size()){
            for(int current_index{begin_index};current_index < hand.size();current_index++){
                if(hand_key_vec[current_index] > max_value){
                    max_value = hand_key_vec[current_index];
                    max_val_index = current_index;
                }
            }
            std::swap(hand_key_vec[begin_index],hand_key_vec[max_val_index]);
            std::swap(hand_copy[begin_index],hand_copy[max_val_index]);
            max_value = 0.0;
            max_val_index = 0;
            begin_index++;
        }
        return {9, hand_copy};
    }
    else{
        return {0, hand};
    }
}

// Determines whether straight flush exists
std::tuple<int,std::vector<Card>> Player::identify_straight_flush(){
    auto [straight_exists, straight_hand] = identify_straight();
    auto [flush_exists, flush_hand] = identify_flush();
    if(straight_exists == 4 && flush_exists == 5){
        return {8,straight_hand};
    }
    else{
        return {0,straight_hand};
    }
}

// Determines whether at four-of-a-kind exists and gets the indexes of those cards in the player's hand
std::tuple<int,std::vector<Card>> Player::identify_four_of_a_kind(){
    std::vector<int> card_val_counter = count_card_values();
    int begin_index {0};
    int end_index {12};
    std::vector<int> four_of_a_kind_hand_index;
    bool four_of_a_kind_exist {false};
    bool index_meet {false};
    // Perform Bidirectional search at the beginning and end of vector, inwards and finds if any of indexes of the counter is equal to 2
    // , if it does exist, then search through any index in the player's hand of that card value
    while(index_meet == false){
        if(card_val_counter[begin_index] == 4){
            four_of_a_kind_exist = true;
            for(int current_card{0}; current_card < hand.size(); current_card++){
                if(hand[current_card].get_card_value() == card_value_A11_vec[begin_index]){
                    four_of_a_kind_hand_index.push_back(current_card);
                }
            }
        }
        else if (card_val_counter[end_index] == 4){
            four_of_a_kind_exist = true;
            for(int current_card{0}; current_card < hand.size(); current_card++){
                if(hand[current_card].get_card_value() == card_value_A11_vec[end_index]){
                    four_of_a_kind_hand_index.push_back(current_card);
                }
            }
        }
        if(begin_index == end_index){
            index_meet = true;
        }
        begin_index++;
        end_index--;
    }

    //Copy hand
    std::vector<Card> hand_copy = hand;
    if(four_of_a_kind_exist == false){
        return {0, hand_copy};
    }
    //Swap pair cards to be in first two cards in hand
    int copy_index {0};
    int four_of_a_kind_index {0};
    while(copy_index < four_of_a_kind_hand_index.size()){
        std::swap(hand_copy[copy_index],hand_copy[four_of_a_kind_hand_index[four_of_a_kind_index]]);
        copy_index++;
        four_of_a_kind_index++;
    }

    // Get key values for each card
    int key_val_index;
    int key_suit_index;
    std::vector<double> hand_key_vec;
    for(int current_card{0}; current_card < hand_copy.size();current_card++){
        key_val_index = find_card_value_vec_index(hand_copy[current_card].get_card_value());
        key_suit_index = find_card_suit_vec_index(hand_copy[current_card].get_card_suit());
        hand_key_vec.push_back(key_A11_vec[key_val_index] + key_suit_vec[key_suit_index]);
    }

    //Sort remaining cards aside from pair
    double max_value{0.0};
    int max_val_index {0};
    while(copy_index < hand.size()){
        for(int current_index{copy_index};current_index < hand.size();current_index++){
            if(hand_key_vec[current_index] > max_value){
                max_value = hand_key_vec[current_index];
                max_val_index = current_index;
            }
        }
        std::swap(hand_key_vec[copy_index],hand_key_vec[max_val_index]);
        std::swap(hand_copy[copy_index],hand_copy[max_val_index]);
        max_value = 0.0;
        max_val_index = 0;
        copy_index++;
    }

    //Return
    if(four_of_a_kind_exist == true){
        return {7, hand_copy};
    }
    else{
        return {0, hand_copy};
    }

    return {0, hand_copy};
}

// Determines whether full house exists
std::tuple<int,std::vector<Card>> Player::identify_full_house(){
    std::vector<int> card_val_counter = count_card_values();
    int begin_index {0};
    int end_index {12};
    int pair_counter{0} ;
    int three_of_a_kind_counter{0};
    std::vector<int> pair_hand_index;
    std::vector<int> three_of_a_kind_hand_index;
    bool index_meet {false};
    // Perform Bidirectional search at the beginning and end of vector, inwards and finds if any of indexes of the counter is equal to 2
    // , if it does exist, then search through any index in the player's hand of that card value
    while(index_meet == false){
        if(card_val_counter[begin_index] == 2){
            pair_counter++;
            for(int current_card{0}; current_card < hand.size(); current_card++){
                if(hand[current_card].get_card_value() == card_value_A11_vec[begin_index]){
                    pair_hand_index.push_back(current_card);
                }
            }

        }
        else if(card_val_counter[end_index] == 2){
            pair_counter++;
            for(int current_card{0}; current_card < hand.size(); current_card++){
                if(hand[current_card].get_card_value() == card_value_A11_vec[end_index]){
                    pair_hand_index.push_back(current_card);
                }
            }
        }
        else if (card_val_counter[begin_index] == 3){
            three_of_a_kind_counter++;
            for(int current_card{0}; current_card < hand.size(); current_card++){
                if(hand[current_card].get_card_value() == card_value_A11_vec[begin_index]){
                    three_of_a_kind_hand_index.push_back(current_card);
                }
            }
        }
        else if (card_val_counter[end_index] == 3){
            three_of_a_kind_counter++;
            for(int current_card{0}; current_card < hand.size(); current_card++){
                if(hand[current_card].get_card_value() == card_value_A11_vec[end_index]){
                    three_of_a_kind_hand_index.push_back(current_card);
                }
            }
        }
        if(begin_index == end_index){
            index_meet = true;
        }
        begin_index++;
        end_index--;
    }

    //Copy player's hand
    std::vector<Card> hand_copy = hand;
    //Create empty hand to insert pairs first
    std::vector<Card> full_house_hand;
    if(pair_counter == 1 && three_of_a_kind_counter == 1){
        int three_of_a_kind_index {0};
        while(three_of_a_kind_index < three_of_a_kind_hand_index.size()){
            full_house_hand.push_back(hand_copy[three_of_a_kind_hand_index[three_of_a_kind_index]]);
            three_of_a_kind_index++;
        }
        int pair_index = 0;
        while(pair_index < pair_hand_index.size()){
            full_house_hand.push_back(hand_copy[pair_hand_index[pair_index]]);
            pair_index++;
        }
        return {6, full_house_hand};
    }
    else{
        
        return {0, full_house_hand};
    }
}

// Determines whether flush exists
std::tuple<int,std::vector<Card>> Player::identify_flush(){
    std::vector<int> card_suit_counter = count_card_suits();
    for(auto suit:card_suit_counter){
        if(suit == 5){
            //Get total value of each card in hand based on key values
            int key_val_index;
            int key_suit_index;
            std::vector<double> hand_key_vec;
            for(int current_card{0}; current_card < hand.size();current_card++){
                key_val_index = find_card_value_vec_index(hand[current_card].get_card_value());
                key_suit_index = find_card_suit_vec_index(hand[current_card].get_card_suit());
                hand_key_vec.push_back(key_A11_vec[key_val_index] + key_suit_vec[key_suit_index]);
            }

            // Sort hand from greatest to least
            double max_value{0.0};
            int max_val_index {0};
            int begin_index {0};
            std::vector<Card> hand_copy = hand;
            while(begin_index < hand.size()){
                for(int current_index{begin_index};current_index < hand.size();current_index++){
                    if(hand_key_vec[current_index] > max_value){
                        max_value = hand_key_vec[current_index];
                        max_val_index = current_index;
                    }
                }
                std::swap(hand_key_vec[begin_index],hand_key_vec[max_val_index]);
                std::swap(hand_copy[begin_index],hand_copy[max_val_index]);
                max_value = 0.0;
                max_val_index = 0;
                begin_index++;
            }
            return {5, hand_copy};
        }
        else{
            std::vector<Card> hand_copy = hand;
            return {0, hand_copy};
        }
    }
    //In case, above doesn't work like intended
    std::vector<Card> hand_copy = hand;
    return {0, hand_copy};
}

// Determines whether straight exists
std::tuple<int,std::vector<Card>> Player::identify_straight(){
    std::vector<int> card_val_counter = count_card_values();
    std::vector<int> card_val_counter2 = count_card_values2();
    std::vector<int> counter_indexes;
    std::vector<int> counter_indexes2;
    bool straight_exist {true};

    // Uses card value counter for 2 through A
    for(int counter_index{0};counter_index < card_val_counter.size();counter_index++){
        if(card_val_counter[counter_index] > 0){
            counter_indexes.push_back(counter_index);
            //std::cout << counter_index << std::endl;
        }
    }
    // Uses card value counter for A through K
    for(int counter_index2{0};counter_index2 < card_val_counter2.size();counter_index2++){
        if(card_val_counter2[counter_index2] > 0){
            counter_indexes2.push_back(counter_index2);
            //std::cout << counter_index2 << std::endl;
        }
    }

    // Boolean expression to make sure that cards are in straight order
    bool difference_equal_one {true};
    bool difference_equal_one2 {true};

    // Checks if the size of the counter indices are equal to 5, which means each card is unique and that there are not any card of the same value
    if(counter_indexes.size() != 5 && counter_indexes2.size() != 5){
        straight_exist = false;
    }

    // Checks cards are in straight order for 2-A
    for(int index{1}; index < counter_indexes.size();index++){
        if(counter_indexes[index] - counter_indexes[index-1] != 1){
            difference_equal_one = false;
        }
    }
    // Checks cards are in straight order for A-K
    for(int index2{1}; index2 < counter_indexes2.size();index2++){
        if(counter_indexes2[index2] - counter_indexes2[index2-1] != 1){
            difference_equal_one2 = false;
        }
    }

    // If cards are not in straight order for both 2-A and A-K, straight does not exist
    if(difference_equal_one == false && difference_equal_one2 == false){
        straight_exist = false;
    }
    
    //If straight exists, check which sequence it is from (e.g. 2-A or A-K)
    if(straight_exist == true){
        if(difference_equal_one == true){
            //Get total value of each card in hand based on key values
            int key_val_index;
            int key_suit_index;
            std::vector<double> hand_key_vec;
            for(int current_card{0}; current_card < hand.size();current_card++){
                key_val_index = find_card_value_vec_index(hand[current_card].get_card_value());
                key_suit_index = find_card_suit_vec_index(hand[current_card].get_card_suit());
                hand_key_vec.push_back(key_A11_vec[key_val_index] + key_suit_vec[key_suit_index]);
            }

            // Sort hand from greatest to least
            double max_value{0.0};
            int max_val_index {0};
            int begin_index {0};
            std::vector<Card> hand_copy = hand;
            while(begin_index < hand.size()){
                for(int current_index{begin_index};current_index < hand.size();current_index++){
                    if(hand_key_vec[current_index] > max_value){
                        max_value = hand_key_vec[current_index];
                        max_val_index = current_index;
                    }
                }
                std::swap(hand_key_vec[begin_index],hand_key_vec[max_val_index]);
                std::swap(hand_copy[begin_index],hand_copy[max_val_index]);
                max_value = 0.0;
                max_val_index = 0;
                begin_index++;
            }
            return {4, hand_copy};
        }
        else if(difference_equal_one2 == true){
            //Get total value of each card in hand based on key values
            int key_val_index;
            int key_suit_index;
            std::vector<double> hand_key_vec;
            for(int current_card{0}; current_card < hand.size();current_card++){
                key_val_index = find_card_value_vec_index2(hand[current_card].get_card_value());
                key_suit_index = find_card_suit_vec_index(hand[current_card].get_card_suit());
                hand_key_vec.push_back(key_A1_vec[key_val_index] + key_suit_vec[key_suit_index]);
            }

            // Sort hand from greatest to least
            double max_value{0.0};
            int max_val_index {0};
            int begin_index {0};
            std::vector<Card> hand_copy = hand;
            while(begin_index < hand.size()){
                for(int current_index{begin_index};current_index < hand.size();current_index++){
                    if(hand_key_vec[current_index] > max_value){
                        max_value = hand_key_vec[current_index];
                        max_val_index = current_index;
                    }
                }
                std::swap(hand_key_vec[begin_index],hand_key_vec[max_val_index]);
                std::swap(hand_copy[begin_index],hand_copy[max_val_index]);
                max_value = 0.0;
                max_val_index = 0;
                begin_index++;
            }
            return {4, hand_copy};
        }
    }
    //In case other return does not work
    std::vector<Card> hand_copy = hand;
    return {0, hand_copy};
}

// Determines whether three-of-a-kind exists and gets the indexes of those cards in the player's hand
std::tuple<int,std::vector<Card>> Player::identify_three_of_a_kind(){
    std::vector<int> card_val_counter = count_card_values();
    int begin_index {0};
    int end_index {12};
    std::vector<int> three_of_a_kind_hand_index;
    bool three_of_a_kind_exists {false};
    bool index_meet {false};
    // Perform Bidirectional search at the beginning and end of vector, inwards and finds if any of indexes of the counter is equal to 2
    // , if it does exist, then search through any index in the player's hand of that card value
    while(index_meet == false){
        if(card_val_counter[begin_index] == 3){
            three_of_a_kind_exists = true;
            for(int current_card{0}; current_card < hand.size(); current_card++){
                if(hand[current_card].get_card_value() == card_value_A11_vec[begin_index]){
                    three_of_a_kind_hand_index.push_back(current_card);
                }
            }
        }
        else if (card_val_counter[end_index] == 3){
            three_of_a_kind_exists = true;
            for(int current_card{0}; current_card < hand.size(); current_card++){
                if(hand[current_card].get_card_value() == card_value_A11_vec[end_index]){
                    three_of_a_kind_hand_index.push_back(current_card);
                }
            }
        }
        if(begin_index == end_index){
            index_meet = true;
        }
        begin_index++;
        end_index--;
    }

    //Copy hand
    std::vector<Card> hand_copy = hand;
    if(three_of_a_kind_exists == false){
        return {0, hand_copy};
    }
    //Swap pair cards to be in first two cards in hand
    int copy_index {0};
    int three_of_a_kind_index {0};
    while(copy_index < three_of_a_kind_hand_index.size()){
        std::swap(hand_copy[copy_index],hand_copy[three_of_a_kind_hand_index[three_of_a_kind_index]]);
        copy_index++;
        three_of_a_kind_index++;
    }

    // Get key values for each card
    int key_val_index;
    int key_suit_index;
    std::vector<double> hand_key_vec;
    for(int current_card{0}; current_card < hand_copy.size();current_card++){
        key_val_index = find_card_value_vec_index(hand_copy[current_card].get_card_value());
        key_suit_index = find_card_suit_vec_index(hand_copy[current_card].get_card_suit());
        hand_key_vec.push_back(key_A11_vec[key_val_index] + key_suit_vec[key_suit_index]);
    }

    //Sort remaining cards aside from pair
    double max_value{0.0};
    int max_val_index {0};
    while(copy_index < hand.size()){
        for(int current_index{copy_index};current_index < hand.size();current_index++){
            if(hand_key_vec[current_index] > max_value){
                max_value = hand_key_vec[current_index];
                max_val_index = current_index;
            }
        }
        std::swap(hand_key_vec[copy_index],hand_key_vec[max_val_index]);
        std::swap(hand_copy[copy_index],hand_copy[max_val_index]);
        max_value = 0.0;
        max_val_index = 0;
        copy_index++;
    }

    //Return
    if(three_of_a_kind_exists == true){
        return {3, hand_copy};
    }
    else{
        return {0, hand_copy};
    }

}

// Determines whether two pairs exists and gets the indexes of those cards in the player's hand
std::tuple<int,std::vector<Card>> Player::identify_two_pairs(){
    // Count how many cards values are in hand and put into vector counter
    std::vector<int> card_val_counter = count_card_values();
    int begin_index {0};
    int end_index {12};
    int pairs_counter{0};
    std::vector<int> two_pair_hand_index1;
    std::vector<int> two_pair_hand_index2;
    bool index_meet {false};
    // Perform Bidirectional search at the beginning and end of vector, inwards and finds if any of indexes of the counter is equal to 2
    // , if it does exist, then search through any index in the player's hand of that card value
    while(index_meet == false){
        if(card_val_counter[begin_index] == 2){
            pairs_counter++;
            if(pairs_counter == 1){
                for(int current_card{0}; current_card < hand.size(); current_card++){
                    if(hand[current_card].get_card_value() == card_value_A11_vec[begin_index]){
                        two_pair_hand_index1.push_back(current_card);
                    }
                }   
            }
            else{
                for(int current_card{0}; current_card < hand.size(); current_card++){
                    if(hand[current_card].get_card_value() == card_value_A11_vec[begin_index]){
                        two_pair_hand_index2.push_back(current_card);
                    }
                }   
            }
        }
        else if (card_val_counter[end_index] == 2){
            pairs_counter++;
            if(pairs_counter == 1){
                for(int current_card{0}; current_card < hand.size(); current_card++){
                    if(hand[current_card].get_card_value() == card_value_A11_vec[end_index]){
                        two_pair_hand_index1.push_back(current_card);
                    }
                }
            }
            else{
                for(int current_card{0}; current_card < hand.size(); current_card++){
                    if(hand[current_card].get_card_value() == card_value_A11_vec[end_index]){
                        two_pair_hand_index2.push_back(current_card);
                    }
                }   
            }
        }
        if(begin_index == end_index){
            index_meet = true;
        }
        begin_index++;
        end_index--;
    }
    
    //Copy player's hand
    std::vector<Card> hand_copy = hand;
    //Create empty hand to insert pairs first
    std::vector<Card> two_pairs_hand;

    //Check if any of these are 0 to indicate that this is not two pairs
    if(two_pair_hand_index1.size() == 0 || two_pair_hand_index2.size() == 0){
        return {0, two_pairs_hand};
    }

    //Determining which pair card value is greater than the other and insert that first into empty hand
    int key_val_index1;
    int key_suit_index1;
    key_val_index1 = find_card_value_vec_index(hand_copy[two_pair_hand_index1[0]].get_card_value());
    key_suit_index1 = find_card_suit_vec_index(hand_copy[two_pair_hand_index1[0]].get_card_suit());
    double card_total_val1 = key_A11_vec[key_val_index1] + key_suit_vec[key_suit_index1];
    
    int key_val_index2;
    int key_suit_index2;
    key_val_index2 = find_card_value_vec_index(hand_copy[two_pair_hand_index2[0]].get_card_value());
    key_suit_index2 = find_card_suit_vec_index(hand_copy[two_pair_hand_index2[0]].get_card_suit());
    double card_total_val2 = key_A11_vec[key_val_index2] + key_suit_vec[key_suit_index2];

    if(card_total_val1 > card_total_val2){
        int pair_index {0};
        while(pair_index < two_pair_hand_index1.size()){
            two_pairs_hand.push_back(hand_copy[two_pair_hand_index1[pair_index]]);
            pair_index++;
        }
        pair_index = 0;
        while(pair_index < two_pair_hand_index2.size()){
            two_pairs_hand.push_back(hand_copy[two_pair_hand_index2[pair_index]]);
            pair_index++;
        }
    }
    else{
        int pair_index {0};
        while(pair_index < two_pair_hand_index2.size()){
            two_pairs_hand.push_back(hand_copy[two_pair_hand_index2[pair_index]]);
            pair_index++;
        }
        pair_index = 0;
        while(pair_index < two_pair_hand_index1.size()){
            two_pairs_hand.push_back(hand_copy[two_pair_hand_index1[pair_index]]);
            pair_index++;
        }
    }

    //Determining missing index from copied hand and insert the last card
    std::vector<int> indices {0,1,2,3,4};
    indices.erase(std::remove(indices.begin(), indices.end(), two_pair_hand_index1[0]), indices.end());
    indices.erase(std::remove(indices.begin(), indices.end(), two_pair_hand_index1[1]), indices.end());
    indices.erase(std::remove(indices.begin(), indices.end(), two_pair_hand_index2[0]), indices.end());
    indices.erase(std::remove(indices.begin(), indices.end(), two_pair_hand_index2[1]), indices.end());

    two_pairs_hand.push_back(hand_copy[indices[0]]);
    
    //Return
    if(pairs_counter == 2){
        return {2, two_pairs_hand};
    }
    else{
        return {0, two_pairs_hand};
    }
}

// Determines whether a pair exists and gets the indexes of those cards in the player's hand
std::tuple<int,std::vector<int>,std::vector<Card>> Player::identify_pair(){
    // Count how many cards values are in hand and put into vector counter
    std::vector<int> card_val_counter = count_card_values();
    int begin_index {0};
    int end_index {12};
    bool pair_exists {false};
    std::vector<int> pair_hand_index;
    bool index_meet {false};
    // Perform Bidirectional search at the beginning and end of vector, inwards and finds if any of indexes of the counter is equal to 2
    // , if it does exist, then search through any index in the player's hand of that card value
    while(index_meet == false){
        if(card_val_counter[begin_index] == 2){
            pair_exists = true;
            for(int current_card{0}; current_card < hand.size(); current_card++){
                if(hand[current_card].get_card_value() == card_value_A11_vec[begin_index]){
                    pair_hand_index.push_back(current_card);
                }
            }
        }
        else if (card_val_counter[end_index] == 2){
            pair_exists = true;
            for(int current_card{0}; current_card < hand.size(); current_card++){
                if(hand[current_card].get_card_value() == card_value_A11_vec[end_index]){
                    pair_hand_index.push_back(current_card);
                }
            }
            break;
        }
        if(begin_index == end_index){
            index_meet = true;
        }
        begin_index++;
        end_index--;
    }

    //Copy hand
    std::vector<Card> hand_copy = hand;
    //Swap pair cards to be in first two cards in hand
    int copy_index {0};
    int pair_index {0};
    while(copy_index < pair_hand_index.size()){
        std::swap(hand_copy[copy_index],hand_copy[pair_hand_index[pair_index]]);
        copy_index++;
        pair_index++;
    }

    // Get key values for each card
    int key_val_index;
    int key_suit_index;
    std::vector<double> hand_key_vec;
    for(int current_card{0}; current_card < hand_copy.size();current_card++){
        key_val_index = find_card_value_vec_index(hand_copy[current_card].get_card_value());
        key_suit_index = find_card_suit_vec_index(hand_copy[current_card].get_card_suit());
        hand_key_vec.push_back(key_A11_vec[key_val_index] + key_suit_vec[key_suit_index]);
    }

    //Sort remaining cards aside from pair
    double max_value{0.0};
    int max_val_index {0};
    while(copy_index < hand.size()){
        for(int current_index{copy_index};current_index < hand.size();current_index++){
            if(hand_key_vec[current_index] > max_value){
                max_value = hand_key_vec[current_index];
                max_val_index = current_index;
            }
        }
        std::swap(hand_key_vec[copy_index],hand_key_vec[max_val_index]);
        std::swap(hand_copy[copy_index],hand_copy[max_val_index]);
        max_value = 0.0;
        max_val_index = 0;
        copy_index++;
    }

    //Return
    if(pair_exists == true){
        return {1, pair_hand_index, hand_copy};
    }
    else{
        return {0, pair_hand_index, hand_copy};
    }
}

// Determines the highest card value in the player's hand and what index it is in the hand
std::tuple<int,std::vector<Card>> Player::get_high_card(){
    
    //Get total value of each card in hand based on key values
    int key_val_index;
    int key_suit_index;
    std::vector<double> hand_key_vec;
    for(int current_card{0}; current_card < hand.size();current_card++){
        key_val_index = find_card_value_vec_index(hand[current_card].get_card_value());
        key_suit_index = find_card_suit_vec_index(hand[current_card].get_card_suit());
        hand_key_vec.push_back(key_A11_vec[key_val_index] + key_suit_vec[key_suit_index]);
    }

    // Sort hand from greatest to least
    double max_value{0.0};
    int max_val_index {0};
    int begin_index {0};
    std::vector<Card> hand_copy = hand;
    while(begin_index < hand.size()){
        for(int current_index{begin_index};current_index < hand.size();current_index++){
            if(hand_key_vec[current_index] > max_value){
                max_value = hand_key_vec[current_index];
                max_val_index = current_index;
            }
        }
        std::swap(hand_key_vec[begin_index],hand_key_vec[max_val_index]);
        std::swap(hand_copy[begin_index],hand_copy[max_val_index]);
        max_value = 0.0;
        max_val_index = 0;
        begin_index++;
    }
    return {0, hand_copy};
}

// Used to find the index within the card value vector based on the card's value for sequence of 2-A
int Player::find_card_value_vec_index(std::string card_val){
    int begin_index {0};
    int end_index {12};
    while(begin_index != end_index){
        if(card_value_A11_vec[begin_index] == card_val){
            return begin_index;
        }
        else if(card_value_A11_vec[end_index] == card_val){
            return end_index;
        }
        else{
            begin_index++;
            end_index--;
        }
    }

    return begin_index;
}

// Used to find the index within the card value vector based on the card's value for sequence of A-K
int Player::find_card_value_vec_index2(std::string card_val){
    int begin_index {0};
    int end_index {12};
    while(begin_index != end_index){
        if(card_value_A1_vec[begin_index] == card_val){
            return begin_index;
        }
        else if(card_value_A1_vec[end_index] == card_val){
            return end_index;
        }
        else{
            begin_index++;
            end_index--;
        }
    }

    return begin_index;
}

// Used to find the index within the card suit vector based on the card's value
int Player::find_card_suit_vec_index(std::string card_suit){
    int begin_index {0};
    int end_index {4};
    while(begin_index != end_index){
        if(card_suit_vec[begin_index] == card_suit){
            return begin_index;
        }
        else if(card_suit_vec[end_index] == card_suit){
            return end_index;
        }
        else{
            begin_index++;
            end_index--;
        }
    }

    return begin_index;
}


std::string Player::compare_hands(std::vector<Card> other_hand, int other_hand_code){
    if(hand_code > other_hand_code){
        return "Win";
    }
    else if(hand_code < other_hand_code){
        return "Lose";
    }
    else{
        switch(hand_code){
            case 1:{
                int key_val_index;
                double hand_val;
                int other_key_val_index;
                double other_val;

                key_val_index = find_card_value_vec_index(hand[0].get_card_value());
                hand_val = key_A11_vec[key_val_index];

                other_key_val_index = find_card_value_vec_index(other_hand[0].get_card_value());
                other_val = key_A11_vec[other_key_val_index];

                if(hand_val > other_val){
                    return "Win";
                    break;
                }
                else if (hand_val < other_val){
                    return "Lose";
                    break;
                }
                else{
                    for(int i {2}; i < hand.size(); i++){
                        key_val_index = find_card_value_vec_index(hand[i].get_card_value());
                        hand_val = key_A11_vec[key_val_index];

                        other_key_val_index = find_card_value_vec_index(other_hand[i].get_card_value());
                        other_val = key_A11_vec[other_key_val_index];
                        if(hand_val > other_val){
                            return "Win";
                            break;
                        }
                        else if (hand_val < other_val){
                            return "Lose";
                            break;
                        }
                        else{
                            return"Draw";
                            break;
                        }
                    }
                }
                
            }
            case 2:{
                int key_val_index;
                double hand_val;
                int other_key_val_index;
                double other_val;

                int key_val_index2;
                double hand_val2;
                int other_key_val_index2;
                double other_val2;

                key_val_index = find_card_value_vec_index(hand[0].get_card_value());
                hand_val = key_A11_vec[key_val_index];

                other_key_val_index = find_card_value_vec_index(other_hand[0].get_card_value());
                other_val = key_A11_vec[other_key_val_index];

                key_val_index2 = find_card_value_vec_index(hand[2].get_card_value());
                hand_val2 = key_A11_vec[key_val_index2];

                other_key_val_index2 = find_card_value_vec_index(other_hand[2].get_card_value());
                other_val2 = key_A11_vec[other_key_val_index2];

                if(hand_val > other_val){
                    return "Win";
                    break;
                }
                else if (hand_val < other_val){
                    return "Lose";
                    break;
                }
                else{
                    if(hand_val2 > other_val2){
                        return "Win";
                        break;
                    }
                    else if (hand_val2 < other_val2){
                        return "Lose";
                        break;
                    }
                    else{
                        key_val_index = find_card_value_vec_index(hand[4].get_card_value());
                        hand_val = key_A11_vec[key_val_index];

                        other_key_val_index = find_card_value_vec_index(other_hand[4].get_card_value());
                        other_val = key_A11_vec[other_key_val_index];
                        if(hand_val > other_val){
                            return "Win";
                            break;
                        }
                        else if (hand_val < other_val){
                            return "Lose";
                            break;
                        }
                        else{
                            return"Draw";
                            break;
                        }
                        
                    }
                    
                }
            }
            case 3:{
                int key_val_index;
                double hand_val;
                int other_key_val_index;
                double other_val;

                key_val_index = find_card_value_vec_index(hand[0].get_card_value());
                hand_val = key_A11_vec[key_val_index];

                other_key_val_index = find_card_value_vec_index(other_hand[0].get_card_value());
                other_val = key_A11_vec[other_key_val_index];

                if(hand_val > other_val){
                    return "Win";
                    break;
                }
                else if (hand_val < other_val){
                    return "Lose";
                    break;
                }
                else{
                    for(int i {3}; i < hand.size(); i++){
                        key_val_index = find_card_value_vec_index(hand[i].get_card_value());
                        hand_val = key_A11_vec[key_val_index];

                        other_key_val_index = find_card_value_vec_index(other_hand[i].get_card_value());
                        other_val = key_A11_vec[other_key_val_index];
                        if(hand_val > other_val){
                            return "Win";
                            break;
                        }
                        else if (hand_val < other_val){
                            return "Lose";
                            break;
                        }
                        else{
                            return"Draw";
                            break;
                        }
                    }
                }
            }
            case 4:{
                int key_val_index;
                double hand_val;
                int other_key_val_index;
                double other_val;
                
                key_val_index = find_card_value_vec_index(hand[0].get_card_value());
                hand_val = key_A11_vec[key_val_index];

                other_key_val_index = find_card_value_vec_index(other_hand[0].get_card_value());
                other_val = key_A11_vec[other_key_val_index];

                if(hand_val > other_val){
                    return "Win";
                    break;
                }
                else if (hand_val < other_val){
                    return "Lose";
                    break;
                }
                else{
                    for(int i {1}; i < hand.size(); i++){
                        key_val_index = find_card_value_vec_index(hand[i].get_card_value());
                        hand_val = key_A11_vec[key_val_index];

                        other_key_val_index = find_card_value_vec_index(other_hand[i].get_card_value());
                        other_val = key_A11_vec[other_key_val_index];
                        if(hand_val > other_val){
                            return "Win";
                            break;
                        }
                        else if (hand_val < other_val){
                            return "Lose";
                            break;
                        }
                        else{
                            return"Draw";
                            break;
                        }
                    }
                }
            }
            case 5:{
                int key_val_index;
                double hand_val;
                int other_key_val_index;
                double other_val;
                
                key_val_index = find_card_value_vec_index(hand[0].get_card_value());
                hand_val = key_A11_vec[key_val_index];

                other_key_val_index = find_card_value_vec_index(other_hand[0].get_card_value());
                other_val = key_A11_vec[other_key_val_index];

                if(hand_val > other_val){
                    return "Win";
                    break;
                }
                else if (hand_val < other_val){
                    return "Lose";
                    break;
                }
                else{
                    for(int i {1}; i < hand.size(); i++){
                        key_val_index = find_card_value_vec_index(hand[i].get_card_value());
                        hand_val = key_A11_vec[key_val_index];

                        other_key_val_index = find_card_value_vec_index(other_hand[i].get_card_value());
                        other_val = key_A11_vec[other_key_val_index];
                        if(hand_val > other_val){
                            return "Win";
                            break;
                        }
                        else if (hand_val < other_val){
                            return "Lose";
                            break;
                        }
                        else{
                            return"Draw";
                            break;
                        }
                    }
                }
            }
            case 6:{
                int key_val_index;
                double hand_val;
                int other_key_val_index;
                double other_val;

                key_val_index = find_card_value_vec_index(hand[0].get_card_value());
                hand_val = key_A11_vec[key_val_index];

                other_key_val_index = find_card_value_vec_index(other_hand[0].get_card_value());
                other_val = key_A11_vec[other_key_val_index];

                if(hand_val > other_val){
                    return "Win";
                    break;
                }
                else if (hand_val < other_val){
                    return "Lose";
                    break;
                }
            }
            case 7:{
                int key_val_index;
                double hand_val;
                int other_key_val_index;
                double other_val;

                key_val_index = find_card_value_vec_index(hand[0].get_card_value());
                hand_val = key_A11_vec[key_val_index];

                other_key_val_index = find_card_value_vec_index(other_hand[0].get_card_value());
                other_val = key_A11_vec[other_key_val_index];

                if(hand_val > other_val){
                    return "Win";
                    break;
                }
                else if (hand_val < other_val){
                    return "Lose";
                    break;
                }
            }
            case 8:{
                int key_val_index;
                double hand_val;
                int other_key_val_index;
                double other_val;
                
                key_val_index = find_card_value_vec_index(hand[0].get_card_value());
                hand_val = key_A11_vec[key_val_index];

                other_key_val_index = find_card_value_vec_index(other_hand[0].get_card_value());
                other_val = key_A11_vec[other_key_val_index];

                if(hand_val > other_val){
                    return "Win";
                    break;
                }
                else if (hand_val < other_val){
                    return "Lose";
                    break;
                }
                else{
                    for(int i {1}; i < hand.size(); i++){
                        key_val_index = find_card_value_vec_index(hand[i].get_card_value());
                        hand_val = key_A11_vec[key_val_index];

                        other_key_val_index = find_card_value_vec_index(other_hand[i].get_card_value());
                        other_val = key_A11_vec[other_key_val_index];
                        if(hand_val > other_val){
                            return "Win";
                            break;
                        }
                        else if (hand_val < other_val){
                            return "Lose";
                            break;
                        }
                        else{
                            return"Draw";
                            break;
                        }
                    }
                }
            }
            case 9:{
                return "Draw";
                break;
            }
            default:{
                int key_val_index;
                double hand_val;
                int other_key_val_index;
                double other_val;

                for(int i {0}; i < hand.size(); i++){
                    key_val_index = find_card_value_vec_index(hand[i].get_card_value());
                    hand_val = key_A11_vec[key_val_index];

                    other_key_val_index = find_card_value_vec_index(other_hand[i].get_card_value());
                    other_val = key_A11_vec[other_key_val_index];
                    if(hand_val > other_val){
                        return "Win";
                        break;
                    }
                    else if (hand_val < other_val){
                        return "Lose";
                        break;
                    }
                    else{
                        return"Draw";
                        break;
                    }
                }
            }
        }
    }
    return "None";
}


// Initialize static attribute of the number of players existing
int Player::number_of_players {0};

// On construct of player object it will increase the number of players
Player::Player(){
    ++number_of_players;
}

// On deconstruct of player object, reduce the number of players
Player::~Player(){
    --number_of_players;
    
}

// Get the number of players that currently exists since runtime
int Player::get_number_of_players(){
    return number_of_players;
}

#endif