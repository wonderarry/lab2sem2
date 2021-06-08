#include <iostream>
#include <cassert>
#include <random>
#include "matrix.h"

using std::cin;
using std::cout;


bool is_auto;
std::random_device rd;
std::mt19937 mersenne(rd());


void twoVectorsTests(){
    int x;
    double realinput, imaginput;
    cout << "Введите натуральное число - количество элементов первого вектора: ";
    cin >> x;
    assert(x > 0 && "\nЗначение вне допустимого диапазона");
    Vector<complex> v1 {x};
    for (int i = 0; i < x; ++i){

        cout << "\nВведите вещественную часть числа под индексом " << i <<" из " << x << " :";
        if (is_auto){
            realinput = -100 + mersenne() % 200;
            cout << realinput;
        }
        else{
            cin >> realinput;
        }
        cout << "\nВведите мнимую часть числа под индексом " << i <<" из " << x << " :";
        if (is_auto){
            imaginput = -100 + mersenne() % 200;
            cout << imaginput;
        }
        else{
        cin >> imaginput;}
        v1.Set(i, complex{realinput, imaginput});
    }
    cout << "\nВведите натуральное число - количество элементов второго вектора: ";
    cin >> x;
    assert(x > 0 && "\nЗначение вне допустимого диапазона");
    Vector<complex> v2 {x};
    for (int i = 0; i < x; ++i){
        cout << "\nВведите вещественную часть числа под индексом " << i <<" из " << x << " :";
        if (is_auto){
            realinput = -100 + mersenne() % 200;
            cout << realinput;
        }
        else{
            cin >> realinput;
        }
        cout << "\nВведите мнимую часть числа под индексом " << i <<" из " << x << " :";
        if (is_auto){
            imaginput = -100 + mersenne() % 200;
            cout << imaginput;
        }
        else{
        cin >> imaginput;}
        v1.Set(i, complex{realinput, imaginput});
    }
    cout << "\nВыберите действие:\n1. Сложение\n2. Вычитание\n3. Скалярное произведение\n";
    cin >> x;
    assert((x == 1 || x == 2 || x == 3) && "\nВыбранной опции не существует.");
    if (x == 1){
        v1 = v1 + v2;
        for (int i = 0; i < v1.GetLength(); ++i){
            v1.Get(i).print();
            cout << '\n';
        }
    }
    if (x == 2){
        v1 = v1 - v2;
        for (int i = 0; i < v1.GetLength(); ++i){
            v1.Get(i).print();
            cout << '\n';
        }
    }
    if (x == 3){
        (v1 * v2).print();
    }
}

void vectorScalarTests(){
    int x;
    double realinput, imaginput;
    cout << "Введите натуральное число - количество элементов вектора: ";
    cin >> x;
    assert(x > 0 && "\nЗначение вне допустимого диапазона");
    Vector<complex> v1 {x};
    for (int i = 0; i < x; ++i){
        cout << "\nВведите вещественную часть числа под индексом " << i <<" из " << x << " :";
        if (is_auto){
            realinput = -100 + mersenne() % 200;
            cout << realinput;
        }
        else{
            cin >> realinput;
        }
        cout << "\nВведите мнимую часть числа под индексом " << i <<" из " << x << " :";
        if (is_auto){
            imaginput = -100 + mersenne() % 200;
            cout << imaginput;
        }
        else{
        cin >> imaginput;}
        v1.Set(i, complex{realinput, imaginput});
    }
    cout << "\nВведите вещественную часть числа:";
    if (is_auto){
        realinput = -100 + mersenne() % 200;
        cout << realinput;
    }
    else{
        cin >> realinput;
    }
    cout << "\nВведите мнимую часть числа:";
    if (is_auto){
        imaginput = -100 + mersenne() % 200;
        cout << imaginput;
    }
    else{
    cin >> imaginput;}
    complex multItem{realinput, imaginput};
    v1 = v1 * multItem;
    for (int i = 0; i < x; ++i){
        v1.Get(i).print();
        cout << '\n';
    }
}

