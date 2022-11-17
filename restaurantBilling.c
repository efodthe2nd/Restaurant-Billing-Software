#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// functions to generate bills
struct items{
	char item[20];
	float price;
	int qty;
};

struct orders{
	char customer[50];
	char date[50];
	int numOfItems;
	struct items itm[50];
};

void generateBillHeader(char name[50], char date[30])
{
	printf("\n\n");
		printf("\t	ADV. Restuarant");
		printf("\n\t	------------------");
		printf("\nDate:%s", date);
		printf("\nInvoice To: %s", name);
		printf("\n");
		printf("------------------------------------\n");
		printf("Items\t\t");
		printf("Qty\t\t");
		printf("Total\t\t");
		printf("\n-----------------------------------");
		printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price)
{
		printf("%s\t\t", item);
		printf("%d\t\t", qty);
		printf("% .2f\t\t", qty * price);
		printf("\n");
}

void generateBillFooter(float total)
{
	printf("\n");
	float dis = 0.1 * total;
	float netTotal = total - dis;
	float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst;
	printf("------------------------------------------\n");
	printf("Sub Total\t\t\t%.2f", total);
	printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
	printf("\n\t\t\t\t------");
	printf("\nNet Total\t\t\t%.2f", netTotal);
	printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
	printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
	printf("\n----------------------------------------");
	printf("\nGrand Total\t\t\t%.2f",grandTotal);
	printf("\n---------------------------------------\n");
}

void main()
{
	float total, tot;
	int opt, i, j, k, l, n, invoiceFound;
	struct orders ord;
	struct orders order;
	char saveBill = 'y', contFlag = 'y';
	char name[50];
	FILE *fp;

	//dashboard
	while (contFlag == 'y')
	{
		system("clear");
		total = 0;
		invoiceFound = 0;
	printf("\t============ADV, RESTUARANT=============");
	printf("\n\nPlease select your prefered operation");
	printf("\n\n1.Generate Invoice");
	printf("\n2.Show all Invoices");
	printf("\n3.Search Invoice");
	printf("\n4.Exit");


	printf("\n\nYour choice:\t");
	scanf("%d", &opt);
	fgetc(stdin);
	
	switch(opt)
	{
		case 1:
			system("clear");
			printf("\nPlease enter the name of the customer:\t");
			fgets(ord.customer, 50, stdin);
			ord.customer[strlen(ord.customer) - 1] = 0;
			strcpy(ord.date, __DATE__);
			printf("\nPlease enter the number of items:\t");
			scanf("%d", &n);
			ord.numOfItems = n;

			for (i = 0; i < n; i++)
			{
				fgetc(stdin);
				printf("\n\n");
				printf("Please enter the item %d:\t", i + 1);
				fgets(ord.itm[i].item, 20, stdin);
				ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
				printf("Please enter the quantity:\t");
				scanf("%d", &ord.itm[i].qty);
				printf("Please enter the unit price:\t");
				scanf("%f", &ord.itm[i].price);
				total += ord.itm[i].qty * ord.itm[i].price;
			}

			generateBillHeader(ord.customer, ord.date);
			
			for (j = 0; j < ord.numOfItems; j++)
			{
				generateBillBody(ord.itm[j].item, ord.itm[j].qty, ord.itm[j].price);
			}
			generateBillFooter(total);

			printf("\nDo you want to save the invoicei [y/n]:\t");
			scanf("%s", &saveBill);

			if (saveBill == 'y')
			{
				fp = fopen("RestaurantBill.dat", "a+");
				fwrite(&ord, sizeof(struct orders), 1, fp);
				if (fwrite != 0)
					printf("\nSuccessfully saved");
				else
					printf("\nError saving");
				fclose(fp);
			}
			break;

		case 2:
			system("clear");
			fp = fopen("RestaurantBill.dat", "r");
			printf("\n *****Your Previous Invoices*****\n");
			while (fread(&order, sizeof(struct orders), 1, fp))
			{
				tot = 0;
				generateBillHeader(order.customer, order.date);
				for (k = 0; k < order.numOfItems; k++)
				{
					generateBillBody(order.itm[k].item, order.itm[k].qty, order.itm[k].price);
					tot += order.itm[i].qty * order.itm[i].price;
				}
				generateBillFooter(tot);
			}
			fclose(fp);
			break;

		case 3:
			printf("\n Enter the name of the customer:\t");
			//fgetc(stdin);
			fgets(name, 50, stdin);
			name[strlen(name) - 1] = 0;
			system("clear");
			fp = fopen("RestaurantBill.dat", "r");
			printf("\t ****** %s's Invoice *****", name);
			
			while (fread(&order, sizeof(struct orders), 1, fp))
			{
				tot = 0;
				
				if (strcmp(order.customer, name) == 0)
				{
					generateBillHeader(order.customer, order.date);
					for (l = 0; l < order.numOfItems; l++)
					{
						generateBillBody(order.itm[l].item, order.itm[l].qty, order.itm[l].price);
						tot += order.itm[l].qty * order.itm[l].price;
					}
					generateBillFooter(tot);
					invoiceFound = 1;
				}
			}
			
			if (!invoiceFound)
				printf("\n\n\t   Error Invalid Customer\n\n");
			fclose(fp);
			break;

		case 4:
			printf("\n\t\t Bye Bye :)\n\n");
			exit(0);
			break;

		default:
			printf("Sorry Invalid Option");
			break;

	}
	printf("\nDo you want to perform another operation?[y/n]:\t");
	scanf("%s", &contFlag);
	}
	printf("\n\n");
}
