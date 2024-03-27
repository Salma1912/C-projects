#include <bits/stdc++.h>
using namespace std;
//Task #1
class Student{
public:
    string name;
    int student_id;
    float gpa;
    Student(string name, int student_id, float gpa) : name(name), student_id(student_id), gpa(gpa) {}
};
class Node {
public:
    Student student;
    Node* next;

    Node(Student student) : student(student), next(NULL) {}
};
class StudentList{
    Node* head;
public:
    StudentList() : head(NULL) {}

    void insert(Student student)
    {
        Node* new_node = new Node(student);
        if (!head || student.student_id < head->student.student_id) //lw empty aw ID new student greater than ID of the first
        {
            new_node->next = head;
            head = new_node;
        }
        else //ID new student less than ID of the next student , new student  inserted after that student.
        {
            Node* curr = head;
            while (curr->next && student.student_id > curr->next->student.student_id)
            {
                curr = curr->next;
            }
            new_node->next = curr->next;
            curr->next = new_node;
        }
    }
    void remove(int student_id)
    {
        Node* curr = head;
        if (curr && curr->student.student_id == student_id)
        {
            head = curr->next;
            delete curr;
            cout << "Student with ID " << student_id << " has been deleted." << endl;
            return;
        }
        while (curr && curr->next)
        {
            if (curr->next->student.student_id == student_id)
            {
                Node* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
                cout << "Student with ID " << student_id << " has been deleted." << endl;
                return;
            }
            curr = curr->next;
        }
        cout << "Student with ID " << student_id << " not found." << endl;
    }
    void display()
    {
        Node* curr = head;
        while (curr!=NULL)
        {
            cout << "Name: " << curr->student.name << ", ID: " << curr->student.student_id << ", GPA: " << curr->student.gpa << endl;
            curr = curr->next;
        }
    }
    void search(int student_id)
    {
        Node* curr = head;
        while (curr!=NULL)
        {
            if (curr->student.student_id == student_id)
            {
                cout << "student:\n Name: " << curr->student.name <<
                     ", ID: " << curr->student.student_id << ", GPA: " << curr->student.gpa << endl;
                return;
            }
            curr = curr->next;
        }
        cout << "Student with ID " << student_id << " not found." << endl;
    }
    int size()
    {
        int count = 0;
        Node* curr = head;
        while (curr!=NULL)
        {
            count++;
            curr = curr->next;
        }
        return count;
    }
    ~StudentList()
    {
        Node* curr = head;
        while (curr!=NULL)
        {
            Node* temp = curr;
            curr= curr->next;
            delete temp;
        }
    }
};
//task #2
class doubly_linked_list {
    struct Node {
        Node *next;
        Node *prev;
        char item;
    };

