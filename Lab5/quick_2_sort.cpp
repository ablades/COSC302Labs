/*Audaris Blades
 * Lab5
 * Quick Sort 2
 */

#include <vector>
#include <iostream>
#include "sorting.h"


void printList(vector <double> &arr){
    for(int i = 0; i < arr.size(); i ++){
        cout << arr[i] << " ";
    }
    cout << endl;
}


void recursiveSort(vector <double> &v, int start, int size, int print)
{
    int first, middle, last;
    int left;
    int right;
    int pivot;
    first = start;
    middle = (start+size)/2;
    last = start + size - 1;

    //Median of 3
    if(v[start] > v[middle])
        swap(v[start], v[middle]);

    if(v[middle] > v[last])
        swap(v[middle], v[last]);

    //Move median to front of vector (if not already)
    if(v[middle] > v[start])
        swap(v[middle], v[start]);

    pivot = start;

    left = start +1;
    right = last;


    //Continue until the left pointer crosses or equals right pointer
    while(left < right){
        //Left pointer increment
        for(int i = start; (v[i] <= pivot) && (left != start+size); i++)
            if(v[i] >= pivot)
                left = i;


        //right pointer decrement
        for(int j = last; (v[j] >= pivot) && (j != start);j--)
            if(v[j] <= pivot)
                right = j;

        //We're done!
        if(left == last && right == start)
            break;
        //Swap elements and increment pointers
        else{
            printList(v);
            swap(v[left],v[right]);
            printList(v);
            left++;
            right--;
        }
    }
    //Swap pivot and left element
    swap(v[left], v[pivot]);
}


void sort_doubles(vector<double> &v, int print){
    recursiveSort(v, 0, v.size(), 1);
};

int main()
{
    int size;
    int print;
    int i, j, k;

    vector<double> v;
    v.push_back(5.77); v.push_back(5.26); v.push_back(6.49); v.push_back(0.43);
    v.push_back(6.09);  v.push_back(4.95);  v.push_back(3.15);  v.push_back(3.46);
    v.push_back(7.55); v.push_back( 6.82); v.push_back(6.69);  v.push_back(3.62);

    recursiveSort(v,0, v.size(), 1);

    return 0;
}