#include <iostream>
#include <vector>
#include <fstream>
#include "Node_List.h"

using namespace std;

int main()
{
	/*int arr[6] = { 2,3,3,4,3,6 };
	List list1(arr, 6);
	list1.insert(3, 6);
	list1.printAll();
	cout << list1.remove(3) << endl;
	cout << list1.length() << endl;
	vector<int> ivec = { 9,8,7,6,8,4,7,5 };
	List list2(ivec);
	List list3;
	list2.split(4, list3);
	cout << list2.find(7) << "\t" << list2.find(4) << endl;
	list2.printAll();
	list3.printAll();
	int arr2[4] = { 45, 83, 900, 837 };
	List list4(arr2, 4);
	list3.combine(list4);
	list3.printAll();
	cout << list3.length() << endl;
	cout << list4.length() << endl;
	list4.printAll();*/
	List mylist;
	ifstream infile("List_record.txt", ifstream::in);
	int num;
	while (infile >> num) {
		if (infile.eof()) break;
		mylist.insert(mylist.length(), num);
		num = 0;
	}
	mylist.printAll();
	return 0;
}