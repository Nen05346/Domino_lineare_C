#ifndef DOMINO_H
#define DOMINO_H

/**
 * @struct Value
 * Struct to save the values of a card, [left|right].
 */
typedef struct {
	int left;
	int right;
}Value;

/**
 * @struct Card
 * Struct which represents the whole card.
 */
struct node{
	Value values;
	struct node *next;
};


/**
 * @struct Selections
 * Struct to create only one type to handle the interactions with a card in the game. The struct contains 
 * three variables: side, if 1 then insert the card on the left side otherwise on the right;
 * swap, if 1 then the values of the card are swapped otherwise nothing happens;
 * confirm, if 1 then the choice is confirmed. 
 */
// selections struct
typedef struct{
	int side;
	int swap;
	int confirm;
}Selections;
/**
 * @typedef Card
 * Card is a typedef for struct node.
 */
typedef struct node Card;
/**
 * @typedef pCard
 * pCard represents a Card* (pointer).
 */
typedef Card* pCard;

/*-------------------- MENU AND GRAPHIC LAYOUT ------------------------------*/

/**
 * @brief Function to print the title of the game.
 * 
 */
void title(void);
/**
 * @brief Menu for handling the interaction with the player.
 * 
 */
void menu(void);
/**
 * @brief Function to print the rules of the game.
 * 
 */
void rules(void);
/**
 * @brief Function to print an error message for a wrong selection.
 * 
 */
void wrong_selection(void);
/**
 * @brief  Function to confirm the selected mode.
 * 
 * @return int 
 */
int start_slection(void);
/**
 * @brief Function to select the level.
 * 
 * @param hand pointer to pCard (pCard is a pointer to Card) 
 * @return int 
 */
int level_menu(pCard *hand);
/**
 * @brief Function to handle the choices during the game.
 * 
 * @return Selections 
 */
Selections game_questions(void);

/*--------------------- GENERAL UTILITIES ------------------------------------*/

/**
 * @brief Check if a list is empty.
 * The function returns 1 if the pointer is NULL.
 * @param head const pointer to Card 
 * @return int 
 */
int is_empty(const pCard head);
/**
 * @brief Check if two pointers are equals.
 * The function returns 1 the two pointers are equlals.
 * @param first pointer to Card
 * @param second pointer to Card
 * @return int 
 */
int equalpointers(pCard first, pCard second);
/**
 * @brief The function generate random numbers between 1 and 6, that is, the possible numbers
 *  each side of a card can hold.
 * 
 * @return int 
 */
int random_number(void);
/**
 * @brief The function check if the card to insert is compatible with the card in the table.
 * The function returns 0 if the two cards are not compatible.
 * @param hand struct Value 
 * @param table struct Value
 * @param side int 
 * @return int 
 */
int pairing_check_selection(Value hand, Value table, int side);
/**
 * @brief Function to calculate the actual score of the game.
 * The function return the sum of the right and left values of each card in the table.
 * @param head pointer to Card
 * @return int 
 */
int score(pCard head);
/**
 * @brief The function check if there are other possible combinations to continue the game.
 * The function check if there are other possible combinations and it increases a counter if a combination
 * exists. If no combinations are found the game ends.
 * @param hand_head pointer to Card 
 * @param table_head pointer to Card 
 * @param table_tail pointer to Card 
 * @return int 
 */
int check_combinations(pCard hand_head, pCard table_head, pCard table_tail);	

/**
 * @brief Function to print a list
 * 
 * @param head const pointer to Card 
 */
void printlist(const pCard head);
/**
 * @brief Function to print the table.
 * This function uses the printlist function.
 * @param head const pointer to Card
 */
void print_table(const pCard head);
/**
 * @brief Function to print the player's hand. 
 * This function uses the printlist function.
 * @param head const pointer to Card
 */
void print_hand(const pCard head);
/**
 * @brief Function to print the total score at the end of the game.
 * 
 * @param head const pointer to Card
 */
void print_final_score(const pCard head);
/**
 * @brief Append a Card's Value at the end of a list.
 * 
 * @param head pointer to Card 
 * @param tail pointer to Card
 * @param val struct Value 
 */
void append(pCard *head, pCard *tail, Value val);
/**
 * @brief Insert a Card's Value at the beginning of a list.
 * 
 * @param head pointer to pCard (pCard is a pointer to Card) 
 * @param tail pointer to pCard (pCard is a pointer to Card) 
 * @param val struct Value type 
 */
void prepend(pCard *head, pCard *tail, Value val);
/**
 * @brief Swaps left value and right value.
 * 
 * @param sides pointer to Value  
 */
void swap(Value *sides);

/**
 * @brief Delete a Card and free the memory.
 * 
 * @param head pointer to pCard (pCard is a pointer to Card)
 * @param card_selection integer that contains card's position in the list 
 */
void delete_card(pCard *head, int card_selection);
/**
 * @brief Function to select a player's hand card and return the left and right values in it. 
 * 
 * @param head pointer to pCard (pCard is a pointer to Card)
 * @param card_selection pointer to card_selection 
 * @return Value 
 */
Value select_card(const pCard *head, int *card_selection);
/**
 * @brief Print an error message for insertion's errors.
 * 
 */
void INSERT_ERROR(void);
/**
 * @brief Print an error message for selection's errors.
 * 
 */
void SELECTION_ERROR(void);		



/*---------------------- DELETE FUNCTIONS -------------------------------------*/

/**
 * @brief The function free the table's memory.
 * 
 * @param head pointer to pCard (pCard is a pointer to Card) 
 * @param tail pointer to pCard (pCard is a pointer to Card) 
 */
void delete_table(pCard *head, pCard* tail);
/**
 * @brief The function free the player's hand memory.
 * 
 * @param head pointer to Card
 */
void delete_hand(pCard *head);

/*---------------------- PLAYER'S HAND ----------------------------------------*/

/**
 * @brief The function fill the player's hand with the number of cards chosen with level_menu.
 * 
 * @param head pointer to pCard (pCard is a pointer to Card)
 * @param len int  
 */
void player_hand(pCard *head, int len);

/*---------------------- GAME FUNCTIONS ----------------------------------------*/
/**
 * @brief Game mode where the player play in an interactive way.
 * 
 * @param selection pointer to int 
 */
void interattiva(int *selection);

#endif // DOMINO_H