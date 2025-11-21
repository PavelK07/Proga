#include<iostream>
#include"DinamicArrMod.h"

int main(){
    DinamicArrMod arr(5);
    arr.setElement(4, 0);
    arr.setElement(7, 1);
    arr.setElement(3, 2);
    arr.setElement(15, 3);
    arr.setElement(10, 4);
    arr.addElement(5);
    std::cout << arr.average() << std::endl;
    std::cout << arr.median() << std::endl;
    std::cout << arr.min() << std::endl;
    std::cout << arr.max() << std::endl;
}