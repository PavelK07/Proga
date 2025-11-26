#include<iostream>
#include"DinamicArr.h"

int main(){
    DinamicArr arr(10);
    for(int i = 0; i<5;i++){
        arr.setElement(i, i);
    }
    arr.setElement(200, 1);
    std::cout << arr.getEllement(1);
}