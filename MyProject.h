#include <iostream>
#include<string>
#include<list>
#include <cmath>
#include<fstream>
#include<Windows.h>
#include<sys/stat.h>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<conio.h>
#include<stdio.h>
#include<msclr\marshal_cppstd.h>
#include <Mmsystem.h>
#include <mciapi.h>
//#include<string>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")
//#include<queue>

struct listData
{
	char x;
	int freq;
	std::string charBits;
	listData()
	{
		x = NULL;
		freq = NULL;
	}
	void setListData(int f, char c)
	{
		x = c;
		freq = f;
	}
};

struct queueData
{
	int frequency;
	char cstr;
	queueData* left;
	queueData* right;
	queueData* next;

	queueData()
	{
		cstr = NULL;
		frequency = NULL;
		left = right = NULL;
	}
	void setQueueData(int freq, char c, queueData* l = NULL, queueData* r = NULL)
	{
		frequency = freq;
		cstr = c;
		left = l;
		right = r;
	}


};
class Queue
{
private:

	queueData* front;


public:

	Queue()
	{
		front = NULL;


	}

	bool isEmpty()
	{
		if (front == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}

	}


	void enqueue(queueData* obj)
	{
		queueData* new_node = new queueData;
		queueData* temp;
		queueData* ntemp;
		new_node->setQueueData(obj->frequency, obj->cstr, obj->left, obj->right);
		if (front == NULL || new_node->frequency <= front->frequency)
		{
			new_node->next = front;
			front = new_node;
		}
		else
		{
			queueData* rear = front;
			while (rear->next != NULL && rear->next->frequency <= new_node->frequency)
			{
				rear = rear->next;
			}
			new_node->next = rear->next;
			rear->next = new_node;
		}
	}
	queueData retrieveTop()
	{
		if (!isEmpty())
		{
			queueData temp;
			temp.setQueueData(front->frequency, front->cstr, front->left, front->right);
			return temp;
		}

	}


	void dequeue()
	{
		if (isEmpty())
		{
			//cout << "Queue is empty\n";
		}
		else
		{
			queueData* temp;
			temp = front;
			front = front->next;
			delete temp;
			temp = NULL;
		}
	}
	void createTree()
	{
		while (size() != 1)
		{
			queueData* new_node = new queueData;
			queueData templeft = retrieveTop();
			dequeue();
			queueData tempright = retrieveTop();
			dequeue();

			new_node->left = new queueData;
			new_node->right = new queueData;
			new_node->frequency = templeft.frequency + tempright.frequency;
			new_node->cstr = '\0';
			new_node->left->setQueueData(templeft.frequency, templeft.cstr, templeft.left, templeft.right);
			new_node->right->setQueueData(tempright.frequency, tempright.cstr, tempright.left, tempright.right);
			enqueue(new_node);
		}
	}


	int size()
	{
		int count = 0;
		queueData* temp = front;
		while (temp != NULL)
		{
			count++;
			temp = temp->next;
		}
		return count;
	}

	bool isleafNode(queueData* root)
	{
		if (!root->left && !root->right)
		{
			return true;
		}
		return false;
	}
	queueData* getFront()
	{
		return front;
	}

	~Queue()
	{
		for (int x = 1; x <= size(); x++)
		{
			dequeue();
		}
	}
};

