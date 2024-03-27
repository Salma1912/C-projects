#include <iostream>
#include <fstream>
#include <string>
using namespace std;
template <typename T>
class MultiArray {
private:
    T** arrays;
    string* arrayname;
    int* arraysize;
    int numarray;
public:
    MultiArray(int num, const int* size, const string* name)
            : numarray(num), arrays(new T*[num]), arrayname(new string[num]), arraysize(new int[num])
    {
        for (int i = 0; i < num; ++i)
        {
            arrayname[i] = name[i];
            arraysize[i] = size[i];
            arrays[i] = new T[size[i]];
        }
    }
    ~MultiArray()
    {
        for (int i = 0; i < numarray; ++i)
        {
            delete[] arrays[i];
        }
        delete[] arrays;
        delete[] arrayname;
        delete[] arraysize;
    }
    MultiArray(const MultiArray& other)
            : numarray(other.numarray), arrays(new T*[numarray]), arrayname(new string[numarray]), arraysize(new int[numarray])
    {
        for (int i = 0; i < numarray; ++i)
        {
            arrayname[i] = other.arrayname[i];
            arraysize[i] = other.arraysize[i];
            arrays[i] = new T[arraysize[i]];
            for (int j = 0; j < arraysize[i]; ++j)
            {
                arrays[i][j] = other.arrays[i][j];
            }
        }
    }
    int getnumofarrays()
    {
        return numarray;
    }
    int* getSizes()
    {
        return arraysize;
    }
    string* getNames()
    {
        return arrayname;
    }
    T** getElements()
    {
        return arrays;
    }
//    void loadFromFile(const string& arrname, const string& filename)
//    {
//        ifstream file(filename);
//        if (!file.is_open())
//        {
//            cout << "Failed to open file: " << filename << endl;
//            return;
//        }
//
//        for (int i = 0; i < numarray; ++i)
//        {
//            if (arrayname[i] == arrname)
//            {
//                for (int j = 0; j < arraysize[i]; ++j)
//                {
//                    if (!(file >> arrays[i][j]))
//                    {
//                        file.clear();
//                        string dummy;
//                        file >> dummy;
//                        if (!(file >> arrays[i][j]))
//                        {
//                            cout << "Failed to read data from file: " << filename << " for array: " << arrname << endl;
//                            break;
//                        }
//                    }
//                }
//                break;
//            }
//        }
//
//        file.close();
//    }
    void loadFromFile(const string& arrname, const string& filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Failed to open file: " << filename << endl;
            return;
        }

        for (int i = 0; i < numarray; ++i)
        {
            if (arrayname[i] == arrname)
            {
                for (int j = 0; j < arraysize[i]; ++j)
                {
                    if (!(file >> arrays[i][j]))
                    {
                        file.clear();
                        string dummy;
                        file >> dummy;
                        if (!(file >> arrays[i][j]))
                        {
                            cout << "Failed to read data from file: " << filename << " for array: " << arrname << endl;
                            break;
                        }
                    }
                }
                break;
            }
        }

