// shitbot.c
// a shit bot
// by ʞ (@velartrill)

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
void* const null = 0;
 
struct node {
	uint8_t v;
	struct node* next;
};

struct list {
	size_t count;
	struct node *head, *end;
};
struct list start[256];

void push(struct list* list, uint8_t v) {
	struct node* new = malloc(sizeof(struct node));
	new->v=v;
	if (list->count==0) list->end = list->head = new;
		else list->end->next = new;
	list->end = new;
	++list->count;
}

void follow(struct list* l) {
	struct node* cur = l->head;
	if (l->count == 0) {printf("\n"); return;}
	for (uint8_t p = rand()%l->count; p != 0; --p) cur=cur->next;
	if (cur->v == 0) {printf("\n"); return;}
	printf("%c", cur->v);
	follow(&start[cur->v]);
}

void munch(struct list* st, const char* str) {
	if (*str==0) {
		push(st, 0);
		return;
	}
	push(st, *str);
	munch(&start[*str], str+1);
}

void repl() {
	char* input = readline("\1\x1b[1m\2>\1\x1b[0m\2 ");
	push(&start[0], *input);
	munch(&start[input[0]], input+1);
	free(input);
	follow(&start[0]);
	repl();
}

int main() {
	for (uint16_t i = 0; i < 256; ++i) {
		start[i].count=0;
	}
	munch(&start[0], corpus);
	repl();
}