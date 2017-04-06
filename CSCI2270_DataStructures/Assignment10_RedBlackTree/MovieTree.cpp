#include <string>
#include <iostream>
#include "MovieTree.h"
#include <cassert>

using namespace std;

MovieTree::MovieTree() {
	root = NULL;
	nil = new MovieNode(-1, "NIL", -1, -1);
	nil->isRed = false;
}

MovieTree::~MovieTree() {
	if (root != NULL) {
		DeleteAll(root);
	}
	delete nil;
}

void MovieTree::printMovieInventory() {
	if (root != NULL) {
		printMovieInventory(root);
	}
}

int MovieTree::countMovieNodes() {
	return countMovieNodes(root);
}

int MovieTree::countLongestPath() {
	return countLongestPath(root);
}

void MovieTree::deleteMovieNode(std::string title) {
	MovieNode* to_delete = searchMovieTree(root, title);
	if (to_delete != nil) {
		if (to_delete->leftChild != nil && to_delete->rightChild != nil) {
			MovieNode* replacement = treeMinimum(to_delete->rightChild);
			to_delete->title = replacement->title;
			to_delete->quantity = replacement->quantity;
			to_delete->ranking = replacement->ranking;
			to_delete->year = replacement->year;
			to_delete = replacement;
		}
		rbDelete(to_delete);
		assert(verifyTree(root));
		assert(rbValid(root));
	}
}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity) {
	MovieNode* n = new MovieNode(ranking, title, releaseYear, quantity);
	n->leftChild = nil;
	n->rightChild = nil;
	n->isRed = true;
	if (root == NULL) {
		root = n;
		n->isRed = false;
		return;
	}
	else {
		addNode(root, n);
	}
	rbAddFixup(n);
	assert(verifyTree(root));
	if (!rbValid(root)) {
		cout << title << endl;
		cout << root->parent << endl << endl << endl;
		assert(false);
	}
	//printWholeTree(root, "", true);
}

void MovieTree::findMovie(std::string title) {
	MovieNode* n = searchMovieTree(root, title);
	if (n == nil) {
		cout << "Movie not found." << endl;
	}
	else {
		printNodeInfo(n);
	}
}

void MovieTree::rentMovie(std::string title) {
	MovieNode* n = searchMovieTree(root, title);
	if (n == nil) {
		cout << "Movie not found." << endl;
	}
	else {
		cout << "Movie has been rented." << endl;
		n->quantity--;
		printNodeInfo(n);
		if (n->quantity == 0) {
			deleteMovieNode(n->title);
		}
	}
}

void MovieTree::printNodeInfo(MovieNode* n) {
	cout << "Movie Info:" << endl;
	cout << "===========" << endl;
	cout << "Ranking:" << n->ranking << endl;
	cout << "Title:" << n->title << endl;
	cout << "Year:" << n->year << endl;
	cout << "Quantity:" << n->quantity << endl;
}

void MovieTree::addNode(MovieNode* tree, MovieNode* new_node) {
	if (new_node->title < tree->title) {
		if (tree->leftChild == nil) {
			tree->leftChild = new_node;
			new_node->parent = tree;
		}
		else {
			addNode(tree->leftChild, new_node);
		}
	}
	else {
		if (tree->rightChild == nil) {
			tree->rightChild = new_node;
			new_node->parent = tree;
		}
		else {
			addNode(tree->rightChild, new_node);
		}
	}
}

void MovieTree::DeleteAll(MovieNode * node) {
	if (node->leftChild != nil) {
		DeleteAll(node->leftChild);
		node->leftChild = NULL;
	}
	if (node->rightChild != nil) {
		DeleteAll(node->rightChild);
		node->rightChild = NULL;
	}
	cout << "Deleting: " << node->title << endl;
	delete node;
}

int MovieTree::countMovieNodes(MovieNode *node) {
	int count = 0;
	if (node->leftChild != nil) {
		count += countMovieNodes(node->leftChild);
	}
	if (node->rightChild != nil) {
		count += countMovieNodes(node->rightChild);
	}
	return count + 1;
}

MovieNode* MovieTree::searchMovieTree(MovieNode *node, std::string value) {
	if (node == nil) {
		return nil;
	}
	else if (node->title == value) {
		return node;
	}
	else if (value > node->title && node->rightChild != nil) {
		return searchMovieTree(node->rightChild, value);
	}
	else if (value < node->title && node->leftChild != nil) {
		return searchMovieTree(node->leftChild, value);
	}
	return nil;
}

MovieNode* MovieTree::treeMinimum(MovieNode *node) {
	if (node->leftChild != nil) {
		return treeMinimum(node->leftChild);
	}
	return node;
}

