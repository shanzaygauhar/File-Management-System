#include <iostream>
#include <list>
#include <iterator>
#include <fstream> 
#include <string>

using namespace std;
class QueueNode
{
	friend ostream& operator << (ostream& out, QueueNode&obj)
	{
		out << " User " << obj.ID << ", ";
		if (obj.operation == 'R')
		{
			cout << "Read\n";
		}
		else if (obj.operation == 'W')
		{
			cout << "Write\n";
		}
		return out;
	}
private:
	int Key;
	int ID;
	char operation;

public:
	QueueNode(int key = 0, int id = 0, char op = '\0')
	{
		Key = key;
		ID = id;
		operation = op;
	}

	char getoperation()
	{
		return operation;
	}
	int getKey()
	{
		return Key;
	}
	int getUserId()
	{
		return ID;
	}
	bool operator >(QueueNode& a)
	{
		if (Key > a.Key)
			return  true;
		return false;
	}
	bool operator <(QueueNode& a)
	{
		if (Key < a.Key)
			return  true;
		return false;
	}
	~QueueNode()
	{

	}
};

template <typename T>
class Queue
{
	friend ostream& operator << (ostream & out, Queue<T> obj)
	{
		for (int i = 0; i < obj.currentsize; i++)
			out << "\t" << obj.data[i];
		return out;
	}
private:
	//T* data;
	int currentsize;
	int maxsize;
	T min;
public:
	T* data;

	Queue(T* dta = nullptr, int cursize = 0, int msize = 0, T m = 0)
	{
		currentsize = cursize;
		maxsize = msize;
		data = new T[msize]; 
		min = m;
	}
	void Reheap_Up(int cnode)
	{
		int parent = (cnode) / 2;  //parent at i/2

		while (cnode > 0)
		{
			if (data[cnode] > data[parent])        //cnode greater than parent swap
				swap(data[cnode], data[parent]);
			cnode = parent;
			parent = (cnode) / 2;
		}
	}
	void Reheap_Down(int cnode)
	{
		while (cnode < currentsize)
		{
			int leftchild = 2 * cnode + 1;
			int rightchild = 2 * cnode + 2;
			int maxchild = leftchild;

			if (leftchild < currentsize && rightchild <= currentsize)
			{
				if (data[leftchild] < data[rightchild])
					maxchild = rightchild;
				if (data[maxchild] > data[cnode])	//maxchld greater than cnode swap
					swap(data[maxchild], data[cnode]);
			}
			cnode = maxchild;
		}
	}
	void BuildQueue(T*& array, int size)
	{
		data = array; 
		currentsize = size;
		for (int i = currentsize / 2 - 1; i >= 0; --i)
		{
			Reheap_Down(i);
		}

		min = Fmin(data, currentsize);

		for (int i = 0; i < size; i++)
		{
			cout << data[i] << endl;
		}
		cout << endl << endl;
		//Takes in an unsorted array and convert in to a priority queue
	}
	T ExtractMax() //Remove and return the maximum element
	{

		T temp = data[0];
		if (currentsize > 0) {
			data[0] = data[currentsize - 1];
			currentsize--;
			Reheap_Down(0);
		}
		return temp;
	}
	T FindMax() // Return the maximum value in O(1) time
	{
		if (data != nullptr)
		{
			return data[0];
		}
	}
	T FindMin()  //Return the minimum value in O(1) time
	{
		if (data != nullptr)
		{
			return min;
		}
	}
	void Insert(T value) // Insert a value with given priority
	{

		if (currentsize <= maxsize && maxsize != 0) {
			data[currentsize] = value;
			currentsize++;
			Reheap_Up(currentsize - 1);
			min = Fmin(data, currentsize - 1);
		}
	}
	T Fmin(T* data, int size)
	{
		if (data != nullptr)
		{
			T min = data[0];
			for (int i = 0; i < size; i++)
			{
				if (min > data[i])
					min = data[i];
			}
			return min;
		}
		return -1;
	}
	void setSize(int m)
	{
		maxsize = m;
	}
	void SetCsize(int m)
	{
		currentsize = m;
	}
	int size()
	{
		return currentsize;
	}
	bool empty()
	{
		if (currentsize == 0)
		{
			return true;
		}


		return false;
	}
	~Queue()
	{
		if (data != nullptr)
		{
			//delete data;
		}
	}
};

