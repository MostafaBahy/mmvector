#include <iostream>
using namespace std;


template <typename mmvector>
class Iteratormm{


public:
    using ValueType = typename mmvector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
    Iteratormm(PointerType ptr){
        m_ptr = ptr;
    }
    Iteratormm& operator++(){
        m_ptr++;
        return *this;
    }
    Iteratormm& operator++(int){
        Iteratormm iter =  *this;
        ++(*this);
        return iter;
    }
    Iteratormm& operator+ (int inc){
        m_ptr + inc;
        return *this;
    }
    ReferenceType operator*(){
        return *m_ptr;
    }

    bool operator == (const Iteratormm& otherItr)const{
        return m_ptr == otherItr.m_ptr;
    }

    bool operator != (const Iteratormm& otherItr)const{

        return !(m_ptr == otherItr.m_ptr);
    }


private:
    PointerType m_ptr;



};


template<typename T>
class mmVector
{
public:
    using ValueType = T;
    using iterator = Iteratormm<mmVector<T>>;
private:

    T *ptr = nullptr;
    int vecSize = 0;
    int vecCapacity = 0;
    void reAlloc(int newCap)
    {
        T* newVec = new T[newCap];

        if(newCap<vecSize)
            vecSize = newCap;

        for(int i = 0 ; i < vecSize ; i++)
            newVec[i] = ptr[i];
        delete [] ptr;
        ptr=newVec;
        vecCapacity=newCap;
    }


public:



    mmVector()//empty constructor
    {
        ptr = new T[1];
        vecCapacity = 1;
        vecSize = 0;
    }

    mmVector (int x)//parametrized constructor
    {
        ptr = new T[x];
        vecCapacity = x;
        vecSize = 0;
    }


    ~mmVector()  //deallocating mmvector
    {
        delete[] ptr;
    }


    iterator begin(){
        return ptr;
    }
    iterator end(){
        return ptr+vecSize;
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


    void push_back(const T& data) //adds data t our vector
    {

        if (vecSize >= vecCapacity)
            reAlloc(2*vecCapacity);


        // Inserting data
        ptr[vecSize] = data;
        vecSize++;
    }



    int capacity() const// Return size of current allocated array
    {
        return vecCapacity;
    }



    T& operator[](int index) //overloads the [] operator
    {
        if (index >= vecSize)
        {
            std::cout << "This index is out of bound";
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
        std::cout<<"Copy assignment"<<std::endl;
        delete[] this->ptr ;
        this->vecCapacity = myVec.vecCapacity;
        this->vecSize = myVec.vecSize;
        this->ptr = new T[vecCapacity];
        // this->reAlloc(myVec.vecCapacity);
        for(int i =0 ; i< myVec.vecSize;i++)
            this->ptr[i]= myVec.ptr[i];

        return *this;
    }


    mmVector(const mmVector& myVec ) //copy constructor
    {
        std:: cout<<"copy constrcutor"<<std::endl;
        vecCapacity = myVec.vecCapacity;
        vecSize = myVec.vecSize;
        ptr = new T[vecCapacity];
        for(int i =0 ; i< myVec.vecSize;i++)
            ptr[i]= myVec.ptr[i];

    }

    mmVector& operator=( mmVector&& other) noexcept// Move assignment
    {
        cout<<"Move assignment"<<endl;
        vecCapacity = other.vecCapacity;
        vecSize = other.vecSize;
        delete[] ptr;
        ptr = other.ptr;
        for(int i =0 ; i< other.vecSize;i++)
            ptr[i]= other.ptr[i];
        other.ptr= nullptr;
        other.vecCapacity=0;
        other.vecSize=0;
        //return *this;


    }


    bool operator==(const mmVector<T>&myVec)// Return true if ==
    {
        if(this->vecSize != myVec.vecSize)
            return false;
        else
        {
            for(int i =0 ; i< myVec.vecSize ; i++)
            {
                if(this->ptr[i] != myVec.ptr[i])
                    return false;
            }
            return true;
        }
    }


    T pop_back()// Remove and return last element in vec
    {
        T popped = this->ptr[vecSize-1];
        if(vecSize>0) {
            vecSize--;
            this->ptr[vecSize-1].~T();
        }
        return popped;
    }

    mmVector (T arr[] , int  n )    // Initialize by n items from array
    {
        vecCapacity = n;
        vecSize = n;
        ptr = new T[n];
        for (int i = 0 ; i < n;i++ )
        {
            ptr[i] = arr[i];
        }
    }
    bool operator< (const mmVector<T>&v) // Compares item by item
    // Return true if first different item in this is < in other
    {
        // bool check = false;
        int sz= min(v.vecSize,this->vecSize);
        for(int i = 0 ; i < sz ; i++ )
        {
            if( this->ptr[i] != v.ptr[i] && this->ptr[i] < v.ptr[i])
                return true;
            else if( this->ptr[i] != v.ptr[i] && this->ptr[i] > v.ptr[i])
                return false;
        }

    }

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


    friend ostream& operator<< (ostream& out, mmVector<T> &v){
        out << "[";
        for (int i = 0; i < v.vecSize; ++i) {
            out << v[i];
            if (i != v.vecSize - 1)
                out << ", ";
        }
        out << "]\n";
        return out;
    }

};




int main()
{


    int arr[5]={1,2,3,4,5};


// test 1
    mmVector<int> varr(arr,5);

    mmVector<int>vec(4);

    cout<<varr;

    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(0);
    vec.push_back(9);
    vec.push_back(0);




// test 2
    mmVector<int>vevec(vec);
    cout<<vevec;


// mostafa have commented this following section to test his code modifications :

/*
    cout<<"vec1 capacity = "<<vec.capacity()<<endl;
    cout<<"vec1 size = "<<vec.size()<<endl;

    for(int i=0 ; i <vec.size();i++)
        cout<<vec[i]<<" ";
    cout<<endl;
    cout<<"the popped element = "<< vec.pop_back()<<endl;
    cout<<"vec1 capacity after pop back = "<<vec.capacity()<<endl;
    cout<<"vec1 size after pop back  = "<<vec.size()<<endl;

    mmVector<int>vec3(vec);
    cout<<"vec3 capacity = "<<vec3.capacity()<<endl;
    cout<<"vec3 size = "<<vec3.size()<<endl;


    vec.clear();
    cout<<"vec1 capacity after clear = "<<vec.capacity()<<endl;
    cout<<"vec1 size after clear  = "<<vec.size()<<endl;


    mmVector<int>vec2;
    cout<<"check if vec2 is empty aka has no elements : "<< vec2.empty()<<endl;
    vec2.resize();
    cout<<"vec2 capacity after resize = "<<vec2.capacity()<<endl;
    cout<<"vec2 size after resize = "<<vec2.size()<<endl;

    vec.push_back(1);
    vec.push_back(3);
    vec2.push_back(7);
    vec2.push_back(3);
    int check = ( vec2 == vec );
    cout<<"check if  vec2 == vec : "<<check<<endl;

    check = ( vec2 < vec );
    cout<<"check if  vec2 < vec  : "<<check<<endl;
    */


// until here


    /*
    vec2=vec;
    cout<<"vec2 capacity after copy assignment = "<<vec2.capacity()<<endl;
    cout<<"vec2 size after copy assignment = "<<vec2.size()<<endl;
    for(int i=0 ; i <vec2.size();i++)
        cout<<vec2[i]<<" ";
    cout<<endl;*/


    //int arr[4]={1,2,3,4};
    //mmVector<int>vec4(arr , 2);


}