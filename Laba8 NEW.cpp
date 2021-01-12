#include <iostream>
using namespace std;
template <class T>
class Matrix 
{
public:
    int n;
    int m;
    T** mas;
    Matrix()  //конструктор
    {
        n = 0, m = 0, mas = NULL;
    }

    Matrix(const Matrix& obj)  //конструктор копирования
    {
        m = obj.m;
        n = obj.n;
        mas = new T * [n];
        for (int i = 0; i < n; i++)

            mas[i] = new int[m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                mas[i][j] = obj.mas[i][j];
            }
        }
    }
    ~Matrix() {}

    void uvelichenie(int ch)  //функция увеличения элементов массива
    {
        int chi = ch;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                mas[i][j] += chi;
            }
    }
    void Vvod(int n1, int m1)
    {
        m = m1;
        n = n1;
        mas = new T * [n];

        for (int i = 0; i < n; i++)
        {
            mas[i] = new int[m];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                cin >> mas[i][j];

        }
    }

    void Vivod(int a)
    {
        if (a == 0) { cout << "that "; }
        else { cout << "prev "; }
        cout << "array is :" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                cout << mas[i][j] << endl;
        }
    }

    T Max(Matrix mas1, Matrix mas2)  //максимальный элементов
    {
        T temp1 = 0;
        T temp2 = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {

                if (mas1.mas[i][j] > temp1)
                    temp1 = mas1.mas[i][j];
            }
        }


        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {



                if (mas2.mas[i][j] > temp2)
                    temp2 = mas2.mas[i][j];
            }

        }

        cout << "Max elem  v 1 mas" << temp1 << endl;
        cout << "Max elem  v 2 mas" << temp2 << endl;
        if (temp1 > temp2)
            cout << "Max elem" << temp1 << endl;
        else
            cout << "Max elem" << temp2 << endl;



        return 0;
    }

    T Av(Matrix mas1, Matrix mas2) // среднее значение
    {
        T av1 = 0, av2 = 0;
        T sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                sum1 += mas1.mas[i][j];
                sum2 += mas2.mas[i][j];
            }
        }
        av1 = sum1 / n;
        av2 = sum2 / n;
        cout << "Average mas1= " << av1 << " Average mas2= " << av2 << endl;
        return 0;
    }

    T operator+(const Matrix& massiv) //сложение массивов

    {
        Matrix masSloz(*this);

        cout << "Slozenie  mas" << endl;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                masSloz.mas[i][j] += massiv.mas[i][j];
            }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cout << masSloz.mas[i][j] << endl;
        return 0;

    }

    T operator < (Matrix right) //меньшие элементы первого массива
    {
        int k = 0;
        int k1 = 0;

        Matrix left(*this);

        cout << "Novii mas" << endl;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                if (left.mas[i][j] <= right.mas[i][j])
                {
                    k++;

                }
            }
        k1 = k;

        T* masNew = new T[k1];
        if (k1 > 0)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {


                    for (int l = 0; l < k1; l++)
                    {
                        if (left.mas[i][j] <= right.mas[i][j])
                        {
                            masNew[l] = left.mas[i][j];
                            cout << "elem " << "= " << masNew[l] << endl;
                            break;

                        }

                    }

                }

            }
        }
        else
            cout << "No elements" << endl;  
        return 0;
    }
};
template <class T2>
class Tran // класс поддержки транзакций
{
    T2* that; // текущее значение объекта класса 
    T2* prev; // предыдущее значение объекта класса 
public:
    Tran() :prev(NULL), that(new T2) {} // конструктор
    Tran(const Tran& obj) : // конструктор копирования
        that(new T2(*(obj.that))), prev(NULL) {}
    ~Tran() { delete that; delete prev; } // деструктор
    Tran& operator=(const Tran& obj); // перегрузка операции присваивания
    void Show(int); // отображение значений (предыдущего и текущего) объекта класса
    int BeginTrans(int); // начало транзакции
    void Commit(); // закрепление транзакции
    void DeleteTrans(); // отмена транзакции
    T2* operator->(); // перегрузка операции ->
};


template <class T2>
Tran<T2>& Tran<T2>::operator=(const Tran<T2>& obj)
{
    if (this != &obj) // проверка на случай obj=obj
    {
        delete that; // удаление текущего значения объекта
        that = new T2(*(obj.that)); // создание и копирование
    }
    return *this;
}



template <class T2>
T2* Tran<T2>::operator->() // перегрузка операции ->
{
    return that;
}


template <class T2>
void Tran<T2>::Show(int fl) // отображение состояние объекта
{
    cout << "Состояние объекта ";
    if (!fl) cout << "до начала транзакции: " << endl;
    else cout << "после выполнения транзакции: " << endl;
    if (prev)  prev->Vivod(1); // предыдущее
    else cout << "prev = NULL" << endl;
    that->Vivod(0); // текущее
}



template <class T2>
int Tran<T2>::BeginTrans(int a) // начало
{
    int chislo = a;
    delete prev; // удаление предыдущего значения
    prev = that; // текущее становится предыдущим
    that = new T2(*prev); // новое значение текущего значения
    if (!that) return 0; // ошибка (необходимо отменить действие)
    that->uvelichenie(chislo); // изменение состояния объекта
    return 1; // успешное окончание транзакции
}


template <class T2>
void Tran<T2>::Commit() // закрепление
{
    delete prev; // удаление предыдущего значения
    prev = NULL; // предыдущего состояния нет
}


template <class T2>
void Tran<T2>::DeleteTrans() // отмена
{
    if (prev != NULL)
    {
        delete that; // удаление текущего значения
        that = prev; // предыдущее становится текущим
        prev = NULL; // предыдущего состояния нет
    }
    cout << "Ошибка при выполнении. Транзакция отменена. Попробуйте еще раз." << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int n = 0;
    int m = 0;
    int chislo;
    cout << "Введите кол-во строк ";
    cin >> n;
    cout << "Введите кол-во столбцов ";
    cin >> m;


    Matrix<int> sloz1;
    Matrix<int> mas1;
    mas1.Vvod(n,m);
    mas1.Vivod(0);
    Matrix<int> mas2=mas1;
    mas2.Vvod(n, m);
    mas2.Vivod(0);
    mas1.Max(mas1, mas2);
    mas1.Av(mas1, mas2);
    //sloz1 = mas2 + mas1;
  //  Matrix<int> raz1 = mas1 < mas2;


    Tran<Matrix<int>> first;
    cout << "Введите элементы " << endl;
    first->Vvod(n, m);
    first.Show(0);

   
 


    cout << "Введите число на которое хотите увеличить элементы массива " << endl;
    cin >> chislo;
    first.BeginTrans(chislo);
    first.Show(1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (first->mas[i][j] < 0)
            {
                first.DeleteTrans();
                first.Show(1);
            }
            else first.Commit();
        }
    cout << "Итоговый результат " << endl;
    first.Show(1);
    
    return 0;

}
