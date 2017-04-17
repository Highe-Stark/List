#include <vector>
#include <stdexcept>
class Node
{
public:
	int value;
	Node* next;
	Node(int v):value(v), next(nullptr){}
	~Node() {}
};


class List
{
private:
	Node* beg;
	int size;
	//initialize the list with the beginning of another list
	List(Node* n);
	// delete the node in the list
	Node* del(Node* &nod);
public:
	//default constructor
	List():beg(nullptr), size(0) {}
	List(const std::vector<int>& v);
	List(int* array, int array_size);
	Node* end();
	int length() const;
	bool insert(int pos, int value);
	int find(int value);
	int remove(int value);
	bool split(int pos, List& new_list);
	void combine(List& append_list);
	void printAll();
	~List() {
		if (this->beg == nullptr) return;
		Node* sec = beg->next;
		delete beg;
		while (sec != nullptr) {
			beg = sec;
			sec = beg->next;
			delete beg;
		}
		//the code below shows that deleting beg doesn't delete the node link afterward.

		/*std::cout << sec->next << "\t" << sec->value << std::endl;
		try {
			std::cout << sec->next->next << "\t" << sec->next->value << std::endl;
		}
		catch (runtime_error err) {
			std::cout << "No next" << std::endl;
		}*/
 	}
};

bool List::insert(int pos, int value)
{
	//check whether the position is out of range
	if (pos > this->size )return false;
	if (pos == 0) {
		this->beg = new Node(value);
		this->size = 1;
		return true;
	}
	//locate from the first position
	Node* pre = this->beg;
	for(int i=1;i!=pos;++i){
		pre = pre->next;
	}
	//make a copy of original node
	Node* orig = pre->next;
	//cover the original link
	pre->next = new Node(value);
	//repair the link between the new one and previous one
	pre->next->next = orig;
	//size is bigger.
	this->size++;
	return true;
}

List::List(Node* n)
{
	this->size = 0;
	//copy every node
	Node* new_node = new Node(n->value);
	this->beg = new_node;
	this->size++;
	Node* pre = this->beg;
	while (n->next != nullptr) {
		pre->next = new Node(n->value);
		n = n->next;
		this->size++;
	}
	//the end node
	pre->next = new Node(n->value);
	this->size++;
}

List::List(const std::vector<int>& v)
{
	this->beg = new Node(v[0]);
	this->size = 1;
	for (; this->size != v.size();){
		this->insert(this->size, v[this->size]);
	}
}

List::List(int* array, int array_size)
{
	this->beg = new Node(array[0]);
	for (this->size = 1; this->size != array_size;) {
		this->insert(this->size, array[this->size]);
	}
}

Node* List::end()
{
	Node* nod = this->beg;
	for (int i = 1; i != this->size; ++i)nod = nod->next;
	return nod;
}

int List::length() const
{
	return this->size;
}
	
int List::find(int value)
{
	int pos(0);
	Node* n = this->beg;
	//from the beginning to search the node whose value is value
	while (n != nullptr && n->value != value) {
		n = n->next;
		pos++;
	}
	if (n == nullptr)
		return -1;
	else
		return pos;
}

Node* List::del(Node* &nod)
{
	//find the node
	Node* n = this->beg;
	while (n->next != nod) n = n->next;
	//move the link to the previous node
	n->next = nod->next;
	//delete the node which is to delete
	delete nod;
	//size -1
	this->size--;
	//return the node right after the deleted node
	return n->next;
}

int List::remove(int value)
{
	int num(0);
	int original_size = this->size;
	Node* n = this->beg;
	//find the node
	//the node found is to be deleted
	//not use find()
	for (int i = 0; i != original_size; ++i) {
		//if node's value is the value required
		if (n->value == value) {
			//delete the node
			n = this->del(n);
			//number of node increase
			num++;
		}
		//if not 
		//the next node
		else n = n->next;
	}
	return num;
}

bool List::split(int pos, List& new_list)
{
	//check whether the position is out of range
	if (pos >= this->length())return false;
	Node* nod = this->beg;
	//find the position to divide
	for (int i = 1; i != pos; i++) {
		nod = nod->next;
	}
	//the new list's begin is this->beg->next
	new_list.beg = nod->next;
	// cut off the link between nod and nod->next;
	nod->next = nullptr;
	//the size of new_list and this list
	new_list.size = this->length() - pos;
	this->size = pos;
	return true;
}

void List::combine(List& append_list)
{
	Node* nod = this->end();
	//
	nod->next = append_list.beg;
	this->size += append_list.length();
	//empty append_list
	append_list = List();
}

void List::printAll()
{
	Node* nod = this->beg;
	for (int i = 0; i != this->size; i++) {
		std::cout << nod->value << " ";
		//try nod++->value
		nod = nod->next;
	}
	std::cout<< std::endl;
}