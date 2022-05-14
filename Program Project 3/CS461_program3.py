# -*- coding: utf-8 -*-
"""
Created on Tue May  3 02:33:24 2022

@author: peter
"""

import tensorflow as tf
import pandas as pd
import numpy as np 
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from tensorflow.keras.models import Sequential, load_model
from tensorflow.keras import Input, Model, models, layers, optimizers
from tensorflow.keras.layers import Dense, Dropout
from sklearn.metrics import accuracy_score, confusion_matrix
import seaborn as sns

#GATHERING INPUT DATA
#####################################################
#Reading .csv file and injecting data in dataframe
df = pd.read_csv('congressional_tweet_training_data.csv')

#Getting column inputs from .csv file
input1 = pd.read_csv('congressional_tweet_training_data.csv', usecols=['favorite_count'])
input2 = pd.read_csv('congressional_tweet_training_data.csv', usecols=['retweet_count'])
hashtag_data = pd.read_csv('congressional_tweet_training_data.csv', usecols=['hashtags'])
full_text_data = pd.read_csv('congressional_tweet_training_data.csv', usecols=['full_text'])


#PROCESSING SECTION
######################################################

#Convert hashtag data into series type
hashtag_data = hashtag_data.squeeze()
#Removing duplicates in cells
hashtag_data_no_duplicates = hashtag_data.str.replace(r'\b(\w+)(\s+\1)+\b', r'\1')
#Split words in the cell through 5 columns (had to experiment with the amount of columns needed)
hashtag_split = hashtag_data_no_duplicates.str.split(" ", 5, expand=True)
#Appending data to a list
hashtag_label_list = hashtag_split[0]
hashtag_label_list = hashtag_label_list.append(hashtag_split[1])
hashtag_label_list = hashtag_label_list.append(hashtag_split[2])
hashtag_label_list = hashtag_label_list.append(hashtag_split[3])
hashtag_label_list = hashtag_label_list.append(hashtag_split[4])
hashtag_label_list = hashtag_label_list.append(hashtag_split[5])

#RUN THIS PART ONCE, LONG RUNTIME
#------------------------------------

#Processing hashtag labels
# n=500
# hashtag_labels = hashtag_label_list.value_counts().index.tolist()[:n]

#Replacing hashtags from label list with index
# print("Pre-Processing Hashtag Data...")
# index = 1
# for label in hashtag_labels:
#     #print(label)
#     hashtag_split = hashtag_split.replace(label,index, regex=True)
#     progress = 'Progress: {:.2f}%'.format(round(index/501*100, 2))
#     print("\r",progress, end=" ")
#     index += 1

# print("\n")

#Replace all empty values with 0
# test = hashtag_split.fillna(0)

#Replace all remaining hashtags with NaN
# test[0] = pd.to_numeric(test[0], errors='coerce')

# test[1] = pd.to_numeric(test[1], errors='coerce')

# test[2] = pd.to_numeric(test[2], errors='coerce')

# test[3] = pd.to_numeric(test[3], errors='coerce')

# test[4] = pd.to_numeric(test[4], errors='coerce')

# test[5] = pd.to_numeric(test[5], errors='coerce')

#Replace NaN with another index that notates 'other' tags
# test = test.fillna(501)

#Replace inf values with another index that notates 'other' tags
# test = test.replace([np.inf, -np.inf], 501)

#------------------------------------
#Loading processed hashtag data
hashtag_data_indices = pd.read_csv("hashtag_data_indices.csv")

#Initializing array to specify colum in hashtag data
column_array = ["0","1","2","3","4","5"]

#Initialing arrays to create indices matrix and counting number of hashtags used
hashtag_index = np.zeros((len(hashtag_data_indices),501), dtype=int)
hashtag_count = np.zeros((len(hashtag_data_indices),1), dtype=int)


