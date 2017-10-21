/*Audaris Blades
 * Lab5
 * Quick Sort 2
 */

#include <vector>
#include <iostream>
#include "sorting.h"



void recursiveSort(vector <double> &v, int start, int size, int print)
{
    int first, middle, last;
    int left, right;
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
        for(int left = start; (v[left] <= pivot) && (left != start+size); left++)
        {

        }
        //right pointer decrement
        for(int right = last; (v[right] >= pivot) && (right != start); right--)
        {

        }
        //We're done!
        if(left == last && right == start)
            break;
        //Swap elements and increment pointers
        else{
            swap(v[left],v[right]);
            left++;
            right--;
        }
    }
    //Swap pivot and left element
    swap(v[left], v[pivot]);
}

//print out vector
void print(){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
}

void sort_doubles(vector<double> &v, int print){
    recursiveSort(v, 0, v.size(), yes);
};

int main()
{
    int size;
    int print;
    int i, j, k;

    vector<double> v;

    return 0;
}