#include <iostream>
#include <cstring>
#include "header.h"

using std::cin;
using std::cout;

int READ_COMMAND(DECK* deckList)
{
	char buffer[20];
	char command[20];
	char* token;
	uint param1 = -1, param2 = -1;
	int arg = 0;

	cin.getline(buffer, 20);

	token = strtok(buffer, " ");
	while (token != NULL)
	{
		if (arg == 0)
		{
			strcpy(command, token);
		}
		else if (arg == 1)
		{
			param1 = 0;
			for (int i = 0; i < strlen(token); ++i)
			{
				if (strchr("0123456789", token[i]) != 0)
				{
					param1 = param1 * 10 + (token[i] - '0');
				}
			}
		}
		else if (arg == 2) 
		{
			param2 = 0;
			for (int i = 0; i < strlen(token); ++i)
			{
				if (strchr("0123456789", token[i]) != 0)
				{
					param2 = param2 * 10 + (token[i] - '0');
				}
			}
		}
		else break;

		++arg;
		token = strtok(NULL, " ");
	}

	//cout <<"COMMAND: "<<command<< "\n"<<"PARAMS: "<< param1 << " " << param2 << '\n';
	PROCESS_COMMAND(command, param1, param2, deckList);
	return 1;
}

int PROCESS_COMMAND(char* command, uint param1, uint param2, DECK* deckList)
{
	if (strcmp(command, "ADD_DECK") == 0)
	{
		cout << "\nAdding cards to deck...\n";
		if (deckList == 0)
			deckList->last = ADD_DECK(param1, deckList);
		else
		{
			DECK* newLDeck = ADD_DECK(param1, deckList->last);
			deckList->last = newLDeck;
		}
	}
	else
	{
		cout << "ERR : INVALID_COMMAND. Please try again.\n";
	}
	return 1;
}

DECK* ADD_DECK(uint cardNum, DECK*& deckList)
{
	DECK* deck = new DECK;
	deck->next = 0;
	deck->prev = deckList;
	if (deckList == 0)
	{
		deckList = deck;
		deckList->cardList = 0;
	}
	CARD* aux = ADD_CARDS(0, cardNum, deckList);
		if(aux)
			cout << "The deck was successfully created with " << cardNum << " cards.\n\n";
	return deck;
}

CARD* ADD_CARDS(uint dIndex, uint cardNum, DECK*& deckList)
{
	if (cardNum == 0)
	{
		// throw new NO_CARDS_IN_DECK exception and return
	}
	DECK* deckPtr = deckList;
	CARD* lastCard = 0;
	for (uint j = 0; j < dIndex; ++j)
	{
		deckPtr = deckPtr->next;
	}
	for (uint i = 1; i <= cardNum; ++i)
	{
		CARD* currCard = new CARD;
		cout << "Card " << i << " in deck " << dIndex << " : ";
		cin >> currCard->value;
		if (currCard->value > 14 || currCard->value < 0)
		{
			// throw INVALID_CARD error and exit function
			return 0;
		}
		cin >> currCard->symbol;
		if (strcmp(currCard->symbol, "PICA") != 0 && strcmp(currCard->symbol, "CUPA") != 0
			&& strcmp(currCard->symbol, "CARO") != 0 && strcmp(currCard->symbol, "TREFLA") != 0)
		{
			// throw INVALID_CARD error and exit
			return 0;
		}
		lastCard = currCard;
		if (deckPtr->cardList == 0)
		{
			deckPtr->cardList = currCard;
			currCard->prev = 0;
			currCard->next = 0;
		}
		else
		{
			deckPtr->cardList->next = currCard;
			currCard->prev = deckPtr->cardList;
			currCard->next = 0;
		}
	}
	cout << "The cards were successfully added to deck " << dIndex << ".\n";
	deckList->cardList->last = lastCard;
	return lastCard;
}