#pragma once
#include<iostream>
using namespace std;


class node {

	node* parent;
	node* left;
	node* right;
	int data;
	char color;
	node* lr_rotate(node* a) {
		node* b = a->left;
		node* c = b->right;
		node* t3 = c->left;
		node* t4 = c->right;

		c->parent = a->parent;
		c->left = b;
		b->parent = c;
		if (t3) t3->parent = b;
		b->right = t3;
		a->parent = c;
		c->right = a;
		if (t4) t4->parent = a;
		a->left = t4;
		recolor(a);
		recolor(c);
		return c;
	}
	node* rl_rotate(node* a) {
		node* b = a->right;
		node* c = b->left;
		node* ct1 = c->left;
		node* ct2 = c->right;

		c->parent = a->parent;
		c->right = b;
		b->parent = c;
		c->left = a;
		a->parent = c;
		if (ct1) ct1->parent = a;
		a->right = ct1;
		if (ct2) ct2->parent = b;
		b->left = ct2;
		recolor(a);
		recolor(c);
		return c;
	}
	node* ll_rotate(node* a) {
		node* b = a->left;
		node* t2 = b->right;

		b->parent = a->parent;
		b->right = a;
		a->parent = b;
		if (t2) t2->parent = a;
		a->left = t2;
		recolor(a);
		recolor(b);
		return b;
	}
	node* rr_rotate(node* a) {
		node* b = a->right;
		node* t2 = b->left;

		b->parent = a->parent;
		b->left = a;
		a->parent = b;
		a->right = t2;
		if (t2)t2->parent = a;

		recolor(a);
		recolor(b);
		return b;
	}

public:
	node(int d = 0) {
		data = d;
		parent = NULL;
		left = NULL;
		right = NULL;
		color = 'r';
	}
	void insert(node*& root, int value) {
		node* n = new node(value);
		if (root == NULL) {
			root = n;
			root->color = 'b';
			return;
		}
		else
		{
			node* temp = root;
			node* prev = root;
			while (temp != NULL)
			{
				prev = temp;
				if (temp->data > value)
					temp = temp->left;
				else if (temp->data <= value)
					temp = temp->right;
			}
			temp = n;
			if (value > prev->data) {
				prev->right = temp;
				temp->parent = prev;
			}
			else {
				prev->left = temp;
				temp->parent = prev;
			}

			node* Grandparent = prev->parent;
			node* parent = prev;
			node* Uncle = NULL;

			if (Grandparent != NULL) {
				if (Grandparent->left == NULL || Grandparent->right == NULL) {
					Uncle = NULL;
				}
				else if (Grandparent->left != parent) {
					Uncle = Grandparent->left;
				}
				else {
					Uncle = Grandparent->right;
				}

				balance(root, temp, parent, Uncle, Grandparent);
			}

		}

	}
	void balance(node*& root, node*& curr, node*& parent, node*& uncle, node*& grandparent) {
		if (curr->color == 'r' && parent->color == 'r') {
			if (uncle != NULL && uncle->color == 'r') {
				uncle->color = 'b';
				parent->color = 'b';
				if (grandparent != root) {
					if (grandparent->color == 'b') {
						grandparent->color = 'r';
					}
					else if (grandparent->color == 'r') {
						grandparent->color = 'b';
					}
				}  
				if (grandparent->parent != NULL) {
					if (grandparent->color == 'r' && grandparent->parent->color == 'r') {
						node* C = grandparent;
						node* P = grandparent->parent;
						node* GP = P->parent;
						node* U = NULL;
						if (GP != NULL) {
							if (GP->left == NULL || GP->right == NULL)
							{
								U == NULL;
							}
							else if (GP->left != parent) {
								U = GP->left;
							}
							else {
								U = GP->right;
							}
							balance(root, C, P, U, GP);
						}
					}
				}
			}
			else if (uncle == NULL || uncle->color == 'b') {
				if (grandparent->left == parent && parent->right == curr) //lr
				{
					if (grandparent->parent != NULL) {
						node* boom = grandparent->parent;
						if (grandparent == boom->right)
							boom->right = lr_rotate(grandparent);
						else
							boom->left = lr_rotate(grandparent);
					}
					else {
						root = lr_rotate(grandparent);
					}
				}
				else if (grandparent->right == parent && parent->left == curr)//rl
				{
					if (grandparent->parent != NULL) {
						node* boom = grandparent->parent;
						if (grandparent == boom->right)
							boom->right = rl_rotate(grandparent);
						else
							boom->left = rl_rotate(grandparent);
					}
					else {
						root = rl_rotate(grandparent);
					}

				}
				else if (grandparent->left == parent && parent->left == curr)//ll
				{
					if (grandparent->parent != NULL) {
						node* boom = grandparent->parent;
						if (grandparent == boom->right)
							boom->right = ll_rotate(grandparent);
						else
							boom->left = ll_rotate(grandparent);
					}
					root = ll_rotate(grandparent);


				}
				else if (grandparent->right == parent && parent->right == curr)//rr
				{

					if (grandparent->parent != NULL) {
						node* boom = grandparent->parent;
						if (grandparent == boom->right)
							boom->right = rr_rotate(grandparent);
						else
							boom->left = rr_rotate(grandparent);
					}
					else {
						root = rr_rotate(grandparent);
					}
				}


				//grandparent->parent->right= lr_rotate(grandparent);

			}
		}
	}
	void recolor(node*& root) {
		if (root->color == 'b') {
			root->color = 'r';
		}
		else root->color = 'b';
	}
	void print(node* root) {
		if (root == NULL)
			return;
		print(root->left);
		cout << root->data << "(" << root->color << ")   ";
		print(root->right);
	}
	int calculte_height(node* root) {
		if (root == NULL) {
			return 0;
		}
		return max(calculte_height(root->left), calculte_height(root->right)) + 1;
	}