for j in range(0, len(hashtag_data_indices)):
    for i in range(0, 6):
        if hashtag_data_indices[column_array[i]][j] == 0:
            break
        else:
            label_index = hashtag_data_indices[column_array[i]][j]
            hashtag_index[j][int(label_index)-2] = 1
            hashtag_count[j] += 1

#Converting numpy arrays into pandas dataframe
hashtag_index_pd = pd.DataFrame(hashtag_index)
hashtag_count_pd = pd.DataFrame(hashtag_count, columns = ['count'])

#Initializing array to determine whether text contains URL and counting tags
url_exist = np.zeros((len(full_text_data),1), dtype=int)
tag_count = np.zeros((len(full_text_data),1), dtype=int)
positions = []

#Determining if URL exists
for k in range(0,len(full_text_data)):
    if(np.char.find(full_text_data["full_text"][k], 'https',start=0, end=None) > 0):
        url_exist[k] = 1
    else:
        url_exist[k] = 0
    for pos,char in enumerate(full_text_data["full_text"][k]):
        if(char == '@'):
            positions.append(pos)
    tag_count[k] = len(positions)
    positions.clear()

    

#Converting numpy arrays into pandas dataframe
url_exist_pd = pd.DataFrame(hashtag_count, columns = ['full_text'])
tag_count_pd = pd.DataFrame(tag_count, columns = ['tag_count'])

#Initializing array to determine length of text
text_length = np.zeros((len(full_text_data),1), dtype=int)

for l in range(0,len(full_text_data)):
    text_length[l] = len(full_text_data['full_text'][l])
    
text_length_pd = pd.DataFrame(text_length, columns = ['text_length'])


#Normalizing inputs
input1 = (input1-input1.mean())/input1.std()
input2 = (input2-input2.mean())/input2.std()
hashtag_count_pd = (hashtag_count_pd-hashtag_count_pd.mean())/hashtag_count_pd.std()
text_length_pd = (text_length_pd-text_length_pd.mean())/text_length_pd.std()
tag_count_pd = (tag_count_pd-tag_count_pd.mean())/tag_count_pd.std()

#GENERATING DATA SET
######################################################
#Concatenating input columns together into input variable
x = pd.concat([input1, input2, hashtag_index_pd, hashtag_count_pd, url_exist_pd, text_length_pd, tag_count_pd], axis=1, join='inner')

#Getting output data
y = pd.read_csv('congressional_tweet_training_data.csv', usecols=['party_id'])

#Pre-processing output data into binary values
y = y.replace("D", 0, regex=True)
y = y.replace("R", 1, regex=True)

#Splitting data into training and test sets
x_train, x_test, y_train, y_test = train_test_split(x,y,test_size = .2)


#CREATING NEURAL NETWORK MODEL
######################################################
#Creating keras model for NN
model_input1 = Input(shape=(1,), name="favorite_count")
model_input2 = Input(shape=(1,), name="retweet_count")
model_input3 = Input(shape=(501,), name="hashtags")
model_input4 = Input(shape=(1,), name="hashtag_count")
model_input5 = Input(shape=(1,), name="url_exist")
model_input6 = Input(shape=(1,), name="text_length")
model_input7 = Input(shape=(1,), name="tag_count")

input1_layer1 = layers.Dense(units=8, activation ='tanh')(model_input1)
input1_model = Model(inputs=model_input1, outputs=input1_layer1)

input2_layer1 = layers.Dense(units=8, activation ='tanh')(model_input2)
input2_model = Model(inputs=model_input2, outputs=input2_layer1)

input3_layer1 = layers.Dense(units=32, activation ='tanh')(model_input3)
input3_layer2 = layers.Dense(units=16, activation ='tanh')(input3_layer1)
input3_layer3 = layers.Dense(units=8, activation ='tanh')(input3_layer2)
input3_model = Model(inputs=model_input3, outputs=input3_layer3)

input4_layer1 = layers.Dense(units=8, activation ='relu')(model_input4)
input4_model = Model(inputs=model_input4, outputs=input4_layer1)

