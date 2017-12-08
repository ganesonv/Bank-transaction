#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> 
#include <sys/time.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>


#include "cs402.h"

#include "my402list.h"

// Structure created for Banking Transactions   
typedef struct  warmupobj
{
    char type; // deposit or withdrawal
    int  time; // time stamp
    char *amount; // Transaction amount
    char *description; // Transaction description 
    int  lines; // line count for error display
}bankobj;

// Swapping the objects
// Used for Bubble sort
// program reused from listtest.c provided
static
void BubbleForward(My402List *pList, My402ListElem **pp_elem1, My402ListElem **pp_elem2)
{
    My402ListElem *elem1=(*pp_elem1), *elem2=(*pp_elem2);
    void *obj1=elem1->obj, *obj2=elem2->obj;
    My402ListElem *elem1prev=My402ListPrev(pList, elem1);
    My402ListElem *elem2next=My402ListNext(pList, elem2);

    // Swapping the objects

    My402ListUnlink(pList, elem1);
    My402ListUnlink(pList, elem2);
    if (elem1prev == NULL) {
        (void)My402ListPrepend(pList, obj2);
        *pp_elem1 = My402ListFirst(pList);
    } else {
        (void)My402ListInsertAfter(pList, obj2, elem1prev);
        *pp_elem1 = My402ListNext(pList, elem1prev);
    }
    if (elem2next == NULL) {
        (void)My402ListAppend(pList, obj1);
        *pp_elem2 = My402ListLast(pList);
    } else {
        (void)My402ListInsertBefore(pList, obj1, elem2next);
        *pp_elem2 = My402ListPrev(pList, elem2next);
    }
}

// Bubble sort used to sort the Timestamp
// Sorting is done using the Unix Timestamp itself
// Bubble sort peice of code reused from the listtest.c
static
void BubbleSortForwardList(My402List *pList, int num_items)
{
    My402ListElem *elem=NULL;
    bankobj *cur_val=NULL;
    bankobj *next_val=NULL;
    int i=0;

    if (My402ListLength(pList) != num_items) {
        fprintf(stderr, "List length is not %1d in BubbleSortForwardList().\n", num_items);
        exit(1);
    }
    for (i=0; i < num_items; i++) {
        int j=0, something_swapped=FALSE;
        My402ListElem *next_elem=NULL;

        for (elem=My402ListFirst(pList), j=0; j < num_items-i-1; elem=next_elem, j++) {
            cur_val=(bankobj*)(elem->obj);

            next_elem=My402ListNext(pList, elem);
            next_val = (bankobj*)(next_elem->obj);

            // Compare for the same Timestamp

            if (cur_val->time == next_val->time) {
              fprintf(stderr,"Timestamp '%d' is repeated in the  Line %d and Line %d\nDuplicate Time Stamps!\nQuit Execution!\n",cur_val->time,cur_val->lines,next_val->lines);
              exit(-1);
            }

            // Compare for sorting

            if (cur_val->time > next_val->time) {
                BubbleForward(pList, &elem, &next_elem);
                something_swapped = TRUE;
            }
        }
        if (!something_swapped) break;
    }
}