class huffmanCode
{
private:
	static const int size = 64;
	std::list<listData> table[size];
	Queue myQueue;
	std::string input;
	std::string binary;
	

public:
	int hashFunction(int key)
	{
		if (key == 46)
		{
			key = size - 1;
			return key;
		}
		else
		{
			return key % size;
		}
	}
	void insert(std::string messageString)
	{
		std::fstream file;
		file.open(messageString, std::ios::in);
		while (!file.eof())
		{
			getline(file, input);
		}
		file.close();
		int top = 0;
		std::list<listData>::iterator it;
		/*cout << "Enter the string : ";
		getline(cin, input);*/
		int key = 0;
		listData obj;
		int count;
		for (int i = 0; i < input.length(); i++)
		{
			key = hashFunction(int(input[i]));
			if (table[key].empty())
			{
				obj.setListData(1, input[i]);
				table[key].push_back(obj);
			}
			else if (!table[key].empty())
			{
				it = table[key].begin();
				count = it->freq;
				count += 1;
				it->freq = count;
			}
		}
		insertIntoQueue();
		generateCodes(myQueue.getFront(), "");
		for (int i = 0; i < input.length(); i++)
		{
			key = hashFunction(int(input[i]));
			it = table[key].begin();
			//cout << input[i] << " : " << it->charBits << "\n";
		}
	}
	void insertIntoQueue()
	{
		std::list<listData>::iterator it;
		for (int i = 0; i < size; i++)
		{
			for (it = table[i].begin(); it != table[i].end(); it++)
			{
				if (!table[i].empty())
				{
					queueData* obj = new queueData;
					obj->setQueueData(it->freq, it->x);
					myQueue.enqueue(obj);
				}
			}
		}
		myQueue.createTree();


	}
	void generateCodes(queueData* root, std::string str)
	{
		if (root->left)
		{
			generateCodes(root->left, str + "0");
		}


		if (root->right) {

			generateCodes(root->right, str + "1");
		}


		if (myQueue.isleafNode(root))
		{
			int key = 0;
			key = hashFunction(int(root->cstr));
			std::list<listData>::iterator it = table[key].begin();
			it->charBits = str;

		}
	}

	void binarycode()
	{
		std::list<listData>::iterator it;
		int i = 0;
		int key = 0;
		std::string s;
		while (i < input.length())
		{
			key = hashFunction(int(input[i]));
			it = table[key].begin();
			s = s + it->charBits;
			i++;
		}
		binary = s;
		std::fstream obj;
		obj.open("encoded.txt", std::ios::out);
		obj << binary;
		obj.close();
		//cout << "binary code is : " << binary << endl;
		encryption();
	}

	void encryption()
	{
		std::string s = "";
		int v = 0;
		int counter = 0;
		int total = 7;
		std::string readstring;
		std::fstream obj;
		obj.open("encoded.txt", std::ios::in);
		getline(obj, readstring);
		obj.close();
		while (counter <= readstring.length())
		{
			if (counter + 7 <= readstring.length())
			{
				for (int i = counter; i < (counter + 7); i++)
				{

					if (readstring[i] == '1')
					{
						v = v + pow(2, total - 1);
					}
					total--;
				}

				char encrypted;
				encrypted = v;
				s = s + encrypted;
			}
			else
			{
				int x = readstring.length() % 7;
				for (int i = counter; i < counter + x; i++)
				{

					if (readstring[i] == '1')
					{
						v = v + pow(2, x - 1);
					}
					x--;
				}

				char encrypted;
				encrypted = v;
				s = s + encrypted;
			}

			counter = counter + 7;
			total = total + 7;
			v = 0;
		}
		obj.open("ecrypted.txt", std::ios::out);
		obj << s;
		obj.close();
		//cout << s;

	}

	void decode(queueData * n)
	{
		std::string readstring;
		std::fstream obj;
		obj.open("encoded.txt", std::ios::in);
		getline(obj, readstring);
		obj.close();
		obj.open("decoded.txt", std::ios::out);
		for (int i = 0; i <= readstring.length(); i++)
		{
			if (n->cstr != NULL)
			{
				obj << n->cstr;
				//cout << n->cstr;
				n = myQueue.getFront();
				i--;
			}
			else
			{
				if (readstring[i] == '0')
				{
					n = n->left;
				}
				else if (readstring[i] == '1')
				{
					n = n->right;
				}
			}
		}
		obj.close();
	}
	void printdecode()
	{
		//cout << endl;
		//cout << "decoding : ";
		decode(myQueue.getFront());
	}
};