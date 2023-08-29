#include<iostream>
#include<fstream>
#include"RBT.h"
using namespace std;

int menu() {
		cout << "Press 1 to insert values in the tree(one by one\n";
		cout<<"Press 2 for searching a value from the tree\n";
		cout<<"Press 3 for pre - order traversal NLR\n";
		cout<<"Press 4 for in - order traversal LNR\n";
		cout<<"Press 5 for post - order traversal LRN\n";
		cout<<"Press 6 for pre - order traversal 2 NRL\n";
		cout<<"Press 7 for in - order traversal 2 RNL\n";
		cout<<"Press 8 for post - order traversal 2 RLN\n";
		cout<<"Press 9 for displaying parent of a node present in Tree\n";
		cout<<"Press 10 to read integer values from the file “input.txt to create a red - black tree”\n";
		cout<<"Press 11 to destroy the complete tree\n";
		cout<<"Press 12 to Print level wise\n";
		cout<<"Press 13 to EXIT\n";
		int choice = 0;
		cout << "enter choice : "; cin >> choice;
		return choice;
}

void insert(node*& root) {
	system("CLS");
	cout << "-----INSERTION FROM USER-----\n\n";
	int val;
	cout << "enter value\n: ";
	cin >> val;
	root->insert(root, val);
	cout << "INSERTION SUCESSFULL\n";
}
void serch(node*&root){
	system("CLS");
	cout << "-----SERCH VALUE-----\n\n";
	int val;
	cout << "enter value\n: ";
	cin >> val;
	if (root->serch(root, val)) {
		cout << "VALUE FOUND\n";
	}
	else {
		cout << "VALUE NOT FOUND\n";
	}
}

int main()
{
	node* root = NULL;
	int num = 0;
	ifstream fin;
	
	int choice = 0;
	while (choice != 13) {
		choice = menu();
	
		if (choice == 13) break;
		switch (choice) {

		case 1:
			insert(root);
			break;
		case 2:
			serch(root);
			break;
		case 3:
			system("cls");
			root->NLR(root); cout << endl;
			break;
		case 4:
			system("cls");
			root->LNR(root);cout<<endl;
			break;
		case 5:
			system("cls");
			root->LRN(root);cout<<endl;
			break;
		case 6:
			system("cls");
			root->NRL(root);cout<<endl;
			break;
		case 7:
			system("cls");
			root->RNL(root);cout<<endl;
			break;
		case 8:
			system("cls");
			root->RLN(root); cout << endl;
			break;
		case 9:
			system("cls");
			root->print_parent(root);
			break;
		case 10:
			system("cls");
			fin.open("input.txt");
			while (fin >> num) {
				root->insert(root, num);
			}
			cout << "DATA COLLECTED SUCESSFULLY\n";
			fin.close();
			break;
		case 11:
			system("cls");
			root->deleteTree(root);
			cout << "Tree deleted sucessfully\n";
			break;
			break;
		case 12:
			system("cls");
			root->printLevelOrder(root);
			break;

		}
	}
	return 0;
}