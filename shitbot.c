// shitbot.c
// a shit bot
// by ʞ (@velartrill)
//
// edited by @benpop for tail-call optimizations

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
	while (l->count != 0) {
		for (uint8_t p = rand()%l->count; p != 0; --p) cur=cur->next;
		if (cur->v == 0) goto end;
		printf("%c", cur->v);
		l = &start[cur->v];
		cur = l->head;
	}
end:
	printf("\n");
}

void munch(struct list* st, const char* str) {
	while (*str!=0) {
		push(st, *str);
		st = &start[*str];
		++str;
	}
	push(st, 0);
}

void repl() {
	for (;;) {
		char* input = readline("\1\x1b[1m\2>\1\x1b[0m\2 ");
		push(&start[0], *input);
		munch(&start[input[0]], input+1);
		free(input);
		follow(&start[0]);
	}
}

int main() {
	for (uint16_t i = 0; i < 256; ++i) {
		start[i].count=0;
	}
	repl();
}