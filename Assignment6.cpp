// Copyright (c) 2022 Alex De Meo All rights reserved
//
// Created By: Alex De Meo
// Date: 04s//22
// Description: This is the final Assignment of the year. I have packed three
// programs into one, a Sum Matcher program that takes a list of numbers and
// a desired sum, it then finds all the possible pairs of numbers that add up to
// that desired sum; an Index Finder program that finds the index of a desired
// element inside of a list; finally, a Remainder program that takes a list of
// integers and a divisor, then finds the remainder of each of the elements in
// the list, divided by the divisor.

#include <list>
#include <array>
#include <iomanip>
#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stof;
using std::array;
using std::list;
using std::to_string;


// This function converts a list of strings into a list of integers. Each
// program needs to do this, so I just made a function once so I wouldn't need
// to write the code multiple times
list<int> StrInt(list<string> strings) {
    list<int> ints;
    int newNum;
    for (string word : strings) {
        newNum = stoi(word);
        ints.push_back(newNum);
    }

    return ints;
}


// Since C++ doesn't have a split() function, I have to make my own
list<string> split(string uList) {
    list<string> words;
    string word = "";
    list<string> newList;

    // goes through each letter in the uList
    for (char letter : uList) {
        // when it reaches a space it will put the word into the list
        if (letter == ' ') {
            words.push_back(word);
            word = "";
        } else {
            word += letter;
        }
    }
    // Pushes the final word into the list because there probably wont be a
    // space after it
    words.push_back(word);
    word = "";

    // This part goes through each letter in the new "words" list, this time it
    // will remove the commas
    for (string element : words) {
        for (char letter : element) {
            // when it reaches a space it will put the word into the list
            if (letter == ',') {
                newList.push_back(word);
                word = "";
            } else {
                word += letter;
            }
        }
    }

    // Pushes the final word into the list because there probably wont be a
    // comma after it
    newList.push_back(word);

    return newList;
}


// this function finds the pairs of numbers in the list that add up to the
// desired sum. It purposefuly excludes repeats or the case where the numbers
// are just switched around. ie. it will only have (7 + 3) = 10 in a list with
// 7, 5, 3, 3, 8, 9.
// This function took a lot of thinking and was a fun little challenge
list<string> FindSumPairs(list<int> ints, int numSum) {
    int counter1 = 0;

    list<string> nPairs;
    list<string> returnPair;
    // first loop is to find what each element needs as a complement to
    // achieve the desired sum
    for (int aNum : ints) {
        counter1 += 1;
        int counter2 = 0;
        int matchNum = numSum - aNum;
        // secong loop is to check if the complement is found
        for (int number : ints) {
            counter2 += 1;
            int counter3 = 0;
            // This basically checks to make sure both loops aren't referencing
            // the same index in the list. If they are it will skip whatever is
            // below and will continue the loop
            if (counter2 == counter1) {
                continue;
            }
            // If the complement is found, it formats it into a string and adds
            // it to the list
            if (number == matchNum) {
                string pair = "(" + to_string(aNum) + " + "
                + to_string(number) + ")";

                nPairs.push_back(pair);
                // This loop checks to make sure that it only counts a pair one
                // time. Ie. instead of having (7 + 3) and (3 + 7) it will only
                // have (7 + 3) because this is all that the user needs
                for (string aPair : nPairs) {
                    // this makes the inverse of the last pair
                    string checkPair = "(" + to_string(number) + " + "
                    + to_string(aNum) + ")";
                    // if the inverse of the pair is in the list, it will
                    // pop/remove that pair from the list. This portion excludes
                    // the case of two numbers being the same, because it would
                    // remove it even though it wasn't already in the list. Ie.
                    // (5 + 5) is the inverse of (5 + 5) so they would both be
                    // removed.
                    if (aPair == checkPair) {
                        nPairs.pop_back();
                    }
                    if (aNum == number) {
                        nPairs.push_front(pair);
                    }
                    counter3 += 1;
                    int counter4 = 0;
                    // this loop takes care of the case where two numbers are
                    // the same. Ie. (5 + 5) or (6 + 6)
                    for (string dPair : nPairs) {
                        counter4 += 1;
                        // again this ensures the loops aren't referencing the
                        // same index in the list
                        if (counter4 == counter3) {
                            continue;
                        }
                        // This will pop/remove the element if there is one just
                        // like it somewhere in the list before it

                        if (aPair == dPair) {
                            nPairs.pop_front();
                        }
                    }
                }
            }
        }
    }

    return nPairs;
}


// This function calculates the remainders of the numbers in the list divided by
// the entered divisor
list<int> CalcRemainders(list<int> ints, int divisor) {
    list<int> lRemainder;
    for (int aNum : ints) {
        int divNum = aNum % divisor;
        lRemainder.push_back(divNum);
    }
    return lRemainder;
}


// This function finds the index of the desired element in the list
int FindIndex(list<int> ints, int number) {
    int found = -1, counter = 0;
    for (int aNum : ints) {
        if (aNum == number) {
            return counter;
        }
        counter++;
    }
    return found;
}


