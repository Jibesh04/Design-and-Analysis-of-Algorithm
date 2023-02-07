/* Polynomial Addition using Linked List */
#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
	int coeff, exp;
	struct Node* next;
} Node;
void createNode(Node **head_ref, int c, int e){
	Node *new = NULL;
	Node *head = *head_ref;
	if(head == NULL){
		new = (Node*) malloc(sizeof(Node));
		new -> coeff = c;
		new -> exp = e;
		new -> next = (Node*) malloc(sizeof(Node));
		new = new -> next;
		new -> next = NULL;
		*head_ref = new;
		return;
	}
	while(head -> next)
		head = head -> next;
	head -> coeff = c;
	head -> exp = e;
	head -> next = (Node*) malloc(sizeof(Node));
	head = head -> next;
	head -> next = NULL;
}
void add(Node* poly_A, Node* poly_B, Node* poly_ans){
	
}
void display(Node* head){
	Node* temp = head;
	while(temp -> next -> next){
		printf("%dx^%d + ", temp -> coeff, temp -> exp);
		temp = temp -> next;
	}
	printf("%dx^%d\n", temp -> coeff, temp -> exp);
}
int main(){
	Node *poly_A = NULL, *poly_B = NULL;
	createNode(&poly_A, 1, 2);
	createNode(&poly_A, 2, 1);
	createNode(&poly_A, 3, 0);
	display(poly_A);
	Node* poly_ans = (Node*) malloc(sizeof(Node));
	return 0;
}
