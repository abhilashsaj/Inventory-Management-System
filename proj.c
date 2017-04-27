#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void clrscr()
{
    system("@cls||clear");
}


typedef struct date
{
	int day;
	int month;
	int year;
}date;


typedef struct item
{
	int prodno;
	char prodname[30];
	int qty;
	float price;
	date mfg;
	date exp;
	char type[100];
}item;


void menu();
void add();
int checkprodno(int prodno, int count);
void checkdate(int day,int month,int year);


void view();
void viewoption();
void sortalphabetically();
void sortprodno();


void deletemenu();
void delprodno();
void delname();
void deldate();


int search(item ptr[],int pno,int count);
int searchname(item ptr[],char *pname,int count);
int dateloc(item product[],int day,int month,int year, int count);


void modifyprice();
void modifylist();
void modifyqty();


int main()
{
	printf("\t\tWelcome to ABHI'S INVENTORY MANAGEMENT SYSTEM\n\n");
	menu();
}


void menu()
{
	
	int choice;
	printf("\n");
	printf("\nEnter option\n\n");
	printf("1.Add Product\n");
	printf("2.Delete Product\n");
	printf("3.Modify Product\n");
	printf("4.View products\n");
	printf("5.Exit");
	printf("\n\nEnter Choice\n");
	scanf("%d",&choice);	
	
	switch(choice)
	{
		case 1: add();
		break;
		case 2: deletemenu();
		break;
		case 3: modifylist();
		break;
		case 4:	viewoption();
		break;
		case 5: exit(0);
		break;
		default:
		printf("Invalid Choice!!!");
		menu();
		
	}
	
}


void viewoption()
{
	clrscr();
	
	int option;
	FILE *counter=fopen("counter.dat","r");
	int count;
	fscanf(counter,"%d",&count);
	printf("\n\t\tTotal number of items in inventory: %d\n",count);
	
	printf("\n1. View items by product number");
	printf("\n2. View items alphabetically ");
	printf("\n3. View items by last added");		
	printf("\n\nEnter option: ");		
	scanf("%d",&option);
	
	switch(option)
	{
		case 1: sortprodno();
		break;
		case 2: sortalphabetically();
		break;
		case 3: view();
		break;
		default: menu();
	
	}
	
}


void add()
{
	item product;
	char ch;
	FILE *fp=fopen("records.bin","ab4");
	
	FILE *counterr=fopen("counter.dat","r");
	int count;
	fscanf(counterr,"%d",&count);
	
	
	/*
	printf("%d",count);

	//printf("Enter Product no: ");
	//scanf("%d",&product.prodno);
	*/
	
	/*
	while (fread(&product,sizeof (item),1,fp))
	{
		count++;
	}
	*/
	
	product.prodno=1000+count;
	product.prodno=checkprodno(product.prodno,count);
	
	printf("Enter Product Name: ");
	scanf("%s",product.prodname);
	printf("Enter Quantity: ");
	scanf("%d",&product.qty);
	printf("Enter Price: ");
	scanf("%f",&product.price);
	printf("Enter manufacturing date of item: (dd/mm/yyyy) \n");
	scanf("%d/%d/%d",&product.mfg.day,&product.mfg.month,&product.mfg.year);
	checkdate(product.mfg.day,product.mfg.month,product.mfg.year);
	printf("Enter expiration date of item: (dd/mm/yyyy) \n");
	scanf("%d/%d/%d",&product.exp.day,&product.exp.month,&product.exp.year);
	checkdate(product.exp.day,product.exp.month,product.exp.year);
	printf("Enter type of item: (veg/fruit/gen) \n");
	scanf("%s",product.type);
	
		
	fclose(counterr);
	count++;
	
	FILE *counterw=fopen("counter.dat","w");
	fprintf(counterw,"%d",count);
	fclose(counterw);

	
	fwrite(&product, sizeof(item), 1, fp);
	fclose(fp);
	
	
	printf("\n\nDo you want to add more items? [Y/N]\n");
	getchar();
	scanf("%c",&ch);
	if(ch=='Y'||ch=='y')
	{
		add();
	}
	else 
	{
		printf("\n\nWould you like to go back to the menu? [Y/N]\n");
		getchar();
		scanf("%c",&ch);
		
		if(ch=='Y'||ch=='y')
		{
			menu();
		}
		
		else 
		{
			exit(0);
		}
		
	}
	
}


