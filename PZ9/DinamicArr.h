#include <iostream>
#include <math.h>
template <typename T>
class DinamicArr{
    T* array;
    int size;
    public:
        //Конструктор
        DinamicArr(int s){
            size = s;
            array = new T[size]{};
        }
        //Конструктор копирования
        DinamicArr(const DinamicArr &other){
            size = other.size;
            array = new T[size];
            for (int i = 0; i < size; i++) {
                array[i] = other.array[i];
            }
        }

        template<typename U = T>
        void setNumericElement(U data, int index) {
            if constexpr (!(std::is_integral_v<U> || std::is_floating_point_v<U>)){
                throw std::bad_typeid();
            }else{
                if (index < 0 || index >= size) {
                    throw std::out_of_range("Index out of range");
                }
                array[index] = data;
            }
        }

        void setElement(T data, int index){
            if (index<0 || index>size){
                throw std::out_of_range("Index out of range");
            }
            array[index] = data;
        }

        void addElement(T data){
            int newSize = size+1;
            T* newArr = new T[newSize]{};
            for (int i=0;i<size;i++){
                newArr[i] = array[i];
            }
            newArr[newSize-1] = data;
            delete[] array;
            array = newArr;
            size = newSize;

        }

        T* getArray() const{
            return array;
        }

        T getElement(int index) const{
            if (index<0 || index>size){
                throw std::out_of_range("Index out of range");
            }
            return array[index];
        }

        template<typename U>
        double euclideanDistance(const DinamicArr<U>& other) const {
            if constexpr (!(std::is_integral_v<U> || std::is_floating_point_v<U>)){
                throw std::bad_typeid();
            }else{
                if (size != other.getSize()) {
                    throw std::invalid_argument("Размер должен быть одинаков");
                }
                
                // Вычисление евклидова расстояния
                double sum = 0.0;
                for (int i = 0; i < size; i++) {
                    double diff = static_cast<double>(array[i]) - static_cast<double>(other.getElement(i));
                    sum += diff * diff;
                }
                
                return std::sqrt(sum);
            }
        }
        
        int getSize() const {
            return size;
        }

        friend std::ostream& operator<<(std::ostream& os, const DinamicArr& obj){
            for (int i=0;i<obj.getSize();i++){
                os << obj.getArray()[i] << ";";
            }
            return os;
        }
        //Деструктор
        ~DinamicArr(){
            delete[] array;
        }
};