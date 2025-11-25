class DinamicArr{
    protected:
        int* array;
        int size;
    public:
        
        DinamicArr(int s){     //Конструктор
            size = s;
            array = new int[size]{};
        }
        
        DinamicArr(const DinamicArr &other){   //Конструктор копирования
            size = other.size;
            array = new int[size];
            for (int i = 0; i < size; i++) {
                array[i] = other.array[i];
            }
        }

        void show();
        
        void setElement(int data, int index);

        int* getArray() const;
        int getEllement(int index) const;
        
        void addElement(int data);

        void add(DinamicArr&arr); //Сложение
        
        void sub(DinamicArr&arr); //Вычитане
        
        virtual int saveToFile(){return 0;};

        virtual ~DinamicArr(){    //Деструктор
            delete[] array;
        }
};
class ArrTxt:public DinamicArr{
    public:
        ArrTxt(int s): DinamicArr(s){}
        ArrTxt(const ArrTxt &other): DinamicArr(other){}
        int saveToFile() override;
        
};
class ArrCSV:public DinamicArr{
    public:
        ArrCSV(int s): DinamicArr(s){}
        ArrCSV(const ArrCSV &other): DinamicArr(other){}
        int saveToFile() override;
        
};