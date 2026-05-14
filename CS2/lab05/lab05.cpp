//
// Created by Thomas Glennon on 3/19/26.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Card, deck, and hand class from Prof Johnson starter code for Lab 5
class Card {
	private:
		string rank;
		char suit;

	public:
		Card() {
			// default so we can have an array of Cards
		}

		// no error checking .... yet
		Card(string face_val, char suit) {
			rank = face_val;
			this->suit = suit;
		}

		void setSuit(char s) {
			suit = s;
		}

		void setRank(string r) {
			rank = r;
		}

		string getRank() {
			return rank;
		}

		string getFullRank() {
			if (rank == "1") {
				return "Ace";
			}
			if (rank == "J") {
				return "Jack";
			}
			if (rank == "Q") {
				return "Queen";
			}
			if (rank == "K") {
				return "King";
			}

			return rank;
		}

		char getSuit() {
			return suit;
		}

		string getFullSuit() {
			if (suit == 'C') {
				return "Clubs";
			}
			if (suit == 'D') {
				return "Diamonds";
			}
			if (suit == 'H') {
				return "Hearts";
			}
			if (suit == 'S') {
				return "Spades";
			}
			return "Suit not found";
		}

		int getSuitVal() {
			if (suit == 'C') {
				return 1;
			}
			if (suit == 'D') {
				return 2;
			}
			if (suit == 'H') {
				return 3;
			}
			if (suit == 'S') {
				return 4;
			}
		}

		int getFaceVal() {
			if (rank == "J")
				return 11;
			else if (rank == "Q")
				return 12;
			else if (rank == "K")
				return 13;
			else
				return stoi(rank);
		}


		void displayCard() {
			if (rank == "1") {
				cout << "A of ";
			} else {
				cout << rank << " of ";
			}
			cout << suit << endl;
		}

};

class Deck {
private:
	Card deck[52];
	int num_remaining = 52;

	// data for initialization in the constructor
	char suits[4] = {'C', 'D', 'H', 'S'};
	string ranks[13] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

public:
	Deck() {
		// seed random number generator
		srand(time(0));

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 13; j++) {
				deck[i * 13 + j].setSuit(suits[i]);
				deck[i * 13 + j].setRank(ranks[j]);
			}
		}
	}

	// print whole deck ... mostly for testing and debugging
	// should make a "pretty print" with the Card class' getters
	void printDeck() {
		for (int i = 0; i < num_remaining; i++) {  // since you might print after dealing some cards!
			if (i % 13 == 0)
				cout << endl;
			deck[i].displayCard();

		}
	}

	// shuffle deck
	void shuffleDeck() {

		int pos[num_remaining];        // for the position to swap with the current card
		Card temp = deck[0];

		for (int i = 0; i < num_remaining; i++) {  // generate the random positions
			pos[i] = rand() % num_remaining;
		}

		for (int i = 0; i < num_remaining; i++) {  // swap the card at i with the card at the random position
			temp = deck[i];
			int swap = pos[i];
			deck[i] = deck[swap];
			deck[swap] = temp;
		}

	}

	Card deal() {
		Card dealt_card = deck[num_remaining - 1];
		num_remaining--;
		return dealt_card;
	}
};

// Utilities from merge sort and binary search homework

bool inputCheck (string input) {
	bool result = false;
	string acceptableInputs[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "C", "D", "H", "S"};
	for (int i = 0; i < 17; i++) {
		if (acceptableInputs[i] == input) {
			result = true;
		}
	}
	return result;
}

string inputPromptToString (string message) {
	cout << message << endl;
	string input;
	bool pass = false;
	while (pass == false) {
		cin >> input;
		if (!(inputCheck(input))) {
			cin.clear();
			cin.ignore();
			cout << "Invalid input" << endl;
			cout << message << endl;
		} else {
			pass = true;
		} // else
	} // while
	return input;
}

