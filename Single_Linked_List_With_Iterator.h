#pragma once
#include <iostream>
#include<cmath>
using namespace std;

struct Node {
	Node* next;
	int data;
	Node(int info) :data(info), next(nullptr) {};
};

class Iterator {
	private:
		Node* slider;

		bool Digits_Even(int num) {//проверка на чётность всех цифр числа
			if (num % 2 != 0) {
				return false;
			}
			while (num != 0) {
				int digit = abs(num % 10); 
				if (digit % 2 != 0) {
					return false; 
				}
				num /= 10; 
			}
			return true; 
		}

	public:
		
		Iterator(Node* start) : slider(start) {//конструктор для того чтобы итератор начинал свою работу с чётного числа
			while (slider != nullptr && !Digits_Even(slider->data)) {
				slider = slider->next;
			}
		}

		Iterator& operator++() {//перегрузка++ к следующиму чётному числу
			if (slider != nullptr) {
				slider = slider->next;
					if (slider != nullptr && !Digits_Even(slider->data)){
						operator++();
				}
			}
			return *this;
		}

		int operator*() {//перегрузка * к получению data
			return slider->data;
		}
		
		bool operator==(const Iterator& it) {//проверка на равенство двух итераторов
			return slider == it.slider;
		}
		bool operator!=(const Iterator& it) {//проверка на неравенство двух итераторов
			return !(*this == it);
		}
		
};

class Single_Linked_List {
	private:
		Node* head;
	public:
		Single_Linked_List(): head(nullptr) {};

		//добавление узла в конец
		void add(int data) {
			Node* NewNode = new Node(data);
			if (head == nullptr) {
				head = NewNode;
				return;
			}
			Node* slider = head;
			while (slider->next != nullptr) {
				slider = slider->next;
			}
			slider->next = NewNode;
		}
		//вывод списка
		void printList() {
			Node* slider = head;
			while (slider != nullptr) {
				cout << slider->data << " ";
				slider = slider->next;
			}
			cout << "\n";
		}

		~Single_Linked_List() {//деструктор
			Node* slider = head;
			while (slider != nullptr) {
				Node* next = slider->next;
				delete slider;
				slider = next;
			}
			head = nullptr;
		}
		
		Iterator begin() { return Iterator(head); }//начало списка

		Iterator end() { return Iterator(nullptr);}//конец списка
};


