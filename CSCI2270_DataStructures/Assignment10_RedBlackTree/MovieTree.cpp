#include <string>
#include "MovieTree.h"

using namespace std;

MovieTree::MovieTree() {
	root = NULL;
	nil = NULL; //yeah... idk why this is here
}

MovieTree::~MovieTree() {
	if (root != NULL) {
		DeleteAll(root);
	}
}

void MovieTree::printMovieInventory() {
	if (root != NULL) {
		printMovieInventory(root);
	}
}

int MovieTree::countMovieNodes() {
	return countMovieNodes(root);
}

void MovieTree::deleteMovieNode(std::string title) {
	MovieNode* to_delete = searchMovieTree(root, title);
	if (n->leftChild && n->rightChild) {
		MovieNode* replacement = treeMinimum(n->rightChild);
		n->title = replacement->title;
		n->quantity = replacement->quantity;
		n->ranking = replacement->ranking;
		n->year = replacement->year;
		to_delete = replacement;
	}
	rbDelete(to_delete);
}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity) {
	MovieNode* n = new MovieNode(ranking, title, releaseYear, quantity);
	n->isRed = true;
	if (root == NULL) {
		root = n;
		n->isRed = false;
	}
	else {
		addNode(root, n);
	}
}

void MovieTree::findMovie(std::string title) {
	MovieNode* n = searchMovieTree(root, title);
	if (n == NULL) {
		cout << "Movie not found." << endl;
	}
	else {
		printNodeInfo(n);
	}
}

void MovieTree::rentMovie(std::string title) {
	MovieNode* n = searchMovieTree(root, title);
	if (n == NULL) {
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

void MovieNode::printNodeInfo(MovieNode* n) {
	cout << "Movie Info:" << endl;
	cout << "===========" << endl;
	cout << "Ranking:" << n->ranking << endl;
	cout << "Title:" << n->title << endl;
	cout << "Year:" << n->year << endl;
	cout << "Quantity:" << n->quantity << endl;
}

void MovieTree::addNode(MovieNode* tree, MovieNode* new_node) {
	if (new_node->title < tree->title) {
		if (tree->leftChild == NULL) {
			tree->leftChild = new_node;
			new_node->parent = tree;
		}
		else {
			addNode(tree->leftChild, new_node);
		}
	}
	else {
		if (tree->rightChild == NULL) {
			tree->rightChild = new_node;
			new_node->parent = tree;
		}
		else {
			addNode(tree->rightChild, new_node);
		}
	}
	rbAddFixup(new_node);
}

void MovieTree::DeleteAll(MovieNode * node) {
	if (node->leftChild != NULL) {
		DeleteAll(node->leftChild);
		node->leftChild = NULL;
	}
	if (node->rightChild != NULL) {
		DeleteAll(node->rightChild);
		node->rightChild = NULL;
	}
	cout << "Deleting: " << node->title << endl;
	delete node;
}

int MovieTree::countMovieNodes(MovieNode *node) {
	int count = 0;
	if (node->leftChild != NULL) {
		count += countMovieNodes(node->leftChild, c);
	}
	if (node->rightChild != NULL) {
		count += countMovieNodes(node->rightChild, c);
	}
	return count + 1;
}

MovieNode* MovieTree::searchMovieTree(MovieNode *node, std::string value) {
	if (node == NULL) {
		return NULL;
	}
	else if (node->title == value) {
		return node;
	}
	else if (value > node->title && node->rightChild != NULL) {
		return searchMovieTree(node->rightChild, value);
	}
	else if (value < node->title && node->leftChild != NULL) {
		return searchMovieTree(node->leftChild, value);
	}
	return NULL;
}

MovieNode* MovieTree::treeMinimum(MovieNode *node) {
	if (node->leftChild != NULL) {
		return treeMinimum(node->leftChild);
	}
	return node;
}

void MovieTree::printMovieInventory(MovieNode* node) {
	if (node->leftChild != NULL) {
		printMovieInventory(node->leftChild);
	}
	cout << "Movie: " << node->title << " " << node->quantity << endl;
	if (node->rightChild != NULL) {
		printMovieInventory(node->rightChild);
	}
}

void MovieTree::rbAddFixup(MovieNode * node) {
	MovieNode* uncle = NULL;
	MovieNode* current_node = node;
	while (1) {
		if (!current_node->parent) {
			current_node->isRed = false;
			return;
		}
		else if (!current_node->parent->isRed) {
			return;
		}
		else if ((uncle = getNodeUncle(current_node)) && (uncle->isRed)) {
			current_node->parent->isRed = false;
			uncle->isRed = false;
			current_node = getNodeGrandparent(current_node);
			current_node->isRed = true;
		}
		else {
			break;
		}
	}
	MovieNode* gp = getNodeGrandparent(current_node);

	if ((current_node == current_node->parent->rightChild) && (n->parent == gp->leftChild)) {
		leftRotate(current_node->parent);
		current_node = current_node->leftChild;
	}
	else if ((current_node == current_node->parent->leftChild) && (current_node->parent == gp->rightChild)) {
		rightRotate(current_node->parent);
		current_node = current_node->rightChild;
	}

	gp = getNodeGrandparent(current_node);
	current_node->parent->isRed = false;
	gp->isRed = true;
	if (current_node = current_node->parent->leftChild) {
		rightRotate(gp);
	}
	else {
		leftRotate(gp);
	}
}

void MovieTree::leftRotate(MovieNode * x) {
	MovieNode* new_root = x->rightChild;
	x->rightChild = new_root->leftChild;
	new_root->leftChild = x;

	new_root->parent = x->parent;
	x->rightChild->parent = x;
	new_root->leftChild->parent = new_root;
}

void MovieTree::rbDelete(MovieNode* n) {
	if (!n->leftChild && !n->rightChild) {
		if (n == n->parent->leftChild) {
			n->parent->leftChild = NULL;
		}
	}
	if ((n->leftChild != NULL) != (n->rightChild != NULL)) {
		MovieNode* child = n->leftChild ? n->leftChild : n->rightChild;

	}
}

void MovieTree::rightRotate(MovieNode * x) {
	MovieNode* new_root = x->leftChild;
	x->leftChild = new_root->rightChild;
	new_root->rightChild = x;

	new_root->parent = x->parent;
	x->leftChild->parent = x;
	new_root->rightChild->parent = new_root;
}

void MovieTree::rbDeleteFixup(MovieNode * node);

void MovieTree::rbTransplant(MovieNode * u, MovieNode * v);

int MovieTree::rbValid(MovieNode * node) { //switched "nil" to "null"
	int lh = 0;
	int rh = 0;

	// If we are at a nil node just return 1
	if (node == NULL) {
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
		if ((node->leftChild != NULL && node->leftChild->title.compare(node->title) > 0) || (node->rightChild != NULL && node->rightChild->title.compare(node->title) < 0))
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

int MovieTree::countLongestPath(MovieNode *node);

MovieNode* MovieTree::getNodeUncle(MovieNode* node) {
	if (node->parent) {
		if (node->parent->leftChild == node) {
			return node->parent->rightChild;
		}
		else {
			return node->parent->leftChild;
		}
	}
	return NULL;
}

MovieNode* MovieTree::getNodeGrandparent(MovieNode* node) {
	if (node->parent) {
		return node->parent->parent;
	}
	return NULL;
}