#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//use this sample data below to test it out (uncomment it then copy)
//1
//orange
//1000
//1
//1
//avocado
//2000
//4
//1
//papaya
//6000
//2

struct Item{
	char itemName[100];
	int itemPrice;
	int itemQty;
};

typedef struct Item list;

void addMenu(struct Item *list, int *i);

void removeMenu(struct Item *list, int* i);

void viewMenu(struct Item *list);

void storeMenu(struct Item *list);

void searchMenu(struct Item *list, int i);

void calculateMenu(struct Item *list, int i);

void readFileMenu();

void mergeSort(struct Item *list, int left, int right);

void merge(struct Item *list, int left, int mid, int right);

int binarySearch(struct Item *list, char name[], int left, int right);

int main(){
	int choice = -1, i = 0;
	list shop[100];
	
	for(int k=0; k<100; k++){
		strcpy(shop[k].itemName, "Empty");
		shop[k].itemPrice = shop[k].itemQty = 0;
	}
	do{
		puts("Shopping Cart Program");
		puts("1. Add Item");
		puts("2. Remove Item");
		puts("3. View List");
		puts("4. Store Item");
		puts("5. Search Item");
		puts("6. Calculate Cost");
		puts("7. Read Stored Item");
		puts("8. Sort Item");
		puts("9. Exit");
		printf("Pick a menu >> ");
		scanf("%d", &choice);
		getchar();
		switch(choice){
			case 1:{
				addMenu(shop, &i);
				break;
}
			case 2:{
				removeMenu(shop, &i);
				break;
			}
			case 3:{
				viewMenu(shop);
				break;
			}
			case 4:{
				storeMenu(shop);
			}
			case 5:{
				searchMenu(shop, i);
				break;
			}
			case 6:{
				calculateMenu(shop, i);
				break;
			}
			case 7:{
				readFileMenu();
				break;
			}
			case 8:{
				mergeSort(shop, 0, i-1);
				break;
			}
			case 9:
				puts("Terimakasih telah menggunakan aplikasi ini");
				break;
		}
	}while(choice != 9);
	
	return 0;
}


void addMenu(list *shop, int *i){
	char name[100];
	int price;
	int qty;
	int len;
	do{
		printf("Input Item Name [6-35 character]: ");
		scanf("%[^\n]", name);
		len = strlen(name);
		getchar();
	}while(len < 6 || len > 35);
	
	do{
		printf("Input Item price [1000 - 100000]: ");
		scanf("%d", &price);
		getchar();
	}while(price < 1000 || price > 100000);
	
	do{
		printf("Input Item price [1 - 10]: ");
		scanf("%d", &qty);
		getchar();
	}while(qty < 1 || qty > 10);
	
	strcpy(shop[*(i)].itemName, name);
	shop[*(i)].itemPrice = price;
	shop[*(i)].itemQty = qty;
	
	*(i) += 1;
}

//menu remove

void removeMenu(list *shop, int* i){
	char name[100];
				int loc = -1;
	
				do{
					printf("Input Item Name [6-35 character]: ");
		scanf("%[^\n]", name);
		getchar();
	}while(strlen(name) < 6 && strlen(name) > 35);
	
	loc = binarySearch(shop, name, 0, *i);//searchItem(shop, 0, i+1, name);//
	
	if(loc == -1){
		puts("Item not available in list!");
	}
	else{
		strcpy(shop[loc].itemName, "Empty");
		shop[loc].itemPrice = shop[loc].itemQty = 0;

		if(strcmp(shop[*(i)-1].itemName, "Empty") != 0){ //for replacing if the deleted item is in the from or the middle
			strcpy(shop[loc].itemName, shop[*(i)-1].itemName);
			shop[loc].itemPrice = shop[*(i)-1].itemPrice;
			shop[loc].itemQty = shop[*(i)-1].itemQty;
			strcpy(shop[*(i)-1].itemName, "Empty");
		shop[*(i)-1].itemPrice = shop[*(i)-1].itemQty = 0;
			puts("Item successfully replaced");
		}
		*(i) -= 1;
	}
	
}

//---------------------------------------------------


//menu view

void viewMenu(list *shop){
		for(int j=0; j<100; j++){
			printf("element %d: %s %d %d\n", j+1, shop[j].itemName, shop[j].itemPrice, shop[j].itemQty);
		}
}

