#include <iostream>
#include <vector>

class Item{
private:
    //Utility score 0-10 (least useful to most useful)
    double utility;
    //Weight of item
    double weight;
    

public:
    //Methods:
    double get_utility();
    double get_weight();

    //Constructor
    Item(double utility_val, double weight_val) : utility{utility_val}, weight{weight_val}{}
    //Deconstructor
    ~Item(){}   
};

//Get utility score of item
double Item::get_utility(){
    return utility;
}

//Get weight of item
double Item::get_weight(){
    return weight;
}