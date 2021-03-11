/*
Ryan Hoang
G00973915
A simple program that reads a data file with addresses and associated aliases.
Allows the user to add, lookup, update, delete, display the location of,
and save this data to a file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct address_t
{
  int first;
  int second;
  int third;
  int fourth;
  char alias[11];
  struct address_t *next;
};
struct address_t* head = NULL;

//==============================Prototypes======================================
void read_in_data();
void add_address(char* address, char* alias);
int alias_exists(char* alias);
int address_exists(int first, int second, int third, int fourth);
void lookup(char* alias);
void update_address(char* alias);
void delete_address(char* alias);
void display_aliases(int first, int second);
void save(char* filename);
int print_menu();
void print_nodes(struct address_t* head);
void removeNewline(char* str);
//==============================================================================

int main()
{
  head = (struct address_t*) malloc(sizeof(struct address_t));

  read_in_data();

  //print_nodes(head->next);

  char buffer[100];

  int flag = 1;
  while(flag)
  {
    int choice = print_menu();
    char address[100];
    char alias[100];

    int first = -1; //Initialize for option 6
    int second = -1;//Initialize for option 6
    int* params[2]; //Initialize for option 6

    switch(choice)
    {
//==============================================================================
      case 1://add address
      printf("Please enter an address: ");
      if(!(fgets(buffer, sizeof(buffer), stdin))) //Read in first line of file.
      {
          perror("Failed to read in string. Exiting.\n");
          exit(-1);
      }

      memcpy(address, buffer, sizeof(address));

      printf("Please enter an alias: ");
      if(!(fgets(buffer, sizeof(buffer), stdin))) //Read in first line of file.
      {
          perror("Failed to read in string. Exiting.\n");
          exit(-1);
      }

      memcpy(alias, buffer, sizeof(alias));
      add_address(address,alias);
      break;
//==============================================================================
      case 2://lookup address
      printf("Enter alias: ");
      if(!(fgets(buffer, sizeof(buffer), stdin))) //Read in first line of file.
      {
          perror("Failed to read in string. Exiting.\n");
          exit(-1);
      }
      memcpy(alias, buffer, sizeof(alias));
      removeNewline(alias);
      lookup(alias);
      break;
//==============================================================================
      case 3://update address
      printf("Enter alias: ");
      if(!(fgets(buffer, sizeof(buffer), stdin))) //Read in first line of file.
      {
          perror("Failed to read in string. Exiting.\n");
          exit(-1);
      }
      memcpy(alias, buffer, sizeof(alias));
      removeNewline(alias);
      update_address(alias);
      break;
//==============================================================================
      case 4://delete address
      printf("Enter alias: ");
      if(!(fgets(buffer, sizeof(buffer), stdin))) //Read in first line of file.
      {
          perror("Failed to read in string. Exiting.\n");
          exit(-1);
      }
      memcpy(alias, buffer, sizeof(alias));
      removeNewline(alias);
      delete_address(alias);
      break;
//==============================================================================
      case 5://display list
      print_nodes(head->next);
      break;
//==============================================================================
      case 6://display aliases for location
      params[0] = &first;
      params[1] = &second;

      int i;
      for(i=0; i<2; i++)
      {
        int* temp = (int*) params[i];

        while((*temp < 0) || (*temp > 255))
        {
          printf("Enter location value #%d (0-255): ",i+1);
          if(!(fgets(buffer, sizeof(buffer), stdin)))
          {
              perror("Failed to read in string. Exiting.\n");
              exit(-1);
          }

          removeNewline(buffer);
          *temp = atoi(buffer);
          if(!(*temp >= 0) || !(*temp <= 255))
          {
            printf("Illegal entry.\n");
          }
        }
      }

      display_aliases(first, second);
      break;
//==============================================================================
      case 7://save to file
      printf("Enter filename: ");
      if(!(fgets(buffer, sizeof(buffer), stdin)))
      {
          perror("Failed to read in string. Exiting.\n");
          exit(-1);
      }
      removeNewline(buffer);
      save(buffer);
      break;
//==============================================================================
      case 8://quit
              printf("Goodbye.\n");
              flag = 0;
      break;
//==============================================================================
      default: //Not an option reprompt user.
      printf("Invalid option, enter a number 1-8 to make a selection.\n");
      break;
//==============================================================================
    }
  }
  return 0;
}

int print_menu()
{
  printf("\n");
  printf("1) Add address\n");
  printf("2) Lookup address\n");
  printf("3) Update address\n");
  printf("4) Delete address\n");
  printf("5) Display list\n");
  printf("6) Display aliases for function\n");
  printf("7) Save to file\n");
  printf("8) Quit\n");
  char buffer[30];

  printf("Please enter a number 1-8 to make a selection.\n\n");
  printf("Enter option: ");
  if(!(fgets(buffer, sizeof(buffer), stdin)))
  {
      printf("Failed to read in string. Exiting.\n");
      return 8;
  }

  int choice = atoi(buffer);
  return choice;
}

void read_in_data()
{
  char filename[] = "CS531_Inet.txt";
  FILE *fp;
  char line_buffer[30];
  ssize_t size = 0;

  fp = fopen(filename, "r");

  if(!fp)
  {
    perror("Error while trying to read in data.");
    exit(-1);
  }

  int line = 0;
  int first = 0;
  int second = 0;
  int third = 0;
  int fourth = 0;
  char alias[11];

  //Read in first line of file.
  if(!(fgets(line_buffer, sizeof(line_buffer), fp)))
  {
      perror("Failed to read in string. Exiting.\n");
      exit(-1);
  }
  //process first line
  sscanf(line_buffer,"%d.%d.%d.%d %s", &first, &second, &third, &fourth, alias);

  struct address_t* t = (struct address_t*) malloc(sizeof(struct address_t));
  if(t == NULL)
  {
    perror("Cannot allocate space for new struct exiting.");
    exit(-1);
  }
  t -> first = first;
  t -> second = second;
  t -> third = third;
  t -> fourth = fourth;
  memcpy(t->alias, alias, sizeof(t->alias));
  t -> next = NULL;
  head -> next = t;

  //process the rest of the lines
  while(fgets(line_buffer, sizeof(line_buffer), fp))
  {
    sscanf(line_buffer,"%d.%d.%d.%d %s",&first,&second, &third, &fourth, alias);
    struct address_t* temp =(struct address_t*)malloc(sizeof(struct address_t));
    if(temp == NULL)
    {
      perror("Cannot allocate space for new struct exiting.");
      exit(-1);
    }

    temp -> first = first;
    temp -> second = second;
    temp -> third = third;
    temp -> fourth = fourth;
    memcpy(temp->alias, alias, sizeof(temp->alias));

    temp -> next = head -> next;
    head -> next = temp;
  }
  fclose(fp);
}

void print_nodes(struct address_t* head)
{
  struct address_t* temp = head;
  int count = 0;
  while(temp != NULL)
  {
    printf("Node #%d\n",count+1);
    printf("First: %d\n",temp->first);
    printf("Second: %d\n",temp->second);
    printf("Third: %d\n",temp->third);
    printf("Fourth: %d\n",temp->fourth);
    printf("Alias: %s\n",temp->alias);
    printf("============================\n");
    temp = temp->next;
    count++;
  }
  printf("Total node count:%d\n",count);
}

void add_address(char* address, char* alias)
{

  int first = 0;
  int second = 0;
  int third = 0;
  int fourth = 0;
  sscanf(address, "%d.%d.%d.%d", &first, &second, &third, &fourth);
  removeNewline(alias);

  if(alias_exists(alias))
  {
    printf("%s already exists.\n", alias);
    return;
  }

  if(address_exists(first,second,third,fourth))
  {
    printf("%d.%d.%d.%d already exists.\n", first, second, third, fourth);
    return;
  }

  struct address_t* node = (struct address_t*) malloc(sizeof(struct address_t));

  node -> first = first;
  node -> second = second;
  node -> third = third;
  node -> fourth = fourth;

  memcpy(node->alias, alias, sizeof(node->alias));

  node -> next = head -> next;
  head -> next = node;
}

//Strips newline characters.
void removeNewline(char* str)
{
  char* position;
  char* pos;

  if((pos = strchr(str, '\n')) != NULL)
  {
    *pos = '\0';
  }
}

int alias_exists(char* alias)
{
  struct address_t* temp = head->next;

  while(temp)
  {
    if(strcmp(temp->alias, alias) == 0)
    {
      return 1;
    }

    temp = temp->next;
  }

  return 0;
}

int address_exists(int first, int second, int third, int fourth)
{
  struct address_t* temp = head->next;

  while(temp)
  {
    if((temp->first == first) && (temp->second == second) && (temp->third == third) && (temp->fourth == fourth))
    {
      return 1;
    }
    temp = temp->next;
  }

  return 0;
}

void lookup(char* alias)
{
  struct address_t* temp = head->next;

  while(temp)
  {
    if(strcmp(temp->alias, alias) == 0)
    {
      printf("Address for %s: %d.%d.%d.%d\n", alias, temp->first, temp->second, temp->third, temp->fourth);
      return;
    }
    temp = temp->next;
  }
  printf("%s does not exist.\n", alias);
}

void update_address(char* alias)
{
  struct address_t* temp = head->next;
  struct address_t* edit = NULL;

  while(temp)
  {
    if(strcmp(temp->alias, alias) == 0)
    {
      printf("Update Address for %s: %d.%d.%d.%d\n", alias, temp->first, temp->second, temp->third, temp->fourth);
      edit = temp;
    }
    temp = temp->next;
  }

  if(edit == NULL)
  {
    printf("%s does not exist.\n", alias);
    return;
  }

  char buffer[20];
  int first = -1;
  int second = -1;
  int third = -1;
  int fourth = -1;

  int* params[4];
  params[0] = &first;
  params[1] = &second;
  params[2] = &third;
  params[3] = &fourth;


  int i;
  for(i=0; i<4; i++)
  {
    int* temp = (int*) params[i];

    while((*temp < 0) || (*temp > 255))
    {
      printf("Enter location value #%d (0-255): ",i+1);
      if(!(fgets(buffer, sizeof(buffer), stdin)))
      {
          perror("Failed to read in string. Exiting.\n");
          exit(-1);
      }

      removeNewline(buffer);
      *temp = atoi(buffer);
      if(!(*temp >= 0) || !(*temp <= 255))
      {
        printf("Illegal entry.\n");
      }
    }
  }
  //printf("%d.%d.%d.%d\n", first, second, third, fourth);
  if(!address_exists(first,second,third,fourth))
  {
    edit -> first = first;
    edit -> second = second;
    edit -> third = third;
    edit -> fourth = fourth;
    //print_nodes(head->next);
  }
  else
  {
    printf("Address already exists, discarding.\n");
    return;
  }
}

void delete_address(char* alias)
{
  struct address_t* temp = head;
  char buffer[20];

  while(temp -> next)
  {
    if(strcmp(temp -> next -> alias, alias) == 0)
    {
      printf("Delete %s %d.%d.%d.%d? (y/n)\n", alias, temp->next->first, temp->next->second, temp->next->third, temp->next->fourth);

      if(!(fgets(buffer, sizeof(buffer), stdin)))
      {
          perror("Failed to read in string. Exiting.\n");
          exit(-1);
      }
      removeNewline(buffer);
      if(strcmp("y",buffer) == 0)
      {
        struct address_t* t = temp->next;
        if(temp -> next -> next == NULL)
        {
          temp -> next = NULL;
        }
        else
        {
          temp -> next = temp -> next -> next;
        }
        free(t);
        printf("%s deleted.\n", alias);
        return;
      }
    }
    temp = temp->next;
  }
  printf("%s does not exist.\n", alias);
}

void display_aliases(int first, int second)
{
  struct address_t* temp = head->next;

  int flag = 0;

  while(temp)
  {
    if(temp -> first == first && temp -> second == second)
    {
      printf("%d.%d.%d.%d %s\n", temp->first, temp->second, temp->third, temp->fourth, temp -> alias);
      flag = 1;
    }
    temp = temp->next;
  }
  if(!flag)
  {
    printf("No locations associated with %d.%d\n", first,second);
  }
}

void save(char* filename)
{

  FILE *fp;
  fp = fopen(filename, "w+");

  if(!fp)
  {
    perror("Could not open file.\n");
    exit(-1);
  }

  struct address_t* temp = head->next;
  while(temp)
  {
    fprintf(fp,"%d.%d.%d.%d %s\n", temp->first, temp->second, temp->third, temp->fourth, temp -> alias);
    temp = temp->next;
  }
  fclose(fp);
  printf("File saved. \n");
}
