#include <iostream>
#include <string>
using namespace std;
class point {
private:
    int x;
    int y;
public:
    void setter(int xcoor, int ycoor)
    {
        x = xcoor;
        y = ycoor;
    }
    int getx() const
    {
        return x;
    }
    int gety() const
    {
        return y;
    }
    void printPoint() const
    {
        cout << "(" << x << ", " << y << ")" << endl;
    }
    point operator+(int z) const
    {
        point result;
        result.x = x + z;
        result.y = y + z;
        return result;
    }
    friend ostream& operator<<(ostream& os, const point& p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    friend istream& operator>>(istream& is, point& p)
    {
        is >> p.x >> p.y;
        return is;
    }
};
class pointarray{
    point** array;
    int rows;
    int columns;
public:
    pointarray() : rows(0), columns(0), array(nullptr) {}
    pointarray(int row, int col)
    {
        rows = row;
        columns = col;
        array = new point*[rows];
        for (int i = 0; i < rows; ++i)
        {
            array[i] = new point[columns];
        }
    }
    pointarray(const pointarray& main)
    {
        rows = main.rows;
        columns = main.columns;
        array = new point*[rows];
        for (int i = 0; i < rows; ++i)
        {
            array[i] = new point[columns];
            for (int j = 0; j < columns; ++j)
            {
                array[i][j] = main.array[i][j];
            }
        }
    }
    int getrows() const
    {
        return rows;
    }
    int getcols() const
    {
        return columns;
    }
    pointarray& operator=(const pointarray& arr){
        if (this == &arr)
        {
            return *this;
        }
        for (int i = 0; i < rows; ++i)
        {
            delete[] array[i];
        }
        delete[] array;
        rows = arr.rows;
        columns = arr.columns;
        array = new point*[rows];
        for (int i = 0; i < rows; ++i)
        {
            array[i] = new point[columns];
            for (int j = 0; j < columns; ++j)
            {
                array[i][j] = arr.array[i][j];
            }
        }
        return *this;
    }
    void setpoint(int row, int col, const point& p)
    {
        if (row >= 0 && row < rows && col >= 0 && col < columns)
        {
            array[row][col] = p;
        }
    }
    pointarray operator+(int value) const
    {
        pointarray result(rows, columns);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                result.array[i][j] = array[i][j] + value;
            }
        }