static
void Printbalance(double Balance)
{

  int s=0;
  int space;
  char short_str[24];
  char disp_amt[12];
  char bal_word[20];
  char *val[2];
  int l=0;
  char *amt;
  int read_amt=0, dec=0, amt1=0, amt2=0, amt3=0;
  double goodbal=0.00;

  // To print when Balance is a positive value
  if(Balance>0)
        {
          if(Balance>=10000000.00)
          printf("  ?,???,???.??  |\n");

          else
          {
            // Breaking the amount to smaller segments, to insert commas
            read_amt=Balance;
            sprintf(bal_word,"%0.2f",Balance);
            amt=NULL;

            amt=bal_word;

            char *amount_check=(char *)malloc(sizeof(amount_check));
            amount_check=NULL;
            amount_check = strtok(amt, ".");
            val[l] = strdup(amount_check);
       
            while(amount_check)
            {
              l++;
              amount_check = strtok(NULL, ".");
              if(amount_check)
              {
                val[l] = strdup(amount_check);
              }
          
            }
            l=0;
            read_amt=atoi(val[0]);
            dec=atoi(val[1]);
            amt1=read_amt%1000;
            read_amt=read_amt/1000;
            if(read_amt==0)
                sprintf(disp_amt,"%d.%02d",amt1,dec);
            else
            {
                amt2=read_amt%1000;
                read_amt=read_amt/1000;
                if(read_amt==0)
                  sprintf(disp_amt,"%d,%03d.%02d",amt2,amt1,dec);
                else
                {
                  amt3=read_amt%10;
                  sprintf(disp_amt,"%d,%03d,%03d.%02d",amt3,amt2,amt1,dec);
                }
            }
            space=0;
            s=0;
        
            if(strlen(disp_amt)<12)
            {
              printf("  ");
              space=12-strlen(disp_amt);
              for(s=space;s!=0;s--)
                  printf(" ");
              printf("%s  |\n",disp_amt);            
            }

            else
            {
                printf("  %s  |\n",short_str);
            }

          }
        }

        // To print when Balance is a negative value

        if(Balance<0)
        {
          if (Balance<=-10000000.00)
          {
          printf(" (?,???,???.??");
          printf(") |\n");
          }

          else
          {
            goodbal=-Balance;

            read_amt=goodbal;
            sprintf(bal_word,"%0.2f",goodbal);
            amt=NULL;

            amt=bal_word;

            char *amount_check=(char *)malloc(sizeof(amount_check));
            amount_check=NULL;
            amount_check = strtok(amt, ".");
            val[l] = strdup(amount_check);
       
            while(amount_check)
            {
              l++;
              amount_check = strtok(NULL, ".");
              if(amount_check)
              {
                val[l] = strdup(amount_check);
              }
          
            }
            l=0;
            read_amt=atoi(val[0]);
            dec=atoi(val[1]);
            amt1=read_amt%1000;
            read_amt=read_amt/1000;
            if(read_amt==0)
              sprintf(disp_amt,"%d.%02d",amt1,dec);
            else
            {
              amt2=read_amt%1000;
              read_amt=read_amt/1000;
              if(read_amt==0)
              sprintf(disp_amt,"%d,%03d.%02d",amt2,amt1,dec);
              else
              {
                  amt3=read_amt%10;
                  sprintf(disp_amt,"%d,%03d,%03d.%02d",amt3,amt2,amt1,dec);
              }
            }
            space=0;
            s=0;      
          
            if(strlen(disp_amt)<12)
            {
              printf(" (");
              space=12-strlen(disp_amt);
              for(s=space;s!=0;s--)
                printf(" ");
              printf("%s) |\n",disp_amt);
            
            }
            else
            {
              printf(" (%s) |\n",disp_amt);
            }
          }

        }

}

