#include "MovieTree.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

void load_movies(MovieTree& tree, char* file_name);

int main(int argc, char** argv) {
	char* file_name = argv[1];
	MovieTree tree;
	load_movies(tree, file_name);
	bool should_quit = false;
	while (!should_quit) {
		cout << "======Main Menu======" << endl;
		cout << "1. Find a movie" << endl;
		cout << "2. Rent a movie" << endl;
		cout << "3. Print the inventory" << endl;
		cout << "4. Delete a movie" << endl;
		cout << "5. Count the movies" << endl;
		cout << "6. Count the longest path" << endl;
		cout << "7. Quit" << endl;

		char input;
		cin >> input;
		cin.ignore(1);
		cin.clear();
		string input_title;
		switch (input)
		{
		default:
			break;
		case '1':
			cout << "Enter title:" << endl;
			getline(cin, input_title);
			tree.findMovie(input_title);
			break;
		case '2':
			cout << "Enter title:" << endl;
			getline(cin, input_title);
			tree.rentMovie(input_title);
			break;
		case '3':
			tree.printMovieInventory();
			break;
		case '4':
			cout << "Enter title:" << endl;
			getline(cin, input_title);
			tree.deleteMovieNode(input_title);
			break;
		case '5':
			cout << "Tree contains: " << tree.countMovieNodes() << " movies." << endl;
			break;
		case '6':
			cout << "Longest Path: " << tree.countLongestPath() << endl;
			break;
		case '7':
			should_quit = true;
			break;
		case '8':
			tree.printEasy();
			break;
		}
	}
	cout << "Goodbye!" << endl;
}

void load_movies(MovieTree& tree, char* file_name) {
	ifstream fs(file_name);

	string line;
	while (getline(fs, line)) {
		stringstream ss(line);
		string rank;
		string title;
		string year;
		string quantity;
		getline(ss, rank, ',');
		getline(ss, title, ',');
		getline(ss, year, ',');
		getline(ss, quantity, ',');

		tree.addMovieNode(stoi(rank), title, stoi(year), stoi(quantity));
	}
}