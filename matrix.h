#include <stdexcept>
#include <cmath>
#include <string>
#include "complex.h"
#include "sequence.h"

template <typename T> class Vector{
private:
    Sequence<T> *row;
    int length;
public:
    Vector(){
        this->row = nullptr;
        this->length = 0;
    }
    Vector(int x){
        this->length = x;
        this->row = (Sequence<T>*) new ArraySequence<T>(x);

    }
    Vector(Vector &item){
        this->row = (Sequence<T>*) new ArraySequence<T>(item.GetLength());
        this->length = item.GetLength();
        for (int i = 0; i < this->length; ++i){
            this->row->Set(i, item.Get(i));
        }
    }

    int GetLength(){return this->length;}
    T Get(int index){return this->row->Get(index);}
    void Set(int index, T value){this->row->Set(index, value);}

    Vector<T> operator+(Vector item) {
        int flag = 0;
        if (item.GetLength() > this->GetLength())
            flag = 1;
        if (flag == 0){
            Vector<T> a {this->GetLength()};
            for (int i = 0; i < item.GetLength(); ++i){
                a.Set(i, this->Get(i) + item.Get(i));
            }
            for (int i = item.GetLength(); i < this->GetLength(); ++i){
                a.Set(i, this->Get(i));
            }
            return a;
        }
        else if (flag == 1){
            Vector<T> a {item.GetLength()};
            for (int i = 0; i < this->GetLength(); ++i){
                a.Set(i, this->Get(i) + item.Get(i));
            }
            for (int i = this->GetLength(); i < item.GetLength(); ++i){
                a.Set(i, item.Get(i));
            }
            return a;
        }
    }

    Vector<T> operator-(Vector item) {
        int flag = 0;
        if (item.GetLength() > this->GetLength())
            flag = 1;
        if (flag == 0){
            Vector<T> a {this->GetLength()};
            for (int i = 0; i < item.GetLength(); ++i){
                a.Set(i, this->Get(i) - item.Get(i));
            }
            for (int i = item.GetLength(); i < this->GetLength(); ++i){
                a.Set(i, this->Get(i));
            }
            return a;
        }
        else if (flag == 1){
            Vector<T> a {item.GetLength()};
            for (int i = 0; i < this->GetLength(); ++i){
                a.Set(i, this->Get(i) - item.Get(i));
            }
            for (int i = this->GetLength(); i < item.GetLength(); ++i){
                a.Set(i, -item.Get(i));
            }
            return a;
        }
    }

    template <typename Z>
    Vector<T> operator*(Z value){
        Vector a{*this};
        for (int i = 0; i < a.GetLength(); ++i){a.Set(i, value * a.Get(i));}
        return a;
    }


    T VectorNorm(){
        T x = T();
        for (int i = 0; i < this->GetLength(); ++i){
            x = x + this->Get(i) * this->Get(i);
        }
        return sqrt(x);
    }

    complex VectorNormComplex(){
        T x = T();
        for (int i = 0; i < this->GetLength(); ++i){
            x = x + this->Get(i) * this->Get(i);
        }
        return x.complex::squareRoot();
    }


    T operator*(Vector<T> &item){
        T x = T();
        int min = item.GetLength() > this->GetLength() ? this->GetLength() : item.GetLength();
        for (int i = 0; i < min; ++i){
            x = x + this->Get(i) * item.Get(i);
        }
        return x;
    }
    ~Vector(){};
};


template <typename T>
class TriangleMatrix {
private:
    Sequence<T>** rows;
    int dimension;
public:

    TriangleMatrix():dimension(0) {
        rows = 0;
    }

