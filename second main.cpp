
#include <bits/stdc++.h>
using namespace std;

template<typename T>
class mmVector
{
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
        cout<<"vector deleted"<<endl;
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
        cout<<"Copy assignment"<<endl;
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
        cout<<"copy constrcutor"<<endl;
        vecCapacity = myVec.vecCapacity;
        vecSize = myVec.vecSize;
        ptr = new T[vecSize];
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


    bool operator == ( const  mmVector<T>&myVec)// Return true if ==
    {
        if(vecSize != myVec.vecSize)
        {
            // cout<<"1"<<endl;
            return false;
        }

        else
        {
            for(int i = 0 ; i< myVec.vecSize ; i++)
            {
                if(ptr[i] != myVec.ptr[i])
                {
                    // cout<< ptr[i] <<"  "<< myVec.ptr[i]<<endl;
                    //cout<<"2"<<endl;
                    return false;
                }
            }
            // cout<<"3"<<endl;
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
        for (int i = 0 ; i < n ; i++ )
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
            if(  this->ptr[i] < v.ptr[i])
                return true;
            else if( this->ptr[i] > v.ptr[i])
                return false;
        }
        return false;
    }

    int resize()  // Relocate to bigger space
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


    friend ostream& operator<< (ostream& out,  mmVector<T>&v)
    {
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

    //this part is a test for initializing with a size or with another vector(copy constructor) , push back , pop back
    //  capacity , size , << overloading  , [] overloading


    mmVector<int>vec1(4);
    vec1.push_back(1);
    vec1.push_back(3);
    vec1.push_back(0);
    vec1.push_back(8);
    vec1.push_back(7);
    cout<<"vec1 capacity = "<<vec1.capacity()<<endl;
    cout<<"vec1 size = "<<vec1.size()<<endl;
    cout<<vec1;
    cout<<"the popped element = "<< vec1.pop_back()<<endl;
    cout<<"vec1 capacity after pop back = "<<vec1.capacity()<<endl;
    cout<<"vec1 size after pop back  = "<<vec1.size()<<endl;
    mmVector<int>vec2(vec1);
    cout<<vec2;
    cout<<"firts element in vec2 : " << vec2[0] << endl ;


    //--------------------------------------------++--------------------------------------------------

    //this part is a test for empty , resize , initializing with elements from an array

    mmVector<int>vec3;
    cout<<"check if vec3 is empty aka has no elements : "<< vec3.empty()<<endl;
    vec3.resize();
    cout<<"vec3 capacity after resize = "<<vec3.capacity()<<endl;
    cout<<"vec3 size after resize = "<<vec3.size()<<endl;

    vec3.push_back(1);
    vec3.push_back(2);
    cout<<"vec3 capacity after push back = "<<vec3.capacity()<<endl;
    cout<<"vec3 size after push back = "<<vec3.size()<<endl;
    cout<< vec3;

    int arr[4]={1,2,3,4};
    mmVector<int>vec4(arr , 2);
    cout<<"vec4 capacity = "<<vec4.capacity()<<endl;
    cout<<"vec4 size = "<<vec4.size()<<endl;
    cout<<vec4;



    //--------------------------------------------++--------------------------------------------------

    //this part is a test for overloading == , overloading < , deep copy assignment

    mmVector<int>vec5;
    mmVector<int>vec6;
    vec5.push_back(1);
    vec5.push_back(2);
    vec6.push_back(1);
    vec6.push_back(2);
    bool check;
    check = (vec5 == vec6 );
    cout<<"check if the two vectors are equal : "<<check<<endl;
    check = (vec5 < vec6 );
    cout<<"check if vec5 < vec6 : "<< check <<endl;

    mmVector<int>vec7;
    mmVector<int>vec8;
    vec7.push_back(1);
    vec7.push_back(9);

    vec8 = vec7;
    cout<<vec8;

}
