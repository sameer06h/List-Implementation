#include <iostream>
#include<list>

using namespace std;

template <class T>
struct list_ {
	T info;
	list_* next;
};

/*
TODO: implement push_front(T element)
simple than push_back
*/
template <class T>

class List {
private:
	struct list_<T>* head;
	struct list_<T>* curr_back;

public:
	List() : head(NULL), curr_back(NULL) {}
	void push_back(T data) {
		if (head == NULL) {
			auto t = new(struct list_<T>);
			t->info = data;
			t->next = NULL;
			head = curr_back =t;
			return;
		}
		auto t = new(struct list_<T>);
		if (t == NULL) {
			cout << "Heap out of memory! aborting without completing requested operation" << endl;
			return;
		}
		t->info = data;
		t->next = NULL;
		curr_back->next = t;
		curr_back = t;
	}

	void print_list() {
		auto curr = head;

		if (head == NULL) {
			cout << "I Wish you had something in the list its Empty!" << endl;
		}
		while (curr != NULL) {
			cout << curr->info << endl;
			curr = curr->next;
		}
	}
	T pop_back() {
		if (curr_back == NULL) {
			cout << "List is empty!" << endl;
			return T(NULL);
		}
		auto curr = head;
		auto prev = head;
		while (curr->next != NULL) {
			prev = curr;
			curr = curr->next;
		}
		cout << "Deleting Element: " << curr->info << endl;
		prev->next = NULL;
		if (head == curr_back) {
			// only one element left when pop operation was requested
			head = curr_back = NULL;
			return T(NULL);
		}
		curr_back = prev;
		free(curr);
	}
	T back(void) {
		if (curr_back == NULL) {
			cout << "List is empty!" << endl;
			return T(NULL);
		}
		return curr_back->info;
	}

	T front() {
		if (head == NULL) {
			cout << "List is empty!" << endl;
			return T(NULL);
		}
		return head->info;
	}
	T pop_front() {
		if (head == NULL) {
			cout << "List is empty!" << endl;
			return T(NULL);
		}
        
		auto t = head;
		t = t->next;
		free(head);
		head = t;
		return T(NULL);
	}

    void reverse(void) {
		struct list_<T>* prev = NULL;
		struct list_<T>* curr = NULL;
		struct list_<T>* next = NULL;

		curr = head;
		if (head == NULL) {
			cout << "List is empty nothing to reverse!" << endl;
			return;
		}
		next = curr->next;
		while (curr) {
			curr->next = prev;
			prev = curr;
			curr = next;
			if(next)
			next = next->next;
		}
		head = prev;
		return;
	}

    /*
	 This function reverses the group of k elements in the list
	 assume the k=3 and list contains (head)10->20->30->40->50->60->NULL
	 the resultant list should look like:
	 (head)30->20->10->60->50->40->NULL

	 steps to solution:
	 reverse only k elements and connect it`s head with tail of its previous k reversed elements
	 lets take a small analysis from the above considered list:
	 1. 1st group of 3 list 30->20->10->NULL
	 2. 2nd group of 3 list 60->50->40->NULL
	 3. connect 10->60 which means the list would look like: 
	 30->20->10->60->50->40->NULL

	 How do we achive it?
	 1. put all the elements that needs to be connected i.e 10, 40 in to a seperate list list.push_back(10, 40)
	 2. once size of list reaches 2, i.e sorting 2 k grouped elements is done connect them


	 This also means if the group size i.e k = 1 then list remains the same!
	 why so? reversing 1 group of elements results in the same 1 element! 
	*/
	void reverse(int k) {
		struct list_<T>* prev = NULL;
		struct list_<T>* curr = NULL;
		struct list_<T>* next = NULL;
		
		auto set_head = true;
		list<struct list_<T>*> connect_nodes;
		
		curr = head;
		if (head == NULL) {
			cout << "List is empty nothing to reverse!" << endl;
			return;
		}
		next = curr->next;
		while (curr) {
			auto count = 1;
			prev = NULL;
			connect_nodes.push_back(curr);
			while ((count <= k) && curr) {
				curr->next = prev;
				prev = curr;
				curr = next;
				if (next)
					next = next->next;
				count++;
			}
			if (set_head) {
				head = prev;
				set_head = false;
			}
			if (connect_nodes.size() == 2) {
				auto connect = connect_nodes.front();
				connect->next = prev;
				connect_nodes.pop_front();
			}
		}
		auto connect = connect_nodes.front();
		connect->next = curr;
		connect_nodes.pop_front();
		return;
	}
};

int main()
{ 
	List<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	list.push_back(40);
	list.print_list();

	//list.pop_back();
	//list.pop_back();
	//list.pop_back();
	//list.pop_back();
    list.reverse(3);
	list.print_list();
	cout << "Done!" << endl;
    
}
