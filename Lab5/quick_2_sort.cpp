/*Audaris Blades
 * Lab5
 * Quick Sort 2
 */

#include <vector>
#include <iostream>
#include "sorting.h"
#include <cmath>
#include <iomanip>

void printList(vector <double> &v){
    for(int i = 0; i < v.size(); i ++){
        if(i == v.size() -1)
            cout << setprecision(2) << fixed << v[i];
        else
            cout << setprecision(2) << fixed << v[i] << " ";
    }
    cout << endl;

}

void quickSort(vector <double> &v, int left, int size, int print){

    if(size > 1 && print == 1){
    cout << setfill(' ') <<"S:" << setw(6)  << left << setw(6) << size << setw(7) << ' '; printList(v);
    }
    //Base Case 1
    if(size < 2)
        return;
    //Base Case 2
    if(size == 2){
        if(v[left] > v[left +1])
            swap(v[left], v[left+1]);
        return;
    }

    int start = left;
    int middle = ((size)/2)+left ;
    int last = start + size - 1;

    //Median of 3
    if(v[middle] == v[last])
        swap(v[last], v[start]);
    else if((v[start] > v[last] && v[last]  > v[middle]) || (v[middle] > v[last] && v[last] > v[start]))
        swap(v[start], v[last]);
    else if((v[start] > v[middle] && v[middle]  > v[last]) || (v[last] > v[middle] && v[middle] > v[start]))
        swap(v[start], v[middle]);

    if(print == 1){
        cout << setfill(' ') <<"M:" << setw(6)  << left << setw(6) << size << setw(6) << setprecision(2) << fixed << v[start] << setw(1) << ' '; printList(v);
    }

    int pivot = left;

    int low = left +1;
    int high = left + size - 1;
    //partition
    while(low <= high){

        while(v[low] < v[pivot] && low != left + size)
            low++;

        while(v[high] > v[pivot])
              high--;


          if(low <= high){
            swap(v[low], v[high]);
            low++;
            high--;
          }

      }

    if(low == high)
        low++;
    //pivot swap
    swap(v[left], v[high]);

    if(print == 1){
        cout << setfill(' ') <<"P:" << setw(6)  << left << setw(6) << size << setw(6) << high << setw(1) << ' '; printList(v);
    }
    
        quickSort(v,left, (low - left) -1, 1);
        quickSort(v, low,  (left + size) - low, 1);
}

void sort_doubles(vector<double> &v, int print){
   quickSort(v, 0, v.size(), print);

    if(print){
        cout << setfill(' ') << setw(25);
        printList(v);
    }
};