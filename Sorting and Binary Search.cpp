#include <bits/stdc++.h>
using namespace std;
void insertion_Linear(int arr[], int s)
{ // 8 5 9 2 6 3  comp=13  shift =10//
    int comparisons = 0;
    int shifts = 0;

    for (int i = 1; i < s; i++)
    {
        int element = arr[i];
        int j = i - 1;
        //shifts+=2;//lw han7sb temp

        while (j >= 0 && arr[j] > element)
        {
            arr[j + 1] = arr[j];
            j--;
            shifts++;
            comparisons++;
        }
        arr[j + 1] = element;
        if (j >= 0)// bra al loop mafee4 shift bs still 3ml comparison
            comparisons++;
    }
    cout << "array sorted with linear search: ";
    for (int i = 0; i < s; i++)
        cout << arr[i] << " ";
    cout << endl;

    cout << "comparisons: " << comparisons << endl;
    cout << "shifts: " << shifts << endl;
}
void insertion_Binary(int arr[], int n)
{
    int comparisons = 0;
    int shifts = 0;

    for (int i = 1; i < n; i++)
    {
        int element = arr[i];
        int l = 0;
        int h = i - 1;
        int position = i;
        while (l <= h)
        {
            int middle = l + (h - l) / 2;
            comparisons++;
            //cout << "Comparing " << arr[middle] << " and " << element << endl;
            //cout<<arr[middle]<<endl;
            // cout<<"low"<<l<<endl;
            //cout<<"high"<<h<<endl;
            if (arr[middle] < element)
            {
                l = middle + 1;
            }
            else
            {
                h = middle - 1;
                position = middle;
            }
        }
        for (int j = i - 1; j >= position ; j--)
        {
            //cout << "Shifting " << arr[j] << " to " << arr[j + 1] << endl;
            arr[j + 1] = arr[j];
            shifts++;
        }

        arr[position] = element;
        //shifts++;// same as temp but not sure
    }
    cout << "Array sorted with binary search: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    cout << "Comparisons: " << comparisons << endl;
    cout << "Shifts: " << shifts << endl;
}
template <class T>
void selectionSort(vector<T> array)
{
    int comparisons=0;
    int moves=0;
    int n=array.size();
    for (int i = 0, j, least; i < n-1; i++)
    {
        for (j = i+1, least = i; j < n; j++)
        {
            comparisons++;
            if (array[j] < array[least])
                least = j;
        }
        swap (array[least], array[i]);
        moves+=3;
    }
    cout<<"Selection sort: "<<endl;
    cout<<"  sorted array: ";
    for(int i=0;i<n;i++)
    {
        cout<<array[i]<<" ";
    }
    cout<<endl;
    cout<<"  comparisons: "<<comparisons<<endl;
    cout<<"  moves: "<<moves<<endl;

}
template <typename T>
void shellsort(vector<T>array)
{
    int comparisons=0;
    int moves=0;
    int n=array.size();
    for(int gap= n / 2; gap > 0; gap /= 2)
        for(int i = gap; i < n; i++)
        {
            T temp = array[i];
            int j = i;
            comparisons++;
            for( ;j >= gap && temp < array[j - gap];j-= gap){
                moves++;
                comparisons++;
                array[j] = array[j - gap];
            }
            moves+=2;
            array[j] = temp;

        }
    cout<<"shell sort: "<<endl;
    cout<<"  sorted array: ";
    for(int i=0;i<n;i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
    cout<<"  comparisons: "<<comparisons<<endl;
    cout<<"  moves: "<<moves<<endl;
}
int comparisons=0;
void merge(vector<int>& arr, int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[middle + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        comparisons++;
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
    }
    while (j < n2)
    {
        arr[k++] = R[j++];
    }

}
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left < right)
    {
        int middle= left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }

}
void printmergesort(const vector<int>& arr) {
    cout<<"merge sort: "<<endl;
    cout<<"  sorted array: ";
    for (int i=0;i<arr.size();i++) {
        cout << arr[i] << " ";
    }
    cout<<endl;
}

vector<vector<int>> load_file(string filename)
{
    vector<vector<int>> arrays;
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cout << "Failed to open the file " << filename << endl;
        return {};
    }

    string line;
    while (getline(inputFile, line))
    {
        int size;
        istringstream f(line);
        f >> size;
        vector<int> array(size);
        for (int i = 0; i < size; i++)
        {
            if (!(f >> array[i]))
            {
                cout << "Invalid input" << endl;
                return {};
            }
        }
        arrays.push_back(array);
    }

    inputFile.close();
    return arrays;
}
int main()
{
    int size;
    cout << "Enter size: "<<endl;
    cin >> size;

    int* arr_linear = new int[size];
    int* arr_binary = new int[size];

    cout << "Enter the elements : ";
    for (int i = 0; i < size; i++)
    {
        cin >> arr_linear[i];
        arr_binary[i] = arr_linear[i];
    }

    insertion_Linear(arr_linear, size);
    insertion_Binary(arr_binary, size);

    delete[] arr_linear;
    delete[] arr_binary;
cout<<"///////////////////////////////////////////////////////////////\n";
    string name="C:/Users/maria/OneDrive/Desktop/code/arrays.txt";
    vector<vector<int>> all_arrays =load_file(name);
    for(vector<int>& array : all_arrays)
    {
        comparisons=0;
        cout<<"original array: ";
        for(int i=0;i<array.size();i++)
        {
            cout<<array[i]<<" ";
        }
        cout<<endl;
        selectionSort(array);
        shellsort(array);
        mergeSort(array, 0, array.size() - 1);
        printmergesort(array);
        cout<<"  comparisons: "<<comparisons<<endl;
    }
    return 0;
}




