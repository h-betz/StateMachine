#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int entry_state(char);
int first_state(char);
int second_state(char);
int exit_state(char);

int (* state[])(char) = {entry_state, first_state, second_state, exit_state};
enum state_codes {entry, first, second, end};       //0, 1, 2, 3

enum ret_codes {ok, fail, repeat};
struct transition {
    
    enum state_codes src_state;
    enum ret_codes ret_code;
    enum state_codes dst_state;
    
};

/*struct transition state_transitions[][3] = {
{[entry] = {entry, ok, first}},
      {entry, fail, end},
      {first, ok, second},
      {first, fail, end},
      {first, repeat, second},
      {second, ok, end},
      {second, fail, end},
      {second, repeat, end}};
*/

int state_transitions[][3] = {
    
      {first}, {end},               //entry: ok -> first, fail -> end
      {second}, {end}, {second},    //first: ok -> second, fail -> end, repeat -> second
      {end}, {end}, {end}           //second: ok -> end, fail -> end, repeat -> end
    
};

int lookup_transitions(enum state_codes cs, enum ret_codes r) {
    
    return state_transitions[cs][r];
}

#define EXIT_STATE end
#define ENTRY_STATE entry

int main(int argc, char** argv) {
    
    enum state_codes curr_state = ENTRY_STATE;
    enum ret_codes rc;
    
    char * string = *(argv + 1);
    int length = strlen(string);

    int (* state_fun)(char);

    char c = NULL;
    int i = 0;
    
    for (i = 0; i < length; i++) {
        c = string[i];
        printf("State: %d\n", curr_state);
        state_fun = state[curr_state];
        rc = state_fun(c);
        if (EXIT_STATE == curr_state) {
            break;
        }
        curr_state = lookup_transitions(curr_state, rc);
        printf("State after: %d\n", curr_state);
    }
    
    return 0;
}

int entry_state(char c) {
    
    if (c == '1') {
        return 0;
    }
    
    return 1;
}

int first_state(char c) {
    
    if (c == '1') {
        return 0;
    }
    
    return 1;
    
}

int second_state(char c) {
    
    if (c == '1') {
        return 0;
    }
    
    return 1;
}

int exit_state(char c) {
    
    return 0;
}