
#include "dynamicarray.h"
#include "linkedlist.h"
#include <stdexcept>
using std::out_of_range;


template <typename T> class Sequence {
public:
    virtual int GetSize() const = 0;
    virtual T Get(int index) const = 0;
    virtual T GetLast() const = 0;
    virtual T GetFirst() const = 0;

    virtual Sequence<T>* GetSubSequence(int start, int end) = 0;

    virtual void Set(int index, T item) = 0;

    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;

    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;

    virtual T operator[](const int index) = 0;
};



template <typename T> class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* dynArray;
public:
    //Способы инициализации - простая, с размером, копирующая, из данных
    ArraySequence(){this->dynArray = new DynamicArray<T>;}
    ArraySequence(int size){this->dynArray = new DynamicArray<T>(size);}
    ArraySequence(const ArraySequence<T> & givenArray){this->dynArray = new DynamicArray<T>(*givenArray.dynArray);}
    ArraySequence(T* data, int dataSize){this->dynArray = new DynamicArray<T>(data, dataSize);}

    int GetSize() const override {return dynArray->GetSize();};

    T GetFirst() const override {
        if (this->GetSize() == 0) {throw out_of_range("index_oor");}
        return dynArray->Get(0);}

    T GetLast() const override {
        if (this->GetSize() == 0) {throw out_of_range("index_oor");}
        return dynArray->Get(dynArray->GetSize() - 1);}

    T Get(int index) const override {
        if (index < 0 || index >= this->GetSize()) {throw out_of_range("index_oor");}
        return dynArray->Get(index);}

    ArraySequence<T>* GetSubSequence(int startGiven, int endGiven) override { //Выдаем отрезки [a, b)
        int startIndex, endIndex;
        if (startGiven > endGiven)
        {
            startIndex = endGiven;
            endIndex = startGiven;
        }
        else
        {
            startIndex = startGiven;
            endIndex = endGiven;
        }

        if (startIndex < 0 || startIndex >= this->GetSize() || endIndex < 0 || endIndex > this->GetSize()) {throw out_of_range("index_oor");}

        ArraySequence<T>* returnedArray = new ArraySequence<T>();
        for (int i = startIndex; i < endIndex; ++i) {
            returnedArray->Append(this->Get(i));
        }
        return returnedArray;
    }

    void Set(int index, T item) override {
        if (index < 0 || index >= this->dynArray->GetSize()) {
            throw out_of_range("index_oor");
        }
        return this->dynArray->Set(index, item);
    };

    void Append(T item) override {
        DynamicArray<T>* resultingArray = new DynamicArray<T>(this->GetSize() + 1);

        resultingArray->Set(this->GetSize(), item);

        for (int i = 0; i < this->GetSize(); ++i) {
            resultingArray->Set(i, this->Get(i));
        }

        this->dynArray = resultingArray;
    };

    void Prepend(T item) override {
        DynamicArray<T>* resultingArray = new DynamicArray<T>(this->GetSize() + 1);

        resultingArray->Set(0, item);

        for (int i = 0; i < this->GetSize(); ++i) {
            resultingArray->Set(i + 1, this->Get(i));
        }

        this->dynArray = resultingArray;
    };

    void InsertAt(T item, int index) override {
        if (index < 0 || index >= this->GetSize()) {throw out_of_range("index_oor");}

        int newSize = this->GetSize() + 1;
        DynamicArray<T>* resultingArray = new DynamicArray<T>(newSize);
        int count = 0;
        for (int i = 0; i < newSize; ++i) {
            if (i == index) {
                resultingArray->Set(i, item);
                continue;
            }
            resultingArray->Set(i, this->Get(count));
            ++count;
        }
        this->dynArray = resultingArray;

    };

    ArraySequence<T>* Concat(Sequence<T> *arr) override {
        ArraySequence<T>* newSequence = new ArraySequence<T>;
        for (int i = 0; i < this->GetSize(); ++i) {
            newSequence->Append(this->Get(i));}
        for (int i = 0;i < arr->GetSize(); ++i){
            newSequence->Append(arr->Get(i));
        }
        return newSequence;
    };

   virtual T operator[](const int index) override {return dynArray->Get(index);}

    ~ArraySequence() = default;

};


template <typename T> class ListSequence : public Sequence<T> {
private:
    LinkedList<T>* linList;
public:
    ListSequence()  {this->linList = new LinkedList<T>();}
    ListSequence(T* item, int size)  {this->linList = new LinkedList<T>(item, size);}
    ListSequence(LinkedList<T>* list) {this->linList = list;}
    ListSequence(const ListSequence<T>& givenSequence) {this->linList = new LinkedList<T>(*givenSequence.linList);}

    int GetSize() const override {return this->linList->GetLength();}

    T Get(int index) const override{
        if (index < 0) {throw out_of_range("index_oor");}
        return this->linList->Get(index);}

    T GetFirst() const override {
        if (this->GetSize() == 0) {throw out_of_range("index_oor");}
        return this->linList->GetFirst();}

    T GetLast() const override {
        if (this->GetSize() == 0) {throw out_of_range("index_oor");}
        return this->linList->GetLast();}

    ListSequence<T>* GetSubSequence(int startGiven, int endGiven) override {
        int startIndex, endIndex;
        if (startGiven > endGiven)
        {
            startIndex = endGiven;
            endIndex = startGiven;
        }
        else
        {
            startIndex = startGiven;
            endIndex = endGiven;
        }

        if (startIndex < 0 || startIndex >= this->GetSize() || endIndex < 0 || endIndex >= this->GetSize()) {throw out_of_range("index_oor");}

        LinkedList<T>* tempList = new LinkedList<T>();
        tempList = this->linList->GetSublist(startIndex, endIndex);
        ListSequence<T>* listSequence =new ListSequence<T>(tempList);
        return listSequence;
    }

    void Set(int index, T item) override {
        if (index < 0 || index > this->GetSize()) {throw out_of_range("index_oor");}
        return this->linList->Set(index, item);}

    void Prepend(T item) override {this->linList->Prepend(item);}

    void Append(T item) override {this->linList->Append(item);}

    void InsertAt(T item, int index) override {this->linList->InsertAt(item, index);}

     ListSequence<T>* Concat(Sequence<T>* list) override {
        ListSequence<T>* returnedList = new ListSequence<T>;
        for (int i = 0; i < this->GetSize(); ++i) {
            returnedList->Append(this->Get(i));
        }

        for (int i = 0; i < list->GetSize(); ++i) {
            returnedList->Append(list->Get(i));
        }
        return returnedList;
    }

    virtual T operator[](const int index) override {return this->linList->Get(index);};

    ~ListSequence() = default;
};