        return result;
    }

    void swapRows(int r1, int r2)
    {
        if (r1 >= 0 && r1 < rows && r2 >= 0 && r2 < rows && r1 != r2)
        {
            point* temp = array[r1];
            array[r1] = array[r2];
            array[r2] = temp;
        }
    }
    void deleteColumn(int col)
    {
        if (col >= 0 && col < columns)
        {
            for (int i = 0; i < rows; ++i)
            {
                for (int j = col; j < columns - 1; ++j)
                {
                    array[i][j] = array[i][j + 1];
                }
            }
            for (int i = 0; i < rows; ++i)
            {
                point* temp = new point[columns - 1];
                for (int j = 0; j < columns - 1; ++j)
                {
                    temp[j] = array[i][j];
                }
                delete[] array[i];
                array[i] = temp;
            }
            columns -= 1;
        }
    }
    void addColumn(int col, point* newcol)
    {
        if (col >= 0 && col <= columns)
        {
            point** arr2 = new point*[rows];
            for (int i = 0; i < rows; ++i)
            {
                arr2[i] = new point[columns + 1];
            }
            for (int i = 0; i < rows; ++i)
            {
                int currcol = 0;
                for (int j = 0; j <= columns; ++j)
                {
                    if (j == col)
                    {
                        arr2[i][j] = newcol[i];
                    }
                    else
                    {
                        arr2[i][j] = array[i][currcol];
                        currcol++;
                    }
                }
            }
            for (int i = 0; i < rows; ++i)
            {
                delete[] array[i];
            }
            delete[] array;
            array = arr2;
            columns += 1;
        }
    }
    void print() const
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                cout << array[i][j] << " ";
            }
            cout <<endl;
        }
    }
    friend istream& operator>>(istream& is, pointarray& obj)
    {
        for (int i = 0; i < obj.rows; i++)
        {
            for (int j = 0; j < obj.columns; j++)
            {
                int x, y;
                cout << "Enter x position(" << i << "," << j << "): " << endl;
                is >> x;
                cout << "Enter y position(" << i << "," << j << "): " << endl;
                is >> y;
                obj.array[i][j].setter(x,y);
            }
        }
        return is;
    }
    friend ostream& operator<<(ostream& os, const pointarray& obj)
    {
        for (int i = 0; i < obj.rows; i++)
        {
            for (int j = 0; j < obj.columns; j++)
            {
                os << "(" << obj.array[i][j].getx() << ", " << obj.array[i][j].gety() << ") ";
            }
            os << endl;
        }
        return os;
    }
    pointarray operator+(int value)
    {
        pointarray result(rows, columns);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                int x = array[i][j].getx() + value;
                int y = array[i][j].gety() + value;
                result.array[i][j].setter(x,y);
                x=0;y=0;
            }
        }
        return result;
    }
    ~pointarray()
    {
        for (int i = 0; i < rows; ++i)
        {
            delete[] array[i];
        }
        delete[] array;
    }
};
int main()
{
    pointarray myarray;
    int choice, rows, columns;
    pointarray copyarray;

    do {
        cout << "\nMenu:\n"
             << "1. Initialize PointsArray\n"
             << "2. Copy PointsArray\n"
             << "3. Display Number of Rows\n"
             << "4. Display Number of Columns\n"
             << "5. Enter PointsArray Elements\n"
             << "6. Display PointsArray Elements\n"
             << "7. Add Integer to PointsArray\n"
             << "8. Swap Rows\n"
             << "9. Delete Column\n"
             << "10. Add Column\n"
             << "11. Print PointsArray as Matrix\n"
             << "12. Exit\n"
             << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter the number of rows: ";
                cin >> rows;
                cout << "Enter the number of columns: ";
                cin >> columns;
                while (rows <= 0 || columns <= 0)
                {
                    cout<<endl;
                    cout << "Please enter positive number." <<endl;
                    cout << "Enter the number of rows: ";
                    cin >> rows;
                    cout << "Enter the number of columns: ";
                    cin >> columns;
                }
                myarray = pointarray(rows, columns);
                break;
            case 2:
                copyarray = myarray;
                cout << "Copied PointsArray:\n" << copyarray << endl;
                break;
            case 3:
                cout << "Number of rows: " << myarray.getrows() << endl;
                break;
            case 4:
                cout << "Number of columns: " << myarray.getcols() << endl;
                break;
            case 5:
                cin >> myarray;
                break;
            case 6:
                cout << "PointsArray Elements:\n" << myarray << endl;
                break;
            case 7:
            {
                int num;
                cout << "Enter an integer to add to the Array: ";
                cin >> num;
                pointarray added = myarray + num;
                cout << "Result after adding " << num << "\n" << added << endl;
                break;
            }
            case 8:
            {
                int row1, row2;
                cout << "Enter the row indices to swap: ";
                cin >> row1 >> row2;
                myarray.swapRows(row1, row2);
                cout << "PointsArray after swapping rows:\n" << myarray << endl;
                break;
            }
            case 9:
            {
                int deletedcol;
                cout << "Enter the column index to delete: ";
                cin >> deletedcol;
                myarray.deleteColumn(deletedcol);
                cout << "PointsArray after deleting column:\n" << myarray << endl;
                break;
            }
            case 10:
            {
                int newcol;
                cout << "Enter the index for the new column: ";
                cin >> newcol;
                point* newcolumn = new point[myarray.getrows()];

                cout << "Enter values for the new column:" << endl;
                for (int i = 0; i < myarray.getrows(); ++i)
                {
                    cout << "Enter value for row " << i << ":\n";
                    cin >> newcolumn[i];
                }

                myarray.addColumn(newcol, newcolumn);

                cout << "PointsArray after adding column:\n" << myarray << endl;
                break;
            }
            case 11:
               myarray.print();
                break;
            case 12:
                cout << "Thank you for using the program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }

    }
    while (choice != 12);

    return 0;
}