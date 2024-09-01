#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include "domino.h"
#include <ctype.h>


/*-------------------- MENU AND GRAPHIC LAYOUT ------------------------------*/

// funzione che stampa il titolo del gioco
void title(void){
	printf("\n%s\n",
			"THE DOMINO'S GAME");
}

// funzione che stampa le regole del gioco
void rules(void)
{
	printf("\n%20s\n%20s\n%20s\n%20s\n%20s\n%20s\n\n",
			"------------------------ RULES ------------------------",
			"All'inizio del gioco ti verrà assegnato un numero di tessere a tua scelta, ogni tessera è composta da due numeri compresi in un intervallo \nda 1 a 6.",
			"lo scopo del gioco è quello di disporre il maggiore numero di tessere sul tavolo seguendo le seguenti regole:",
			"- le tessere vanno inserite l'una accanto all'altra in modo tale che i numeri dei lati adiacenti siano uguali",
			"- è possibile inserire una tessera solo a destra o a sinistra della serie disposta sul tavolo.",
			"Il punteggio totale viene calcolato sommando tutti i valori presenti sulle tessere, maggiore sarà il numero delle tessere inserite maggiore \nsarà il punteggio totale.");

}

// funzione per la gestione del menu
void menu(void)
{
	title();
	
	// variabile per la pulizia del buffer
	int c; 
	int selection;
	do{
		
		printf("\n%s\n%s\n%s\n\n",
				"Seleziona una tra le seguenti opzioni:",
				"-1. Modalità interattiva",
				"-0. Exit");
		scanf("%d", &selection);
		
		while ((c = getchar()) != '\n' && c != EOF);

		switch(selection){
			case 0:
				exit(EXIT_SUCCESS);
				break;
			case 1:
				interattiva(&selection);
				break;
			default:
				wrong_selection();
				break;
		}	
	}while(selection < 0 || selection > 1);
}

// funzione che stampa un messaggio di "scelta sbagliata"
void wrong_selection(void){
	printf("\n%s\n%s\n\n", 
			"Scelta sbagliata!!", 
			"Scegliere una delle opzioni precedenti...");
}

// funzione pe la gestione del menu secondario
int start_slection(void){
	// variabile per la pulizia del buffer
	int c;
	int selection;
	do{
		printf("\n%s\n%s\n\n",
				"-1. per giocare",
				"-0. per ritornare al menu principale");
		scanf("%d", &selection);
		while ((c = getchar()) != '\n' && c != EOF);
		if(selection < 0 || selection > 1){
			wrong_selection();
		}
	}while(selection < 0 || selection > 1);
	return selection;
}
// funzione per decidere il livello di difficoltà
int level_menu(pCard *hand){
	// variabile per la pulizia del buffer
	int c;
	int level;
	int cards;
	do{
		printf("\n%s\n%s\n%s\n%s\n\n",
				"Scegliere il livello di difficoltà:",
				"-1. Facile (24 tessere)",
				"-2. Intermedio (60 tessere)",
				"-3. Difficile (120 tessere)");
		scanf("%d", &level);
		while ((c = getchar()) != '\n' && c != EOF);
		switch(level){
			case 1:
				cards = 24;
				player_hand(hand, cards);
				break;
			case 2:
				cards = 60;
				player_hand(hand, cards);
				break;
			case 3:
				cards = 120;
				player_hand(hand, cards);
				break;
			default:
				wrong_selection();
				break;
		}
	}while(level < 1 || level > 3);
	return cards;
}
// funzione per la gestione delle scelte di gioco
Selections game_questions(void){
	// variabile per la pulizia del buffer
	int c;
	Selections game_selection = {0,0,0};
	// choice: right or left side
	do{
		printf("%s\n%s\n%s\n%s",
							"Dove vuoi inserire la tessera:",
							"1. sinistra",
							"2. destra",
							"... ");
		// side = 1 -> sinistra, side = 2 -> destra
		scanf("%d", &game_selection.side);
		while ((c = getchar()) != '\n' && c != EOF);
	}while(game_selection.side < 1 || game_selection.side > 2);
	
	// swap choice
	do{
		printf("%s\n%s\n%s\n%s",	
							"Vuoi ruotare la tessera prima di inserirla?",
							"1. Si",
							"2. No",
							"... ");
		scanf("%d", &game_selection.swap);
		while ((c = getchar()) != '\n' && c != EOF);
	}while(game_selection.side < 1 || game_selection.side > 2);

	// confirm for insertion
	do{
		printf("%s\n%s\n%s\n%s", 
							"Vuoi davvero inserire la tessera selelezionata? (Potrebbero esserci combinazioni migliori)",
							"1. Si",
							"2. No",
							"... ");
		scanf("%d", &game_selection.confirm);
		if(game_selection.confirm == 2) game_selection.confirm = 0;
		while ((c = getchar()) != '\n' && c != EOF);
	}while(game_selection.confirm < 0 || game_selection.confirm > 1);
	return game_selection;
}
/*--------------------- GENERAL UTILITIES ------------------------------------*/

