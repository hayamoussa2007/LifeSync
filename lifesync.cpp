#include<iostream>
#include <string>
using namespace std;
#define TABLE_SIZE 10

class TaskNode{
        
    public:
        string taskTitle;
        string category;
        int priority;
        TaskNode *next;
        TaskNode(){
            taskTitle="None";
            category="none";
            priority=0;
            next=NULL;
        }
        TaskNode(string title, string cat, int p){
            taskTitle=title;
            category=cat;
            priority=p;
            next=NULL;
        }
        
};

class TaskLinkedList{
    private:
        TaskNode* head;
    public:
        TaskLinkedList(){
            head=NULL;
        }
        void addTask(string title, string category, int priority){
            TaskNode *p= new TaskNode(title, category, priority);
            if(head==NULL || priority<head->priority){ //handles if the list is empty or if the priority entered is less than the head's priority
                p->next=head;
                head=p;
                return;
            }
            TaskNode *curr=head;
            while(curr->next!=NULL && curr->next->priority <= priority){ //inserts in the middle/ at end
                curr=curr->next;
            }
            p->next=curr->next; //new node points to the node after curr
            curr->next=p;

        }

        void removeTask(string title){
            if(head==NULL){
                cout<<"No task to be removed"<<endl;
                return;
            }
            if(head->taskTitle==title){ //remove head
                TaskNode*tmp=head;
                head=head->next;
                delete tmp;
                cout<<"Task removed"<<endl;
                return;
            }
            TaskNode *curr=head;
            while(curr->next!=NULL && curr->next->taskTitle!=title){
                curr=curr->next;
            }
            if(curr->next==NULL){
                cout<<"Task not found"<<endl;
                return;
            }
            TaskNode*tmp= curr->next;
            curr->next=tmp->next;
            delete tmp;
            cout<<"Task removed"<<endl;
        }

        void searchByTitle(string title){
            TaskNode * curr=head;
            bool found=false;
            while(curr){
                if(curr->taskTitle== title){
                    cout<<"Task found"<<endl;
                    cout<<"Title: "<<curr->taskTitle<<endl;
                    cout<<"Category: "<<curr->category<<endl;
                    cout<<"Priority: "<<curr->priority<<endl;
                    found=true;
                    break;
                }
                curr=curr->next;
            }
            if(!found){
                cout<<"Task not found"<<endl;
            }
        }
        void searchByCategory(string category){
            TaskNode*curr=head;
            bool found=false;
            cout<<"Tasks in category "<<category<<": "<<endl;
            while(curr){
                if(curr->category== category){
                    found=true;
                    cout<<"- "<<curr->taskTitle<<"(priority: "<<curr->priority<<")"<<endl;
                }
                curr=curr->next;
            }
            if(!found){
                cout<<"No tasks found in this category"<<endl;
            }
        }
        void display(){
            TaskNode*curr=head;
            if(curr==NULL){
                cout<<"No tasks to display"<<endl;
                return;
            }
            while(curr){
                cout<<"Title: "<<curr->taskTitle<<"(Category: "<<curr->category<<" , priority: "<<curr->priority<<")"<<endl;
                curr=curr->next;
            }
        }
};

void taskMenu(){
    TaskLinkedList t;
    int choice;
    while(true){
        cout<<"Task Management Menu: "<<endl
            <<"1. Add Task"<<endl
            <<"2. Remove Task"<<endl
            <<"3. Search By Title"<<endl
            <<"4.Search By Category"<<endl
            <<"5.Display All Tasks"<<endl
            <<"6.Exit"<<endl
            <<"Enter choice: "<<endl;
        cin>>choice;
        if(choice==6){
            cout<<"GoodBye!"<<endl;
            break;
        }
        string title, category;
        int priority;
        switch(choice){
            case 1:
                cout<<"Enter title: ";
                cin.ignore();
                getline(cin,title);
                cout<<"Enter Category: ";
                getline(cin,category);
                cout<<"Enter priority: ";
                cin>>priority;
                t.addTask(title,category,priority);
                cout<<"Task added"<<endl;
                break;
            case 2:
                cout<<"Enter title of task to remove: ";
                cin.ignore();
                getline(cin,title);
                t.removeTask(title);
                break;
            case 3:
                cout<<"Enter title to search for: ";
                cin.ignore();
                getline(cin,title);
                t.searchByTitle(title);
                break;
            case 4:
                cout<<"Enter category to search for: ";
                cin.ignore();
                getline(cin, category);
                t.searchByCategory(category);
                break;
            case 5:
                t.display();
                break;
            default:
                cout<<"Invalid choice"<<endl;
        }
    }
}

class Event {
public:
    string eventTitle;
    int eventTime;
    string eventDescription;

    Event() {
        eventTitle = "";
        eventTime = 0;
        eventDescription = "";
    }

    Event(string title, int time, string description) {
        eventTitle = title;
        eventTime = time;
        eventDescription = description;
    }
};

