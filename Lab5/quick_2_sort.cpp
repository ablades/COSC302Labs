/*Audaris Blades
 * Lab5
 * Quick Sort 2
 */

#include <vector>
#include <iostream>
#include "sorting.h"
#include <cmath>


void printList(vector <double> &arr){
    for(int i = 0; i < arr.size(); i ++){
        cout << arr[i] << " ";
    }
    cout << endl;

}

void quickSort(vector <double> &v, int left, int size, int print){
    cout <<"S :     " << left << "    " << size << "    "; printList(v);
    if(size < 2)
        return;

    if(size == 2){
        if(v[left] > v[left +1])
            swap(v[left], v[left+1]);
        return;
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
    cout <<"P :     " << left << "    " << size << " " << high << "  "; printList(v);


    quickSort(v,left, (low - left) -1, 1);
    quickSort(v, low,  (left + size) - low, 1);
   // cout << "second qSort index"  << left+ low << " " << (left + size) - low << endl;


 /*       cout <<"S :     " << left << "    " << left+size << "    "; printList(v);
      if(size < 2)
          return;

      if(size == 2){
          if(v[left] > v[left + 1])
              swap(v[left],v[left + 1]);

          return;
      }


      int pivot = left;
      //left index
      int low = left+1;
      //right index
      int high = left + size-1;
    int end = left + size;

      if(high < low)
          return;

      //while the index havent crossed
      while(low < high){
          //increment low pointer until it reaches the end or find element
          //increment high pointer until it reaches the front or finds element
          while(v[high] > v[pivot])
              high--;
          //     cout <<"high: "<< high << " ";
          while(v[low] < v[pivot] && low <= high)
              low++;
        //  cout <<"low: "<< low << " ";


          if(low < high){
              swap(v[low],v[high]);
              cout << " Swapped " << low << " and " << high << endl << endl;
              low++;
              high--;
          } else
              break;
      }

      if(low == high)
          low++;

      //swap pivot
      swap(v[left], v[high]);
      cout <<"P :     " << left << "    " << left+size  << " " << high << "  "; printList(v); cout << endl;
      cout << "recurse on " << left << " " << high - 1<<endl;
      cout << "recurse on " << high << " " << size<<endl;
      quickSort(v, left, high - 1, 1);
      quickSort(v, high+1, size, 1);

      swap(v[pivot],v[high]);
      cout << "low: " << low << " high: " << high <<endl;
      cout <<"P :     " << start << "    " << end << " " << high << "  "; printList(v);
      //left half recurse
      quickSort(v, start, end - low, 1);
      //right half recurse
      quickSort(v, low + 1, high, 1);

*/


}





void sort_doubles(vector<double> &v, int print){
   // recursiveSort(v, 0, v.size(), 1);
};

int main()
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

    v.push_back(5.77);  v.push_back(5.26);  v.push_back(6.49);  v.push_back(0.43);
    v.push_back(6.09);  v.push_back(4.95);  v.push_back(3.15);  v.push_back(3.46);
    v.push_back(7.55);  v.push_back(6.82);  v.push_back(6.69);  v.push_back(3.62);

    /*v.push_back(5.77);  v.push_back(5.26);  v.push_back(6.49);  v.push_back(0.43);  v.push_back(6.09);
    v.push_back(4.95);  v.push_back(3.15);  v.push_back(3.46);  v.push_back(7.55);  v.push_back(6.82);
    v.push_back(6.69);  v.push_back(3.62);*/


    quickSort(v,0, v.size(), 1);

    return 0;
}