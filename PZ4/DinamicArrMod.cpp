#include<algorithm>
#include"DinamicArrMod.h"

double DinamicArrMod::average(){
    int summ = 0;
    for (int i=0;i<size;i++){
        summ += array[i];
    }
    return (double)summ / size;
}
double DinamicArrMod::median(){
    int* temp = new int[size];
    double result;
    for (int i = 0; i < size; i++) {
        temp[i] = array[i];
    }
    std::sort(temp, temp+size);
    if (size == 0){
        return 0.0;
    }else if (size % 2 == 1){
        result = temp[size / 2];
    }else{
        result = (temp[size/2-1] + temp[size/2])/2;
    }
    delete[] temp;
    return result;
}
int DinamicArrMod::min(){
    int min = array[0];
    for (int i=0;i<size;i++){
        if (min > array[i]){
            min = array[i];
        }
    }
    return min;

}
int DinamicArrMod::max(){
    int max = array[0];
    for (int i=0;i<size;i++){
        if (max < array[i]){
            max = array[i];
        }
    }
    return max;
}