int checkprodno(int prodno, int count)
{
	item product[100]; 
	FILE *fp=fopen("records.bin","rb");
	fread(&product, sizeof(product), 1, fp);

	for(int i=0;i<count;i++)
	{
		if(prodno==product[i].prodno)
		{
			return prodno+100;
		}
	
	}
	
	return prodno;
	
	/*
	if(flag==0)
	{
		char ch;
		printf("\n\tSorry, the product number you inserted already exist");
		printf("\n\nWould you like to try again with another product number? [Y/N]\n");
		getchar();
		scanf("%c",&ch);
		if(ch=='Y'||ch=='y')
		{
			add();
		}
		else 
		{
			menu();
		}
	}
	*/
	
}


void view()
{
	item product[100]; 
	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");
	
	int count=0;
	
	
	fscanf(counter,"%d",&count);
	fread(&product, sizeof(product), 1, fp);
	fclose(fp);
	
	/*
	while (fread(&product,sizeof (item),1,fp))
	{
		count++;
	}
	*/
	
	printf("\n -----------------------------------------------------------------------------------------------------------");
	printf("\n|   Product no   |   Product Name   |   Stock   |    Price   |    Mfg date   |    Exp date    |     Type    |" );
	printf("\n -----------------------------------------------------------------------------------------------------------");
	
	for(int i=0;i<count;i++)
	{
		printf("\n|   %10d   |   ",product[i].prodno);
		printf("%12s   |   ",product[i].prodname);
		printf("%5d   |   ",product[i].qty);
		printf("%.2f    |   ",product[i].price);
		printf("%2d/%2d/%2d  |   ",product[i].mfg.day,product[i].mfg.month,product[i].mfg.year);
		printf("%2d/%2d/%2d   |   ",product[i].exp.day,product[i].exp.month,product[i].exp.year);
		printf("%5s     |",product[i].type);
	}
	
	printf("\n -----------------------------------------------------------------------------------------------------------");
	
	char ch;
	printf("\n\nWould you like to go back to the menu? [Y/N]\n");
	getchar();
	scanf("%c",&ch);
	
	if(ch=='Y'||ch=='y')
	{
		menu();
	}
	
	else 
	{
		exit(0);
	}
	
}


void sortprodno()
{
	item product[100]; 
	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");
	
	int count;
	fscanf(counter,"%d",&count);
	
	fread(&product, sizeof(product), 1, fp);
	
	int j=0;
	for(int i=0;i<count;i++)
	{
		for(j=i+1;j<count;j++)
		{
			if(product[i].prodno>product[j].prodno)
			{
				item temp=product[i];
				product[i]=product[j];
				product[j]=temp;
			}
				
		}
	
	}

	
	printf("\n -----------------------------------------------------------------------------------------------------------");
	printf("\n|   Product no   |   Product Name   |   Stock   |    Price   |    Mfg date   |    Exp date    |     Type    |" );
	printf("\n -----------------------------------------------------------------------------------------------------------");
	
	for(int i=0;i<count;i++)
	{
		printf("\n|   %10d   |   ",product[i].prodno);
		printf("%12s   |   ",product[i].prodname);
		printf("%5d   |   ",product[i].qty);
		printf("%.2f    |   ",product[i].price);
		printf("%2d/%2d/%2d  |   ",product[i].mfg.day,product[i].mfg.month,product[i].mfg.year);
		printf("%2d/%2d/%2d   |   ",product[i].exp.day,product[i].exp.month,product[i].exp.year);
		printf("%5s     |",product[i].type);
	}
	
	printf("\n -----------------------------------------------------------------------------------------------------------");		
	
	char ch;
	fclose(fp);
	printf("\n\nWould you like to go back to the menu? [Y/N]\n");
	getchar();
	scanf("%c",&ch);
	
	if(ch=='Y'||ch=='y')
	{
		clrscr();
		menu();
	}
	
	else 
	{
		exit(0);
	}
	
}


