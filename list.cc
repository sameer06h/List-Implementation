#include <iostream>

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
};

int main()
{ 
	List<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	list.push_back(40);
	list.print_list();

	list.pop_back();
	list.pop_back();
	list.pop_back();
	list.pop_back();
	list.print_list();
	cout << "Done!" << endl;
    
}
