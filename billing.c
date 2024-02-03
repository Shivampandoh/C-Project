#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item
{
  char name[50];
  int quantity;
  float price;
};

struct Receipt
{
  char name[100];
  char mobile[20];
  int num_items;
  struct Item items[50];
  float total_price;
};

int total_items = 0;
struct Item *menu = NULL;
int total_receipts = 0;
struct Receipt *receipts = NULL;

// Function to load item menu from file
void load_item_menu()
{
  FILE *f = fopen("menu.dat", "rb");
  if (f == NULL)
  {
    total_items = 0;
    return;
  }
  fread(&total_items, sizeof(int), 1, f);
  menu = (struct Item *)malloc(total_items * sizeof(struct Item));
  fread(menu, sizeof(struct Item), total_items, f);
  fclose(f);
  if (total_items == 0)
    return;
  printf("\nItem Menu Loaded Successfully from file.\n");
}

// Function to save item menu to file
void save_item_menu()
{
  if (total_items == 0)
    return;
  FILE *f = fopen("menu.dat", "wb");
  fwrite(&total_items, sizeof(int), 1, f);
  fwrite(menu, sizeof(struct Item), total_items, f);
  fclose(f);
  printf("\nItem Menu Saved Successfully to file.\n");
}

// Function to add item to menu
void add_item()
{
  total_items++;
  menu = (struct Item *)realloc(menu, total_items * sizeof(struct Item));
  printf("\nEnter Item Name: ");
  scanf(" %[^\n]s", menu[total_items - 1].name);
  printf("Enter Item Price: ");
  scanf("%f", &menu[total_items - 1].price);
  printf("\nItem Added Successfully.\n");
}

// Function to remove item from menu
void remove_item()
{
  int item_num;
  printf("\n%-4s%-50s%s\n", "No.", "Item Name", "Price");
  for (int i = 0; i < total_items; i++)
    printf("%-4d%-50s%.2f\n", i + 1, menu[i].name, menu[i].price);
  printf("\n");
  printf("\nEnter Item Number to Remove: ");
  scanf("%d", &item_num);
  if (item_num < 1 || item_num > total_items)
  {
    printf("\nInvalid Item Number.\n");
    return;
  }
  for (int i = item_num - 1; i < total_items - 1; i++)
    menu[i] = menu[i + 1];
  total_items--;
  menu = (struct Item *)realloc(menu, total_items * sizeof(struct Item));
  printf("\nItem Removed Successfully.\n");
}

// Function to modify item in menu
void modify_item()
{
  int item_num;
  printf("\n%-4s%-50s%s\n", "No.", "Item Name", "Price");
  for (int i = 0; i < total_items; i++)
    printf("%-4d%-50s%.2f\n", i + 1, menu[i].name, menu[i].price);
  printf("\n");
  printf("\nEnter Item Number to Modify: ");
  scanf("%d", &item_num);
  if (item_num < 1 || item_num > total_items)
  {
    printf("\nInvalid Item Number.\n");
    return;
  }
  printf("Enter New Item Name: ");
  scanf(" %[^\n]s", menu[item_num - 1].name);
  printf("Enter New Item Price: ");
  scanf("%f", &menu[item_num - 1].price);
  printf("\nItem Modified Successfully.\n");
}

// Function to load receipts from file
void load_receipts()
{
  FILE *f = fopen("receipts.dat", "rb");
  if (f == NULL)
  {
    total_receipts = 0;
    return;
  }
  fread(&total_receipts, sizeof(int), 1, f);
  receipts = (struct Receipt *)malloc(total_receipts * sizeof(struct Receipt));
  for (int i = 0; i < total_receipts; i++)
    fscanf(f, "%[^&]&%[^&]&%f\n", receipts[i].name, receipts[i].mobile, &receipts[i].total_price);
  fclose(f);
  if (total_receipts == 0)
    return;
  printf("\nReceipts Loaded Successfully from file.\n");
}

// Function to save receipts to file
void save_receipts()
{
  if (total_receipts == 0)
    return;
  FILE *f = fopen("receipts.dat", "wb");
  fwrite(&total_receipts, sizeof(int), 1, f);
  for (int i = 0; i < total_receipts; i++)
    fprintf(f, "%s&%s&%.2f\n", receipts[i].name, receipts[i].mobile, receipts[i].total_price);
  fclose(f);
  printf("\nReceipts Saved Successfully to file.\n");
}
//Function to delete receipts
void delete_receipts()
{
    int receipt_num;
    if (total_receipts == 0)
  {
    printf("\nNo Receipts Found.\n");
    return;
  }
  printf("\%20d Receipts Found!\n\n", total_receipts);
  printf("\n%-4s%-20s%-20s%s\n", "No.", "Name", "Mobile Number", "Total Price");
  for (int i = 0; i < total_receipts; i++)
    printf("%-4d%-20s%-20s%.2f\n", i + 1, receipts[i].name, receipts[i].mobile, receipts[i].total_price);
    printf("Enter Receipt Number you want to delete : ");
    scanf("%d", &receipt_num);
    if(receipt_num<1 || receipt_num>total_receipts){
        printf("\nInvalid Receipt Number!\n");
        return;
    }
    for(int i=receipt_num-1;i<total_receipts;i++)
        receipts[i]=receipts[i+1];
    total_receipts--;
    receipts=(struct Receipt *)realloc(receipts, total_receipts*sizeof(struct Receipt));
    system("cls");
    printf("\nReceipt Removed Successfully...\n");

}

