//Libraries
//FINAL CODE
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//Global Variables
int SUITS = 4; //suits of deck, (columns)
int CARDS = 13; //cards of the each suit, (rows)
int MAX = 21; //max total you can have 

//Card Struct
typedef struct{
	//to show card's name (some cards have unique name)
	char* cardName;
	//to show card's suite
	char* suit;
	//to keep track of card's values
	int value;
}Card;

//Deck Struct
typedef struct{
	//to keep track of max number of decks being used
	int maxDecks;
	//to keep track of deck matrix (cards distributed)
	int** matrix;
}Deck;

//Player Struct
typedef struct {
	//to keep track of number of cards in players hand
	int numOfCards;
	//an array to keep track of the cards made on the heap
	Card** cards;
}Hand;

//Game States
enum
{
	//Initializing Phase
	INIT,
	//Quit Phase
	QUIT,
	//User's Turn
	USER,
	//Dealer's Turn
	DEALER,
	//Finish the game
	FINISH

} Game_State;    //GameState are like "datatype" and defines what "values"  

//Function to Create and Allocate Memory to Deck Matrix
int** createDeckMatrix(){
	//create the pointer
	int** deckMatrix;
	//allocate memory (rows)
	deckMatrix = calloc(CARDS, sizeof(int*));
	//allocate memory (columns)
	int i;
	for (i = 0; i < CARDS; ++i){
		deckMatrix[i] = calloc(SUITS, sizeof(int));
	}
	//return deck matrix
	return deckMatrix;
}

//Function to free the memory after use
void freeMem(int** deckMatrix){
	//loop through rows and free
	int i;
	for (i = 0; i < CARDS; ++i){
		free(deckMatrix[i]);
	}
	free(deckMatrix);
}

//Function to make the card
Card* makeCard(int suite, int card){
	//make a card variable
	Card* aCard = (Card*)malloc(sizeof(Card));
	char* buffer = (char*)malloc(2*sizeof(char));

	//assign suite
	switch (suite)
	{
	case 0:
		aCard->suit = "Diamond";
		break;
	case 1:
		aCard->suit = "Clover";
		break;
	case 2:
		aCard->suit = "Hearts";
		break;
	default:
		aCard->suit = "Spade";
		break;
	}

	//assign card name
	switch (card)
	{
	case 0:
		aCard->cardName = "Ace";
		break;
	case 10:
		aCard->cardName = "Jack";
		break;
	case 11:
		aCard->cardName = "Queen";
		break;
	case 12:
		aCard->cardName = "King";
	default:
		//assign physical value as card name

		sprintf(buffer, "%d", card + 1);
		aCard->cardName = buffer;
		break;
	}

	//assign card value
	if (card < 9 && card > 0){
		aCard->value = card + 1;
	}
	else if (card == 0){
		aCard->value = 11;
	}
	else{
		aCard->value = 10;
	}

	//return the card
	return aCard;
}


//Function to give a card
Card* giveCard(Deck* gameDeck){
	//pick random values for suite and card
	int suiteIndex = SUITS - 1;
	int cardIndex = CARDS - 1;
	int suite = rand() % (suiteIndex);
	int card = rand() % (cardIndex);

	//while that card has been given out completely from the decks
	while (gameDeck->matrix[card][suite] == gameDeck->maxDecks){
		//generate new random suite and card
		suite = rand() % (suiteIndex);
		card = rand() % (cardIndex);
	}

	//increment in matrix
	gameDeck->matrix[card][suite] += 1;

	//give user/dealer the card
	Card* cardToGive = makeCard(suite, card);

	return cardToGive;
}


//Function to calculate total of a hand
int getTotal(Hand* aHand){
	int total = 0;
	//loop through and cumilate
	int i;
	for (i = 0; i < aHand->numOfCards; ++i){
		total += aHand->cards[i]->value;
	}
	return total;
}

//Function to change value of wild card Ace
void changeAce(Hand* aHand){
	//loop through find and modify
	int i;
	for (i = 0; i < aHand->numOfCards; ++i){
		if (aHand->cards[i]->value == 11){
			aHand->cards[i]->value = 1;
			return;
		}
	}
}

//Add a card to hand
void addToHand(Hand* aHand, Card* aCard){
	//Before adding check if needed change wild card value to 1 then add or
	if (getTotal(aHand) + aCard->value > MAX){
		if (aCard->value == 11){
			aCard->value = 1;
		}
		//modify and old wildcard ace to 1
		else{
			changeAce(aHand);
		}
	}

	//otherwise nothing else could be done with wildcard just add the card
	aHand->cards[aHand->numOfCards] = aCard;
	++aHand->numOfCards;
}

//Function to print the cards in the hand
void printHand(Hand* aHand){
	//loop through and print cards
	int i;
	for (i = 0; i < aHand->numOfCards; ++i){
		printf("%s %s\n", aHand->cards[i]->suit, aHand->cards[i]->cardName);
	}
}


