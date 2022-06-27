import re
import string
import sys
import operator
import json


file = open("CS210_Project_Three_Input_File.txt", "r")
data = file.read()
words = data.split()
file.close()

unwanted_space = " "
numItemsOccur = {}
for raw_word in words:
    word = raw_word.strip(unwanted_space)
    if word not in numItemsOccur:
        numItemsOccur[word] = 0 
    numItemsOccur[word] += 1


#writes information in dictionary to frequency.dat file without punctuation 
def WriteToFile():

    #open file
     file = open('frequency.dat', 'w')

     #loop that adds dictionary elements to file 
     for key, value in numItemsOccur.items():
         file.write(key)
         file.write(" ")
         file.write(str(value))
         file.write(" ")




#prints all items purchased 
def ItemsPurchased():

    #loop to print dictionary elements with ":" in between 
    for key, value in numItemsOccur.items():
        print(key, ":", value)



#allows user to see how many of a specific item was sold
def GetNumItemsSold():

    #asks user to input item
    item_num = str(input("Enter item: "))

    #capitalize input 
    item_num = item_num.capitalize() 

    #look for item in keys of dictionary or prints error 
    if item_num in numItemsOccur.keys():
        print(item_num, ":", numItemsOccur[item_num])
    else:
        print ("Item Error: item not in system")



#sorts items by popularity 
def MostPopularItems():

    #sorts dictionary 
    sorted_dict = dict( sorted(numItemsOccur.items(),
                           key=lambda item: item[1],
                           reverse=True))

    #prints sorted dictionary 
    for key, value in sorted_dict.items():
       print(key, ":", value)