int binarySearchRank(Card array[], int length, int target) {
	int max = length;
	int min = 0;
	int mid = 0;
	bool found = false;

	while (!found && min <= max) {
		mid = (min + max) / 2;

		if (array[mid].getFaceVal() == target) {
			found = true;
		} else if (array[mid].getFaceVal() < target) {
			min = mid + 1;
		} else {
			max = mid - 1;
		} // else
	} // while
	if (found) {
		return mid;
	} // if found

	return -1;

} // func

int binarySearchSuit(Card array[], int length, int target) {
	int max = length;
	int min = 0;
	int mid = 0;
	bool found = false;

	while (!found && min <= max) {
		mid = (min + max) / 2;

		if (array[mid].getSuitVal() == target) {
			found = true;
		} else if (array[mid].getSuitVal() < target) {
			min = mid + 1;
		} else {
			max = mid - 1;
		} // else
	} // while
	if (found) {
		return mid;
	} // if found

	return -1;

} // func

void rankMerge(Card array[], int low, int high, int mid) {

	int sizeHigh = high - mid;
	int sizeLow = mid - low + 1;

	Card HiArr[sizeHigh], LoArr[sizeLow];

	for (int i = 0; i < sizeHigh; i++) {
		HiArr[i] = array[mid + 1 + i];
	} // for
	for (int i = 0; i < sizeLow; i++) {
		LoArr[i] = array[low + i];
	} // for

	int i =0, j = 0, k = low;
	while (i < sizeLow && j < sizeHigh) {
		if (LoArr[i].getFaceVal() <= HiArr[j].getFaceVal()) {
			array[k] = LoArr[i];
			i++;
		} else {
			array[k] = HiArr[j];
			j++;
		}
		k++;
	} // while

	while (i < sizeLow) {
		array[k] = LoArr[i];
		i++;
		k++;
	}

	while (j < sizeHigh) {
		array[k] = HiArr[j];
		j++;
		k++;
	}
}

void rankMergeSort (Card array[], int low, int high) {

	if (low < high) {
		for (int i = low; i <= high; i++) {
		}

		int mid = (high - low) / 2 + low;

		rankMergeSort(array, low, mid);
		rankMergeSort(array, mid + 1, high);

		rankMerge(array, low, high, mid);
	}
}

void suitMerge(Card array[], int low, int high, int mid) {

	int sizeHigh = high - mid;
	int sizeLow = mid - low + 1;

	Card HiArr[sizeHigh], LoArr[sizeLow];

	for (int i = 0; i < sizeHigh; i++) {
		HiArr[i] = array[mid + 1 + i];
	} // for
	for (int i = 0; i < sizeLow; i++) {
		LoArr[i] = array[low + i];
	} // for

	int i =0, j = 0, k = low;
	while (i < sizeLow && j < sizeHigh) {
		if (LoArr[i].getSuitVal() <= HiArr[j].getSuitVal()) {
			array[k] = LoArr[i];
			i++;
		} else {
			array[k] = HiArr[j];
			j++;
		}
		k++;
	} // while

	while (i < sizeLow) {
		array[k] = LoArr[i];
		i++;
		k++;
	}

	while (j < sizeHigh) {
		array[k] = HiArr[j];
		j++;
		k++;
	}
}

void suitMergeSort (Card array[], int low, int high) {

	if (low < high) {
		for (int i = low; i <= high; i++) {
		}

		int mid = (high - low) / 2 + low;

		suitMergeSort(array, low, mid);
		suitMergeSort(array, mid + 1, high);

		suitMerge(array, low, high, mid);
	}
}

class Hand {
private:
	Card cards[7];
	int num_cards = 0;

public:
	Hand(Deck* the_deck) {
		for (int i = 0; i < 7; i++) {
			cards[i] = the_deck->deal();
			num_cards++;
		}

	}

	// print Hand ... try to make it more user-friendly and readable
	void printHand() {
		cout << "Your hand consists of:\n";
		for (int i = 0; i < num_cards; i++) {
			cout << cards[i].getFullRank() << " of " << cards[i].getFullSuit() << endl;
		}
	}