bool MovieTree::verifyTree(MovieNode* node) {
	bool result = true;
	if (node->leftChild != nil) {
		result &= verifyTree(node->leftChild);
		result &= node->leftChild->title < node->title;
		if (node->leftChild->parent != node) {
			cout << "parent verification error: " << node->title << " IS NOT PARENT of LC: " << node->leftChild->title 
				<< "(" << node->leftChild->parent->title << ")"<< endl;
			result = false;
		}
	}
	if (node->rightChild != nil) {
		result &= verifyTree(node->rightChild);
		result &= node->rightChild->title > node->title;
		if (node->rightChild->parent != node) {
			cout << "parent verification error: " << node->title << " IS NOT PARENT of RC: " << node->rightChild->title
				<< "(" << node->rightChild->parent->title << ")" << endl;
			result = false;
		}
	}
	return result;
}

void MovieTree::printMovieInventory(MovieNode* node) {
	if (node->leftChild != nil) {
		printMovieInventory(node->leftChild);
	}
	cout << "Movie: " << node->title << " " << node->quantity << endl;
	if (node->rightChild != nil) {
		printMovieInventory(node->rightChild);
	}
}

void MovieTree::rbAddFixup(MovieNode * node) {
	MovieNode* uncle = NULL;
	MovieNode* current_node = node;
	while (1) {
		if (current_node->parent == NULL) {
			current_node->isRed = false;
			return;
		}
		else if (!current_node->parent->isRed) {
			return;
		}
		else if (((uncle = getNodeUncle(current_node)) != NULL) && (uncle->isRed)) {
			current_node->parent->isRed = false;
			uncle->isRed = false;
			current_node = getNodeGrandparent(current_node);
			current_node->isRed = true;
		}
		else {
			break;
		}
	}
	//cout << "finished insert loop" << endl;
	MovieNode* p = current_node->parent;
	MovieNode* g = getNodeGrandparent(current_node);
	MovieNode* n = current_node;
	//left left case
	if (g->leftChild == p && p->leftChild == n) {
		rightRotate(g);
		bool temp = p->isRed;
		p->isRed = g->isRed;
		g->isRed = temp;
	}
	else if (g->leftChild == p && p->rightChild == n) {
		leftRotate(p);
		rightRotate(g);
		bool temp = n->isRed;
		n->isRed = g->isRed;
		g->isRed = temp;
	}
	else if (g->rightChild == p && p->rightChild == n) {
		leftRotate(g);
		bool temp = p->isRed;
		p->isRed = g->isRed;
		g->isRed = temp;
	}
	else {
		rightRotate(p);
		leftRotate(g);
		bool temp = n->isRed;
		n->isRed = g->isRed;
		g->isRed = temp;
	}
}

void MovieTree::leftRotate(MovieNode * x) {
	MovieNode* r = x->rightChild;
	x->rightChild = r->leftChild;
	if (x->rightChild != nil) {
		x->rightChild->parent = x;
	}

	r->parent = x->parent;
	if (x->parent == NULL) {
		root = r;
	}
	else if (x->parent->leftChild == x) {
		x->parent->leftChild = r;
	}
	else {
		x->parent->rightChild = r;
	}
	r->leftChild = x;
	x->parent = r;

	nil->parent = NULL;
	nil->leftChild = NULL;
	nil->rightChild = NULL;
}

void MovieTree::rbDelete(MovieNode* n) {
	if (n->parent) {
		MovieNode** n_ptr = n->parent->leftChild == n ? &n->parent->leftChild : &n->parent->rightChild;
		(*n_ptr) = n->rightChild; //can only be right child because in-order successor is used
	}
	n->rightChild->parent = n->parent;
	if (n->isRed || n->rightChild->isRed) {
		n->rightChild->isRed = false;
	}
	else {
		rbDeleteFixup(n->rightChild);
	}
	delete n;
}

void MovieTree::rightRotate(MovieNode * x) {
	MovieNode* r = x->leftChild;
	x->leftChild = r->rightChild;
	if (x->leftChild != nil) {
		x->leftChild->parent = x;
	}

	r->parent = x->parent;
	if (x->parent == NULL) {
		root = r;
	}
	else if (x->parent->leftChild == x) {
		x->parent->leftChild = r;
	}
	else {
		x->parent->rightChild = r;
	}

	r->rightChild = x;
	x->parent = r;

	nil->parent = NULL;
	nil->leftChild = NULL;
	nil->rightChild = NULL;
}

