#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Pitch.h"

using namespace std;

//QuickSort adapted from Zybooks
template<typename currType>
int partition(vector<currType>& numbers, int i, int k) {
    int l;
    int h;
    int midpoint;
    currType pivot;
    currType temp;
    bool done;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = numbers[midpoint];

    done = false;
    l = i;
    h = k;

    while (!done) {

        /* Increment l while numbers[l] < pivot */
        while (numbers[l] < pivot) {
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers[h]) {
            --h;
        }

        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }

    return h;
}

template<typename currType>
void quickSort(vector<currType>& numbers, int i, int k) {
    int j;

    /* Base case: If there are 1 or zero elements to sort,
     partition is already sorted */
    if (i >= k) {
        return;
    }

    /* partition the data within the array. Value j returned
     from partitioning is location of last element in low partition. */
    j = partition(numbers, i, k);

    /* Recursively sort low partition (i to j) and
     high partition (j + 1 to k) */
    quickSort(numbers, i, j);
    quickSort(numbers, j + 1, k);
}

//MergeSort adapted from Lab 2
template<typename currType>
void mergeSortedLists(vector<currType>& a, vector<currType>& tmp, int left, int middle, int right) {
    //mergeSort shouldn't pass empty vectors to mergeSortedLists, but user might call mergeSortedLists with an empty vector
    if (a.empty()) {
        return;
    }

    //These indices split the section of the vector into two parts
    int i = left;           //start first part
    int j = middle + 1;     //start second part
    int tmpIndex = left;    //index of temp to which values will be copied


    //While loop to compare entries in the first and second half, copying the smaller entry into tmp
    while (i <= middle && j <= right) {
        //lesser value is in the first section
        if (a.at(i) <= a.at(j)) {
            tmp.at(tmpIndex) = a.at(i);     //copy to tmp
            i++;                            //increment i
        }
            //lesser value is in the second section
        else {
            tmp.at(tmpIndex) = a.at(j);     //copy to tmp
            j++;                            //increment j
        }
        tmpIndex++;
    }

    //If i or j have not iterated over their respective sections, make them finish
    while (i <= middle) {
        tmp.at(tmpIndex) = a.at(i);
        i++;
        tmpIndex++;
    }

    while (j <= right) {
        tmp.at(tmpIndex) = a.at(j);
        j++;
        tmpIndex++;
    }

    //Copy ONLY the values changed by this call...
    //Using (i = 0; i < a.size(); i++) can potentially remove data by copying null values from tmp to a
    for (i = left; i <= right; i++) {
        a.at(i) = tmp.at(i);
    }
}

template<typename currType>
void mergeSort(vector<currType>& a, vector<currType>& tmp, int left, int right){
    //base is implicit:
    // because of the if statement and void function type, vectors sized 0 and 1 will fall through
    if(left < right){
        //break the vector down recursively (only shifting indices)
        int midpoint = (left + right - 1)/2;
        mergeSort(a, tmp, left, midpoint);
        mergeSort(a, tmp, midpoint + 1, right);

        //run the merge operation on each part
        mergeSortedLists(a, tmp, left, midpoint, right);
    }
}//



int main() {
    //stream files
    ifstream spreadsheet;
    ofstream outFile;

    //vector for parsed data
    vector<Pitch> dataV;

    //parsing data
    cout << "Reading dataset..." << endl;
    spreadsheet.open("../pitchdata.csv");
    if(!spreadsheet.is_open()){
        cout << "Could not open file." << endl;
    }

    while(!spreadsheet.eof()){

        //put each line into a stringstream for parsing
        string line;
        getline(spreadsheet, line);
        stringstream s(line);

        //parse data into string variables
        string strStartSpeed, strEndSpeed, result, type;
        getline(s, strStartSpeed, ',');
        getline(s, strEndSpeed, ',');
        getline(s, result, ',');
        getline(s, type,',');

        //add an object of Pitch to the vector
        dataV.emplace_back(stod(strStartSpeed), stod(strEndSpeed), result, type);

    }
    spreadsheet.close();

    //Copy vectors to be sorted by each algorithm
    vector<Pitch> dataV_B = dataV; //BubbleSort vector
    vector<Pitch> dataV_S = dataV; //SelectionSort vector
    vector<Pitch> dataV_Q = dataV; //QuickSort vector
    vector<Pitch> dataV_M = dataV; //MergeSort vector

    //allocate original integer vector
    vector<int> intV;
    intV.resize(dataV.size());//optimize speed and memory allocation by setting size first
    int randomValue;
    srand(time(nullptr));
    for(int & element : intV){
        randomValue = rand() % 100;
        element = randomValue;
    }

    //Copy vectors to be sorted by each algorithm
    vector<int> intV_B = intV; //BubbleSort vector
    vector<int> intV_S = intV; //SelectionSort vector
    vector<int> intV_Q = intV; //QuickSort vector
    vector<int> intV_M = intV; //MergeSort vector

    //QuickSort
    quickSort(dataV_Q, 0, dataV.size()-1);
    quickSort(intV_Q, 0, intV.size()-1);

    /*
    //MergeSort
    vector<Pitch> tempPitch;
    tempPitch.resize(dataV.size());
    mergeSort(dataV_M, tempPitch, 0, dataV.size()-1);

    vector<int> tempInt;
    tempInt.resize(intV.size());
    mergeSort(intV_M, tempInt, 0, intV.size()-1);
    */

    outFile.open("../output.txt");
    for(auto i = 0; i < dataV.size(); i++){
        outFile << i << endl;
        //outFile << dataV_Q.at(i) << endl;
        //outFile << intV_Q.at(i) << endl;

        //outFile << dataV_M.at(i) << endl;
        //outFile << intV_M.at(i) << endl;

    }


    return 0;
}
