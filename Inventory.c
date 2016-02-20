#include <stdio.h>
#include <stdlib.h>



struct inventory
{
    struct inventory *prev;
    long int item_code;
    char item_name[50];
    int quantity;
    char doa[20];
    char dom[20];
    char ed[20];
    struct inventory *next;
};
typedef struct inventory inv;
inv *LP=NULL,*temp,*temp1,*temp2,*RP=NULL;

void create();
void insert1();
void insert2();
void insert3();
void display();
void deletei();
void savetofile();
void readfromfile();

int count = 0;

int main()
{
    int ch;

    printf("\n 1 - Create Inventory");
    printf("\n 2 - Insert item at beginning");
    printf("\n 3 - Insert item at end");
    printf("\n 4 - Insert item at position i");
    printf("\n 5 - Delete item at i");
    printf("\n 6 - Display Inventory from beginning");
    printf("\n 7 - Write items into file");
    printf("\n 8 - Read items from file");
    printf("\n 9 - Exit");

    while (1)
    {
        printf("\n Enter choice : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            create();
            break;
        case 2:
            insert1();
            break;
        case 3:
            insert2();
            break;
        case 4:
            insert3();
            break;
        case 5:
            deletei();
            break;
        case 6:
            display();
            break;
        case 7:
             savetofile();
             break;
        case 8:
            readfromfile();
              break;
        case 9:
            exit(0);
             break;

        default:
            printf("\n Wrong choice menu");
        }
    }
    return 0;
}

/* TO create an empty node */
void create()
{


    temp =(inv *)malloc(1*sizeof(inv));
    temp->prev = NULL;
    temp->next = NULL;
    printf("\n Enter item code : ");
    scanf("%ld", &temp->item_code);
    printf("\n Enter name of the item : ");
    scanf("%s",temp->item_name);
    printf("\n Enter the quantity : ");
    scanf("%d",&temp->quantity);
    printf("\n Enter date of arrival : ");
    scanf("%s",temp->doa);
    printf("\n Enter date of manufacture : ");
    scanf("%s",temp->dom);
    printf("\n Enter expiry date : ");
    scanf("%s",temp->ed);
    count++;
}

/*  TO insert at beginning */
void insert1()
{
    if (LP == NULL)
    {
        create();
        LP = temp;
        temp1 = LP;
    }
    else
    {
        create();
        temp->next = LP;
        LP->prev = temp;
        LP = temp;
        RP=temp;
    }
}

/* To insert at end */
void insert2()
{
    if (LP == NULL)
    {
        create();
        LP = temp;
        temp1 = LP;
    }
    else
    {
        create();
        temp1->next = temp;
        temp->prev = temp1;
        temp1 = temp;
        RP=temp;
        temp->next=NULL;
    }
}

/* To insert at any position */
void insert3()
{
    int pos, i = 2;

    printf("\n Enter position to be inserted : ");
    scanf("%d", &pos);
    temp2 = LP;

    if ((pos < 1) || (pos >= count + 1))
    {
        printf("\n Position out of range to insert");
        return;
    }
    if ((LP == NULL) && (pos != 1))
    {
        printf("\n Empty list cannot insert other than 1st position");
        return;
    }
    if ((LP == NULL) && (pos == 1))
    {
        create();
        LP = temp;
        temp1 = LP;
        return;
    }
    else
    {
        while (i < pos)
        {
            temp2 = temp2->next;
            i++;
        }
        create();
        temp->prev = temp2;
        temp->next = temp2->next;
        temp2->next->prev = temp;
        temp2->next = temp;
    }
}

/* To delete an element */
void deletei()
{
    int i = 1, pos;

    printf("\n Enter position to be deleted : ");
    scanf("%d", &pos);
    temp2 = LP;

    if ((pos < 1) || (pos >= count + 1))
    {
        printf("\n Error : Position out of range to delete");
        return;
    }
    if (LP == NULL)
    {
        printf("\n Error : Empty list no elements to delete");
        return;
    }
    else
    {
        while (i < pos)
        {
            temp2 = temp2->next;
            i++;
        }
        if (i == 1)
        {
            if (temp2->next == NULL)
            {
                printf("Node deleted from list");
                free(temp2);
                temp2 = LP = NULL;
                return;
            }
        }
        if (temp2->next == NULL)
        {
            temp2->prev->next = NULL;
            free(temp2);
            printf("Node deleted from list");
            return;
        }
        temp2->next->prev = temp2->prev;
        if (i != 1)
            temp2->prev->next = temp2->next;    /* Might not need this statement if i == 1 check */
        if (i == 1)
            LP = temp2->next;
        printf("\n Node deleted");
        free(temp2);
    }
    count--;
}

void display()
{
     inv *temp2;
     temp2=LP;
     if(temp2==NULL)
      {
         printf("List is Empty");
      }
     while(temp2!=NULL)
     {
          printf("\n%ld",temp2->item_code);
          printf("\n%s",temp2->item_name);
          printf("\n%d",temp2->quantity);
          printf("\n%s",temp2->doa);
          printf("\n%s",temp2->dom);
          printf("\n%s",temp2->ed);
          temp2=temp2->next;
          printf("\n------------------------------------\n");
     }
     printf("NULL");
}


void savetofile()
{
    FILE *fp;
    inv *ptr;

    if(LP == NULL)
    {
        printf("Empty.\n");
        return;
    }

    ptr = LP;
    if((fp=fopen("c:\\database.txt", "wb")) == NULL)
    {
        printf("No such file.\n");
        return;
    }
    else
    {
        fwrite(&ptr, sizeof(inv), 1, fp);
        fclose(fp);
        printf("Saved to disk.\n");
        system("PAUSE");
    }
}



void readfromfile()
{

    FILE *fp;
    inv *ptr = malloc(sizeof(*ptr));
    ptr = LP;

    fp=fopen("c:\\database.txt", "rb");

    while(fread(&ptr, sizeof(inv), 1, fp) ==1)
    {
        printf("\nTHE DETAILS WRITTEN INTO THE FILE ARE :\n");
        printf("Item code: %ld\n", ptr->item_code);
        printf("Item name: %s\n", ptr->item_name);
        printf("Quantity: %d\n",ptr->quantity);
        printf("Date of arrival: %s\n",ptr->doa);
        printf("Date of manufacture: %s\n",ptr->dom);
        printf("Expiry Date: %s\n",ptr->ed);
        ptr = ptr->next;
    }
         fclose(fp);
       system("PAUSE");
}