        file.close();  // Close the file after reading the current array
    }

    T* subArray(const string& name, int start, int end, int step = 1)
    {
        for (int i = 0; i < numarray; ++i)
        {
            if (arrayname[i] == name)
            {
                // Ensure a non-negative subsize
                int subsize = max(0, (end - start) / step + 1);

                T* subdata = new T[subsize];

                if (start <= end)
                {
                    for (int j = start, k = 0; j <= end; j += step, k++)
                    {
                        subdata[k] = arrays[i][j];
                    }
                }
                else
                {
                    for (int j = start, k = 0; j >= end; j -= step, k++)
                    {
                        subdata[k] = arrays[i][j];
                    }
                }

                return subdata;
            }
        }
        return nullptr;
    }

    void reverse(const string& name)
    {
        for (int i = 0; i < numarray; ++i)
        {
            if (arrayname[i] == name)
            {
                int start = 0;
                int end = arraysize[i] - 1;
                while (start < end) {
                    T temp = arrays[i][start];
                    arrays[i][start] = arrays[i][end];
                    arrays[i][end] = temp;
                    ++start;
                    --end;
                }
                break;
            }
        }
    }
    void sort(const string& name)
    {
        for (int i = 0; i < numarray; ++i)
        {
            if (arrayname[i] == name)
            {
                for (int j = 0; j < arraysize[i] - 1; ++j)
                {
                    for (int k = 0; k < arraysize[i] - 1 - j; ++k)
                    {
                        if (arrays[i][k] > arrays[i][k + 1])
                        {
                            T temp = arrays[i][k];
                            arrays[i][k] = arrays[i][k + 1];
                            arrays[i][k + 1] = temp;
                        }
                    }
                }
                break;
            }
        }
    }
    bool search(T item)
    {
        for (int i = 0; i < numarray; ++i)
        {
            for (int j = 0; j < arraysize[i]; ++j)
            {
                if (arrays[i][j] == item)
                {
                    return true;
                }
            }
        }
        return false;
    }
    T& operator()(const string& name, int index)
    {
        for (int i = 0; i < numarray; ++i)
        {
            if (arrayname[i] == name)
            {
                if (index >= 0 && index < arraysize[i])
                {
                    return arrays[i][index];
                }
                else if (index < 0 && -index <= arraysize[i])
                {
                    return arrays[i][arraysize[i] + index];
                }
                else
                {
                    throw out_of_range("Invalid index");
                }
            }
        }
        throw invalid_argument("Array not found");
    }
    MultiArray split(const string& name)
    {
        for (int i = 0; i < numarray; ++i)
        {
            if (arrayname[i] == name)
            {
                int originalsize = arraysize[i];
                int halfsize = originalsize / 2;
                MultiArray splitarr(2, new int[2]{halfsize, originalsize - halfsize}, new string[2]{"first", "second"});

                splitarr.arrays[0] = new T[halfsize];
                for (int j = 0; j < halfsize; ++j)
                {
                    splitarr.arrays[0][j] = arrays[i][j];
                }
                splitarr.arrays[1] = new T[originalsize - halfsize];
                for (int j = halfsize, k = 0; j < originalsize; ++j, ++k)
                {
                    splitarr.arrays[1][k] = arrays[i][j];
                }
                cout << "Elements in first: ";
                for (int k = 0; k < halfsize; k++)
                {
                    cout << splitarr.arrays[0][k] << " ";
                }
                cout << endl;

                cout << "Elements in second: ";
                for (int k = 0; k < originalsize - halfsize; k++)
                {
                    cout << splitarr.arrays[1][k] << " ";
                }

                return splitarr;
            }
        }
        throw invalid_argument("Array not found");
    }
    T* merge()
    {
        int totalsize = 0;
        for (int i = 0; i < numarray; ++i)
        {
            totalsize += arraysize[i];
        }

        T* mergarr = new T[totalsize];
        int currindex = 0;

        for (int i = 0; i < numarray; ++i)
        {
            for (int j = 0; j < arraysize[i]; ++j)
            {
                mergarr[currindex] = arrays[i][j];
                currindex++;
            }
        }
        cout << "Merged Array: ";
        for (int i = 0; i < totalsize; ++i)
        {
            cout << mergarr[i] << " ";
        }
        cout << endl;

        return mergarr;
    }

    void applyToArray(const string& name, void (*fn)(T&))
    {
        for (int i = 0; i < numarray; ++i)
        {
            if (arrayname[i] == name)
            {
                for (int j = 0; j < arraysize[i]; ++j)
                {
                    fn(arrays[i][j]);
                }
                return;
            }
        }
        throw invalid_argument("Array not found");
    }
    friend ostream& operator<<(ostream& os, const MultiArray& arr)
    {
        for (int i = 0; i < arr.numarray; ++i)
        {
            os << arr.arrayname[i] << ": ";
            for (int j = 0; j < arr.arraysize[i]; ++j)
            {
                os << arr.arrays[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }
};
template <typename T2>
void square(T2& x)
{
    x *= x;
}
int main()
{
    int * size = new int[2];
    size[0] = 4;
    size[1] = 4;
    string *names = new string[2];
    names[0] = "number";
    names[1] = "grade";
    cout<<"the Array :\n";
    MultiArray<int> myArray(2, size, names);
    myArray.loadFromFile("number", "file.txt");
    myArray.loadFromFile("grade","file.txt");
    for (int i = 0; i < myArray.getnumofarrays(); i++)
    {
        cout << myArray.getNames()[i] << ": ";
        for (int j = 0; j < myArray.getSizes()[i]; j++)
        {
            cout << myArray.getElements()[i][j] << " ";
        }
        cout << endl;
    }

    cout<<"SubArray : ";
    int * array =myArray.subArray("number",0,2,1);
    for (int i = 0; i < 3; ++i)
    {
        cout<<array[i];
        cout<<" ";
    }
    cout<<endl;

    cout<<"Searched value :";
    if (myArray.search(20))
    {
        cout<<"true\n";
    }
    else
    {
        cout<<"false\n";
    }

    cout<<"Sorted Array: ";
    myArray.sort("number");
    for (int i = 0; i < myArray.getSizes()[0]; i++)
    {
        cout << myArray.getElements()[0][i] << " ";
    }cout << endl;

    cout<<"Splitting Array :\n";
    myArray.split("number");
    cout << endl;

    cout<<"Reversed Array: ";
    myArray.reverse("number");
    for (int i = 0; i < myArray.getSizes()[0]; i++)
    {
        cout << myArray.getElements()[0][i] << " ";
    }cout << endl;

    myArray.merge();

    cout<<"The value in index is: ";
    cout<<myArray("number",1)<<endl;


    cout<<"The value in index is: ";
    cout<<myArray("number",-2)<<endl;


    cout<<"Squared Array: ";
    myArray.applyToArray("number",square);
    for (int i = 0; i < myArray.getSizes()[0]; i++)
    {
        cout << myArray.getElements()[0][i] << " ";
    }
    cout<<endl;

    return 0;
}