void checkdate(int day,int month,int year)
{
	if( (day>30 && month == (  2 || 4 || 6 || 9 ||  11 )))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		add();
	}
	
	if( (day>31 && month == (  1 || 2 || 3 || 5 || 7 ||  8 ||  10 ||  12 )))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		add();
	}
	
	if( (day>29 && month == 2))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		add();
	}
	
	if (year<0 || year>2500)
	{
		printf("\nInvalid date\nPlease enter details again\n");
		add();
	}
	
	if (month<1 || month>12)
	{
		printf("\nInvalid date\nPlease enter details again");
		add();
	}

}


void sortalphabetically()
{
	item product[100]; 
	
	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");
	
	int count;
	fscanf(counter,"%d",&count);
	
	fread(&product, sizeof(product), 1, fp);
	
	int j;
	for(int i=0;i<count;i++)
	{
		for(j=i+1;j<count;j++)
		{
			if(strcmp(product[i].prodname,product[j].prodname)>0)
			{
				item temp=product[i];
				product[i]=product[j];
				product[j]=temp;
			}
				
		}
		
	}

	
	printf("\n -----------------------------------------------------------------------------------------------------------");
	printf("\n|   Product no   |   Product Name   |   Stock   |    Price   |    Mfg date   |    Exp date    |     Type    |" );
	printf("\n -----------------------------------------------------------------------------------------------------------");
	
	for(int i=0;i<count;i++)
	{
		printf("\n|   %10d   |   ",product[i].prodno);
		printf("%12s   |   ",product[i].prodname);
		printf("%5d   |   ",product[i].qty);
		printf("%.2f    |   ",product[i].price);
		printf("%2d/%2d/%2d  |   ",product[i].mfg.day,product[i].mfg.month,product[i].mfg.year);
		printf("%2d/%2d/%2d   |   ",product[i].exp.day,product[i].exp.month,product[i].exp.year);
		printf("%5s     |",product[i].type);
	}
	printf("\n -----------------------------------------------------------------------------------------------------------");
	
	fclose(fp);
	
	char ch;
	printf("\n\nWould you like to go back to the menu? [Y/N]\n");
	getchar();
	scanf("%c",&ch);
	
	if(ch=='Y'||ch=='y')
	{
		clrscr();
		menu();
	}
	
	else 
	{
		exit(0);
	}
	
}


void deletemenu()
{
	clrscr();
	
	int choice;
	
	printf("\nHow would you like to delete items?");
	printf("\n\t1. Product Number");
	printf("\n\t2. Itemname");
	printf("\n\t3. Remove Expired Goods");
	
	printf("\n\nEnter choice: ");
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 1: delprodno();
		break;
		case 2: delname();
		break;
		
		case 3: deldate();
		break;
		default: 
		printf("\nInvalid Choice");
	}
	
}