// This is the function that gets all the necessary input to find the index of
// the desired element in the list
void IndexFinder() {
    bool failureLoop3 = true;
    // list<string> lStr3;
    // list<int> lInts3;
    cout << "" << endl;
    // list allows for the list to be re-entered incase of invalid input
    do {
        string uInts3;
        cout << "Enter a list of integers (Each number must be separated" <<
        " by ',' followed by a space): ";
        getline(cin, uInts3);

        // splitting at the commas
        list<string> lStr3 = split(uInts3);

        try {
            // calls the function that converts the strings to ints inside list
            list<int> lInts3 = StrInt(lStr3);

            bool indexFailure = true;
            // Allows for the desired element to be re-entered incase of invalid
            // input
            while (indexFailure) {
                string uFind;
                cout << "Enter the integer you are looking for: ";
                cin >> uFind;
                try {
                    int find = stoi(uFind);

                    indexFailure = false;
                    failureLoop3 = false;

                    // Calls the func that will return the index of the
                    // desired element in the list of numbers
                    int index = FindIndex(lInts3, find);
                    // Displaying results to user
                    if (index != -1) {
                        cout << endl << "The first index of the number " <<
                        find << " is " << index << endl;
                    } else {
                        cout << endl << find << " is not in your list!" << endl;
                    }
                } catch (...) {
                    cout << "The integer you entered wasn't a real integer" <<
                    endl;
                }
            }
        } catch (...) {
            cout << "There was something wrong with the list of integers" <<
            " entered" << endl;
        }
    } while (failureLoop3);
}


// This is the function that gets all the necessary input to find the pairs that
// equal the desired sum
void SumMatcher() {
    bool failureLoop2 = true;

    // loop allows for the list to be re-entered incase of invalid input
    while (failureLoop2) {
        string uInts2;
        cout << "Enter a list of integers (Each number must be separated" <<
        " by ',' followed by a space): ";
        getline(cin, uInts2);

        // splitting at the commas
        list<string> lStr2 = split(uInts2);

        try {
            // calls a func to convert the strings to ints inside list
            list<int> lInts2 = StrInt(lStr2);

            bool sumFailure = true;
            // allows for the desired sum to be re-done incase of invalid input
            while (sumFailure) {
                string uSum;
                cout << "Enter the integer that you would like the sum to be: ";
                getline(cin, uSum);
                try {
                    int sumInt = stoi(uSum);

                    failureLoop2 = false;
                    sumFailure = false;
                    // Calls the function that will return a list of the pairs
                    // of elements that add up to the desired sum
                    list<string> pairs = FindSumPairs(lInts2, sumInt);

                    // Displaying results to user
                    if (pairs.size() == 0) {
                        cout << "There were no pairs of numbers adding up to" <<
                        " " << sumInt << endl;
                    } else {
                        cout << "The pairs of numbers that add up to " <<
                        sumInt << " are:" << endl;
                        for (string displayPair : pairs) {
                            cout << displayPair << " ";
                        }
                        cout << "" << endl;
                    }
                } catch (...) {
                    cout << "You didn't enter an integer! Try again." << endl;
                }
            }
        } catch (...) {
            cout << "There was something wrong with the list of integers" <<
            endl;
        }
    }
}


// this is the function that gets all the necessary input to find the remainders
// of every index in the entered list
void FindRemainder() {
    bool failureLoop = true;

    // Loop allows for the list to be re-entered incase of invalid input
    while (failureLoop) {
        string uInts;
        cout << "Enter a list of integers (Each number must be separated" <<
        " by ',' followed by a space): ";
        getline(cin, uInts);

        // splitting at commas
        list<string> lStr = split(uInts);
        try {
            // calls a func that converts strings to ints inside list
            list<int> lInts = StrInt(lStr);

            bool divFailure = true;
            // This loop allows for the divisor to be re-entered incase of
            // invalid input
            while (divFailure) {
                string uDivisor;
                cout << "Enter an integer you'd like to divide by: ";
                getline(cin, uDivisor);

                try {
                    int divisorInt = stoi(uDivisor);

                    divFailure = false;
                    failureLoop = false;

                    // calls the function that will calculate the remainders
                    // of each element divided by the divisor
                    list<int> remainders = CalcRemainders(lInts, divisorInt);
                    // displays results
                    int counter = 0;
                    for (int fRemainder : remainders) {
                        cout << "The remainder of position " << counter <<
                        " is " << fRemainder << endl;

                        counter++;
                    }
                } catch (...) {
                    cout << "That was not a valid integer" << endl;
                }
            }
        } catch (...) {
            cout << "There was something wrong with the list of numbers you" <<
            " entered" << endl;
        }
    }
}


int main() {
    bool restartLoop = true;
    // loop allows for the user to choose a new program once the previous
    // calculations are complete
    while (restartLoop) {
        bool retryLoop = false;
        // getting user's choice for the program
        string choice;
        cout << "Choose a program to run: " << endl <<
        "1 - Remainder finder program" <<
        endl << "2 - Sum Matcher program" << endl <<
        "3 - Index finder program" << endl << endl <<
        "Selection: ";
        getline(cin, choice);
        // calls whichever function was chosen
        if (choice == "1") {
            FindRemainder();
            retryLoop = true;
        } else if (choice == "2") {
            SumMatcher();
            retryLoop = true;
        } else if (choice == "3") {
            IndexFinder();
            retryLoop = true;
        } else {
            cout << "I don't understand, Please try again." << endl;
        }

        while (retryLoop) {
            string choice2;
            cout << "Would you like to play again? (y/n): ";
            getline(cin, choice2);

            // this is what decides whether or not to rum the program again
            if (choice2 == "y") {
                retryLoop = false;
            } else if (choice2 == "n") {
                retryLoop = false;
                restartLoop = false;
            } else {
                cout << "I don't understand, try again!" << endl;
            }
        }
    }
}