template <typename T, typename K>
class Hash
{
private:
	typename list<T>* List;
	int size;
public:
	Hash(int S = 0, list<T>* l = nullptr)
	{
		List = l;
		size = S;
		if (size > 0 && List == nullptr)
		{
			List = new list<T>[size];
		}
	}
	K Hash_Function(K key)
	{
		//return ((11 * key + 23) % 1001) % size; 
		return	((11 * key + 23) % 100003) % size;
	}
	void Insert(K key, T item)
	{
		K index = Hash_Function(key);
		K i = search(key);

		if (i == -1)
		{
			if (size > 0)
			{
				List[index].push_back(item);
			}
		}
	}
	void PrintHashTable() {

		int index = 0;
		while (index < size)
		{
			cout << "H" << index; //this is the index

			for (T element : List[index])
			{
				cout << " --> " << element;
			}
			cout << "\n";
			index++;
		}
	}
	K search(K ID)
	{
		K index = Hash_Function(ID);
		auto i = List[index].begin();
		K j = 0;

		for (; i != List[index].end(); i++, j++)
		{
			if ((*i).getID() == ID)
				return j;
		}
		return -1;
	}
	list<T>* getList()
	{
		return List;
	}
	void Delete(K key)
	{
		K index = Hash_Function(key);

		list<T>::iterator i;

		for (i = List[index].begin(); i != List[index].end(); i++)
		{
			if (*(i) == key)		//element is found
				break;
		}

		if (i != List[index].end())     //means element is found
		{
			if (((*i).getCurrUser().empty()))
			{
				List[index].erase(i);
			}
			else
				cout << "\n\nCURRENTLY IN USE\n\n";
		}
		else
			cout << "\n\nDoesn't Exists\n\n";
	}

};

class file {
	friend ostream& operator << (ostream& out, file a)
	{
		out << "FILE " << a.ID << "...Access Granted to...  ";
		for (int i = 0; i < a.currentUser.size(); i++)
		{
			out << a.currentUser.data[i] << "  ";		//prints currentUser
		}

		cout << "\n\tNext User\t";
		if (!a.WaitingUser.empty())
		{
			cout << a.WaitingUser.data[0];
		}
		
		if (a.WaitingUser.size() != 0)
		{
			cout << "\n\tWaiting" << a.WaitingUser.size() - 1 << " Users\n";
		}
		else{
			cout << "\n\tWaiting" << a.WaitingUser.size() << " Users\n";
		}
		return out;
	}
private:
	int ID;
	Queue<QueueNode> currentUser;
	Queue<QueueNode> WaitingUser;
public:
	file(int id = 0)
	{
		ID = id;
		currentUser.data = new QueueNode[100];
		currentUser.setSize(100);						//initialised at default size
		WaitingUser.data = new QueueNode[100];
		WaitingUser.setSize(100);
	}

	file& operator=(const file& other)
	{
		if (this != &other)
		{
			ID = other.ID;
			currentUser = other.currentUser;
			WaitingUser = other.WaitingUser;
		}
		return *this;
	}

	Queue<QueueNode> getCurrUser()
	{
		return currentUser;
	}
	void removeAccess(int User_id, int file_id)
	{
		for (int i = 0; i < currentUser.size(); i++)
		{
			if (currentUser.data[i].getUserId() == User_id)
			{
				currentUser.data[i] = currentUser.data[currentUser.size()];
				currentUser.SetCsize(currentUser.size() - 1);
				if (currentUser.size() != 0)
					currentUser.Reheap_Down(currentUser.size() - 1);   //after deleteion
			}
		}
		if (!WaitingUser.empty())
		{
			if (currentUser.size() == 0 || currentUser.data[0].getoperation() == 'R')
			{
				QueueNode Wait = WaitingUser.FindMax();
				if (Wait.getoperation() == 'R')			//simultaneous read access
				{
					Wait = WaitingUser.ExtractMax();
					currentUser.Insert(Wait);
				}
				else if (Wait.getoperation() == 'W' && currentUser.size() == 0) //exclusive write
				{
					Wait = WaitingUser.ExtractMax();
					currentUser.Insert(Wait);
				}

				if (currentUser.data[0].getoperation() == 'R' && !WaitingUser.empty()) //if waiting exists and crrent operation is read
				{
					Wait = WaitingUser.FindMax();
					while (Wait.getoperation() == 'R' && !WaitingUser.empty())
					{
						Wait = WaitingUser.ExtractMax();		//extracts this if read and inserts in reader
						currentUser.Insert(Wait);
						Wait = WaitingUser.FindMax();
					}
				}
			}

		}
	}
	void requestAccess(int user_id, int file_id, char oper, int priority)
	{
		QueueNode que(priority, user_id, oper);

		if (currentUser.size() == 0)
			currentUser.Insert(que);

		else if (oper == 'R')
		{
			int s = currentUser.size();
			if (currentUser.data[s-1].getoperation() == 'R') ///simultaneous read
				currentUser.Insert(que);
			else
				WaitingUser.Insert(que);	//if writing
		}
		else if (oper == 'W')	//exclusive write access
		{
			int s = currentUser.size();
			if (currentUser.data[s - 1].getoperation() == 'R')
			{
				WaitingUser.Insert(que); 
			}
			else if (currentUser.data[s-1].getoperation() == 'W')
			{
				WaitingUser.Insert(que);
			}

		}
	}
	void requestAccessLH(int user_id, int file_id, char oper, char priority)
	{
		int K = 0;
		if (priority == 'H')
		{
			if (!WaitingUser.empty())
			{
				QueueNode b = WaitingUser.FindMax();
				int K = b.getKey();
				K = K + 1;		//add 1 since its a max heap
			}
			else
				K = 100;		//random highest number
		}
		else if (priority == 'L')
		{
			if (!WaitingUser.empty())
			{
				QueueNode b = WaitingUser.FindMin();
				int K = b.getKey();
				K = K + 1;		//add 1 since its a max heap
			}
			else
				K = 0;		//random highest number
		}
		
		requestAccess(user_id, file_id, oper, K);


	}

