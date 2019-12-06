/*
 * Benjamin Raiford
 * 12/05/2019
 */
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Data.h"

using namespace std;

//BubbleSort adapted from Slides 22
template<typename currType>
void bubbleSort(vector<currType>& numbers, int size){
    int i, j;
    bool swapped;
    for (i = 0; i < size-1; i++){
        swapped = false;
        for (j = i+1; j < size-1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                swap(numbers[j], numbers[j + 1]);
                swapped = true;
            }
        }
        if(!swapped)
            break;
    }
}


//SelectionSort adapted from Slides 22
template <typename currType>
void selectionSort(vector<currType>& numbers, int size){
    int min;
    for (int i = 0; i < size - 1; ++i){
        min = i;
        for (int j = i + 1; j < size; ++j) {
            if (numbers[j] < numbers[min]) {
                min = j;
            }
        }
        swap(numbers[i], numbers[min]);
    }
}


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

    //vector for parsed data
    vector<Data> dataV;

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

        //add an object of Data to the vector
        dataV.emplace_back(stod(strStartSpeed), stod(strEndSpeed), result, type);
    }
    spreadsheet.close();
    cout << "Dataset entered." << endl;

    //allocate original integer vector
    vector<int> intV;
    intV.resize(dataV.size());//optimize speed and memory allocation by setting size first
    int randomValue;
    srand(time(nullptr));
    for(int & element : intV){
        randomValue = rand() % 100;
        element = randomValue;
    }


// Sort unsorted vectors
    for (int numElements = 1000; numElements <= dataV.size(); numElements += 1000){

        //Copy vectors to be sorted by each algorithm
        vector<Data> dataV_B = dataV; //BubbleSort vector
        vector<Data> dataV_S = dataV; //SelectionSort vector
        vector<Data> dataV_Q = dataV; //QuickSort vector
        vector<Data> dataV_M = dataV; //MergeSort vector

        vector<int> intV_B = intV; //BubbleSort vector
        vector<int> intV_S = intV; //SelectionSort vector
        vector<int> intV_Q = intV; //QuickSort vector
        vector<int> intV_M = intV; //MergeSort vector

        //Run sorting algorithms on unsorted vectors

        //BubbleSort
        cout << "Starting BubbleSort..." << endl;
        bubbleSort(dataV_B, numElements);
        bubbleSort(intV_B, numElements);
        cout << "\tBubbleSort finished.\n" << endl;


        //SelectionSort
        cout << "Starting SelectionSort..." << endl;
        selectionSort(dataV_S, numElements);
        selectionSort(intV_S, numElements);
        cout << "\tSelectionSort finished.\n" << endl;


        //QuickSort
        cout << "Starting QuickSort..." << endl;
        quickSort(dataV_Q, 0, numElements);
        quickSort(intV_Q, 0, numElements);
        cout << "\tQuickSort finished.\n" << endl;


        //MergeSort
        cout << "Starting MergeSort..." << endl;
        vector<Data> tempPitch;
        tempPitch.resize(dataV.size());
        mergeSort(dataV_M, tempPitch, 0, numElements);

        vector<int> tempInt;
        tempInt.resize(intV.size());
        mergeSort(intV_M, tempInt, 0, numElements);
        cout << "\tMergeSort finished.\n" << endl;
    }


/*
 * Below is code for running sorting algorithms on a sorted list.
 * I reused the for loop from above, but sorted dataV and intV before running it so that all copies are sorted.
 */

/*
    vector<Data> tmp_Pitch;
    tmp_Pitch.resize(dataV.size());
    mergeSort(dataV, tmp_Pitch, 0, dataV.size()-1);

    vector<int> tmp_Int;
    tmp_Int.resize(intV.size());
    mergeSort(intV, tmp_Int, 0, intV.size()-1);

    for (int numElements = 1000; numElements <= dataV.size(); numElements += 1000){

        //Copy vectors to be sorted by each algorithm
        vector<Data> dataV_B = dataV; //BubbleSort vector
        vector<Data> dataV_S = dataV; //SelectionSort vector
        vector<Data> dataV_Q = dataV; //QuickSort vector
        vector<Data> dataV_M = dataV; //MergeSort vector

        vector<int> intV_B = intV; //BubbleSort vector
        vector<int> intV_S = intV; //SelectionSort vector
        vector<int> intV_Q = intV; //QuickSort vector
        vector<int> intV_M = intV; //MergeSort vector

        //Run sorting algorithms on unsorted vectors

        //BubbleSort
        //cout << "Starting BubbleSort..." << endl;

        clock_t startPitch_B = clock(); //start clock
        bubbleSort(dataV_B, numElements);
        clock_t endPitch_B = clock(); //end clock
        double elapsedPitch_B = double(endPitch_B - startPitch_B) / CLOCKS_PER_SEC;

        clock_t startInt_B = clock(); //start clock
        bubbleSort(intV_B, numElements);
        clock_t endInt_B = clock(); //end clock
        double elapsedInt_B = double(endInt_B - startInt_B) / CLOCKS_PER_SEC;

        //cout << "\tBubbleSort finished.\n" << endl;


        //SelectionSort
        //cout << "Starting SelectionSort..." << endl;

        clock_t startPitch_S = clock(); //start clock
        selectionSort(dataV_S, numElements);
        clock_t endPitch_S = clock(); //end clock
        double elapsedPitch_S = double(endPitch_S - startPitch_S) / CLOCKS_PER_SEC;

        clock_t startInt_S = clock(); //start clock
        selectionSort(intV_S, numElements);
        clock_t endInt_S = clock();
        double elapsedInt_S = double(endInt_S - startInt_S) / CLOCKS_PER_SEC;

        //cout << "\tSelectionSort finished.\n" << endl;


        //QuickSort
        //cout << "Starting QuickSort..." << endl;

        clock_t startPitch_Q = clock(); //start clock
        quickSort(dataV_Q, 0, numElements);
        clock_t endPitch_Q = clock(); //end clock
        double elapsedPitch_Q = double(endPitch_Q - startPitch_Q)/ CLOCKS_PER_SEC;

        clock_t startInt_Q = clock(); //start clock
        quickSort(intV_Q, 0, numElements);
        clock_t endInt_Q = clock(); //start clock
        double elapsedInt_Q = double(endInt_Q - startInt_Q) / CLOCKS_PER_SEC;

        //cout << "\tQuickSort finished.\n" << endl;


        //MergeSort
        //cout << "Starting MergeSort..." << endl;
        vector<Data> tempPitch;
        tempPitch.resize(dataV.size());

        clock_t startPitch_M = clock(); //start clock
        mergeSort(dataV_M, tempPitch, 0, numElements);
        clock_t endPitch_M = clock(); //end clock
        double elapsedPitch_M = double(endPitch_M - startPitch_M) / CLOCKS_PER_SEC;


        vector<int> tempInt;
        tempInt.resize(intV.size());

        clock_t startInt_M = clock(); //start clock
        mergeSort(intV_M, tempInt, 0, numElements);
        clock_t endInt_M = clock(); //end clock
        double elapsedInt_M = double(endInt_M - startInt_M) / CLOCKS_PER_SEC;


        //cout << "\tMergeSort finished.\n" << endl;

        cout << numElements << "\t" <<
             elapsedPitch_B << "\t" <<
             elapsedInt_B << "\t" <<
             elapsedPitch_S << "\t" <<
             elapsedInt_S << "\t" <<
             elapsedPitch_Q << "\t" <<
             elapsedInt_Q << "\t" <<
             elapsedPitch_M << "\t" <<
             elapsedInt_M <<
             endl;
    }
*/

    return 0;
}
