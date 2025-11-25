#include<iostream>
#include"DinamicArr.h"

int main(){
    DinamicArr* arrays[2];
    arrays[0] = new ArrTxt(5);
    arrays[1] = new ArrCSV(5);

    for(int i = 0; i<10;i++){
        arrays[0]->setElement(i, i);
        arrays[1]->setElement(i, i);
    }
    for (int i = 0; i < 2; i++){
        arrays[i]->saveToFile();
        delete arrays[i];
    }
    std::cout << '3' << std::endl;
}