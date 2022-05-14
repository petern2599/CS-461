# CS-461
Repository to store the code used in the program projects for the course CS-461.

## Program 1 - Poker
Recreate the poker game and use the Monte-Carlo Simulations method to have one player playing against five other players and determine the percentage of winning with a drawn hand of cards. In the simulations, the main player will draw a hand of cards that will be identified (e.g. pairs, full house, etc.) and compared to the other players' hands. After determining whether the main player's hand wins or loses, the other players redraw their hands while the main player keeps theirs. After some amount of iterations (~1000 iterations). the main player will redraw their hand along with the other players. Repeat this whole process for a set amount of iterations (~1000 iterations) and record the wins/losses, the main player's cards, and the identified hand.

[Example of Monte Carlo Output For Poker Game](https://github.com/petern2599/CS-461/blob/main/Program%20Project%201/Poker_Result.txt)

## Program 2 - Simulated Annealing
There is a list of several items (1000+ items) that can be taken for a camping trip that describes the weight and utility score of the item. Determine an optimal solution of what combinations of items to take that maximizes the total utility score and does not exceed the weight capacity of the vehicle (500 lbs weight capacity). If the current combination of items observed exceeds the weight limit, penalize the total utility score.

[Simulated Annealing Output](https://user-images.githubusercontent.com/42896783/168448631-3a6df49b-de1e-45c0-9d03-127e01bb1c5e.PNG)

## Program 3 - Neural Networks
Develop a neural network model that can differentiate tweet posts made between two different congressional parties. Split the dataset into three subsets: training set, testing set, and the validation set. Countinuously add parameters and modify the model architecture to increase the accuracy of the neural network on the dataset.

[model_plot](https://user-images.githubusercontent.com/42896783/168448723-2efa4630-b2e5-410b-a00e-b7b718221334.png)

[Accuracy_vs_Epochs](https://user-images.githubusercontent.com/42896783/168448727-bab9563b-19aa-4191-8873-d08afac929e7.png)

[Loss_vs_Epochs](https://user-images.githubusercontent.com/42896783/168448728-f1072254-59cc-43b6-b884-67acf1d29c2b.png)

[Confusion_Matrix](https://user-images.githubusercontent.com/42896783/168448731-cc892000-98fd-4bda-8352-aad0d68f9d48.png)
