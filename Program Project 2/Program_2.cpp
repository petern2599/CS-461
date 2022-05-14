#include <iostream>
#include <fstream>
#include <tuple>
#include <math.h>
#include "Item.h"

using namespace std;

vector<Item> create_item_vector();
void get_random_state(vector<bool> &item_selected, int number_of_items);
int change_random_item_selection(vector<bool> &item_selected);
tuple<double,double> get_total_weight_and_utility(vector<Item> item_vec, vector<bool> item_selected);
double calculate_overweight_factor(double max_weight, double total_weight);
void calculate_total_utility_with_overweight_penalty(int overweight_factor, double overweight_penalty, double &total_utility);
tuple<bool,double,double> check_simulated_annealing_probability(double &simulated_annealing_temp, double cost_difference);


int main(){
    srand(time(NULL));
    //Create a vector of all the items in text file
    vector<Item> item_vec = create_item_vector();

    //Create a vector corresponding to when each is selected or not
    vector<bool> item_selected(item_vec.size(),false);

    //Create vector for referencing item selected and variables for total weight and score difference
    vector<bool> reference_items_selected;
    double reference_total_weight_of_items;
    double reference_item_utility_score_difference {999999.0};

    //Getting the iteration count it took to reach this selection
    int best_items_selected_iteration;

    //Defining weight constraint
    double max_weight{500.0};
    //Defining penalty utility score for overweight
    double overweight_penalty{20};

    //Defining simulated annealing initial temperature
    double simulated_annealing_temp;
    cout << "Enter the desired initial temperature: ";
    cin >> simulated_annealing_temp;
    
    //Defining benchmark to minimize
    double utility_score_benchmark {1000.0};
    
    //Defining successful changes counter
    int successful_changes_counter {0};
    //Defining successful changes threshold
    int successful_changes_threshold {4000};

    //Definine iteration counter
    int iteration_counter {0};

    //Defining temperature scheduling
    int temperature_schedule {4000};
    
    
    //Define boolean statement to break loop if no changes are made even after temperature reduced
    bool change_occurred_after_temperature_change {false};

    //Defining initial number of items to observe
    int number_of_items{20};

    //Define boolean break statement
    bool break_bool {false};

    //Defining probabilities to check
    bool probability_check {false};
    double prob_obtained;
    double sim_prob;
    //Define random index selected in case probability is not accepted and change needs to be reverted
    int random_index_selected;

    //Define attempt counter and threshold to track when to break out of loop
    int attempt_counter {0};
    int attempt_threshold {4000};

    //Get initial random state of items
    get_random_state(item_selected, number_of_items);
    

    while(break_bool != true){
        
        //Calculate the total weight and total utility
        auto[total_weight, total_utility] = get_total_weight_and_utility(item_vec, item_selected);
        //Calculate overweight factor
        double overweight_factor = calculate_overweight_factor(max_weight,total_weight);
        //Calculate total utility with penalty
        calculate_total_utility_with_overweight_penalty(overweight_factor, overweight_penalty, total_utility);

        //Calculate utility score difference with benchmark
        double utility_score_difference = utility_score_benchmark - total_utility;
        

        //If score difference is less than the best score difference, update item information
        //else check probability with simulated annealing equation on whether to update item information
        double diff = utility_score_difference - reference_item_utility_score_difference;
        if(diff <= 0){
            reference_items_selected = item_selected;
            reference_total_weight_of_items = total_weight;
            reference_item_utility_score_difference = utility_score_difference;
            change_occurred_after_temperature_change = true;
            successful_changes_counter++;
            attempt_counter = 0;
            
        }
        else if(diff > 0){
            auto[probability_check,prob_obtained,sim_prob] = check_simulated_annealing_probability(simulated_annealing_temp, diff);
            if(probability_check == true){
                reference_items_selected = item_selected;
                reference_total_weight_of_items = total_weight;
                reference_item_utility_score_difference = utility_score_difference;
                change_occurred_after_temperature_change = true;
                successful_changes_counter++;
                attempt_counter = 0;
                
            }
            else if(probability_check == false)
            {
                if(item_selected[random_index_selected] == false){
                    item_selected[random_index_selected] = true;
                }
                else{
                    item_selected[random_index_selected] = false;
                }
                change_occurred_after_temperature_change = false;
                attempt_counter++;
            }
            
        }

        //While loop break conditions
        if(change_occurred_after_temperature_change == false && attempt_counter >= attempt_threshold){
            break_bool = true;
        }
        if(floor(simulated_annealing_temp*100)/100 == 0){
            break_bool = true;
        }

        //If the number of attempts reach a threshold, reduce temperature using geometric cooling
        if(successful_changes_counter >= temperature_schedule){
            
            simulated_annealing_temp*=.95;
            change_occurred_after_temperature_change = false;
            successful_changes_counter = 0;
            
        }

        //Change an item selected from item_selected vector
        random_index_selected = change_random_item_selection(item_selected);

        iteration_counter++;

    }

    //Get number of items selected
    int number_of_items_selected {0};
    for(auto item:reference_items_selected){
        if(item==true){
            number_of_items_selected++;
        }
    }   

    //Print out output/results
    cout << "Number of items selected: " << number_of_items_selected << endl;
    cout << "Total Weight: " << reference_total_weight_of_items << endl;
    cout << "Best utility score: " << utility_score_benchmark - reference_item_utility_score_difference << endl;
    cout << "Utility difference: " << reference_item_utility_score_difference << endl;
    cout << "Total iterations: " << iteration_counter << endl;
    cout << "Temperature: " << simulated_annealing_temp << endl;

    
    return 0;
}

