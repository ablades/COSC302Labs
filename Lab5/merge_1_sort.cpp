

//Swaps when down to two elements if necessary
void checkSwap(vector<doube> &v,int start){
    if(v[start + 1] > v[start])
        swap(v[start + 1], v[start]);
}

//
void merge(vector <double> &v, vector<double> &temp,int start, int size){
    //copy elements into temp based on order
    for(int i = start, j = size; i < size; i ++, j++){
        if(i<= size/2 && v[i] < v[j])
            temp[i] = v[i];
        else
            temp[i] = v[j];

    }

    //Copy from temp vector to perm in proper position
    for(int k = 0; k < size; k++)
        v[start +k] = temp[k];

}

void recursive_sort(vector <double> &v, vector<double> &temp, int start, int size, int print){
    base cases
    if(size == 1)
        return;
    else if(size == 2)
        checkSwap(v,start);
    else{
        //First Half Sort
        recursive_sort(v, temp, start, (start + size)/2, 1);
        //Second Half Sort
        recursive_sort(v, temp, size/2 + 1, size - size/2, 1);
    }

    merge(v,temp,start,size);



}



int main(){
    return 0;
}