input5_layer1 = layers.Dense(units=8, activation ='relu')(model_input5)
input5_model = Model(inputs=model_input5, outputs=input5_layer1)

input6_layer1 = layers.Dense(units=8, activation ='tanh')(model_input6)
input6_model = Model(inputs=model_input6, outputs=input6_layer1)

input7_layer1 = layers.Dense(units=8, activation ='tanh')(model_input7)
input7_model = Model(inputs=model_input7, outputs=input7_layer1)

merged_layers = layers.concatenate([input1_model.output, input2_model.output, input3_model.output, input4_model.output, input5_model.output, input6_model.output, input7_model.output])

merged_layer1 = layers.Dense(units=8, activation ='tanh')(merged_layers)
merged_layer2 = layers.Dense(units=4, activation ='tanh')(merged_layer1)
output_layer = layers.Dense(units=1, activation ='sigmoid')(merged_layer2)

# input_layer = layers.concatenate([model_input1, model_input2, model_input3, model_input4, model_input5, model_input6, model_input7])
# layer1 = layers.Dense(units=6, activation ='tanh')(input_layer)
# layer2 = layers.Dense(units=4, activation ='tanh')(layer1)
# layer3 = layers.Dense(units=2, activation ='tanh')(layer2)
# output_layer = layers.Dense(units=1, activation ='sigmoid')(layer3)

model = Model(
    inputs=[input1_model.input, input2_model.input, input3_model.input, input4_model.input, input5_model.input, input6_model.input, input7_model.input],
    outputs=[output_layer],
)

opt = optimizers.Adam(learning_rate=0.01)

#Compiling model with cross entropy loss function
model.compile(loss='binary_crossentropy', optimizer = opt, metrics='accuracy')


#TRAINING NEURAL NETWORK MODEL
######################################################
#Fitting model
hist = model.fit([x_train["favorite_count"].to_numpy(), x_train["retweet_count"].to_numpy(), x_train[x_train.columns[2:503]].to_numpy(),x_train['count'].to_numpy(), x_train['full_text'].to_numpy(), x_train['text_length'].to_numpy(), x_train['tag_count'].to_numpy()],y_train["party_id"].to_numpy(), batch_size = 300, epochs = 50)


#PREDICTING TEST DATA
######################################################
#Predicting classifications of test data with model
y_hat = model.predict([x_test["favorite_count"].to_numpy(),x_test["retweet_count"].to_numpy(), x_test[x_test.columns[2:503]].to_numpy(), x_test['count'].to_numpy(), x_test['full_text'].to_numpy(), x_test['text_length'].to_numpy(), x_test['tag_count'].to_numpy()])

#Defining binary value output based on prediction
y_hat = [0 if val < 0.5 else 1 for val in y_hat]


#PLOTS AND RESULTS
######################################################
#Print out accuracy score of model on test data
print("\nTest accuracy: ", accuracy_score(y_test,y_hat), "\n")


plt.style.use('ggplot')
plt.plot(hist.history['loss'], label = 'loss')
plt.title("Loss vs Epochs")
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.legend()
plt.show()

plt.style.use('ggplot')
plt.plot(hist.history['accuracy'], label = 'accuracy')
plt.title("Accuracy vs Epochs")
plt.xlabel("Epochs")
plt.ylabel("Accuracy")
plt.legend()
plt.show()

tf.compat.v1.keras.utils.plot_model(model, to_file='model_plot.png', show_shapes=True, show_layer_names=True)

cf_matrix = confusion_matrix(y_test,y_hat)
print("Confusion Matrix: \n", cf_matrix,"\n")
ax = sns.heatmap(cf_matrix, annot=True, cmap='Blues')

ax.set_title('Confusion Matrix');
ax.set_xlabel('\nPredicted Values')
ax.set_ylabel('Actual Values ');

## Ticket labels - List must be in alphabetical order
ax.xaxis.set_ticklabels(['True','False'])
ax.yaxis.set_ticklabels(['True','False'])

## Display the visualization of the Confusion Matrix.
plt.show()