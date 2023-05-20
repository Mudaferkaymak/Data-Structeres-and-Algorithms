#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 1000
typedef struct Tree{
	int number;
	int power;
	struct Tree *right;
	struct Tree *left;
		
}TREE;
typedef struct Stack{
	int apples[MAX];
	int top;
}STACK;
TREE* createTheTree( int N, int M);
int numberControl(TREE* head,int value);
TREE* insertToBST(TREE* root, int number);
void printHorizontal(TREE* root, int depth);
void implementTheDamage(int value, int damage, TREE** root,int,STACK* stack);
TREE* changeTheTree(TREE* root, int value);
TREE* searchTheValue(TREE* current, int value, int damage, int* health,STACK* stack);
void addToStack(STACK* stack,int value);
void printStack(STACK*);
void initStack(STACK*);
int popStack(STACK* stack);
STACK* stackToStack(STACK* stack);
int main(){
	srand((int) time(0));
	STACK* stack = (STACK*)malloc(sizeof(STACK));
	STACK* stack2 = (STACK*)malloc(sizeof(STACK));
	TREE* root = NULL;
	int N, M, i,fruitValue,damage;
	printf("Enter the maximum weight of a fruit = ");
	scanf("%d",&N);
	printf("Enter how many fruit there will be in the tree = ");
	scanf("%d",&M);		
	
	TREE *head = NULL;
	
	root = createTheTree(N,M);
	initStack(stack);
	initStack(stack2);
	printf("\n->First situation of the tree\n");
	printHorizontal(root, 0);
	
	while(root != NULL){
			
		printf("\nEnter the value of the fruit you want to hit = ");
		scanf("%d",&fruitValue);
		printf("Enter how much do you want to hit = ");
		scanf("%d",&damage);
		while(numberControl(root,fruitValue) != 1){
			printf("There is no fruit which has the value you have entered!\n ");
			printf("\nEnter the value of the fruit you want to hit = ");
			scanf("%d",&fruitValue);
			printf("Enter how much do you want to hit = ");
			scanf("%d",&damage);
		}
		
		implementTheDamage(fruitValue,damage,&root,M,stack);
		if(root!=NULL)
			printf("\n->Current situation of the tree\n");
		printHorizontal(root, 0);
	}
	printHorizontal(root, 0);
	
	stack2 = stackToStack(stack);	
	printf("\nOutput = ");
	printStack(stack2);
	
}
TREE* createTheTree(int N, int M){
	TREE* head = NULL;
	srand(time(NULL));
	int number,i;
	i = 0;
	while(i < M){
		
		number = rand() % N + 1;
		if(!numberControl(head,number)){
		    head = insertToBST(head,number);
		    i++;
		}	
	}
	return head;
}
int numberControl(TREE* head,int value){
if (head == NULL)
        return 0;

    if (value == head->number)
        return 1;

    if (value < head->number)
        return numberControl(head->left, value);

    return numberControl(head->right, value);
}

TREE* insertToBST(TREE* root, int number) {
    if(root == NULL) {
        root = (TREE*)malloc(sizeof(TREE));
        root->number = number;
        root->power = number;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    if(number < root->number) {
        root->left = insertToBST(root->left, number);
    } else if(number > root->number) {
        root->right = insertToBST(root->right, number);
    }
    return root;
}

void printHorizontal(TREE* root, int depth) {
    if(root == NULL) {
        return;
    }
    depth += 8;
    printHorizontal(root->right, depth);
    printf("\n");
    int i;
    for(i = 8; i < depth; i++) {
        printf(" ");
    }
    printf("%d(%d)\n", root->number,root->power);
    printHorizontal(root->left, depth);
}
void implementTheDamage(int value, int damage,TREE** root,int M,STACK* stack){
    int health = 0; // ilk baþta en az bir deðer var
	if(health<M){
		*root = searchTheValue(*root,value,damage,&health,stack);
	}
}

TREE* searchTheValue(TREE* current, int value, int damage, int* health, STACK* stack){
    if(current == NULL){
        return NULL;
    }
    
    if(current->number == value){
        current->power -= damage;
        if(current->power <= 0){
            *health += 1;
            addToStack(stack,current->number);
            printf("Bucket = ");
            printStack(stack);
            printf("\n");
            return changeTheTree(current, value);
        }
    } else if(current->number < value){
        current->right = searchTheValue(current->right, value, damage, health,stack);
    } else {
        current->left = searchTheValue(current->left, value, damage, health,stack);
    }
    return current;
}

TREE* changeTheTree(TREE* root, int value){
    if (root == NULL)
        return NULL;

    if (value < root->number) {
        root->left = changeTheTree(root->left, value);
    } else if (value > root->number) {
        root->right = changeTheTree(root->right, value);
    } else {
    	if(root->left == NULL && root->right == NULL ){
    		free(root);
    		root = NULL;
		}
        else if (root->left == NULL) {
            TREE* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TREE* temp = root->left;
            free(root);
            return temp;
        } else {
            TREE* min_node = root->right;
            while (min_node->left != NULL) {
                min_node = min_node->left;
            }
            root->number = min_node->number;
            root->power = min_node->power;
            root->right = changeTheTree(root->right, min_node->number);
            return root;
        }
    }
    return root;
}
void initStack(STACK* stack){
	stack->top = 0;
}
void addToStack(STACK* stack,int value){
	stack->apples[stack->top] = value;
	stack->top++;
}
void printStack(STACK* stack){
	int i;
	//stack->top--;
	for(i=stack->top-1;i>=0;i--){
		printf("%d ",stack->apples[i]);
	//	stack->top--;
	}
}
int popStack(STACK* stack){
	stack->top--;
	return stack->apples[stack->top];
}
STACK* stackToStack(STACK* stack){
	STACK* stack2 = (STACK*)malloc(sizeof(STACK));
	int num;
	while(stack->top>0){
		 num =  popStack(stack);
		 addToStack(stack2,num);
	}
	return stack2;
}