// Final display
static
void Printoutput(My402List *list)
{
  char *times;
  char *value[5];
  char Type;
  int i=0;
  double Balance =0.00;
  double Amount=0.00;
  My402ListElem *elem=NULL;
  bankobj *disp=NULL;
  int k=0, s=0;
  int space;
  char short_str[24];
  char disp_amt[12];
  char *amt;
  char *val[2];
  int read_amt=0, dec=0, amt1=0, amt2=0, amt3=0;
  int l=0;


  fprintf(stdout,"+-----------------+--------------------------+----------------+----------------+\n");
  fprintf(stdout,"|       Date      | Description              |         Amount |        Balance |\n");
  fprintf(stdout,"+-----------------+--------------------------+----------------+----------------+\n");

  for (elem=My402ListFirst(list), k=My402ListLength(list); k != 0; k--, elem=My402ListNext(list, elem)) 
  {

      
        
      disp = (bankobj*)elem->obj;
      Type=disp->type;

      // Convert the unix Timestamp to a readable Time value
        
      time_t raw_time = disp->time;
      char word[20];
  
      times=ctime(&raw_time);
      char *token=(char *)malloc(strlen(times)+1);
      token=NULL;
      token = strtok(times, " \n");
      value[i] = strdup(token);
  
      //printf("%s ", value[i]);
      
      while(token)
      {
          i++;
          token = strtok(NULL, " \n");
          if(token)
          {
              value[i] = strdup(token);
          }
          
      }
      i=0;

      sprintf(word, "%s %s %2d %s", value[0],value[1],atoi(value[2]),value[4]);
      printf("| %s |",word);


      // to remove the leading white spaces from the code

      char* Strings = disp->description;

      while(*Strings != '\0' && isspace(*Strings))
      {
          ++Strings;
      }
         

      memmove(disp->description, Strings, strlen(Strings)+1);



      if(strlen(disp->description)<24)
      {
        printf(" %s",disp->description);
        space=24-strlen(disp->description);
        for(s=space;s!=0;s--)
          printf(" ");
        printf(" |");
      }
      else
      {
        strncpy(short_str,disp->description,24);
        printf(" %s |",short_str);
      }

      Amount=atof(disp->amount);
      
      if(Amount>=10000000.00)
      {
        if(Type=='+')
          printf("  ?,???,???.??  |");
        if (Type=='-')
        {
          printf(" (?,???,???.??");
          printf(") |");
        }

      }
      else
      {

      amt=NULL;

      amt=disp->amount;

      char *amount_check=(char *)malloc(sizeof(amount_check));
      amount_check=NULL;
      amount_check = strtok(amt, ".");
      val[l] = strdup(amount_check);
  
      // To obtain the decimal values and the integer values
      
      while(amount_check)
      {
          l++;
          amount_check = strtok(NULL, ".");
          if(amount_check)
          {
              val[l] = strdup(amount_check);
          }
          
      }
      l=0;

      // To break down the amount to insert commas at the appropriate places
      read_amt=atoi(val[0]);
      dec=atoi(val[1]);
      amt1=read_amt%1000;
      read_amt=read_amt/1000;
      if(read_amt==0)
        sprintf(disp_amt,"%d.%02d",amt1,dec);
      else
      {
        amt2=read_amt%1000;
        read_amt=read_amt/1000;
        if(read_amt==0)
            sprintf(disp_amt,"%d,%03d.%02d",amt2,amt1,dec);
        else
        {
            amt3=read_amt%10;
            sprintf(disp_amt,"%d,%03d,%03d.%02d",amt3,amt2,amt1,dec);
        }
      }
        space=0;
        s=0;
        if(Type=='+')
        {
          if(strlen(disp_amt)<12)
          {
            printf("  ");
            space=12-strlen(disp_amt);
            for(s=space;s!=0;s--)
                printf(" ");
            printf("%s  |",disp_amt);
            
          }
        else
          {
            printf("  %s  |",short_str);
          }
        }
        else if (Type=='-')
          {
            if(strlen(disp_amt)<12)
            {
              printf(" (");
              space=12-strlen(disp_amt);
              for(s=space;s!=0;s--)
                printf(" ");
              printf("%s) |",disp_amt);
            
            }
            else
            {
              printf(" (%s) |",disp_amt);
            }
          }

      }
   
// To calculate the Balance 
      if(Type=='+')
      {
        Balance=Amount+Balance;
        Printbalance(Balance);        
      }
      
      else if(Type=='-')
      {
        Balance=Balance-Amount;
        Printbalance(Balance);
      }


}

fprintf(stdout,"+-----------------+--------------------------+----------------+----------------+\n");

  
}


/* ----------------------- main() ----------------------- */