const int MAX_HEAP_SIZE = 100;

class EventMinHeap
{
    private:
        Event heap[MAX_HEAP_SIZE];
        int Size;

        int leftChild(int i) { return 2 * i + 1; }
        int rightChild(int i) { return 2 * i + 2; }
        int parent(int i) { return (i - 1) / 2; }

        void minHeapify(Event arr[], int Size, int i)
        {
            int smallest = i;
            int left = leftChild(i);
            int right = rightChild(i);

            if (left < Size && arr[left].eventTime < arr[smallest].eventTime)
                smallest = left;

            if (right < Size && arr[right].eventTime < arr[smallest].eventTime)
                smallest = right;

            if (smallest != i)
            {
                swap(arr[i], arr[smallest]);
                minHeapify(arr, Size, smallest);
            }
        }
        

        void insert(Event arr[], int& Size, Event newEvent)
        {
            if (Size >= MAX_HEAP_SIZE) return;
            
            int i = Size;
            arr[Size] = newEvent;//insert at end
            Size++;
            

            while (i > 0 && arr[parent(i)].eventTime > arr[i].eventTime)//bubble up new element
            {
                swap(arr[i], arr[parent(i)]);
                i = parent(i);
            }
        }

        Event extractMin(Event arr[], int& Size)
        {
            if (Size <= 0) return Event();
            
            Event minEvent = arr[0];  // store root
            arr[0] = arr[Size - 1];   // copy last element in root
            Size--;
            
            if (Size > 0) //restore minheap
            {
                minHeapify(arr, Size, 0);
            }
            
            return minEvent;
        }

        
        void heapSort(Event arr[], int Size) //array sorted from max to min
        {
            //no need to build minheap since insert function inserts as minheap
            for (int i = Size - 1; i > 0; i--)
            {
                swap(arr[0], arr[i]);//move root to end
                minHeapify(arr, i, 0);
            }
        }
        

        
        string formatTime(int time) // helps fix issue of 900 showing as 9:0 but not 9:00
        {
            int hours = time / 100;
            int minutes = time % 100;
            
            string timeStr;
            if (hours < 10) timeStr += "0";
            timeStr += to_string(hours) + ":";//convert int hours to string
            if (minutes < 10) timeStr += "0";
            timeStr += to_string(minutes);//convert int minutes to string
            
            return timeStr;
        }

    public:
        EventMinHeap()
        {
        Size = 0;
        }

        void addEvent(string title, int time, string description)
        {
            int hours = time / 100;
            int minutes = time % 100;
            if (time < 0 || time > 2359 || hours < 0 || hours > 23 || minutes < 0 || minutes > 59) // make sure time entered is valid
            {
                cout << "Invalid time\n";
                return;
            }
            insert(heap, Size, Event(title, time, description));// Use insert function to add event to heap in correct minheap position
            cout << "Event added: " << title << " at " << formatTime(time) << endl;
        }

        void removeEvent()
        {
            if (Size == 0)
            {
                cout << "No events to remove\n";
                return;
            }

            Event removed = extractMin(heap, Size);//use extract min to remove root of minheap which is the earliest event

            cout << "Removed Event: " << removed.eventTitle << " at " << formatTime(removed.eventTime) << endl;
        }


        void getNextEvent() //basically a getmin function to view the root of the minheap
        {
            if (Size == 0)
            {
                cout << "No upcoming events\n";
                return;
            }
            cout << "Next Event:\n";
            cout << "Title: " << heap[0].eventTitle << endl;
            cout << "Time: " << formatTime(heap[0].eventTime) << endl;
            cout << "Description: " << heap[0].eventDescription << endl;
        }

        void displayAllEvents()
        {
            if (Size == 0)
            {
                cout << "no upcoming events.\n";
                return;
            }

            cout << "all events (earliest to latest):\n";
            
            Event sorted[MAX_HEAP_SIZE];
            for (int i = 0; i < Size; i++) // copy original heap to sorted
            {
                sorted[i] = heap[i];
            }
            heapSort(sorted, Size); //sort copied array from max to min
            int indx = 1;
            for (int i = Size-1; i >= 0; i--) //reverse loop on array elements
            {
                cout << indx  << ". " << sorted[i].eventTitle << " at " << formatTime(sorted[i].eventTime)<< " - " << sorted[i].eventDescription << endl;
                indx++;
            }
        }
};

void eventMenu(){
    EventMinHeap calendar;
    int choice;
    while(true){
        cout<<"\nEvent Organizer Menu:\n"
        <<"1. Add Event\n"
        <<"2. Remove Event\n"
        <<"3. View Next Event\n"
        <<"4. Display All Events\n"
        <<"5. Exit\n";
        cin>>choice;
        if(choice==5) break;
        string title, description;
        int time;
        if(choice==1){
            cin.ignore();
            cout<<"Enter event title: ";
            getline(cin,title);
            cout<<"Enter event time (0000-2359 , HHMM): ";
            cin>>time;
            cin.ignore();
            cout<<"Enter event description: ";
            getline(cin,description);
            calendar.addEvent(title,time,description);
        }
        else if(choice==2) calendar.removeEvent();
        else if(choice==3) calendar.getNextEvent();
        else if(choice==4) calendar.displayAllEvents();
    }
}