	int searchRank(string request) {

		int rankRequestInt = 0;

		if (request == "J") {
			rankRequestInt = 11;
		}
		else if (request == "Q") {
			rankRequestInt = 12;
		}
		else if (request == "K") {
			rankRequestInt = 13;
		}
		else {
			rankRequestInt = stoi(request);
		}
		if (rankRequestInt == 0) {
			cout << "Rank not found. Enter either a number between 1 and 10, or J, Q, or K." << endl;
			return -1;
		}

		rankMergeSort(cards, 0, 6);

		return binarySearchSuit(cards, 7, rankRequestInt);
	}

	int searchSuit(string request) {

		int suitRequestInt = 0;

		if (request == "C") {
			suitRequestInt = 1;
		}
		if (request == "D") {
			suitRequestInt = 2;
		}
		if (request == "H") {
			suitRequestInt = 3;
		}
		if (request == "S") {
			suitRequestInt = 4;
		}
		if (suitRequestInt == 0) {
			cout << "Suit not found. Enter either C, D, H, or S." << endl;
			return -1;
		}

		suitMergeSort(cards, 0, 6);

		return binarySearchSuit(cards, 7, suitRequestInt);
	}

	void sortRank() {
		rankMergeSort(cards, 0, 6);
		cout << "Sorted hand by rank!" << endl;
	}

	void sortSuit() {
		suitMergeSort(cards, 0, 6);
		cout << "Sorted hand by suit!" << endl;
	}

	int linearCardSearch(string suitRequest, string rankRequest) {

		int suitRequestInt = 0;

		if (suitRequest == "C") {
			suitRequestInt = 1;
		}
		if (suitRequest == "D") {
			suitRequestInt = 2;
		}
		if (suitRequest == "H") {
			suitRequestInt = 3;
		}
		if (suitRequest == "S") {
			suitRequestInt = 4;
		}
		if (suitRequestInt == 0) {
			cout << "Suit not found. Enter either C, D, H, or S." << endl;
			return -1;
		}

		int rankRequestInt = 0;

		if (rankRequest == "J") {
			rankRequestInt = 11;
		}
		else if (rankRequest == "Q") {
			rankRequestInt = 12;
		}
		else if (rankRequest == "K") {
			rankRequestInt = 13;
		}
		else {
			rankRequestInt = stoi(rankRequest);
		}
		if (rankRequestInt == 0) {
			cout << "Rank not found. Enter either a number between 1 and 10, or J, Q, or K." << endl;
			return -1;
		}

		int foundIndex = -1;
		int i = 0;

		while (i < num_cards && foundIndex == -1) {
			if (cards[i].getFaceVal() == rankRequestInt && cards[i].getSuitVal() == suitRequestInt) {
				foundIndex = i;
			}
			i++;
		}

		return foundIndex;

	} // func

	void linearCardSearchWrapper(string suitRequest, string rankRequest) {
		int foundIndex = -1;
		foundIndex = linearCardSearch(suitRequest, rankRequest);
		if (foundIndex == -1) {
			cout << "The card you are looking for is not in your hand." << endl;
		} else {
			cout << "The card you are looking for is at index " << foundIndex << endl;
		}
	}


};


int main() {
	Deck deck;
	deck.shuffleDeck();
	Deck* deck_ptr = &deck;

	Hand tommy_hand(deck_ptr);
	tommy_hand.printHand();

	for (int i = 0; i < 7; i++) {
		string rankRequest = inputPromptToString("input a rank");
		string suitRequest = inputPromptToString("input a suit");

		tommy_hand.linearCardSearchWrapper(suitRequest, rankRequest);
	}

	tommy_hand.sortSuit();
	tommy_hand.printHand();
	tommy_hand.sortRank();
	tommy_hand.printHand();

	return 0;
}