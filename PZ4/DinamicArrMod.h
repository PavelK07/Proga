#include"DinamicArr.h"

class DinamicArrMod : public DinamicArr {
    public:
        DinamicArrMod(int s) : DinamicArr(s){
        }
        DinamicArrMod(const DinamicArr &other) : DinamicArr(other){    //Конструктор копирования
        }
        double average();
        double median();
        int min();
        int max();
};