    Node *head;
    Node *tail;
    int size;
public:
    doubly_linked_list(){
        head=NULL;
        tail=NULL;
        size=0;

    }
    bool empty(){
        return(head==NULL);
    }
    void insert_at_beginning(char item){
        Node*newnode=new Node;
        newnode->item=item;
        if(empty()){
            newnode->next=NULL;
            newnode->prev=NULL;
            head=tail=newnode;
        }
        else{
            newnode->next=head;
            newnode->prev=NULL;
            head->prev=newnode;
            head=newnode;
        }
        size++;



    }
    void  insert_at_end(char  item){
        Node*newnode=new Node;
        newnode->item=item;
        if(empty()){
            head=tail=newnode;
            newnode->next=NULL;
            newnode->prev=NULL;
        }
        else{
            newnode->next=NULL;
            newnode->prev=tail;
            tail->next=newnode;
            tail=newnode;
        }
        size++;
    }
    void insert_at(int position,char item){
        if(position<0 ||position>size){
            cout<<"can't insert out of range"<<endl;
        }
        else{
            Node*newnode=new Node;
            newnode->item=item;
            if(position==0){
                insert_at_beginning(item);
            }
            else if (position==size){
                insert_at_end(item);
            }
            else{
                Node*curr=head;
                for(int i=1;i<position;i++){
                    curr=curr->next;
                }
                newnode->next=curr->next;
                newnode->prev=curr;
                curr->next->prev=newnode;
                curr->next=newnode;
                size++;
            }

        }
    }
    void delete_first(){
        if (size == 0)
            cout << "list is already empty" << endl;
        else if (size == 1){
            delete head;
            head = tail = NULL;
        }
        else{
            Node* curr = head;
            head = head->next;
            head->prev = NULL;
            delete curr;
        }
        size--;
    }
    void delete_last(){
        if (size == 0)
            cout << "list is already empty" << endl;
        else if (size == 1){
            delete tail;
            tail = head = NULL;
            size--;
        }
        else{
            Node *curr = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete curr;
            size--;
        }
    }
    void delete_char(int position){
        if (position < 0 || position >= size) {
            cout << "index is out of range" << endl;
            return;
        }
        else if (position == 0)
            delete_first();

        else if (position == size - 1)
            delete_last();

        else {
            Node *curr = head->next;
            for (int i = 1; i <position; i++)
            {
                curr = curr->next;
            }
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            size--;
        }
    }
    void concatenation(doubly_linked_list &obj){
        if(obj.empty()){// al list aly ba3mlha concat fadya fa hasyb al list al 2ola zy ma hya
            return;
        }
        if(empty()){//current list fadya
            head=obj.head;//al head ya4awr 3la al head bta3 al list al tanya
            tail=obj.tail;//same ll tail
        }
        else{
            tail->next=obj.head;//al tail bta3 list 1 yab2a al head bta3 list2
            obj.head->prev=tail;// al prev bta3 al head fy al list2 hwa tail al list1
            tail=obj.tail;//al tail hwa al tail bta3 list 2
        }
        size+=obj.size;
        cout << "Size after concatenation: " << size << endl;
    }
    string substring_extraction(int index,int len){
        string sub="";
        Node*curr=head;
        int counter=0;
        while(curr!=NULL&&counter<index){//loop l7d al index ,btbd2 mn al b3d al start??
            curr=curr->next;
            counter++;
        }
        while(curr!=NULL&&len>0){//check length w ya7ood al char fy al substring
            sub+=curr->item;
            curr=curr->next;
            len--;
        }
        return sub;
    }

    int search(string sub) {
        if (size == 0) {
            cout << "list is empty" << endl;
        }
        Node *curr = head;
        int index = 0;
        while(curr!=NULL) {
            bool found = true;
            Node *temp=curr;
            for(int j=0;j<sub.size();j++){
                if(sub[j] != temp->item ) {
                    found = false;
                    break;
                }
                temp=temp->next;
            }
            if(found){
                break;
            }
            index++;
            curr = curr->next;
        }
        if (index<size) {
            return index;
        }
        return -1;
    }

    void replacement(string sub,string new_sub){
        int sub_pos = search(sub);
        if (sub_pos == -1) {
            cout << "substring doesn't exist";
            return;
        }
        while(true) {
            sub_pos = search(sub);
            if (sub_pos == -1) {
                return;
            }
            for (int i = 0; i < sub.size(); i++) {
                delete_char(sub_pos);
            }
            for (int i = sub_pos, j = 0; i < (sub_pos + new_sub.size()); i++) {
                insert_at(i, new_sub[j]);
                j++;
            }
        }
    }

