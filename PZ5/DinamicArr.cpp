#include<iostream>
#include"DinamicArr.h"
#include<chrono>
#include<fstream>
#include<ctime>
 
void DinamicArr::show(){
    for (int i=0;i<size;i++){
        std::cout << array[i] << std::endl;
    }
}

int* DinamicArr::getArray() const{
    return array;
}
int DinamicArr::getEllement(int index) const{
    if (index>=0 && index<size){
        return array[index];
    }else{
        return -1;
    }
}
void DinamicArr::setElement(int data, int index){
    if (index>=0 && index<size && data > -100 && data < 100){
        array[index] = data;
    }
}
void DinamicArr::addElement(int data){
    if (data > -100 && data < 100){
        int new_size = size+1;
        int* new_arr = new int[new_size]{};
        for (int i=0;i<size;i++){
            new_arr[i] = array[i];
        }
        new_arr[new_size-1] = data;
        delete[] array;
        array = new_arr;
        size = new_size;
    }

}
void DinamicArr::add(DinamicArr&arr){
    for (int i = 0;i < size;i++){
        if(arr.getEllement(i) != -1){
            array[i] = array[i] + arr.getEllement(i);
        }
    }
}
void DinamicArr::sub(DinamicArr&arr){
    for (int i = 0;i < size;i++){
        if(arr.getEllement(i) != -1){
            array[i] = array[i] - arr.getEllement(i);
        }
    }
}
int ArrTxt::saveToFile(){
    if (size > 0){
        std::time_t now = std::time(nullptr);
        std::tm* local_time = std::localtime(&now);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y_%H_%M_%S", local_time);
        auto name = std::string(buffer) + ".txt";


        std::ofstream file(name);
        if (file.is_open()){
            for (int i=0;i<size;i++){
                file << array[i] << std::endl;
            }
        }else{
            return 1;
        }
    }
    return 0;
}
int ArrCSV::saveToFile(){
    if (size > 0){
        std::time_t now = std::time(nullptr);
        std::tm* local_time = std::localtime(&now);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y_%H_%M_%S", local_time);
        std::string name = std::string(buffer) + ".csv";
        std::cout << name << std::endl;
        std::ofstream file(name);
        if (file.is_open()){
            std::cout << name << std::endl;
            for (int i=0;i<size;i++){
                file << array[i] << std::endl;
            }
        }else{
            return 1;
        }
    }
    return 0;
}