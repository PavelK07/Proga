#include<iostream>
#include"DinamicArr.h"

int main() {
    try {
        DinamicArr<double> arr1(3);
        arr1.setNumericElement(1.0, 0);
        arr1.setNumericElement(2.0, 1);
        arr1.setNumericElement(3.0, 2);
        
        DinamicArr<double> arr2(3);
        arr2.setElement(4.0, 0);
        arr2.setElement(5.0, 1);
        arr2.setElement(6.0, 2);

        double dist = arr1.euclideanDistance(arr2);
        std::cout << "Евклидова метрика: " << dist << std::endl;

        DinamicArr<std::string> strArr(3);
        strArr.setElement("Hello", 0);
        strArr.setElement("Word", 1);
        strArr.setElement("!", 2);
        std::cout << strArr;
          
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } 
    return 0;
}