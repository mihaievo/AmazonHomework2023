#include <iostream>
#include "header.h"

using std::cout;

int main(void)
{
	cout << "=========================================================\n";
	cout << "|            CRACIUN MIHAI'S CARD GAME                  |\n";
	cout << "=========================================================\n";
	cout << "Commandline started. Type HELP for details.\n";
	cout << "[player @ game] ~ ";
	DECK* deckList = 0;
	DECK* lastDeck = deckList;
	int run = READ_COMMAND(deckList);
	while (run)
	{
		cout << "[player @ game] ~ ";
		run = READ_COMMAND(deckList);
	}
}