    TriangleMatrix(int size) :dimension(size) {
        rows = (Sequence<T>**) new ArraySequence<T>*[size];
        for (int i = 0; i < size; ++i) {
            rows[i] = new ArraySequence<T>(size);
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                this->SetElement(i,j,0);
            }
        }
    }

    TriangleMatrix(const TriangleMatrix<T>& matrix) {
        this->dimension = matrix.dimension;
        this->rows = matrix.rows;
    }

    int GetDim() {
        return this->dimension;
    }

    Sequence<T>* GetRow(int index) {
        if (index < 0 || index >= this->dimension) {
            throw out_of_range("index_oor");
        }
        return rows[index];
    }



    T GetElement(int row, int col) {
        if (row < 0 || col < 0 || col >= dimension || row >= dimension) {throw out_of_range("index_oor");}

        return this->GetRow(row)->Get(col);
    }



    void SetElement(int row, int col, T item) {
        if (row < 0 || col < 0 || col >= dimension || row >= dimension) {throw out_of_range("index_oor");}
        Sequence<T>* temp = this->GetRow(row);
        temp->Set(col, item);
        rows[row] = temp;

    }

    TriangleMatrix(ArraySequence<T> sequence, int size, std::string str) : TriangleMatrix(size)  {
       if (str == "top") {
           int count = 0;
           for (int i = 0; i<size; i++) {
               for (int j=i; j<size; j++) {
                   this->SetElement(i,j, sequence[count]);
                   count++;
               }
           }
       }
       else if (str == "bottom") {
           int count = 0;
           for (int i = 0; i < size; ++i) {
               for (int j = 0; j < i + 1;++j) {
                   this->SetElement(i,j, sequence[count]);
                   ++count;
               }
           }
       }
       else {
           throw out_of_range("given string value is not accepted");
       }
       this->dimension=size;
   }

    TriangleMatrix<T> operator+(TriangleMatrix<T>& matrix) {
        if (this->dimension != matrix.dimension)  {
            throw out_of_range("dimensions of the matrices are not equal");
        }
        TriangleMatrix<T> resultMatrix = TriangleMatrix<T>(matrix.dimension);

        for(int i = 0; i < matrix.dimension; ++i) {
            for(int j = 0; j < matrix.dimension; ++j){
                T item = this->GetElement(i, j)+matrix.GetElement(i, j);
                resultMatrix.SetElement(i, j, item);
            }
        }
        return resultMatrix;
    }


    TriangleMatrix<T> operator-(TriangleMatrix<T>& matrix) {
        if (this->dimension != matrix.dimension)  {
            throw out_of_range("dimensions of the matrices are not equal");
        }
        TriangleMatrix<T> resultMatrix = TriangleMatrix<T>(matrix.dimension);

        for(int i = 0; i < matrix.dimension; ++i) {
            for(int j = 0; j < matrix.dimension; ++j){
                T item = this->GetElement(i, j) - matrix.GetElement(i, j);
                resultMatrix.SetElement(i, j, item);
            }
        }
        return resultMatrix;
    }


    template<typename U>
    TriangleMatrix<T> operator*(U factor) {
        TriangleMatrix<T> resultMatrix = TriangleMatrix<T>(this->dimension);
        for(int i = 0; i < this->dimension; ++i) {
            for(int j = 0; j < this->dimension; ++j){
                T item =((this->GetElement(i, j)) * factor);
                resultMatrix.SetElement(i, j, item);
            }
        }
        return (resultMatrix);
    }


    T MatrixNorm(){
        T x = T();
        for(int i = 0; i < this->dimension; ++i) {
            for(int j = 0; j < this->dimension; ++j){
                x = x + ((this->GetElement(i, j)) * (this->GetElement(i, j)));
            }
        }
        return std::sqrt(x);
    }

    complex MatrixNormComplex(){
        T x = T();
        for(int i = 0; i < this->dimension; ++i) {
            for(int j = 0; j < this->dimension; ++j){
                x = x + ((this->GetElement(i, j)) * (this->GetElement(i, j)));
            }
        }
        return x.complex::squareRoot();
    }


    Sequence<T>* operator[](const int index) {
       return this->GetRow(index);
    }

    ~TriangleMatrix(){};


};