//Create a vector of all the items in text file after prompting user of the file name
vector<Item> create_item_vector(){
    double utility_val;
    double weight_val;
    vector<Item> item_vec;
    ifstream txt_file;
    string file_name;

    cout << "Enter name of text file to create vector from: ";
    cin >> file_name;

    txt_file.open(file_name);
    if(txt_file.is_open()){
        while(!txt_file.eof()){
            txt_file >> utility_val;
            txt_file >> weight_val;
            Item item(utility_val,weight_val);
            item_vec.push_back(item);
        }
    }
    else{
        cout << "File doesn't exist..." << endl;
    }

    // Popping last element in vector because the last row in text file is duplicated
    item_vec.pop_back();

    return item_vec;
}

//Getting initial random state of items selected
void get_random_state(vector<bool> &item_selected, int number_of_items){
    for(int item_index{0}; item_index < number_of_items; item_index++){
        int random_number = rand() % item_selected.size();
        //cout << random_number << endl;
        if(item_selected[random_number] == false){
            item_selected[random_number] = true;
        }
        else{
            //Find another item if one chosen is already set to true
            while(item_selected[random_number] == true){
                random_number = rand() % item_selected.size();
                if(item_selected[random_number] == false){
                    item_selected[random_number] = true;
                    break;
                }
            }
        }
    }
}

//Gets a random index in boolean vector and flip the original boolean value
int change_random_item_selection(vector<bool> &item_selected){
    
    int random_number = rand() % item_selected.size();
    //cout << random_number << endl;
    if(item_selected[random_number] == false){
        item_selected[random_number] = true;
        return random_number;
    }
    else{
        item_selected[random_number] = false;
        return random_number;
    }
    
}

//Calculate the total weight and utility score of the items selected
tuple<double,double> get_total_weight_and_utility(vector<Item> item_vec, vector<bool> item_selected){
    double total_weight{0.0};
    double total_utility{0.0};

    int begin_index {0};
    long long unsigned int end_index {item_vec.size() - 1};

    //Bidirectional search of item_vec to get total weight and utility of items selected
    while(begin_index != end_index){
        if(item_selected[begin_index]==true){
            total_weight += item_vec[begin_index].get_weight();
            total_utility += item_vec[begin_index].get_utility();
        }
        else if(item_selected[end_index==true]){
            total_weight += item_vec[end_index].get_weight();
            total_utility += item_vec[end_index].get_utility();
        }

        if(end_index - begin_index == 1){
            break;
        }

        begin_index++;
        end_index--;
        
    }

    //If the item_vec size is odd and begin_index == end_index, check if that item at
    //that index is selected or not
    if(begin_index == end_index){
        if(item_selected[begin_index]==true){
        total_weight += item_vec[begin_index].get_weight();
        total_utility += item_vec[begin_index].get_utility();
        }
    }

    return {total_weight, total_utility};
}

//Calculate the overweight factor, which is every pound over the weight limit
double calculate_overweight_factor(double max_weight, double total_weight){
    if(total_weight > max_weight){
        return total_weight - max_weight;
    }
    else{
        return 0.0;
    }
}

//Penalize the total utility score by some penalty score per pound overweight
void calculate_total_utility_with_overweight_penalty(int overweight_factor, double overweight_penalty, double &total_utility){
    double subtractable_utility = overweight_factor * overweight_penalty;
    total_utility -= subtractable_utility;
}

//Determine the probability of accepting and updating best item selection with current selection with simulated annealing probability equation
tuple<bool,double, double> check_simulated_annealing_probability(double &simulated_annealing_temp, double cost_difference){
    double random_probability = (rand() % 100);
    
    random_probability = random_probability /100;
    
    double loss = cost_difference;
    double simulated_annealing_probability = exp(-(loss/simulated_annealing_temp));
    
    if(random_probability <= simulated_annealing_probability){
        return {true, random_probability, simulated_annealing_probability};
    }
    else{
        return {false,  random_probability, simulated_annealing_probability};
    }
}