class StackNode {
public:
    string data;
    StackNode* next;

    StackNode(string val) {
        data = val;
        next = NULL;       // end of stack node
    }
};

class LinkedStack {
private:
    StackNode* topNode;

public:
    LinkedStack() {
        topNode = NULL;    // stack starts empty
    }

    void push(string val) {
        StackNode* node = new StackNode(val);
        node->next = topNode;   // link new node to old top
        topNode = node;         // update top
    }

    void pop() {
        if (topNode == NULL)    // no version to remove
            return;
        StackNode* temp = topNode;
        topNode = topNode->next;
        delete temp;            // free memory
    }

    string top() {
        if (topNode == NULL)    // stack empty
            return "";
        return topNode->data;   // last saved version
    }

    bool empty() {
        return topNode == NULL; // check if stack is empty
    }
};

class MyNote {
private:
    string note;
    LinkedStack history;

public:
    MyNote() {
        note = "";
    }

    MyNote(string initial) {
        note = initial;
    }

    void updateNote(string newText) {
        history.push(note);     // save old version before update
        note = newText;
    }

    void undoNote() {
        if (history.empty())    // no old version exists
            return;
        note = history.top();   // restore last version
        history.pop();          // remove restored version from stack
    }

    string getNote() {
        return note;
    }
};

struct NoteEntry {
    char title[50];
    MyNote note;
    bool isUsed;
};

class NoteSystem {
private:
    NoteEntry table[TABLE_SIZE];

    int hashFunction(char title[]) {
        int sum = 0;
        for (int i = 0; title[i] != '\0'; i++) {
            sum += title[i];    // convert title to number
        }
        return sum % TABLE_SIZE; // map to table index
    }

public:
    NoteSystem() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].isUsed = false; // mark all slots empty
        }
    }

    void addNote(char title[], string content) {
        int index = hashFunction(title);

        while (table[index].isUsed)  // linear probing for collision
            index = (index + 1) % TABLE_SIZE;

        int i = 0;
        while (title[i] != '\0') {
            table[index].title[i] = title[i];
            i++;
        }
        table[index].title[i] = '\0';

        table[index].note = MyNote(content);
        table[index].isUsed = true;
    }

    void updateNote(char title[], string newText) {
        int index = hashFunction(title);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int pos = (index + i) % TABLE_SIZE; // search whole table
            if (table[pos].isUsed &&
                string(table[pos].title) == string(title)) {
                table[pos].note.updateNote(newText);
                return;
            }
        }
    }

    void undoNote(char title[]) {
        int index = hashFunction(title);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int pos = (index + i) % TABLE_SIZE;
            if (table[pos].isUsed &&
                string(table[pos].title) == string(title)) {
                table[pos].note.undoNote();
                return;
            }
        }
    }

    void displayNotes() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].isUsed) {
                cout << "Title: " << table[i].title << endl;
                cout << "Content: " << table[i].note.getNote() << endl;
                cout << "------------------\n";
            }
        }
    }
};
    
void noteMenu(){
    NoteSystem ns;
    int choice;
    char title[50];
    string content;

    do{
        cout<<"\nNote System Menu:\n"
            <<"1. Add Note\n"
            <<"2. Update Note\n"
            <<"3. Undo Last Change\n"
            <<"4. Display All Notes\n"
            <<"5. Exit\n"
            <<"Enter choice: ";

        cin>>choice;
        cin.ignore();   // clear newline

        if(choice==1){
            cout<<"Enter note title: ";
            cin.getline(title,50);
            cout<<"Enter note content: ";
            getline(cin,content);
            ns.addNote(title,content);
        }
        else if(choice==2){
            cout<<"Enter note title to update: ";
            cin.getline(title,50);
            cout<<"Enter new content: ";
            getline(cin,content);
            ns.updateNote(title,content);
        }
        else if(choice==3){
            cout<<"Enter note title to undo: ";
            cin.getline(title,50);
            ns.undoNote(title);
        }
        else if(choice==4){
            ns.displayNotes();
        }

    }
    while(choice!=5);
}


int main(){
    int choice;
    while(true){
        cout<<"\nLifeSync Organizer\n"<<"1. Task Management"<<endl<<"2. Event Organizer"<<endl<<"3. Note System"<<endl<<"4. Exit"<<endl;
        cin>>choice;
        if(choice==1) taskMenu();
        else if(choice==2) eventMenu();
        else if(choice==3) noteMenu();
        else if(choice==4) break;
    }
    return 0;
}