//------------------------------------------

//menu store

void storeMenu(list *shop){
	FILE *fptr;
	fptr = fopen("shoppinglist.txt", "w");
				if(fptr == NULL){
					puts("Error in opening file !");
					exit(1);
				}
				for(int k=0; k<100; k++){
					fprintf(fptr, "%s,%d,%d\n", shop[k].itemName, shop[k].itemPrice, shop[k].itemQty);
				}
				fclose(fptr);
				puts("shopping list has been stored");
}


//-----------------------------------------

//menu search

void searchMenu(list *shop, int i){
			char name[100];
				scanf("%[^\n]", &name);
				getchar();
				int loc = binarySearch(shop, name, 0, i);
				if(loc == -1) puts("Name not available");
				else printf("%s is at index %d\n", name, loc);
}


//-------------------------------------------

//calculate menu

void calculateMenu(struct Item *list, int i){
	int sumCost = 0, sumItem = 0, sumArr[i];
	puts("====================================");
	for(int j=0; j<i; j++){
		puts("====================================");
		sumArr[j] = list[j].itemPrice * list[j].itemQty;
		printf("Element %d : %d\n", j+1, sumArr[j]);
		sumCost += sumArr[j];
		sumItem += list[j].itemQty;
	}
	printf("Total cost = %d\nTotal Item = %d\n", sumCost, sumItem);
	puts("====================================");
}

// track shoppinglist menu

void readFileMenu(){
	char name[100];
	int price;
	int qty;
	int size, i = 0;
	FILE *fptr;
	fptr = fopen("shoppinglist.txt", "r");
		if(fptr == NULL){
			puts("Error in opening file !");
			exit(1);
		}
	while(!feof(fptr)){
		fscanf(fptr, "%[^,],%d,%d\n", name, &price, &qty);
		size++;
		printf("Element %d : %s %d %d\n", i+1, name, price, qty);
		i++;
	}			
	fclose(fptr);
}

//mergesort

void mergeSort(list *shop, int left, int right){
	
	if(left < right){
		int mid = (left + (right-1)) / 2;
//		printf("mid skrng = %d\n", mid);
		mergeSort(shop, left, mid);
		mergeSort(shop, mid+1, right);
		merge(shop, left, mid, right);
	}
}