int main(int argc, char *argv[])
{
    
    My402List list;
    char send_buf[1024];
    int i=0, j=0, l=0, curtime=0;
    char *token;
    char *val[2];
    char *value[4];
    char *amt;
    double check=0.0;
    time_t Timer;
    //char cmd[4]="sort";
    
    memset(&list, 0, sizeof(My402List));

    // Doubly circular linked list is initiated
    My402ListInit(&list);

    // Current time is calculated

    curtime=time(&Timer);
    
    
    if(argc<2)
    {
        fprintf(stderr, "Insufficient command: Please insert appropriate command: '\\warmup1 sort' or '\\warmup1 sort [filename]'\n");
        exit(-1);
    }

    

    if (strncmp(argv[1],"sort",3)!= 0) 
    {
        fprintf(stderr, "Malformed command: Please enter appropriate command\nThe second argument should be 'sort'\n");
        exit(-1);
    }

    if(argc>=4)
    {
        fprintf(stderr, "Too many commands: Please insert appropriate command: '\\warmup1 sort' or '\\warmup1 sort [filename]'\n");
        exit(-1);
    }

    FILE *fp=NULL;
    int status;
    struct stat st_buf;

    if(argv[2]) 
    {

        status = stat (argv[2], &st_buf);
        if (status != 0) {
        fprintf (stderr,"Input file '%s': %s\n", argv[2], strerror(errno));
        exit(-1);
        }
        // Check if it is a directory or a file
        if (S_ISDIR (st_buf.st_mode)) {
        fprintf (stderr,"'%s' is a directory.\n", argv[2]);
        exit(-1);
        }
    
        fp=fopen(argv[2],"r");
        if(fp==NULL)
        {
            fprintf(stderr, "Input file '%s': %s\n",argv[2],strerror(errno));
            exit(-1);
        }

    }
    // if file name not provided, then read from the command prompt
    else
    {
      if(strncmp(argv[1],"sort",10)!=0)
        {
        fprintf(stderr, "Malformed command: Please enter appropriate command\nThe second argument should be 'sort'\n");
        exit(-1);
        }
        
      else
        fp=stdin;
      
    }

   int count=0;;

    // read line by line from file or command prompt
    while((fgets(send_buf, sizeof(send_buf), fp)) != NULL) 
    {  

      count++;
      if(strlen(send_buf)>1024)
      {
        fprintf(stderr, "Line %d: Length of the string is too long\nQuit Execution!\n",count);
        exit(-1);
      }
      
      i=0;
      token=NULL;
      token = strtok(send_buf, "\t\n");
      value[i] = strdup(token);
    
      
      while(token)
      {
          i++;
          token = strtok(NULL, "\t\n");
          if(token)
          {
              value[i] = strdup(token);
          }
          
      }

      // Check to see if all the fields are provided
      
      if(i>4)
      {
            fprintf(stderr, "Line %d: Too many fields entered.\nPlease enter the following four: Transaction Type, Timestamp, Amount, Description\nQuit Execution!\n",count);
            exit(-1);
      }

      if(i<4)
      {
            fprintf(stderr, "Line %d: The fields are not according to file format.\nPlease enter the following four: Transaction Type, Timestamp, Amount, Description.\nQuit Execution!\n",count);
            exit(-1);
      }

      
      // Check for Transaction type
     
        if(value[0][0]!='-'&& value[0][0]!='+')
        {
            fprintf(stderr, "Line %d: Enter the right Transaction type, '+' for deposit and '-' for withdrawal.\nQuit Execution!\n",count);
            exit(-1);
        }

      // Check the unix Timestamp validity
     

      if(strlen(value[1])>=11)
      {
           fprintf(stderr, "Line %d: Timestamp corrupted.\nQuit Execution!\n",count);
           exit(-1);
      }

     // Check if there is any description written
      if(strlen(value[3])==0)
      {
        fprintf(stderr, "Line %d: Please enter the description for the transaction.\nQuit Execution!\n",count);
        exit(-1);
      }



      // Object is allocated for every iteration to ensure that it does not overlap
      bankobj *bank;
      bank = (bankobj*)malloc(sizeof(bankobj));

      amt=NULL;

      amt=value[2];

      // Tokenizing
      // Peice of code was used in my previous project EE450- Socket programming

      char *amount_check=(char *)malloc(sizeof(amount_check));
      amount_check=NULL;
      amount_check = strtok(amt, ".");
      val[l] = strdup(amount_check);
      
      while(amount_check)
      {
          l++;
          amount_check = strtok(NULL, ".");
          if(amount_check)
          {
              val[l] = strdup(amount_check);
          }
          
      }
      l=0;

      // Check the validity of Amount
      
      if(strlen(val[0])>7)
      {
        fprintf(stderr,"Line %d: The amount is greater than 10,000,000.00 (7 digits)\nQuit Execution!\n",count);
        exit(-1);
      }

      if(strlen(val[1])>2)
      {
        fprintf(stderr,"Line %d: The cents in the transaction amount is greater than 2 digits\nQuit Execution!\n",count);
        exit(-1);
      }

      sprintf(value[2],"%s.%s",val[0],val[1]);

      // Assigning the tokenized pieces to the structure
      
      bank->type=value[0][0];
      bank->time=atoi(value[1]);
      bank->amount=value[2];
      bank->description=value[3];
      bank->lines=count;

      // Amount entered cannot be a negative value

      check= atof(bank->amount);
      if(check<0)
      {
        fprintf(stderr,"Line %d: Invalid amount entered\nQuit Execution!\n",count);
        exit(-1);
      }

      // Check if the Timestamp is greater than the current time

      if(bank->time>curtime)
      {
        fprintf(stderr, "Line %d: Timestamp is greater than the current time.\nQuit Execution!\n",count);
        exit(-1);
      }

      // Check if the Timestamp is lesser than zero

      if(bank->time<0)
      {
        fprintf(stderr, "Line %d: Timestamp cannot be lesser than 0.\nQuit Execution!\n",count);
        exit(-1);
      }
      

      //Appending the objects into a list
      My402ListAppend(&list, (void*)bank);


    }

    

    j=My402ListLength(&list);


    // Bubble sort is used to sort the Timestamp
    // implemented using the My402list and My402listElem

    BubbleSortForwardList(&list,j);

    // To print the final output

    Printoutput(&list);

  
    
    

   return 0;

    
}

    
    

    