// funzione che controlla se una lista è vuota
int is_empty(const pCard head){
	return head == NULL;
}
// funzione che controlla se due puntatori sono uguali
int equalpointers(pCard first, pCard second){
	return first == second;
}
// funzione che genera numeri casauli da 1 a 6
int random_number(void){
	return 1 + rand() % 6;
}

// funzione controllo compatibilità tra la tessera inserita e quella già presente sul tavolo
// side = 1 -> sinistra, side = 2 -> destra
int pairing_check_selection(Value hand, Value table, int side){
	if(side == 1){
		return hand.right == table.left;
	}else if(side == 2){
		return hand.left == table.right;
	}
	return 0;
}

// funzione per il calcolo del punteggio
int game_score(pCard head){
	int score = 0;
	if(!is_empty(head)){
		while(head){
			score += ((head->values.left) + (head->values.right));
			head = head->next;
		}
	}
	return score;
}
// controlla e conta le combinazioni che ci sono tra le tessere nella mano del giocatore e le tessere presenti sul tavolo
int check_combinations(pCard hand_head, pCard table_head, pCard table_tail){
	int combinations = 0;
	if(!is_empty(hand_head) && !is_empty(table_head)){
		while(hand_head){
			if(hand_head->values.left == table_head->values.left || hand_head->values.right == table_head->values.left)
				combinations += 1;
			if(hand_head->values.left == table_tail->values.right || hand_head->values.right == table_tail->values.right)
				combinations += 1;

			hand_head = hand_head->next;
		}
	}
	return combinations;
}

// funzione errore inserimento
void INSERT_ERROR(void){
	printf("\n%s\n", "Non è possibile inserire la tessera selezionata");
}

// funzione errore selezione 
void SELECTION_ERROR(void){
	printf("\n%s\n", "La tessera selezionata non è presente nel mazzo");
}

// funzione stampa         					
void printlist(const pCard head){
	if(!is_empty(head))
	{
		int i = 1;
		pCard curr = head;
		while(curr != NULL)
		{
			printf("%d).[%d|%d] ", i++, curr->values.left, curr->values.right);
			curr = curr->next;
		}
	}else{
		printf("\nThe list is empty\n");
	}
	puts("");
}

// funzione per stampare il tavolo da gioco
void print_table(const pCard head){
	printf("\n\n%s%100s:%d\n\n", "TAVOLO DA GIOCO", "SCORE", game_score(head));
	if(!is_empty(head))
	{
		pCard curr = head;
		while(curr != NULL)
		{
			printf("[%d|%d]", curr->values.left, curr->values.right);
			curr = curr->next;
		}
	}else{
		printf("\nThe list is empty\n");
	}
	puts("");
}

// funzione per stampare la mano del giocatore
void print_hand(const pCard head){
	printf("\n\n%s\n", "TESSERE DEL GIOCATORE");
	printlist(head);
}
// funzione che stampa il punteggio finale
void print_final_score(const pCard head){
	printf("\n%s\n","La partita è terminata!!");
	puts("");
	printf("\n%s%d%s\n", "Congratulazioni hai totalizzato ", game_score(head), " punti!!");
}

// append tavolo
void append(pCard *head, pCard *tail, Value val)
{
	pCard new_card = (pCard)malloc(sizeof(Card));
	new_card->values.left = val.left;
	new_card->values.right = val.right;
	new_card->next = NULL;

	if(equalpointers(*head, *tail)){
		if((*head == NULL) && (*tail == NULL)){
			*head = new_card;
			*tail = new_card;
		}else{
			(*tail)->next = new_card;
			*tail = new_card;
		}
	}else{
		(*tail)->next = new_card;
			*tail = new_card;
	}
}

// prepend tavolo
void prepend(pCard *head, pCard *tail, Value val)
{
	pCard new_card = (pCard)malloc(sizeof(Card));
	new_card->values.left = val.left;
	new_card->values.right = val.right;
	new_card->next = NULL;

	if(!is_empty(*head)){
		new_card->next = *head;
		*head = new_card;
	}else{
		append(head, tail, val);
	}
}

// funzione di swap
void swap(Value *sides)
{
	int tmp = sides->left;
	sides->left = sides->right;
	sides->right = tmp; 
}

// funzione che elimina il nodo corrispondente alla tessera precedentemente selezionata
void delete_card(pCard *head, int card_selection)
{
	if(!is_empty(*head))
	{
		// preparo i due puntatori per scorrere la lista
		pCard curr = *head;
		pCard prev = NULL;
		if(card_selection > 1)
		{
			prev = *head;
			curr = (*head)->next;
			while(--card_selection > 1 && curr != NULL)
			{
				prev = prev->next;
				curr = curr->next;
			}	
		}

		// controllo se non sono arrivato alla fine della lista
		if(curr != NULL)
		{
			// se sono da qualche parte in mezzo alla lista o alla fine
			if(!equalpointers(*head, curr))
			{
				prev->next = curr->next;
				curr->next = NULL;	
			}else{
				// se sono all'inizio
				*head = (*head)->next;
				curr->next = NULL;
			}		
		}
		// libero il nodo della memoria
		free(curr);
		curr = NULL;
	}
}

