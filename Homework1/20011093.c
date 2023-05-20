#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Node{
	int number;
	struct Node *next;
	struct Node *prev;
		
}NODE;
void createNode(NODE**, int, int, int, int);
void repetitionControl(NODE**,NODE**,NODE**,int, int,int);
int specificNodeControl(NODE*,int,int);
int findTheKey(int,int,int);
void rotateTheWheel(NODE**,int);
int findTheCommonNumber(NODE**,NODE**,NODE**,int );
int findTheLocation(NODE**,int,int);
void printTheWheels(NODE**,NODE**,NODE**,int );
int main(){
	srand((int) time(0));
	int N, M, i, commonNumber, commonPlace, temp2, temp1,change2,change3, foundCommon,location1,location2,location3;
	NODE randNumber;
	printf("Enter the number of numbers to generate = ");
	scanf("%d",&N);
	printf("Enter the number of lockers = ");
	scanf("%d",&M);		
	
	while(N<(2*M)-1){	
		printf("\nYour inputs is not logical, please try again!\n");
		printf("Enter the number of numbers to generate = ");
		scanf("%d",&N);
		printf("Enter the number of lockers = ");
		scanf("%d",&M);		
	}
	NODE *head1 = NULL;
	NODE *head2 = NULL;
	NODE *head3 = NULL;
	
	commonNumber = (rand() % (N+1));

	commonPlace = rand() % M;
	temp2 = commonPlace;
	createNode(&head1,N,M,commonNumber,commonPlace); 
	
	commonPlace = rand() % M;
	while(temp2 == commonPlace){
		commonPlace = rand() % M;	
	}
	createNode(&head2,N,M,commonNumber,commonPlace);
	
	temp1=commonPlace;
	commonPlace = rand() % M;
	while(commonPlace == temp2 || commonPlace == temp1){
			commonPlace = rand() % M;
	}
	createNode(&head3,N,M,commonNumber,commonPlace);
	
	repetitionControl(&head1,&head2,&head3,commonNumber,M,N);

	printTheWheels(&head1,&head2,&head3,M);

	
	change2 = findTheKey(++temp2,++temp1,M);
	change3 = findTheKey(temp2,++commonPlace,M);
	
	foundCommon = findTheCommonNumber(&head1,&head2,&head3,M);
	printf("\n\nCommon Number = %d\n",foundCommon);
	
	location1 = findTheLocation(&head1,M,foundCommon);
	location2 = findTheLocation(&head2,M,foundCommon);
	location3 = findTheLocation(&head3,M,foundCommon);
	

	printf("\nPosition on the first wheel = %d",location1);
	printf("\nPosition on the second wheel = %d",location2);
	printf("\nPosition on the third wheel = %d",location3);
	

	rotateTheWheel(&head2,change2); 
	rotateTheWheel(&head3,change3);
	printf("\n\nDecrypted!\n");
	if(change2<0){
		printf("The second wheel has to rotate right %d time/times\n",abs(change2));
	}else{
		printf("The second wheel has to rotate left %d time/times\n",abs(change2));
	}
	if(change3<0){
		printf("The third wheel has to rotate right %d time/times\n",abs(change3));
	}else{
		printf("The third wheel has to rotate left %d time/times\n",abs(change3));
	}
	printTheWheels(&head1,&head2,&head3,M);
	
		
	return 0;
}
void createNode(NODE** head, int N, int M, int common,int commonPlace) {
    int i = 0;
    NODE* temp = NULL;

    while(i < M) {
        NODE* randNumber = (NODE*)malloc(sizeof(NODE));	
    	if(commonPlace == i){
    		randNumber->number = common;
    		randNumber->next = *head;
    		randNumber->prev = NULL;
    		if(*head != NULL){
    			(*head)->prev = randNumber;
			}	
    		*head = randNumber;
    		i++;

		}
		else{
		
	        randNumber->number = (rand() % (N + 1));
	        temp = *head;
	
	        // check if the number already exists in the list
	        int found = 0;
	        while(temp != NULL && !found) {
	            if(temp->number == randNumber->number || randNumber->number == common) {
	                found = 1;
	            }
	            temp = temp->next;
	        }
	        
	        if(!found && randNumber->number != common) {
	            // the number does not exist in the list, add the new node
	            randNumber->next = *head;
	            randNumber->prev = NULL;
	            if(*head != NULL){
	                (*head)->prev = randNumber;
	            }
	            *head = randNumber;
	            i++;
	       	 }
    	}
	}		
				NODE* last = *head;
				while(last->next != NULL){
				    last = last->next;
				} 
			
				(*head)->prev = last;
				last->next = *head;
	        
 //   printf("\n\n ---------------------------------\n\n");

}
void repetitionControl(NODE** head1, NODE** head2, NODE** head3, int commonNumber, int M,int N){
	int flag=0, i=0,j=0,k=0,l;
	NODE* first = *head1;
	NODE* second = *head2;
	NODE* third	= *head3;
	while(i<M){
		j=0;
		while(j<M){

			if(first->number == second->number && first->number != commonNumber){
				for(k=0;k<M;k++){
					if(first->number == third->number){
						flag=1;
	//					printf("\nbulunan ortak sayi = %d \n",first->number);
						do{
						third->number = (rand() % (N + 1));
						}while(third->number == first->number || specificNodeControl(third,third->number,M) == 1);									
					}
					third = third->next;
				}
			}
			second = second->next;
			j++;
		}
		first = first->next;
		i++;
	}
	
//	printf("flag %d",flag);
}
int specificNodeControl(NODE* head, int number,int M){
	int i,flag=0;
	NODE* temp = head;
	temp=temp->next;
	for(i=0;i<M-1;i++){
		if(number == temp->number){
			flag = 1;
//			printf("\n3.node da tekrarlananýn konumu = %d\n",i);
		}
		temp = temp->next;
	}
//	printf("spesifik fonksiyonu flagi= %d",flag);
	return flag;
}
int findTheKey(int place1 ,int place2or3,int M){
	int reverse ;
	if(place1>M/2){
		reverse = place1-M;
	}
	else{
		reverse=place1+M;
	}
	int temp1,temp2;
	//for third node
	temp1 = reverse-place2or3;
	temp2 = place1-place2or3;
	if(abs(temp1)<abs(temp2)){
		place2or3 = temp1;
	}else{
		place2or3 = temp2;
	}

	return place2or3;
}
void rotateTheWheel(NODE** head,int change){
	int i;
	if( change > 0 ){
		for(i=0;i<change;i++){
			(*head) = (*head)->next;
		}
	}else if( change < 0 ){
		for(i=0;i<abs(change);i++){
			(*head) = (*head)->prev;
		}
	}
}int findTheCommonNumber(NODE** head1,NODE** head2,NODE** head3,int M){
	int isFound=0, i=0,j=0,k=0,commonNumber;
	NODE* first = *head1;
	NODE* second = *head2;
	NODE* third	= *head3;
	while(i<M && isFound == 0){
		j=0;
		while(j<M && isFound == 0){
			k=0;
			if(first->number == second->number){
				while(k<M && isFound == 0){
					if(first->number == third->number){
							isFound=1;
							commonNumber = third->number;	
					}
					third = third->next;
					k++;
				}
			}
			second = second->next;
			j++;
		}
		first = first->next;
		i++;
	}	
	
	return commonNumber;
}int findTheLocation(NODE** head,int M,int number){
	NODE* temp = *head;
	int count=0,isFound = 0;
	while(!isFound){
		if(temp->number == number){
			isFound = 1;
		}
		count++;
		temp = temp->next;
	}
	return count;
}
void printTheWheels(NODE** head1,NODE** head2,NODE** head3,int M ){
	NODE* temp = *head1;
	int i;
	printf("\n1.Wheel -> ");
	
	for(i=0 ; i<M ;i++){
		printf("%d\t",temp->number);
		temp = temp->next;
	}
	
	printf("\n\n");
	printf("2.Wheel -> ");
    temp = *head2;
    
	for(i=0 ; i<M ;i++){
		printf("%d\t",temp->number);
		temp = temp->next;
	}
	
	printf("\n\n");
	temp = *head3;
	printf("3.Wheel -> ");
	
	for(i=0 ; i<M ;i++){
		printf("%d\t",temp->number);
		temp = temp->next;
	}
	
}