void MovieTree::rbDeleteFixup(MovieNode* node) { //this function has a lot of side effects...
	MovieNode* parent = node->parent;
	if (parent) {
		MovieNode* s = getNodeSibling(parent, node);
		if (s->isRed) {
			parent->isRed = true;
			s->isRed = false;
			node == parent->leftChild ? leftRotate(parent) : rightRotate(parent);

			parent = node->parent;
			s = getNodeSibling(parent, node);
		}
		if (!parent->isRed &&
				!s->isRed &&
				!s->leftChild->isRed &&
				!s->rightChild->isRed) {
			s->isRed = true;
			rbDeleteFixup(parent);
		}
		else {
			if (parent->isRed && !s->isRed && !s->leftChild->isRed && !s->rightChild->isRed) {
				s->isRed = true;
				node->parent->isRed = false;
			}
			else {
				if ((node == parent->leftChild) && (!s->rightChild->isRed) && (s->leftChild->isRed)) {
					s->isRed = true;
					s->leftChild->isRed = false;

					rightRotate(s);
					parent = node->parent;
					s = getNodeSibling(parent, node);
				}
				else if ((node == parent->rightChild) && (!s->leftChild->isRed)) {
					s->isRed = true;
					s->rightChild->isRed = false;

					leftRotate(s);
					parent = node->parent;
					s = getNodeSibling(parent, node);
				}
				s->isRed = parent->isRed;
				parent->isRed = false;
				if (node == parent->leftChild) {
					s->rightChild->isRed = false;
					leftRotate(parent);
				}
				else {
					s->leftChild->isRed = false;
					rightRotate(parent);
				}
			}
		}
	}
	else {
		root = node;
	}
}

void MovieTree::rbTransplant(MovieNode * u, MovieNode * v) {

}

int MovieTree::rbValid(MovieNode * node) {
	int lh = 0;
	int rh = 0;

	// If we are at a nil node just return 1
	if (node == nil) {
		return 1;
	} else
	{
		// First check for consecutive red links. 
		if (node->isRed)
		{
			if (node->leftChild->isRed || node->rightChild->isRed)
			{
				cout << "This tree contains a red violation" << endl;
				return 0;
			}
		}

		// Check for valid binary search tree. 
		if ((node->leftChild != nil && node->leftChild->title.compare(node->title) > 0) || (node->rightChild != nil && node->rightChild->title.compare(node->title) < 0))
		{
			cout << "This tree contains a binary tree violation" << endl;
			return 0;
		}

		// Deteremine the height of let and right children. 
		lh = rbValid(node->leftChild);
		rh = rbValid(node->rightChild);

		// black height mismatch 
		if (lh != 0 && rh != 0 && lh != rh)
		{
			cout << "This tree contains a black height violation" << endl;
			return 0;
		}

		// If neither height is zero, incrament if it if black. 
		if (lh != 0 && rh != 0)
		{
			if (node->isRed)
				return lh;
			else
				return lh + 1;
		}

		else
			return 0;

	}
}

void MovieTree::printEasy() {
	printWholeTree(root, "", true);
}

int MovieTree::countLongestPath(MovieNode *node) {
	int left = 1;
	int right = 1;
	if (node->rightChild != nil) {
		right += countLongestPath(node->rightChild);
	}
	if (node->leftChild != nil) {
		left += countLongestPath(node->leftChild);
	}
	return left > right ? left : right;
}

MovieNode* MovieTree::getNodeUncle(MovieNode* node) {
	MovieNode* grandparent = getNodeGrandparent(node);
	if (grandparent) {
		return grandparent->leftChild == node->parent ? grandparent->rightChild : grandparent->leftChild;
	}
	cout << "node has no parent and/or grandparent, cannot have uncle" << endl;
	return NULL;
}

MovieNode* MovieTree::getNodeGrandparent(MovieNode* node) {
	if (node->parent) {
		return node->parent->parent;
	}
	return NULL;
}

MovieNode* MovieTree::getNodeSibling(MovieNode* parent, MovieNode* node) {
	return parent->leftChild == node ? parent->rightChild : parent->leftChild;
}

void MovieTree::printWholeTree(MovieNode* n, string indent, bool last) {
	cout << indent;
	if (last) {
		cout << "\\-";
		indent += " ";
	}
	else {
		cout << "|-";
		indent += "| ";
	}
	if (n->isRed) {
		cout << redify(to_string(n->ranking)) << endl;
	}
	else {
		cout << n->ranking << endl;
	}

	if (n->leftChild != nil) {
		printWholeTree(n->leftChild, indent, n->rightChild == nil);
	}
	if (n->rightChild != nil) {
		printWholeTree(n->rightChild, indent, true);
	}
}

string MovieTree::redify(string text) {
	return "\033[1;31m" + text + "\033[0m";
}