void delprodno()
{
	item product[100]; 
	int location;
	
	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");
	
	int count;
	fscanf(counter,"%d",&count);
	
	fread(&product, sizeof(product), 1, fp);
	
	printf("\nEnter Product number of item to be deleted: ");
	int prodno;
	scanf("%d",&prodno);
	
	location=search(product,prodno,count);
	int i;
	if(location!=-1)
	{
		for(i=location;i<count-1;i++)
		{
			product[i]=product[i+1];
		}
		count--;
		printf("Record has been succesfully deleted\n");	

		fclose(counter);
		
		FILE *counterw=fopen("counter.dat","w");
		fprintf(counterw,"%d",count);
		fclose(counterw);
		
		printf("\n -----------------------------------------------------------------------------------------------------------");
		printf("\n|   Product no   |   Product Name   |   Stock   |    Price   |    Mfg date   |    Exp date    |     Type    |" );
		printf("\n -----------------------------------------------------------------------------------------------------------");
		
		for(int i=0;i<count;i++)
		{
			printf("\n|   %10d   |   ",product[i].prodno);
			printf("%12s   |   ",product[i].prodname);
			printf("%5d   |   ",product[i].qty);
			printf("%.2f    |   ",product[i].price);
			printf("%2d/%2d/%2d  |   ",product[i].mfg.day,product[i].mfg.month,product[i].mfg.year);
			printf("%2d/%2d/%2d   |   ",product[i].exp.day,product[i].exp.month,product[i].exp.year);
			printf("%5s     |",product[i].type);
		}
		
		printf("\n -----------------------------------------------------------------------------------------------------------");		
		
		/*FILE *fp2=fopen("records2.bin","wb");
		fwrite(&product, sizeof(item), 1, fp2);
		remove("record.bin");
		rename("record1.bin","record.bin");
		fclose(fp2);
		*/
		
		FILE *fp2=fopen("records1.bin","wb");
		fwrite(&product, sizeof(item), count, fp2);
		remove("records.bin");
		rename("records1.bin","records.bin");
		fclose(fp2);
		
		getchar();
		char ch;
		printf("\nDo you want to delete more records? [Y/N] ");
		scanf("%c",&ch);
		
		if(ch=='y'|| ch=='Y')
		{
			delprodno();
		}
		
		else
		{
			menu();
		}
		
	}
	
	if(location==-1)
		{
			
			printf("We are sorry the item your looking for is not found\n\n");
			char ch;
			printf("\n\nWould you like to go back to the menu? [Y/N]\n");
			getchar();
			scanf("%c",&ch);
			
			if(ch=='Y'||ch=='y')
			{
				clrscr();
				menu();
			}
			else 
			{
				exit(0);
			}
			
		}

}


int search(item ptr[],int pno,int count) 
{
	int i;
	for(i=0;i<count;i++)
	{
		if(pno==ptr[i].prodno)
		{
			return i;
			
		}
		
	}
	return -1;
	
}

	
	
void delname()
{
	item product[100]; 
	int location;
	
	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");
	
	int count;
	char pname[100];
	
	fscanf(counter,"%d",&count);
	fclose(counter);
	
	fread(&product, sizeof(product), 1, fp);
	
	printf("\nEnter name of item to be deleted: ");
	scanf("%s",pname);
	
	location=searchname(product,pname,count);
	int i;
	if(location!=-1)
	{
	
		for(i=location;i<count-1;i++)
		{
			product[i]=product[i+1];
		
		}
		count--;	
	
		printf("Record has been succesfully deleted\n");
		printf("\n -----------------------------------------------------------------------------------------------------------");
		printf("\n|   Product no   |   Product Name   |   Stock   |    Price   |    Mfg date   |    Exp date    |     Type    |" );
		printf("\n -----------------------------------------------------------------------------------------------------------");
		
		for(int i=0;i<count;i++)
		{
			printf("\n|   %10d   |   ",product[i].prodno);
			printf("%12s   |   ",product[i].prodname);
			printf("%5d   |   ",product[i].qty);
			printf("%.2f    |   ",product[i].price);
			printf("%2d/%2d/%2d  |   ",product[i].mfg.day,product[i].mfg.month,product[i].mfg.year);
			printf("%2d/%2d/%2d   |   ",product[i].exp.day,product[i].exp.month,product[i].exp.year);
			printf("%5s     |",product[i].type);
		}
		
		printf("\n -----------------------------------------------------------------------------------------------------------");		
		
		/*FILE *fp2=fopen("records2.bin","wb");
		fwrite(&product, sizeof(item), 1, fp2);
		remove("record.bin");
		rename("record1.bin","record.bin");
		fclose(fp2);
		*/
		
		FILE *fp2=fopen("records1.bin","wb");
		fwrite(&product, sizeof(item), count, fp2);
		remove("records.bin");
		rename("records1.bin","records.bin");
		fclose(fp2);
			
		FILE *counterw=fopen("counter.dat","w");
		fprintf(counterw,"%d",count);
		fclose(counterw);
		
		getchar();
		char ch;
		printf("\nDo you want to delete more records? [Y/N] ");
		scanf("%c",&ch);
		
		if(ch=='y'|| ch=='Y')
		{
			delprodno();
		}
		
		else
		{
			
			menu();
		}
		
	}
	
	if(location==-1)
		{
			printf("We are sorry the item your looking for is not found\n\n");
			char ch;
			printf("\n\nWould you like to go back to the menu? [Y/N]\n");
			getchar();
			scanf("%c",&ch);
		
			if(ch=='Y'||ch=='y')
			{
				clrscr();
				menu();
			}
		
			else 
			{
				exit(0);
			}
		
		}

} 

	
int searchname(item ptr[],char *pname,int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		if(strcmp(pname,ptr[i].prodname)==0)
		{
			return i;
			
		}

	}
	return -1;
	
}


