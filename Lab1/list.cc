#include <iostream>
#include "list.h"
using namespace std;

List::List() {
	first = nullptr;
	
	
}

List::~List() {
	Node *pointer = first;
	while(pointer != nullptr) {
		Node *temp = pointer->next;
		delete pointer;
		pointer = temp;
	}
}

bool List::exists(int d) const {
	Node *temp = first;
	for(int i = 0; i<size(); i++){
		if(temp->value == d){
			return true;
	}
		else{
			temp = temp->next;
		}
	}
	return false;
}

int List::size() const {
	Node *temp;
	int i = 0;
	for(temp = first; temp != nullptr; temp = temp->next){
		i++;
	}
	return i;
}

bool List::empty() const {
	if(first == nullptr){
		return true;
	}
	return false;
}

void List::insertFirst(int d) {
	Node *newNode = new Node(d,first);
	first = newNode;
}

void List::remove(int d, DeleteFlag df) {
	Node *cur = first;
	Node *prev = first;
	
	if(first != nullptr){
		switch(df){
				
			case DeleteFlag::LESS:
				while (cur != nullptr){
					if (cur->value < d){
						prev -> next = prev -> next -> next;
						break;
						
					}
					else if (cur == prev){
						cur = cur->next;
					}
					else{
						prev = prev->next;
						cur = prev->next;
					}
				}
				
				
				break;
				
			case DeleteFlag::EQUAL:
				while (cur != nullptr){
					if (cur->value == d){
						prev -> next = prev -> next -> next;
						break;
						
					}
					else if (cur == prev){
						cur = cur->next;
					}
					else{
						prev = prev->next;
						cur = prev->next;
					}
				}
				
				
				break;
				
			case DeleteFlag::GREATER:
				while (cur != nullptr){
					if (cur->value > d){
						prev -> next = prev -> next -> next;
						break;
						
					}
					else if (cur == prev){
						cur = cur->next;
					}
					else{
						prev = prev->next;
						cur = prev->next;
					}
				}
				
					
				break;
				
		}
	}
}

void List::print() const {
	Node *temp = first;
	for(temp = first; temp != nullptr; temp = temp->next){
		cout<<temp->value<< endl;
	}
	
}