// Function to generate receipt
void generate_receipt()
{
  if (total_items == 0)
  {
    printf("\nItem Menu is Empty. Add Items First.\n");
    return;
  }
  struct Receipt receipt;
  printf("\nEnter Name: ");
  scanf(" %[^\n]s", receipt.name);
  printf("Enter Mobile Number: ");
while (1) {
  scanf("%s", receipt.mobile);
  if (strlen(receipt.mobile) != 10) {
    printf("\nInvalid Number!!! \n\nPlease enter a valid 10-digit Mobile number: ");
  } else {
    break;
  }
}
  printf("Enter Number of Items: ");
  int num_items;
  scanf("%d", &num_items);
  float total_price = 0.0;
  printf("\n%-4s%-50s%s\n", "No.", "Item Name", "Price");
  for (int i = 0; i < total_items; i++)
    printf("%-4d%-50s%.2f\n", i + 1, menu[i].name, menu[i].price);
  printf("\n");
  for (int i = 0; i < num_items; i++)
  {
    int item_num, item_qty;
    printf("Enter Item %d Number: ", i + 1);
    scanf("%d", &item_num);
    if (item_num < 1 || item_num > total_items)
    {
      printf("\nInvalid Item Number.\n");
      i--;
      continue;
    }
    printf("Enter Item %d Quantity: ", i + 1);
    scanf("%d", &item_qty);
    total_price += (menu[item_num - 1].price * item_qty);
    strcpy(receipt.items[i].name, menu[item_num - 1].name);
    receipt.items[i].price = menu[item_num - 1].price;
    receipt.items[i].quantity = item_qty;
  }
  receipt.num_items = num_items;
  receipt.total_price = total_price;
  printf("\n%-20s: %s\n", "Name", receipt.name);
  printf("%-20s: %s\n", "Mobile Number", receipt.mobile);
  printf("\n%-4s%-50s%-10s%s\n", "No.", "Item Name", "Quantity", "Price");
  for (int i = 0; i < num_items; i++)
    printf("%-4d%-50s%-10d%.2f\n", i + 1, receipt.items[i].name, receipt.items[i].quantity, receipt.items[i].quantity * receipt.items[i].price);
  printf("\nTotal Price: %.2f\n", total_price);
  printf("\nDo you want to save the receipt? (y/n): ");
  char save;
  scanf(" %c", &save);
  if (save == 'y' || save == 'Y')
  {
    total_receipts++;
    receipts = (struct Receipt *)realloc(receipts, total_receipts * sizeof(struct Receipt));
    receipts[total_receipts - 1] = receipt;
    printf("\nReceipt Saved Successfully.\n");
  }
}

// Function to view all receipts
void view_all_receipts()
{
    system("cls");
  if (total_receipts == 0)
  {
    printf("\nNo Receipts Found.\n");
    return;
  }
  printf("\%20d Receipts Found!\n\n", total_receipts);
  printf("\n%-4s%-20s%-20s%s\n", "No.", "Name", "Mobile Number", "Total Price");
  for (int i = 0; i < total_receipts; i++)
    printf("%-4d%-20s%-20s%.2f\n", i + 1, receipts[i].name, receipts[i].mobile, receipts[i].total_price);
}

// Function to search receipt
void search_receipt()
{
  if (total_receipts == 0)
  {
    printf("\nNo Receipts Found.\n");
    return;
  }

  char mobile[20];

  printf("Enter Mobile Number: ");
  scanf("%s", mobile);
  while(strlen(mobile) != 10){
    printf("Invalid Number!\n Enter Number Again : ");
    scanf("%s", mobile);
  }

  int found = 0;

  for (int i = 0; i < total_receipts; i++)
  {
    if (strcmp(receipts[i].mobile, mobile) == 0)
    {
      printf("\nReceipt Found! \n");
      printf("\n%-10s: %s\n", "Name", receipts[i].name);
      printf("%-10s: %s\n", "Mobile", receipts[i].mobile);
      printf("%-10s: %.2f\n", "Total Price", receipts[i].total_price);
      found = 1;
      break;
    }
  }

  if (!found)
    printf("\nReceipt Not Found.\n");
}

// Function to edit item menu
void edit_item_menu()
{
  int choice;
  do
  {
    printf("\nItem Menu\n");
    printf("1. Add Item\n");
    printf("2. Remove Item\n");
    printf("3. Modify Item\n");
    printf("4. Exit\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      add_item();
      break;
    case 2:
      remove_item();
      break;
    case 3:
      modify_item();
      break;
    case 4:
      system("cls");
      break;
    default:
      printf("\nInvalid Choice.\n");
    }
  } while (choice != 4);
}

// Main Function
int main()
{
  int choice;
  load_item_menu();
  load_receipts();
  do
  {
    printf("\nCustomer Billing System\n");
    printf("1. Generate Receipt\n");
    printf("2. View All Receipts\n");
    printf("3. Search Receipt\n");
    printf("4. Edit Item Menu\n");
    printf("5. Remove Receipt\n");
    printf("6. Save and Exit\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      generate_receipt();
      break;
    case 2:
      view_all_receipts();
      break;
    case 3:
      search_receipt();
      break;
    case 4:
      edit_item_menu();
      break;
    case 5:
        delete_receipts();
        break;
    case 6:
      save_item_menu();
      save_receipts();
      printf("\nData Saved Successfully.\n");
      break;
    default:
      printf("\nInvalid Choice.\n");
    }
  } while (choice != 6);
  return 0;
}