    void reverse(){
        if (empty()){
            cout<<"empty list"<<endl;
        }
        else{
            Node*temp=tail;
            while(temp!=NULL){
                cout<<temp->item;
                temp=temp->prev;
            }
        }
    }
    void display(){
        if(empty()){
            cout<<"list is empty"<<endl;
        }
        else{
            Node*temp=head;
            while(temp!=NULL){
                cout<<temp->item<<"";
                temp=temp->next;
            }
        }
        cout<<endl;
    }

};
int main() {
    while (true) {
        int task_choice;
        cout << "1.Task1" << endl << "2.Task2" << endl <<"3.Exist"<<endl<< "Enter choice" << endl;
        cin >> task_choice;
        switch (task_choice) {
            case 1: {
                StudentList list;
                while (true) {
                    int choice;
                    cout << "1. Insert student\n2. Display student list\n3. Delete student\n"
                            "4. Search for a student\n5. Print size of the list\n6. Add a new student\n7.Exist\n"
                            "Enter  choice: ";
                    cin >> choice;
                    switch (choice) {
                        case 1: {
                            int num_students;
                            cout << "Enter the number of students to insert: ";
                            cin >> num_students;

                            for (int i = 0; i < num_students; ++i) {
                                string name;
                                int student_id;
                                float gpa;

                                cout << "\nStudent " << i + 1 << ":" << endl;
                                cout << "Enter student name: ";
                                cin.ignore();
                                getline(cin, name);

                                cout << "Enter student ID: ";
                                cin >> student_id;

                                cout << "Enter student GPA: ";
                                cin >> gpa;

                                Student student(name, student_id, gpa);
                                list.insert(student);
                            }
                            break;
                        }
                        case 2: {
                            cout << "Student list:" << endl;
                            list.display();
                            break;
                        }
                        case 3: {
                            int student_id;
                            cout << "Enter student ID to delete: ";
                            cin >> student_id;
                            list.remove(student_id);
                            break;
                        }
                        case 4: {
                            int student_id;
                            cout << "Enter student ID to search: ";
                            cin >> student_id;
                            list.search(student_id);
                            break;
                        }
                        case 5: {
                            cout << "Size of the list: " << list.size() << endl;
                            break;
                        }
                        case 6: {
                            string name;
                            int student_id;
                            float gpa;

                            cout << "Enter student name: ";
                            cin.ignore();
                            getline(cin, name);

                            cout << "Enter student ID: ";
                            cin >> student_id;

                            cout << "Enter student GPA: ";
                            cin >> gpa;

                            Student student(name, student_id, gpa);
                            list.insert(student);
                            break;
                        }
                        case 7:{
                            cout << "Exisiting Task 1." << endl;
                            break;
                        }
                        default:
                            cout << "Invalid choice. Please enter a valid option." << endl;
                    }
                    if(choice==7){
                        break;
                    }
                }
                break;
            }
            case 2:{
                string first;
                string second;
                cout<<"Enter string to add to list 1 "<<endl;
                cin>>first;
                cout<<"Enter string to add to list 2"<<endl;
                cin>>second;
                doubly_linked_list list1,list2;
                for(char c:first){
                    list1.insert_at_end(c);
                }
                for(char c:second){
                    list2.insert_at_end(c);
                }
                int index;
                char c;
                list1.concatenation(list2);
                cout<<"Using concatenation function"<<endl;
                list1.display();
                //list2.display();

                //deletion
                cout<<"choose a character by index to remove: ";
                cin>>index;
                cout<<"list after removal: ";
                list1.delete_char(index);
                list1.display();

                //search
                string substring;
                cout<<"search for a string in the list: ";
                cin>>substring;
                int value=list1.search(substring);
                if(value>=0){
                    cout << "found at index: ";
                    cout<<list1.search(substring)<<endl;
                }
                else{
                    cout << "substring doesn't exist"<<endl;
                }

                //replacement
                cout<<"enter two substrings to replace one with another: ";
                string string1,string2;
                cin>>string1>>string2;
                list1.replacement(string1,string2);
                cout<<endl;
                cout<<"list after replacement: ";
                list1.display();

                int length;
                cout<<"Enter the index and the value to insert"<<endl;
                cin>>index>>c;
                list1.insert_at(index,c);
                list1.display();

                cout<<"Enter index and length to find substring "<<endl;
                cin>>index>>length;
                cout<<"Sub string is "<<list1.substring_extraction(index,length)<<endl;
                cout <<"Reversed list: ";
                list1.reverse();
                break;
            }
            case 3:{
                cout << "Exisiting the program." << endl;
                return 0;
            }
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }

    }
}