// funzione che estrae il valore della tessera senza eliminare il nodo corrispondente
Value select_card(const pCard *head, int *card_selection){
	// variabile per pulizia buffer
	int c;
	int selected_card = -1;
	Value val = {0,0};
	do{
		printf("Scegli una carta dalla tua mano... \n");
		scanf("%d", &selected_card);
		while ((c = getchar()) != '\n' && c != EOF);

		*card_selection = selected_card;
		if(!is_empty(*head))
		{
			pCard curr = *head;
			while(--selected_card && curr){
				curr = curr->next;
			}
			if(curr)
				val = curr->values;
		}
	}while(selected_card < 0);

	return val;
}

/*---------------------- DELETE FUNCTIONS -------------------------------------*/

// Funzione delete
void delete_hand(pCard *head)
{
	pCard curr = NULL;
	while(!is_empty(*head))
	{
		curr = *head;
		*head = (*head)->next;
		free(curr);
	}
	*head = NULL;
}

void delete_table(pCard *head, pCard* tail)
{
	*tail = NULL;
	pCard curr = NULL;
	while(!is_empty(*head))
	{
		curr = *head;
		*head = (*head)->next;
		free(curr);
	}
	*head = NULL;
}

/*---------------------- PLAYER'S HAND ----------------------------------------*/

// player's hand generation
void player_hand(pCard *head, int len)
{
	while(len-- > 0)
	{
		pCard new_card = (pCard)malloc(sizeof(Card));
		if(new_card != NULL)
		{
			// allocazione andata a buon fine
			new_card->values.left = random_number();
			new_card->values.right = random_number();
			new_card->next = NULL;

			// controllo lista vuota
			if(is_empty(*head))
			{
				(*head) = new_card;
			}else
			{
				pCard curr = *head;
				
				while(curr->next != NULL)
				{
					curr = curr->next;
				}
				curr->next = new_card;
			}	
		}
	}
}

/*---------------------- GAME FUNCTIONS ----------------------------------------*/

// funzione modalità interattiva
void interattiva(int *selection){
	
	// scelta se iniziare modalità interattiva o ritornare al menu principale
	int START = start_slection();
	// inizia la partita
	while(START){
		// regole del gioco
		rules();
		// variabile per regolare flusso partita
		int CONTINUE = 1;
		// lista mano giocatore
		pCard hand_head = NULL;
		// lista tavolo
		pCard table_head = NULL;
		pCard table_tail = NULL;

		// scelta livello di difficoltà
		int number_of_cards = level_menu(&hand_head);

		printf("\nComincia la partita\n");
		print_hand(hand_head);
		
		while(CONTINUE)
		{
			int card_selection = 0;
			do{
				// con select_card() solo recupero il valore senza eliminare la tessera
				Value of_card = select_card(&hand_head, &card_selection);
				// caso in cui il tavolo è vuoto
				if(is_empty(table_head) && of_card.left && of_card.right)
				{
					delete_card(&hand_head, card_selection);
					append(&table_head, &table_tail, of_card);
					card_selection = -1;
					// caso in cui il tavolo non è vuoto
				}else if(!is_empty(table_head) && of_card.left && of_card.right)
				{
					// struttura Selection 
					Selections selection = game_questions();

					// rotazione
					if(selection.swap == 1)
					{
						swap(&of_card);
					}

					// inserimento tessera lato sinistro
					if(selection.side == 1 && pairing_check_selection(of_card, table_head->values, selection.side) && selection.confirm)
					{
						delete_card(&hand_head, card_selection);
						prepend(&table_head, &table_tail, of_card);
						card_selection = -1;

					// inserimento tessera lato destro
					}else if(selection.side == 2 && pairing_check_selection(of_card, table_tail->values, selection.side) && selection.confirm)
					{
						delete_card(&hand_head, card_selection);
						append(&table_head, &table_tail, of_card);
						card_selection = -1;

					// conferma inserimento tessera
					}else if(!selection.confirm){
						print_table(table_head);
						print_hand(hand_head);
						printf("\n%s\n", "Procedere con un'altra scelta..");

					// errore inserimento tessera
					}else{
						INSERT_ERROR();
						print_table(table_head);
						print_hand(hand_head);
					}
				}else if(!of_card.left && !of_card.right){
					SELECTION_ERROR();
				}
				// card selection >= 0 è la sentinella per verficare se la scelta della tessera è definitiva e la tessera è stata eliminata dalla mano del giocatore
			}while(card_selection >= 0);

			print_table(table_head);
			print_hand(hand_head);

			// controllo combinazioni per fine partita
			// se non ci sono combinazioni la funzione ritorna 0, il valore di CONTINUE viene impostato a 0, e la partita si conclude
			if((!check_combinations(hand_head, table_head, table_tail)) && table_head)
				CONTINUE = 0;
		}
		print_final_score(table_head);
		delete_hand(&hand_head);
		delete_table(&table_head, &table_tail);
		START = start_slection();
	}
	if(START == 0)
		*selection = -1;	
}




