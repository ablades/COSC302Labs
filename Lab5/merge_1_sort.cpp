/*Audaris Blades
 * Lab 5
 * Merge Sort
 */
#include <vector>
#include <iostream>
#include "sorting.h"
#include <cmath>
#include <iomanip>

void merge(vector <double> &v,vector<double> &temp,  int start,int left, int right){
    //counters
    int c = 0;
    int c1 = 0;
    int c2 = 0;
    //Fill temp vector
    while((c1 < left) && (c2 < right)){

           if( v[start + left + c2] <v[start + c1])
                temp[c++] = v[start + left + c2++];
             else
               temp[c++] = v[start + c1++];
    }

    //Insert remaining elements
    while(c1 < left)
        temp[c++] = v [start + c1++];
    while(c2 < right)
        temp[c++] = v [start + left + c2++];

    //merge into final vector
    for(int i = 0; i < left+right; i++)
        v[start + i] = temp[i];
}

void printList(vector <double> &v){
    for(int i = 0; i < v.size(); i ++){
        if(i == v.size() -1)
            cout << setprecision(2) << fixed << v[i];
        else
            cout << setprecision(2) << fixed << v[i] << " ";
    }
    cout << endl;

}

void mergeSort(vector <double> &v, vector<double> &temp, int start, int size, int print){
    //Base Case 1
    if(size == 1)
        return;

    if(print && size > 1) {
        cout << setfill(' ') << "B:" << setw(6) << start << setw(6) << size << setw(3) << ' ';
        printList(v);
    }

    //Base Case 2
    if(size == 2){
        if(v[start] > v[start + 1])
            swap(v[start + 1], v[start]);

        cout << setfill(' ') << "E:" << setw(6) << start << setw(6) << size << setw(3) << ' '; printList(v);
        return;
    }

    int mid = start + size / 2;
    if(size > 1){
        //First Half Sort
        mergeSort(v, temp, start, size/2, 1);
        //Second Half Sort
        mergeSort(v, temp, mid, size - size/2 , 1);
    }

    merge(v, temp, start, size/2, size - size/2);
    cout << setfill(' ') << "E:" << setw(6) << start << setw(6) << size << setw(3) << ' ';printList(v);


}

void sort_doubles( vector<double> &v, int print){
    vector <double> temp;
    temp.resize(v.size());
    mergeSort(v, temp, 0, v.size(), print);

    if(print){
        cout << setfill(' ') << setw(21);
        printList(v);
    }
}