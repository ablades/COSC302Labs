/*Audaris Blades
 * Lab5
 * Quick Sort 2
 */

#include <vector>
#include <iostream>
#include "sorting.h"
#include <cmath>
#include <iomanip>


void printList(vector <double> &arr){
    for(int i = 0; i < arr.size(); i ++){
        cout << arr[i] << " ";
    }
    cout << endl;

}

void quickSort(vector <double> &v, int left, int size, int print){
    if(size > 1 && print == 1){
    cout << setfill(' ') <<"S:" << setw(6)  << left << setw(6) << size << setw(8) << ' '; printList(v);
 //   cout <<"S :     " << left << "    " << size << "    "; printList(v);
    }
    if(size < 2)
        return;

    if(size == 2){
        if(v[left] > v[left +1])
            swap(v[left], v[left+1]);
        return;
    }

    int start = left;
    int middle = (left + size)/2;
    int last = start + size - 1;

    //Median of 3

    if((v[start] > v[last]  >= v[middle]) || (v[middle] >= v[last] > v[start]))
        swap(v[start], v[last]);
    else if((v[start] > v[middle]  > v[last]) || (v[last] > v[middle] > v[start]))
        swap(v[start], v[middle]);

    if(print == 1){
        cout << setfill(' ') <<"M:" << setw(6)  << left << setw(6) << size << setw(6) << v[start] << setw(2) << ' '; printList(v);
    }

    int pivot = left;

    int low = left +1;
    int high = left + size - 1;

    while(low <= high){

        while(v[low] < v[pivot] && low != left + size)
            low++;

        while(v[high] > v[pivot])
              high--;


          if(low <= high){
            swap(v[low], v[high]);
            low++;
            high--;

          //    cout << "new values " << low << ' ' << high << endl;
          }

      }

    if(low == high)
        low++;
//    cout << "PIVOT VALUE" << high << endl;
    swap(v[left], v[high]);
    //cout << "pivot swap " << left << "and " << high << endl;
    //cout <<"P :     " << left << "    " << size << " " << high << "  "; printList(v);
    if(print == 1){
    cout << setfill(' ') <<"P:" << setw(6)  << left << setw(6) << size << setw(6) << high << setw(2) << ' '; printList(v);
    }

    quickSort(v,left, (low - left) -1, 1);
    quickSort(v, low,  (left + size) - low, 1);
}





void sort_doubles(vector<double> &v, int print){
   quickSort(v, 0, v.size(), print);
};

/*int main()
{
    int size;
    int print;
    int i, j, k;

    vector<double> v;
   /* v.push_back(0.08); v.push_back(0.91); v.push_back(7.42); v.push_back(0.60);
    v.push_back(4.71);  v.push_back(7.30);  v.push_back(1.51);  v.push_back(9.64);
    v.push_back(7.63); v.push_back( 3.36);

  /*  v.push_back(9.85);  v.push_back(2.93);  v.push_back(7.70);  v.push_back(9.85);
    v.push_back(7.70);  v.push_back(9.85);  v.push_back(7.70);  v.push_back(2.93);
    v.push_back(9.85);  v.push_back(2.93);  v.push_back(2.93);  v.push_back(9.85);*/

  /*  v.push_back(5.77);  v.push_back(5.26);  v.push_back(6.49);  v.push_back(0.43);
    v.push_back(6.09);  v.push_back(4.95);  v.push_back(3.15);  v.push_back(3.46);
    v.push_back(7.55);  v.push_back(6.82);  v.push_back(6.69);  v.push_back(3.62);

    /*v.push_back(5.77);  v.push_back(5.26);  v.push_back(6.49);  v.push_back(0.43);  v.push_back(6.09);
    v.push_back(4.95);  v.push_back(3.15);  v.push_back(3.46);  v.push_back(7.55);  v.push_back(6.82);
    v.push_back(6.69);  v.push_back(3.62);*/

/*
    quickSort(v,0, v.size(), 1);

    return 0;
}*/