void deldate()
{
	item product[100]; 
	int location=0;

	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");

	int count;
	fscanf(counter,"%d",&count);
	fread(&product, sizeof(product), 1, fp);
	fclose(counter);
	
	date d;
	printf("Enter current date(dd/mm/yyyy)\n");
	scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	
	if( (d.day>30 && d.month == (  2 || 4 || 6 || 9 ||  11 )))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	}

	if( (d.day>31 && d.month == (  1 || 2 || 3 || 5 || 7 ||  8 ||  10 ||  12 )))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	}

	if( (d.day>29 && d.month == 2))
	{
		printf("\nInvalid date\nPlease enter details again\n");
		scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	}

	if (d.year<0 || d.year>2500)
	{
		printf("\nInvalid date\nPlease enter details again\n");
		scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	}

	if (d.month<1 || d.month>12)
	{
		printf("\nInvalid date\nPlease enter details again");
		scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	}
	

	printf("\nDeleted item list\n");

	while(1)
	{
		location=dateloc(product,d.day,d.month,d.year,count);
		if(location!=-1)
		{
			for(int i=location;i<count;i++)
			{
				printf("Product Number: %d   |    Product name: %s\n",product[i].prodno,product[i].prodname);
				product[i]=product[i+1];
				count--;
				
			}
			
			FILE *counterw=fopen("counter.dat","w");
			fprintf(counterw,"%d",count);
			fclose(counterw);
			
			FILE *fp=fopen("records.bin","wb");
			fwrite(&product, sizeof(item), 1, fp);
			fclose(fp);
		
		}
		
		if(location==-1)
		{
			printf("\nThere are no more expired items in the inventory\n\n");
			char ch;
			printf("\n\nWould you like to go back to the menu? [Y/N]\n");
			getchar();
			scanf("%c",&ch);
		
			if(ch=='Y'||ch=='y')
			{
				clrscr();
				menu();
			}
		
			else 
			{
				exit(0);
			}
		
		}
	
	}

}	
	


int dateloc(item product[],int day,int month,int year, int count)
{
	int i;

	for(i=0;i<count;i++)
	{
		if(year>product[i].exp.year)
		{
			return i;
		}
		
		else if(year==product[i].exp.year && month>product[i].exp.month)
		{
			return i;
		}
		
		else if(year==product[i].exp.year && month==product[i].exp.month && day>product[i].exp.day)
		{
			return i;
		}
		
	}

	return -1;

}


void modifylist()
{
	printf("\nOptions\n");
	printf("\n\t1. Update Price");
	printf("\n\t2. Update Quantity");
	printf("\n\nEnter choice\n");
	int choice; 
	scanf("%d",&choice);

	switch (choice)
	{
		case 1: modifyprice();
		break; 

		case 2: modifyqty();
		break;

		default: printf("\nInvalid choice!!");
		modifylist();
				
	}
	
}


