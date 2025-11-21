#include<iostream>
#include"DinamicArr.h"

int main(){
    DinamicArr arrA(5), arrB(10);

    arrA.setElement(50, 0);
    arrB.setElement(40, 0);
    arrA.setElement(10, 3);
    arrB.setElement(10, 3);
    std::cout << arrA.getEllement(0) << std::endl << "------" << std::endl;
    arrA.addElement(15);
    arrB.setElement(5, 5);
    arrA.show(); std::cout << "------" << std::endl;
    arrB.show(); std::cout << "------------" << std::endl;
    arrA.add(arrB);
    arrA.show(); std::cout << "------" << std::endl;
    arrA.sub(arrB);
    arrA.show(); std::cout << std::endl;
}