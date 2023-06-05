#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALPHABET_SIZE 10

#define MAX_CAPACITY 200
typedef struct key {
    char* chars;
    int number;
} KEY;

typedef struct node {
    struct node* child[ALPHABET_SIZE];
    short isEnd;
    char* word;
} NODE;

NODE* createTreeNode();
void insertToTree(NODE* currentNode, int key, int i, char* words[], int j);
KEY* importKey(KEY keys[], int number, const char* letters, int nodeCount);
KEY* createKey(KEY* keys);
int searchKeys(KEY* keys, char letter);
void readFromFile(const char* filename, char* words[], int* wordCount);
int power(int base, int exponent);    
void getResult(int input,NODE* root);    
void createAllTree(char* words[],NODE** root,int countWords,KEY* keys);
int main() {
	KEY keys[10];
	const char* filename = "words.txt";
    char* words[100];
    int wordCount = 0,input=1;
	NODE* root = createTreeNode();
	createKey(keys);
	int key = searchKeys(keys,'d'); 

	
	insertToTree(root,key,0,words,0);
    readFromFile(filename, words, &wordCount);
	

	createAllTree(words,&root,wordCount,keys);
	while(input != 0){
		printf("\n\nEnter '0' to Exit\n");
		printf("Input = ");
		scanf("%d",&input);
		if(input != 0){
			printf("->%d\n",input);
			getResult(input,root);
		}
	}


	
    return 0;
}
void readFromFile(const char* filename, char* words[], int* wordCount) {
    FILE* fp = fopen(filename, "r");
	
	if(fp == NULL){
		printf("An Error Has Occured While Opening The File!\n");
		return;
	}
	char line[MAX_CAPACITY];
	fgets(line, MAX_CAPACITY,fp);
	
	char* token = strtok(line,",");
	while(token != NULL){
		words[*wordCount] = (char*)malloc(sizeof(char)*(strlen(token)+1));
		strcpy(words[*wordCount],token);
		(*wordCount)++;
		token = strtok(NULL,",");
	}
	fclose(fp);			
}
void createAllTree(char* words[],NODE** root,int countWords,KEY* keys){

	NODE* temp = *root;
	int i,key,j=0;
	//printf("%c",words[3][2]);
	for(i=0;i<countWords;i++){

		
		while(words[i][j] != '\0'){


			key = searchKeys(keys,words[i][j]);
		
		
			insertToTree(temp,key,i,words,j);

			temp = temp->child[key];
			j++;

		}

		j=0;	
		temp=*root;
	}


}
int searchKeys(KEY* keys, char letter) {
    int i, j;
    for (i = 0; i < 10; i++) {
        j = 0;
        while (keys[i].chars[j] != '\0') {
        	
            if (keys[i].chars[j] == letter) {

                return i+1;
            }
            
            j++;
        }
    }
    return -1; // Aranan harf bulunamazsa -1 döndürülür
}
KEY* createKey(KEY* keys){
	    
    importKey(keys, 1, "çðüþ", 0);
	importKey(keys, 2, "abc", 1);
	importKey(keys, 3, "def", 2);
	importKey(keys, 4, "ghi", 3);
	importKey(keys, 5, "jkl", 4);
	importKey(keys, 6, "mno", 5);
	importKey(keys, 7, "pqrs", 6);
	importKey(keys, 8, "tuv", 7);
	importKey(keys, 9, "wxyz", 8);
   
	return keys;
}
void insertToTree(NODE* currentNode, int key, int i, char* words[], int j) {
    NODE* temp = currentNode;
    
    if (temp->child[key] == NULL) {
        temp->child[key] = createTreeNode();
        temp->isEnd = 0;

        if (strlen(words[i]) - 1 == j) {
            strcpy(temp->child[key]->word, words[i]);
            temp->child[key]->isEnd = 1;
        }
    }
    else if (temp->child[key] != NULL && temp->child[key]->isEnd != 0 && (strlen(words[i]) - 1 == j)) {
        temp = temp->child[key];
        
        
        while (temp->child[0] != NULL) {
            temp = temp->child[0];
            
        }

        temp->child[0] = createTreeNode();
        strcpy(temp->child[0]->word, words[i]);
    }
    else {
        temp->child[key]->isEnd = 0;
    }
}
NODE* createTreeNode() {
    NODE* root = (NODE*)malloc(sizeof(NODE));
    int i;
	root->word = (char*)malloc(sizeof(char)*40);
    strcpy(root->word,"Kelime bulunmuyor");
	if(root != NULL){
		    for (i = 0; i < ALPHABET_SIZE; i++) {
		        root->child[i] = NULL;
		        
		    }
		    root->isEnd = 0;
		    
	}


    return root;
}
KEY* importKey(KEY keys[], int number, const char* letters, int nodeCount) {
    KEY newKey;
    newKey.number = number;
    newKey.chars = (char*)malloc((strlen(letters) + 1) * sizeof(char));
    strcpy(newKey.chars, letters);

    keys[nodeCount] = newKey;

  //  return keys;
}
void getResult(int input,NODE* root){
	int numberOfDigits = log10(input) + 1;

	int num;
	num = input/power(10,numberOfDigits-1);

	if(root->child[num] == NULL){
		printf("Kelime bulunmuyor");
	}else{
			while(root->isEnd == 0 && input > 0 && root->child[num] != NULL){

			root = root->child[num];
			input = input % (power(10,numberOfDigits-1));
			numberOfDigits--;
			num = input/power(10,numberOfDigits-1);
			
	} 
		printf("%s\n",root->word);
		while(root->child[0] != NULL){
			root= root->child[0];
			printf("%s\n",root->word);
		}
	}

}
int power(int base, int exponent) {
    int result = 1.0;
    int i;
        for (i = 0; i < exponent; i++) {
            result *= base;
        }
    return result;
}
