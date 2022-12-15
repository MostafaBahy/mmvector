#include <bits/stdc++.h>
using namespace std;
template<typename T>

class mmVector
{
private:

    T *ptr;
    int vecSize;
    int vecCapacity;

public:

    mmVector(){}

    mmVector (int x)//constructor
    {
        ptr = new T[x];
        vecCapacity = x;
        vecSize = 0;
    }


    ~mmVector()  //deallocating mmvector
    {
        delete[] ptr;
    }


    int size() const// Return current size of vec
    {
        return vecSize;
    }


    bool empty()  // Return true if size is 0
    {
        if(vecSize)
            return false;
        else
            return true;
    }


    void push_back(T data)
    {

        if (vecSize == vecCapacity)
        {
            T* temp = new T[2 * vecCapacity];

            // copying old array elements to new array
            for (int i = 0; i < vecCapacity; i++)
                temp[i] = ptr[i];
            // deleting previous array
            delete[] ptr;
            vecCapacity *= 2;
            ptr = temp;
            delete[] temp;
        }

        // Inserting data
        ptr[vecSize] = data;
        vecSize++;
    }



    int capacity() const// Return size of current allocated array
    {
        return vecCapacity;
    }



    T& operator[](int index)
    {
        if (index >= vecSize)
        {
            cout << "This index is out of bound";
            exit(0);
        }
        else
            return ptr[index];
    }


    void clear()  // Delete all vector content
    {
        T* temp = new T[1];
        delete[] ptr;
        ptr = temp;
        vecCapacity = 1;
        vecSize = 0;
    }


    mmVector &operator=(const mmVector& myVec )  // Copy assignment
    {
        delete[] this->ptr ;
        this->vecCapacity = myVec.vecCapacity;
        this->vecSize = myVec.vecSize;
        this->ptr = new T[vecCapacity];
        for(int i =0 ; i< myVec.vecSize;i++)
            this->ptr[i]= myVec[i];

        return *this;
    }




    mmVector(const mmVector& myVec ){

        vecCapacity = myVec.vecCapacity;
        vecSize = myVec.vecSize;
        ptr = new T[vecCapacity];
        for(int i =0 ; i< myVec.vecSize;i++)
            ptr[i]= myVec[i];

    }

    bool operator==(const mmVector<T>&myVec)// Return true if ==
    {
        if(this->vecSize != myVec.vecSize)
            return false;
        else
        {
            for(int i =0 ; i< myVec.vecSize;i++)
            {
                if(this->ptr[i]!= myVec[i])
                    return false;
            }
            return true;
        }


    }

    T pop_back()// Remove and return last element in vec
    {
        T popped = this->ptr[vecSize-1];
        vecSize--;
        return popped;
    }

    mmVector (T* arr[] , int  n )    // Initialize by n items from array
    {
       vecCapacity = n;
       vecSize = n;
       ptr = new T[n];
       for (int i = 0 ; i < sizeof(arr)/sizeof(arr[0]);i++ )
       {
           ptr[i] = arr[i];
       }
    }



    /* mmVector &operator=(const mmVector&&)// Move assignment
     {
         delete[] this.ptr ;
         this.vecCapacity = mmVector.vecCapacity;
         this.vecSize = mmVector.vecSize;
         this.ptr = new T[vecCapacity];
         for(int i =0 ; i< mmVector.vecSize;i++)
             this.ptr[i]= mmVector[i];
             return *this;
     }*/


 int resize()         // Relocate to bigger space
    {
        T* temp = new T[2 * vecCapacity];
        // copying old array elements to new array
        for (int i = 0; i < vecCapacity; i++)
            temp[i] = ptr[i];
        // deleting previous array
        delete[] ptr;
        vecCapacity *= 2;
        ptr = temp;
        delete[] temp;

    }




};


int main()
{
    mmVector<int>vec(4);
    cout<<vec.capacity()<<endl;
    cout<<vec.size()<<endl;
    vector<int>vect(4);
    cout<<vect.capacity()<<endl;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(0);


}