void vectorNormTests(){
    int x;
    double realinput, imaginput;
    cout << "Введите натуральное число - количество элементов вектора: ";
    cin >> x;
    assert(x > 0 && "\nЗначение вне допустимого диапазона");
    Vector<complex> v1 {x};
    for (int i = 0; i < x; ++i){
        cout << "\nВведите вещественную часть числа под индексом " << i <<" из " << x << " :";
        if (is_auto){
            realinput = -100 + mersenne() % 200;
            cout << realinput;
        }
        else{
            cin >> realinput;
        }
        cout << "\nВведите мнимую часть числа под индексом " << i <<" из " << x << " :";
        if (is_auto){
            imaginput = -100 + mersenne() % 200;
            cout << imaginput;
        }
        else{
        cin >> imaginput;}
        v1.Set(i, complex{realinput, imaginput});
    }
    v1.VectorNormComplex().print();
}


void vectorTests(){
    int b;
    cout << "\nДоступны следующие варианты тестирования:\n1. Ввод двух векторов и расчет их суммы/разности/произведения\n2. Ввод вектора и числа, расчет произведения\n3. Ввод вектора, расчет Евклидовой нормы";
    assert((b == 1 || b == 2 || b == 3) && "\nВыбранной опции не существует.");
    cin >> b;
    if (b == 1){
        twoVectorsTests();
    }
    if (b == 2){
        vectorScalarTests();
    }
    if (b == 3){
        vectorNormTests();
    }
}

void triangleMatrixTests(){
    int y;
    int dim;
    double realinput, imaginput;
    cout << "\nУкажите натуральное число - размерность матрицы (количество строк/столбцов): ";
    cin >> dim;
    assert(dim > 0 && "\nИзмерения - натуральное число");
    ArraySequence<complex> a{};
    for (int i = 0; i < (dim+1)*(dim/2); ++i){
        cout << "\nВведите вещественную часть числа под индексом " << i <<" из " << (dim+1)*(dim/2) - 1 << " :";
        if (is_auto){
            realinput = -100 + mersenne() % 200;
            cout << realinput;
        }
        else{
            cin >> realinput;
        }
        cout << "\nВведите мнимую часть числа под индексом " << i <<" из " << (dim+1)*(dim/2) - 1 << " :";
        if (is_auto){
            imaginput = -100 + mersenne() % 200;
            cout << imaginput;
        }
        else{
        cin >> imaginput;}
        a.Append(complex{realinput, imaginput});
    }
    cout << "\nВведите 1 для создания верхней треугольной матрицы, 2 - для нижней: ";
    cin >> y;
    assert((y == 1 || y == 2) && "\nВыбранной опции не существует.");
    TriangleMatrix<complex> res;
    if (y == 1){
        res = TriangleMatrix<complex> {a, dim, "top"};
    }
    else if (y == 2){
        res = TriangleMatrix<complex> {a, dim, "bottom"};
    }
    for (int i = 0; i < dim; ++i){
        cout << '\n';
        for (int j = 0; i < dim; ++j){
            res.GetElement(i, j).print();
            cout << "   ";
        }
    }
}