	bool operator ==(const file& obj)
	{
		if (ID == obj.ID)
			return true;
		return false;
	}

	bool operator ==(const int obj)
	{
		if (ID == obj)
			return true;
		return false;
	}

	int getID()
	{
		return ID;
	}
};


void Loadfile(ifstream& in, Hash<file, int>& z)
{
	in.open("file.txt");
	if (!in)
	{
		cout << "Error opening file\n";
	}
	else {
		char temp[100];
		in.getline(temp, 100);

		int i = 0;
		int file_id;
		int User_id;
		int Priority;
		char access;
		char tmp;

		while (!in.eof()) {
			in >> file_id;

			in >> tmp; //,
			in >> User_id;
			in >> tmp; //,
			in >> Priority;
			in >> tmp; //,
			in >> access;

			QueueNode T(Priority, User_id, access);
			Queue<QueueNode> que(0, 0, 100, 0);

			que.Insert(T);

			int index = z.Hash_Function(file_id);

			list<file>::iterator i;

			for (i = z.getList()[index].begin(); i != z.getList()[index].end(); i++)
			{
				if ((*i).getID() == file_id)
					break;
			}

			if (i == z.getList()[index].end())
			{
				file File(file_id);
				File.requestAccess(User_id, file_id, access, Priority);
				z.Insert(file_id, File);
			}
			else {
				(*(i)).requestAccess(User_id, file_id, access, Priority);
				z.Insert(file_id, *i);
			}
		}
	}

}

void menu() {
	cout << "\n------------------------------------------------------\n";
	cout << "Please Take an Option\n";
	cout << "1. Print Hash table with file information\n";
	cout << "2. Load data\n";
	cout << "3. Insert a file\n";
	cout << "4. Delete a file\n";
	cout << "5. Request an access to a file by a user\n";
	cout << "6. Release the file by a user\n";
	cout << "7. To Exit\n";
	cout << "\n------------------------------------------------------\n";
}
int main()
{
	int size;
	cout << "Please enter the Prime maxSize Of HashTable\n";
	cin >> size;
	Hash<file, int> z(size);
	int input;
	menu();
	cin >> input;

	while (input < 7 && input > 0)
	{
		if (input == 1){
			cout << "\n------------------------------------------------------\n";
			z.PrintHashTable();
			cout << "\n------------------------------------------------------\n";
		}
		else if (input == 2)
		{
			ifstream in;
			Loadfile(in, z);
		}
		else if (input == 3)
		{
			int file_id;
			cout << "\nPlease enter the file Id\n";
			cin >> file_id;

			int index = z.Hash_Function(file_id);

			list<file>::iterator i;

			for (i = z.getList()[index].begin(); i != z.getList()[index].end(); i++)
			{
				if ((*i).getID() == file_id)
					break;
			}

			if (i == z.getList()[index].end())
			{
				file File(file_id);
				z.Insert(file_id, File);
			}
			else
				cout << "The File already exists\n";
		}
		else if (input == 4)
		{
			int file_id;

			cout << "\nPlease enter the file Id\n";
			cin >> file_id;
			z.Delete(file_id);
		}
		else if (input == 5)
		{

			//request an access to file
			int user;
			int key;
			string Key;
			char op;
			int file_id;
			int choice;

			cout << "\nPlease enter the file Id\n";
			cin >> file_id;
			cout << "\n User id: ";
			cin >> user;

			cout << "\nKey: \n";
			cout << "Press 1 to input as Low or High\n";
			cout << "Press 2 for integer\n";
			cin >> choice;

			cout << "\nKey: \n";
			if (choice == 2)
				cin >> key;
			else if (choice == 1)
				cin >> Key;

			cout << "\nOperation Type: ";
			cin >> op;


			int index = z.Hash_Function(file_id);

			list<file>::iterator i;

			for (i = z.getList()[index].begin(); i != z.getList()[index].end(); i++)
			{
				if ((*i).getID() == file_id)
					break;
			}

			if (i == z.getList()[index].end())
			{
				cout << "\nFILE DOESNT EXISTS\n";
			}
			else{
				if (choice == 2)
				{
					(*(i)).requestAccess(user, file_id, op, key);
				}
				else{
					(*(i)).requestAccessLH(user, file_id, op, Key[0]);
				}
			}
		}
		if (input == 6)
		{
			int file_id;
			int user;

			cout << "\nPlease enter the file Id\n";
			cin >> file_id;
			cout << "\n User id: ";
			cin >> user;

			int index = z.Hash_Function(file_id);

			list<file>::iterator i;

			for (i = z.getList()[index].begin(); i != z.getList()[index].end(); i++)
			{
				if ((*i).getID() == file_id)
					break;
			}

			if (i == z.getList()[index].end())
			{
				cout << "The file doesnt exists\n";
			}
			else{
				(*(i)).removeAccess(user, file_id);
			}


		}
		menu();
		cin >> input;
	}

}