void merge(list *shop, int left, int mid, int right){
	int n = (right-left+1);
	list tempList[n];
	int i,j,k;
	i = left;
	j = mid+1;
	k = 0;
	
	while(i<=mid && j<=right){
		if(strcmp(shop[i].itemName/*->itemName*/, shop[j]/*->*/.itemName) < 0/*shop[i].itemPrice < shop[j].itemPrice*//**/ /*&& ((strcmp(list[i].itemName, "Empty") != 0) || (strcmp(list[j].itemName, "Empty")))*/){
			strcpy(tempList[k]/**/.itemName, shop[i]/**/.itemName);
			tempList[k].itemPrice = shop[i]/*->*/.itemPrice;
			tempList[k].itemQty = shop[i]/*->*/.itemQty;
//			printf("templist ke %d diassign data i = %d :\n", k, i);
//			printf("%s\n", tempList[k]/**/.itemName);
//			printf("%d\n", tempList[k].itemPrice);
//			printf("%d\n", tempList[k].itemQty);
//			printf("%s\n", shop[i]/**/.itemName);
//			printf("%d\n", shop[i]/*->*/.itemPrice);
//			printf("%d\n", shop[i]/*->*/.itemQty);
			k++;
			i++;
		}
		else/*(strcmp(list[i].itemName, list[j].itemName) > 0 && ((strcmp(list[i].itemName, "Empty") != 0) && (strcmp(list[j].itemName, "Empty"))))*/{
			strcpy(tempList[k].itemName, shop[j]/*->*/.itemName);
			tempList[k].itemPrice = shop[j]/*->*/.itemPrice;
			tempList[k].itemQty = shop[j]/*->*/.itemQty;
//			printf("templist ke %d diassign data j = %d : \n", k, j);
//			printf("%s\n", tempList[k]/**/.itemName);
//			printf("%d\n", tempList[k].itemPrice);
//			printf("%d\n", tempList[k].itemQty);
//			printf("%s\n", shop[j]/**/.itemName);
//			printf("%d\n", shop[j]/*->*/.itemPrice);
//			printf("%d\n", shop[j]/*->*/.itemQty);
			k++;
			j++;
		}
	}
	
	while(i<=mid){
//		strcpy(tempList[k].itemName, list[i].itemName);
			strcpy(tempList[k].itemName, shop[i]/*->*/.itemName);
			tempList[k].itemPrice = shop[i]/*->*/.itemPrice;
			tempList[k].itemQty = shop[i]/*->*/.itemQty;
//			printf("templist ke %d diappend data sisaan i dimana i = %d:\n", k, i);
//			printf("%s\n", tempList[k]/**/.itemName);
//			printf("%d\n", tempList[k].itemPrice);
//			printf("%d\n", tempList[k].itemQty);
//			printf("%s\n", shop[i]/**/.itemName);
//			printf("%d\n", shop[i]/*->*/.itemPrice);
//			printf("%d\n", shop[i]/*->*/.itemQty);
			k++;
			i++;
	}
	while(j<=right){
			strcpy(tempList[k].itemName, shop[j]/*->*/.itemName);
			tempList[k].itemPrice = shop[j]/*->*/.itemPrice;
			tempList[k].itemQty = shop[j]/*->*/.itemQty;
			printf("templist ke %d diappend data sisaan j dimana j = %d:\n", k, j);
			printf("%s\n", tempList[k]/**/.itemName);
			printf("%d\n", tempList[k].itemPrice);
			printf("%d\n", tempList[k].itemQty);
//			printf("%s\n", shop[j]/**/.itemName);
//			printf("%d\n", shop[j]/*->*/.itemPrice);
//			printf("%d\n", shop[j]/*->*/.itemQty);
			k++;
			j++;
	}
	
	int ind = 0;
//	for(;ind < right; ind++)
//		printf("%s %d %d\n", )
	for(int i = left; i<=mid; i++){
			strcpy(shop[i].itemName/*->*/, tempList[ind].itemName);
			shop[i]/*->*/.itemPrice = tempList[ind].itemPrice;
			shop[i]/*->*/.itemQty = tempList[ind].itemQty;
//			printf("shoplist ke %d diappend data ke %d:\n",i, ind);
//			printf("%s\n", tempList[ind]/**/.itemName);
//			printf("%d\n", tempList[ind].itemPrice);
//			printf("%d\n", tempList[ind].itemQty);
//			printf("%s\n", shop[i]/**/.itemName);
//			printf("%d\n", shop[i]/*->*/.itemPrice);
//			printf("%d\n", shop[i]/*->*/.itemQty);
			ind++;
	}
	
	for(int j=mid+1; j<=right; j++){
		strcpy(shop[j]/*->*/.itemName, tempList[ind].itemName);
		shop[j]/*->*/.itemPrice = tempList[ind].itemPrice;
		shop[j]/*->*/.itemQty = tempList[ind].itemQty;
//		printf("shoplist ke %d diappend data ke %d:\n", j, ind);
//		printf("%s\n", tempList[ind]/**/.itemName);
//			printf("%d\n", tempList[ind].itemPrice);
//			printf("%d\n", tempList[ind].itemQty);
//			printf("%s\n", shop[j]/**/.itemName);
//			printf("%d\n", shop[j]/*->*/.itemPrice);
//			printf("%d\n", shop[j]/*->*/.itemQty);
		ind++;
	}
}

//-------------------------------------------------------

//int linearSearch(struct Item *list, char* name){
//	for(int k=0; k<100; k++){
//		if(strcmp(list[k].itemName, name) == 0){
//			printf("%d\n", k);
//			return k;
//		} 
//	}
//	return -1;
//}


//binary search
int binarySearch(list *shop, char name[], int left, int right){
	if(left<right){
		int mid = (left + (right-1))/2;
//		printf("mid = %d\n", mid);
//		printf("string value %s and %s = %d\n", shop[mid].itemName, name, strcmp( name, shop[mid].itemName));
		if(strcmp(name, shop[mid].itemName) == 0) return mid;
		else if(strcmp(shop[mid].itemName, name) < 0) return binarySearch(shop, name, mid+1, right);
		else if(strcmp(shop[mid].itemName, name) > 0) return binarySearch(shop, name, left, mid);
	}
	return -1;
}