void twoMatricesTests(){
    int dim;
    double realinput, imaginput;
    cout << "\nУкажите натуральное число - размерность матрицы (количество строк/столбцов): ";
    cin >> dim;
    assert(dim > 0 && "\nИзмерения - натуральное число");
    cout << "\nПриготовьтесь к вводу чисел в первую матрицу.\n";
    TriangleMatrix<complex> m1{dim}, m2{dim};
    for (int i = 0; i < dim; ++i){
        for (int j = 0; i < dim; ++j){
            cout << "\nВведите вещественную часть числа под индексами " << i << ", " << j << "из " << dim << ", " << dim << ": ";
            if (is_auto){
                realinput = -100 + mersenne() % 200;
                cout << realinput;
            }
            else{
                cin >> realinput;
            }
            cout << "\nВведите мнимую часть числа под индексами " << i << ", " << j << "из " << dim << ", " << dim << ": ";
            if (is_auto){
                imaginput = -100 + mersenne() % 200;
                cout << imaginput;
            }
            else{
            cin >> imaginput;}
            m1.SetElement(i, j, complex{realinput, imaginput});
        }
    }
    cout << "\nПриготовьтесь к вводу чисел во вторую матрицу.\n";
    for (int i = 0; i < dim; ++i){
        for (int j = 0; i < dim; ++j){
            cout << "\nВведите вещественную часть числа под индексами " << i << ", " << j << "из " << dim << ", " << dim << ": ";
            if (is_auto){
                realinput = -100 + mersenne() % 200;
                cout << realinput;
            }
            else{
                cin >> realinput;
            }
            cout << "\nВведите мнимую часть числа под индексами " << i << ", " << j << "из " << dim << ", " << dim << ": ";
            if (is_auto){
                imaginput = -100 + mersenne() % 200;
                cout << imaginput;
            }
            else{
            cin >> imaginput;}
            m2.SetElement(i, j, complex{realinput, imaginput});
        }
    }
    int y;
    cout << "\nВыберите действие: \n1. Сложение\n2. Вычитание";
    cin >> y;
    assert((y == 1 || y == 2) && "\nВыбранной опции не существует.");
    if (y == 1){
        m1 = m1 + m2;
    }
    if (y == 2){
        m1 = m1 - m2;
    }
    for (int i = 0; i < dim; ++i){
        cout << '\n';
        for (int j = 0; i < dim; ++j){
            m1.GetElement(i, j).print();
            cout << "   ";
        }}
}

void matrixNormTests(){
    double realinput, imaginput;
    int dim;
    cout << "\nУкажите натуральное число - размерность матрицы (количество строк/столбцов): ";
    cin >> dim;
    assert(dim > 0 && "\nИзмерения - натуральное число");
    TriangleMatrix<complex> m1{dim};
    for (int i = 0; i < dim; ++i){
        for (int j = 0; i < dim; ++j){
            cout << "\nВведите вещественную часть числа под индексами " << i << ", " << j << "из " << dim << ", " << dim << ": ";
            if (is_auto){
                realinput = -100 + mersenne() % 200;
                cout << realinput;
            }
            else{
                cin >> realinput;
            }
            cout << "\nВведите мнимую часть числа под индексами " << i << ", " << j << "из " << dim << ", " << dim << ": ";
            if (is_auto){
                imaginput = -100 + mersenne() % 200;
                cout << imaginput;
            }
            else{
            cin >> imaginput;}
            m1.SetElement(i, j, complex{realinput, imaginput});
        }
    }
    m1.MatrixNormComplex().print();
}

void matrixTests(){
    int c;
    cout << "\nДоступны следующие варианты тестирования:\n1. Ввод треугольной матрицы\n2. Ввод двух матриц равных измерений, сложение/вычитание\n3. Ввод матрицы, вычисление Евклидовой нормы";
    assert((c == 1 || c == 2 || c == 3) && "\nВыбранной опции не существует.");
    cin >> c;
    if (c == 1){
        triangleMatrixTests();
    }
    if (c == 2){
        twoMatricesTests();
    }
    if (c == 3){
        matrixNormTests();
    }
}


void menuInit(){
    int a;
    cout << "-----------Главное меню тестирования-----------\n\nОпции:\n0. Ручной ввод\n1. Автоматический выбор значений\nВыбор: ";
    assert((is_auto == 0 || is_auto == 1) && "\nВыбранной опции не существует.");
    cin >> is_auto;
    cout << "\n1. Тестирование вектора\n2. Тестирование треугольной (или квадратной) матрицы\nВыбор: ";
    cin >> a;
    assert((a == 1 || a == 2) && "\nВыбранной опции не существует.");
    if (a == 1){
        vectorTests();
    }
    if (a == 2){
        matrixTests();
    }
}




int main(){
    std::setlocale(LC_ALL, "Russian");
    menuInit();
}
