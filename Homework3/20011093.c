#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct Node{
	int vertex;
	struct Node* next;
}NODE;

typedef struct Graph{
	int numberofVertices;
	struct Node ** adjList;
}GRAPH;

NODE* createNode(int v);
GRAPH* createGraph(int nVertices);
void addEdge(GRAPH* graph, int src, int dest, NODE* node1, NODE* node2);
int** fileRead();
int getNumberofLessons();
void printGraph(GRAPH* graph, int numberofLessons);
void createtheList(GRAPH* graph, int numberofLessons,int** matris);
int* calculatetheInDegree(GRAPH* graph);
int findmaxIndegree(int* a,int n);
void calculatetheTerms(GRAPH* graph,int* a);
void printMatris(int** matris,int n);
int main() {
    int **matris = fileRead();
    int numberofLessons = getNumberofLessons();
    printMatris(matris,numberofLessons);
    GRAPH* graph = createGraph(numberofLessons); 
	createtheList(graph,numberofLessons,matris);
    printGraph(graph,numberofLessons);
 	int *a = calculatetheInDegree(graph);
	calculatetheTerms(graph,a);
	
    return 0;
}
NODE* createNode(int v){
	NODE *newNode = malloc(sizeof(NODE));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}
GRAPH* createGraph(int nVertices){
    GRAPH* newGraph = malloc(sizeof(GRAPH));
    newGraph->numberofVertices = nVertices;

    newGraph->adjList = malloc(nVertices * sizeof(NODE*));  // Bellek ayrýmý

    int i;
    for(i = 0; i < nVertices; i++){
        newGraph->adjList[i] = NULL;
    }
    return newGraph;
}
void addEdge(GRAPH* graph, int src, int dest, NODE* node1, NODE* node2) {
    // Kaynak düðüm için yeni bir baðlantý oluþtur
    NODE* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Eðer düðüm1 ve düðüm2 geçerliyse, bunlarý baðla
    if (node1 != NULL && node2 != NULL) {
        node1->next = node2;
        node2->next = node1;
    }
}
int** fileRead() {
    FILE *dosya;
    int numberofLessons, i, j;

    dosya = fopen("dersler.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi!");
        return NULL;
    }

    fscanf(dosya, "%d", &numberofLessons);

    int **matris = (int **)malloc(numberofLessons * sizeof(int *));
    for (i = 0; i < numberofLessons; i++) {
        matris[i] = (int *)malloc(numberofLessons * sizeof(int));
    }

    for (i = 0; i < numberofLessons; i++) {
        for (j = 0; j < numberofLessons; j++) {
            fscanf(dosya, "%d", &matris[i][j]);
        }
    }

    fclose(dosya);
    return matris;
}
int getNumberofLessons(){
	int numberofLessons;
	FILE* file;
	file = fopen("dersler.txt","r");
	if (file == NULL) {
        printf("Dosya acilamadi!");
        return 1;
    }

    fscanf(file, "%d", &numberofLessons);

	return numberofLessons;
}
void printGraph(GRAPH* graph, int numberofLessons){
	int i;
	printf("\n-Adjacency List-");
	for (i = 0; i < numberofLessons; i++) {
	    NODE* current = graph->adjList[i];
	    printf("\nAdjacency of Course-%d = ", i+1);
	    while (current != NULL) {
	        printf("%d ", current->vertex+1);
	        current = current->next;
	    }
	}

	printf("\n");
	
}
void createtheList(GRAPH* graph, int numberofLessons,int** matris){
	int i,j;
	NODE* node1 = NULL;
	NODE* node2 = NULL;
    for (i = 0; i < numberofLessons; i++) {
    	node1 = createNode(i);
        for (j = 0; j < numberofLessons; j++) {
        	if(i == 0){
            	node2 = createNode(j);
			}
            if(matris[i][j] == 1){    	
            	addEdge(graph,i,j,node1,node2);
	    	}
        }
    }
}
int* calculatetheInDegree(GRAPH* graph){
	int i;
	int *a = calloc(graph->numberofVertices,sizeof(int));
	for (i = 0; i < graph->numberofVertices; i++){
	    NODE* current = graph->adjList[i];
	    
	    while (current != NULL) {
	    	a[current->vertex]++;
	        current = current->next;
	    }
	}
	for(i=0;i<graph->numberofVertices;i++){
		printf("\nCourse-%d number of indegrees = %d ",i+1,a[i]);
	}
	return a;
}
int findmaxIndegree(int* a,int n){
	int i,max=0;
	for(i=0; i<n;i++){
		if(max<a[i]){
			max = i;
		}
	}
	return max;
}
void calculatetheTerms(GRAPH* graph,int* a){
	int max = findmaxIndegree(a,graph->numberofVertices);
	int i,j,termCount=1,control=0;
	printf("\n");
	while(a[max] > -1){
		printf("\n%d.Term = ",termCount);
		int *b = calloc(graph->numberofVertices,sizeof(int));
		for(i=0 ; i<graph->numberofVertices;i++){
			if(a[i]==0){
				printf(" Course-%d",i+1);
				a[i]--;
				b[i] = i;
			}
		}	
		max = findmaxIndegree(a,graph->numberofVertices);
		for(i=0 ; i<graph->numberofVertices;i++){
			
			if(b[i] == i ){
				if(i==0 && control==0){
					NODE* current = graph->adjList[i];
					while (current != NULL) {
						a[current->vertex]--;			
	       				current = current->next;
	    				}		
						control = 1;		
					
				}else if(i>0){
					NODE* current = graph->adjList[i];
					while (current != NULL) {
						a[current->vertex]--;			
	       				current = current->next;
	    				}		
					}

			}
		}
		
		termCount++;
	}
	printf("\n\nTotal number of terms = %d",termCount-1);
}
void printMatris(int** matris,int n){
	int i,j;
	printf("-Matrix- \n");
	for(i=0;i<n; i++){
		for(j=0 ; j<n ; j++){
			printf("%d ",matris[i][j]);
		}
		printf("\n");	
	}
}
