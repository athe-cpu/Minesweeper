#include "hof.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

/**
 * Сортировка массива list по параметру score
 * сортировка по убыванию. 
 * изменяется входной  параметр list
 * @param list массив структур player
 * @param size размер массива
 * */


/**
 * Load hall of fame from the file
 * @return the number of loaded entries or 0, if there was error in loading
 */
int read_scores(char *filename, Player *list_of_players) {
    assert(filename != NULL);
    assert(list_of_players != NULL);
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return 0;
    }
    int index_of_player = 0;
    while (fscanf(file, "%s %d", list_of_players[index_of_player].name,
                  &list_of_players[index_of_player].score) != EOF
           && index_of_player < PLAYERS_LIMIT) {

        index_of_player++;
    }
sort_scores(list_of_players, index_of_player);
    fclose(file);
    return index_of_player;
}


/**
 * Save the hall of fame array to the file
 */
void save_scores(char *filename, Player *list_of_players, const int size) {
     sort_scores( list_of_players, size);
    assert(filename != NULL);
    assert(list_of_players != NULL);
    FILE *file = fopen(filename, "w");

    if (file == NULL) { return; }
    for (int i = 0; i < size; i++) {
        if (i < PLAYERS_LIMIT) {
            fprintf(file, "%s %d\n", list_of_players[i].name, list_of_players[i].score);
        }
    }
    fclose(file);
}


/**
 * Add Player to the hall of fame array
 * @return true, if Player (entry) was added to the list, false otherwise
 */
bool add_player_to_list(Player list_of_players[], int *size_of_list, const Player player) {
    assert(list_of_players != NULL && size_of_list != NULL);

    if (*size_of_list <= PLAYERS_LIMIT) {
        // adds player on the end of the list
        list_of_players[*size_of_list] = player;
        *size_of_list = *size_of_list + 1;
        sort_scores( list_of_players, *size_of_list);
        if(*size_of_list>10){
        *size_of_list = *size_of_list - 1;
            
        }
    } else {
        
        return false;
    }

    return true;
}

void sort_scores(Player list_of_players[], const int size_of_list){
    for(int i = 1; i < size_of_list; ++i){
        int k = i;

        while(k > 0 && list_of_players[k-1].score < list_of_players[k].score){
            Player tmp = list_of_players[k -1];
            list_of_players[k -1] = list_of_players[k];
            list_of_players[k] = tmp;
            k -= 1;
        }
    }
}