	void printLevelOrder(node* root)
	{
		int h = calculte_height(root);
		int i;
		for (i = 1; i <= h; i++)
		{
			printGivenLevel(root, i);
			cout << endl;
		}
	}
	void printGivenLevel(node* root, int level)
	{
		if (root == NULL)
			return;
		if (level == 1)
			cout << root->data << "(" << root->color << ")   ";
		else if (level > 1)
		{
			printGivenLevel(root->left, level - 1);
			printGivenLevel(root->right, level - 1);
		}
	}
	void NLR(node* root) {
		if (root == NULL)
			return;
		
		cout << root->data << "(" << root->color << ")   ";
		NLR(root->left);
		NLR(root->right);
	}

	void NRL(node* root) {
		if (root == NULL)
			return;
		
		cout << root->data << "(" << root->color << ")   ";
		NRL(root->right);
		NRL(root->left);
	}

	void LNR(node* root) {
		if (root == NULL)
			return;
		LNR(root->left);
		cout << root->data << "(" << root->color << ")   ";
		LNR(root->right);
		
	}
	void RNL(node* root) {
		if (root == NULL)
			return;
		RNL(root->left);
		cout << root->data << "(" << root->color << ")   ";
		RNL(root->right);

	}
	void LRN(node* root) {
		if (root == NULL)
			return;
		LRN(root->left);
		LRN(root->right);
		cout << root->data << "(" << root->color << ")   ";
	}

	void RLN(node* root) {
		if (root == NULL)
			return;
		RLN(root->right);
		RLN(root->left);
		cout << root->data << "(" << root->color << ")   ";
	}
	void deleteTree(node* &node)
	{
		if (node == NULL) return;
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
	void print_parent(node* root) {
		if (root == NULL)
			return;
		print_parent(root->left);
		cout << "node ::> " << root->data<<"\t";
		if (root->parent == NULL) {
			cout << "NULL\n";
		}
		else 
			cout << "parent ::> " << root->parent->data << "\n";

		print_parent(root->right);
	}
	bool serch(node* root, int number)
	{
		if (root == NULL)
			return false;
		if (number == root->data) {
			return true;
		}
		if (number < root->data) {
			return serch(root->left, number);
		}
		else if (number > root->data) {
			return serch(root->right, number);
		}
	}
};