void modifyprice()
{
	item product[100];
	int pno; 

	FILE *fp=fopen("records.bin","rb");
	fread(&product, sizeof(product),1,fp);
	
	FILE *counter=fopen("counter.dat","r");
	int count;
	fscanf(counter,"%d",&count);
	fclose(counter);
	
	printf("\nEnter product number of item to be modified: ");
	scanf("%d",&pno); 

	int price; 
	printf("\nEnter new price: ");
	scanf("%d",&price); 
	
	int i;
	int flag=0;
    for(i=0;i<count;i++)
    {
    	
    	if(product[i].prodno==pno)
    	{
    		flag=1;
    		
    		product[i].price=price;
    		printf("\n\nPrice updated\n");
    		break;
    	}
    	
    }
    
    if (flag==1)
    {
		FILE *fp2=fopen("records1.bin","wb");
		fwrite(&product, sizeof(item), count, fp2);
		remove("records.bin");
		rename("records1.bin","records.bin");
		fclose(fp2);
		
		char ch;
		printf("\n\nDo you want to modify more records? [Y/N]\n ");
		getchar();
		scanf("%c",&ch);
		
		if(ch=='y'|| ch=='Y')
		{
			modifyprice();
		}
		
		else
		{
			char ch;
			printf("\nWould you like to go back to menu? [Y/N]\n ");
			getchar();
			scanf("%c",&ch);	
		
			if(ch=='y'|| ch=='Y')
			{
				menu();
			}
		
			else
			{
				exit(0);
			}
		
		}

		
    }
    
    else
    {
		printf("\n\nEntered item not found!\n");
		char ch;
		printf("\nDo you want to try again? [Y/N] ");
		scanf("%c",&ch);
		
		if(ch=='y'|| ch=='Y')
		{
			modifyprice();
		}
		
		else
		{
			menu();
		}
		
	}
		
		
}
    
    
void modifyqty()
{
	item product[100];
	int pno; 
	FILE *fp=fopen("records.bin","rb");
	fread(&product, sizeof(product),1,fp);
	
	FILE *counter=fopen("counter.dat","r");
	int count;
	fscanf(counter,"%d",&count);
	fclose(counter);
	
	printf("\nEnter product number of item to be modified\n");
	scanf("%d",&pno); 
	int qty; 
	printf("\nEnter new Quantity\n");
	scanf("%d",&qty); 
	
	int i;
	int flag=0;
    for(i=0;i<count;i++)
    {
    	
    	if(product[i].prodno==pno)
    	{
    		flag=1;
    		product[i].qty=qty;
    		printf("\n\tQuantity updated\n");
    		break;
    	}
    	
    }
    
    if (flag==1)
    {
		FILE *fp2=fopen("records1.bin","wb");
		fwrite(&product, sizeof(item), count, fp2);
		remove("records.bin");
		rename("records1.bin","records.bin");
		fclose(fp2);
		
		char ch;
		printf("\nDo you want to modify more records? [Y/N] \n");
		getchar();
		scanf("%c",&ch);
		if(ch=='y'|| ch=='Y')
		{
			modifyprice();
		}
		
		else
		{
			char ch;
			printf("\nWould you like to go back to menu? [Y/N] \n");
			getchar();
			scanf("%c",&ch);	
		
			if(ch=='y'|| ch=='Y')
			{
				menu();
			}
		
			else
			{
				exit(0);
			}
		
		}

		
    }
    
    else
    {
		printf("\n\nEntered item not found!\n");
		char ch;
		printf("\nDo you want to try again? [Y/N] \n");
		scanf("%c",&ch);
		
		if(ch=='y'|| ch=='Y')
		{
			modifyprice();
		}
		
		else
		{
			char ch;
			printf("\nWould you like to go back to menu? [Y/N] \n");
			scanf("%c",&ch);	
		
			if(ch=='y'|| ch=='Y')
			{
				menu();
			}
		
			else
			{
				exit(0);
			}
			
		}
	
	}
				
}
