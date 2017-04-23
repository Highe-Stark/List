#include <vector>
#include <stdexcept>
template <typename T>
class Node
{
public:
	T value;
	Node<T>* next;
	Node<T>(T v):value(v), next(nullptr){}
	~Node() {}
};

template <typename T>
class List
{
private:
	Node<T>* beg;
	int size;
	//initialize the list with the beginning of another list
	List(Node<T>* n);
	// delete the node in the list
	Node<T>* del(Node<T>* &nod);
public:
	//default constructor
	List<T>():beg(nullptr), size(0) {}
	List<T>(const std::vector<T>& v);
	List<T>(int* array, int array_size);
	Node<T>* end();
	int length() const;
	bool insert(int pos, T value);
	int find(T value);
	int remove(T value);
	bool split(int pos, List<T>& new_list);
	void combine(List<T>& append_list);
	void printAll();
	void sort();
	~List<T>() {
		if (this->beg == nullptr) return;
		Node<T>* sec = beg->next;
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

template <typename T>
bool List<T>::insert(int pos, T value)
{
	//check whether the position is out of range
	if (pos > this->size )return false;
	if (pos == 0) {
		this->beg = new Node<T>(value);
		this->size = 1;
		return true;
	}
	//locate from the first position
	Node<T>* pre = this->beg;
	for(int i=1;i!=pos;++i){
		pre = pre->next;
	}
	//make a copy of original node
	Node<T>* orig = pre->next;
	//cover the original link
	pre->next = new Node<T>(value);
	//repair the link between the new one and previous one
	pre->next->next = orig;
	//size is bigger.
	this->size++;
	return true;
}

template <typename T>
List<T>::List(Node<T>* n)
{
	this->size = 0;
	//copy every node
	Node<T>* new_node = new Node<T>(n->value);
	this->beg = new_node;
	this->size++;
	Node<T>* pre = this->beg;
	while (n->next != nullptr) {
		pre->next = new Node<T>(n->value);
		n = n->next;
		this->size++;
	}
	//the end node
	pre->next = new Node<T>(n->value);
	this->size++;
}

template <typename T>
List<T>::List(const std::vector<T>& v)
{
	this->beg = new Node<T>(v[0]);
	this->size = 1;
	for (; this->size != v.size();){
		this->insert(this->size, v[this->size]);
	}
}

template <typename T>
List<T>::List(int* array, int array_size)
{
	this->beg = new Node<T>(array[0]);
	for (this->size = 1; this->size != array_size;) {
		this->insert(this->size, array[this->size]);
	}
}

template <typename T>
Node<T>* List<T>::end()
{
	//return the final node
	//the final node->next is nullptr
	Node<T>* nod = this->beg;
	for (int i = 1; i != this->size; ++i)nod = nod->next;
	return nod;
}

template <typename T>
int List<T>::length() const
{
	return this->size;
}

template<typename T>
int List<T>::find(T value)
{
	int pos(0);
	Node<T>* n = this->beg;
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

template <typename T>
Node<T>* List<T>::del(Node<T>* &nod)
{
	//find the node
	Node<T>* n = this->beg;
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

template <typename T>
int List<T>::remove(T value)
{
	int num(0);
	int original_size = this->size;
	Node<T>* n = this->beg;
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

template <typename T>
bool List<T>::split(int pos, List<T>& new_list)
{
	//check whether the position is out of range
	if (pos >= this->length())return false;
	Node<T>* nod = this->beg;
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

template <typename T>
void List<T>::combine(List<T>& append_list)
{
	Node<T>* nod = this->end();
	//
	nod->next = append_list.beg;
	this->size += append_list.length();
	//empty append_list
	append_list = List<T>();
}

template <typename T>
void List<T>::printAll()
{
	Node<T>* nod = this->beg;
	for (int i = 0; i != this->size; i++) {
		std::cout << nod->value << " ";
		//try nod++->value
		nod = nod->next;
	}
	std::cout<< std::endl;
}

template <typename T>
void List<T>::sort()
{
	Node<T>* start = this->beg;
	for (Node<T>* nod = start; nod != this->end(); nod = nod->next) {
		for (Node<T>* nn = nod->next; nn != nullptr; nn = nn->next) {
			if (nod->value < nn->value) {
				T tempi = nod->value;
				nod->value = nn->value;
				nn->value = tempi;
			}
		}
	}
}