//main
int main() {
	//For Random Number Generator
	srand(time(NULL));


	//Ininitialze Game States and Objects
	Game_State = INIT;
	Hand* userHand = (Hand*)malloc(sizeof(Hand));
	Hand* dealerHand = (Hand*)malloc(sizeof(Hand));
	Deck* deck = (Deck*)malloc(sizeof(Deck));
	int userTotal;
	int dealerTotal;
	int hit;
	int replay;

	//While Game State is not QUIT run the game
	while (Game_State != QUIT){
		switch (Game_State)
		{
			//Initializing Game Objects
		case INIT:
			//make user hand
			userHand->numOfCards = 0;
			userHand->cards = (Card**)malloc(sizeof(Card));
			//make dealer hand
			dealerHand->numOfCards = 0;
			dealerHand->cards = (Card**)malloc(sizeof(Card));
			//make the deck matrix
			printf("How many decks to play with? Maximum 4, Minimum 1: ");
			scanf("%d", &deck->maxDecks);
			
			deck->matrix = createDeckMatrix();

			//give user two cards
			Card* aCard = giveCard(deck);

			addToHand(userHand, aCard);

			Card* bCard = giveCard(deck);
			addToHand(userHand, bCard);

			//give dealer two cards
			Card* cCard = giveCard(deck);
			addToHand(dealerHand, cCard);
			Card* dCard = giveCard(deck);
			addToHand(dealerHand, dCard);

			//print one card of dealer, one card of player
			printf("One of User's Cards: %s %s\n", userHand->cards[userHand->numOfCards - 1]->suit, userHand->cards[userHand->numOfCards - 1]->cardName);
			puts("");
			printf("One of the Dealer's Cards: %s %s\n", dealerHand->cards[userHand->numOfCards - 1]->suit, dealerHand->cards[userHand->numOfCards - 1]->cardName);
			puts("");
			//change game state to user, for user's turn
			Game_State = USER;
			break;
		case QUIT:
			break;
		case USER:
			//display user's hand and total value
			printf("User's Cards: \n");
			printHand(userHand);
			puts("");
			userTotal = getTotal(userHand);
			printf("Total Value: %d\n", userTotal);
			//check if the user busted
			if (userTotal > MAX){
				puts("You Busted!!!!");
				Game_State = FINISH;
			}
			//if not ask user to hit or not
			else{
				printf("Enter 1 to hit a card and 0 to stop your turn: \n");
				scanf("%d", &hit);
				//if hit then give a card
				if (hit == 1){
					Card* hitcard = giveCard(deck);
					addToHand(userHand, hitcard);
					if(getTotal(userHand) == 21){
						Game_State = FINISH;
					}
				}
				//otherwise make it dealer'sturn now
				else{
					Game_State = DEALER;
				}
			}
			break;
		case DEALER:
			//display dealer's hand and total value
			printf("Dealer's Cards: \n");
			printHand(dealerHand);
			puts("");
			dealerTotal = getTotal(dealerHand);
			printf("Total Value: %d\n", dealerTotal);
			//check if the dealer busted
			if (dealerTotal > MAX){
				puts("You Busted!!!!\n");
				Game_State = FINISH;
			}
			//if not dealer keeps hitting until he gets upto 17
			else{
				if (dealerTotal < 18){
					Card* dealerHit = giveCard(deck);
					addToHand(dealerHand, dealerHit);
				}
				//otherwise make it end the dealer's end
				else{
					Game_State = FINISH;
				}
			}
			break;
		case FINISH:
			//get totals
			userTotal = getTotal(userHand);
			dealerTotal = getTotal(dealerHand);
			//check who busted
			if(userTotal == 21){
				printf("21! User Wins\n");
			}
			else if (userTotal > MAX && dealerTotal <= MAX){
				puts("User Busted, Dealer Wins!!!\n");
			}
			else if (dealerTotal > MAX && userTotal <= MAX){
				puts("Dealer Busted, User Wins!!!\n");
			}
			else if (dealerTotal > MAX && userTotal > MAX){
				puts("Both Player Busted, It is a tie!!!\n");
			}
			//check who has higher than who
			else if (userTotal > dealerTotal && userTotal <= MAX){
				puts("User Wins!!!\n");
			}
			else if (dealerTotal > userTotal && dealerTotal <= MAX){
				puts("Dealer Wins!!!\n");
			}

			//clear the memory
			freeMem(deck->matrix);

			//ask to see if they want to replay
			printf("Do you want to play again? 1 for yes 0 for no\n");
			scanf("%d", &replay);
			//if yes then change game state to init
			if (replay == 1){
				Game_State = INIT;
			}
			else{
				Game_State = QUIT;
			}
			//otherwise quit
			break;
		default:
			puts("Game Error!!!\n");
			return(1);
			break;
		}
	}

	return(0);
}
