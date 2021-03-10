/*
Ryan Hoang
G00973915
A simple program that reads in a data file with addresses and associated aliases.
It will allow the user to add, lookup, update, delete, display the location of,
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

void read_in_data();
void add_address(char* address, char* alias);
int alias_exists(char* alias);
int address_exists(int first, int second, int third, int fourth);
void update_address(char* alias, char* address);
void delete_address(char* alias);
void display_aliases(int first, int second);
void save();
int print_menu();
void print_nodes(struct address_t* head);
void removeNewline(char* str);



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

    switch(choice)
    {
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
      //print_nodes(head->next);

      break;

      case 2://lookup address
      printf("You chose option 2\n");
      flag = 0;
      break;

      case 3://update address
      printf("You chose option 3\n");
      flag = 0;
      break;

      case 4://delete address
      printf("You chose option 4\n");
      flag = 0;
      break;

      case 5://display list
      //printf("You chose option 5\n");
      print_nodes(head->next);
      break;

      case 6://display aliases for location
      printf("You chose option 6\n");
      flag = 0;
      break;

      case 7://save to file
      printf("You chose option 7\n");
      flag = 0;
      break;

      case 8://quit
              printf("You chose option 8\n");
              flag = 0;
      break;

      default: //Not an option reprompt user.
              printf("That was not a valid option, please enter a number 1-8 to make a selection.\n");
      break;
    }
  }

  return 0;
}

int print_menu()
{
  printf("1) Add address\n");
  printf("2) Lookup address\n");
  printf("3) Update address\n");
  printf("4) Delete address\n");
  printf("5) Display list\n");
  printf("6) Display aliases for function\n");
  printf("7) Save to file\n");
  printf("8) Quit\n");
  char buffer[30];

  printf("Please enter a number 1-8 to make a selection.\n");
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

  if(!(fgets(line_buffer, sizeof(line_buffer), fp))) //Read in first line of file.
  {
      perror("Failed to read in string. Exiting.\n");
      exit(-1);
  }
  sscanf(line_buffer, "%d.%d.%d.%d %s", &first, &second, &third, &fourth, alias);//process first line

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


  while(fgets(line_buffer, sizeof(line_buffer), fp)) //process the rest of the lines
  {
    sscanf(line_buffer, "%d.%d.%d.%d %s", &first, &second, &third, &fourth, alias);//process first line
    struct address_t* temp = (struct address_t*) malloc(sizeof(struct address_t));
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
}

void print_nodes(struct address_t* head)
{
  struct address_t* temp = head;
  int count = 1;
  while(temp != NULL)
  {
    printf("Node #%d\n",count);
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

void update_address(char* alias, char* address)
{

}

void delete_address(char* alias)
{

}

void display_aliases(int first, int second)
{

}

void save_to_file()
{

}
