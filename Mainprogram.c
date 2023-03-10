#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ncurses.h>

void generatebillheading(char name[50],char date[30],char time[30]) //three arguments for name, date and time
{
    printf("\n\n");
    // \t is used for spacing(4 spaces)
    printf("        .-----------------------.");
    printf("\n\t|                       |\n\t|     ABC RESTAURANT    |");    // name of the restaurant
    printf("\n\t|                       |");
    printf("\n        '-----------------------'\n"); 
    
    printf("\n-----------------------------------------\n");
    printf("\nDate:%s",date);
    printf("\tTime:%s",time);
    printf("\n\nINVOICE TO: %s",name); // taking string as input for name
    printf("\n");
    printf("\n-----------------------------------------\n");
    printf("Items\t\t");
    printf("Quantity\t");
    printf("Total\t\t");
    printf("\n-----------------------------------------");
    printf("\n\n\n");  //new line
}

// function to generate total amount including taxes
void generatebillfooter(float total)
{
    printf("\n");
    float dis = 0.1*total; // dicount from the total price
    float nettotal = total-dis;
    float cgst=0.09*nettotal,grandtotal=nettotal + 2*cgst; // nettotal +cgst +sgst and sgst=cgst
    printf("-----------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t-%.2f","%",dis);
    printf("\n\t\t\t\t---------");
    printf("\nNet Total\t\t\t%.2f",nettotal);
    printf("\nCGST @9%s\t\t\t+%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t+%.2f","%",cgst);
    printf("\n---------------------------------------\n");
    printf("\nGrand Total\t\t\t=%.2f Rs.",grandtotal);
    printf("\n---------------------------------------\n");
}

// function for bill body taking input of item, price and qty of material and displaying
void generatebillbody(char item[30],int qty,float price)
{
     printf("%s\t\t",item);
     printf("%d\t\t",qty);
     printf("%.2f\t\t",qty*price);
     printf("\n");
}
//declaring stuctures
 struct items       
 {
  char item[20];
  float price;
  int qty;
 };

 struct orders
 {
     char customer[50];
     char date[50];
     char time[50];
     int numofitems;
     struct items itm[50];

 };

struct details
{ char username[30];
  char password[30];
  char name[30];

};

int main()
{   
    

    FILE *lg;       //declaring file pointer for login details
    int option;
    char name1[30],psword[30],cpsword[30];
    char Saveinfo = 'y';
    struct details detail,det,detmatch;     //variable declaration of structure
    system("clear");
    printf("\n\t........Choose your desired option........\n\n");
    printf("\n\n1.Create Account\n");
    printf("\n\n2.Login to your account\n");
    printf("\n\nYour Choice:\t\t");
    scanf("%d",&option);

    // switch case for different choices
    switch(option)      
    {   
        case 1:

        fgetc(stdin);
        system("clear");        //to clear previous output from the screen
        printf("\n\nEnter your name:\t ");
        fgets(detail.name,30,stdin);        // to take string as an input from user
        detail.name[strlen(detail.name)-1]=0;    //to assign 0 at the end of string
        printf("\n\nCreate your username:\t");
        fgets(detail.username,30,stdin);
        detail.username[strlen(detail.username)-1]=0;

        initscr();
        noecho();
        char passwd[10];
        int p=0; char ch;
        printw("Enter Password: ");
        while(1)
        {
          ch=getch();
          if(ch==10)
          {
              break;
          }
          else if(ch==127)
          {
              if(p>0)
              {
                  p--;
                  passwd[p]='\0';
                  printw("\b \b");
              }
          }
          else
          {
              passwd[p]=ch;
              p++;
              printw("*");
          }
        }
        passwd[p]='\0';
        printw("\n\nConfirm password: ");
        p=0;
            while(1)
        {
          ch=getch();
          if(ch==10)
          {
              break;
          }
          else if(ch==127)
          {
              if(p>0)
              {
                  p--;
                  cpsword[p]='\0';
                  printw("\b \b");
              }
          }
          else
          {
              cpsword[p]=ch;
              p++;
              printw("*");
          }
        }
        cpsword[p]='\0';
        endwin();
        strcpy(detail.password,passwd);               
        if(strcmp(detail.password,cpsword)==0){     //strcmp returns 0 if strings match
        printf("\n\n\tDo You want to save the details?[y/n]\t");
        scanf("%s",&Saveinfo);
        if(Saveinfo=='y')
        {
            lg=fopen("logindetails.dat","a+");          //open login file in append mode
            fwrite(&detail,sizeof(struct details),1,lg);    //to write data into the file in form of structure
            if(fwrite!=0)                   //if data is stored in file
            printf("\n\t\tSuccessfully Saved");
            
            else
            printf("\n Error Occurred");
            fclose(lg);      //close file
            goto label;      //to jump to case 2
            
        }
        break;

        case 2:

        label:
        fgetc(stdin);
        system("clear");        //to clear previous output
        printf("\n\n\n\t\tLogin\n\n");
        printf("\n\nEnter Your Username:\t");
        fgets(name1,30,stdin);          // to take string as an input from user
        name1[strlen(name1)-1]=0;       //to assign 0 at the end of string
        initscr();
        noecho();
        char passwd[10];
        int p=0; 
        clear();
        printw("Enter Your Password: ");
        while(1)
        {
          ch=getch();
          if(ch==10)
          {
              break;
          }
          else if(ch==127)
          {
              if(p>0)
              {
                  p--;
                  passwd[p]='\0';
                  printw("\b \b");
              }
          }
          else
          {
              passwd[p]=ch;
              p++;
              printw("*");
          }
        }
        passwd[p]='\0';
        endwin();
        strcpy(psword,passwd);
            lg =fopen("logindetails.dat","r+");         //open login file in read mode
            while(fread(&detmatch,sizeof(struct details),1,lg))     //to read data from file one by one
            {   
                
                if((strcmp(detmatch.username,name1)==0)&&(strcmp(detmatch.password,psword)==0))
                {       system("clear");
                        printf("\n\n\t\tWELCOME %s\n",detmatch.name);
                        sleep(2);           // to pause the screen for 2 seconds
                        FILE *fp, *fp1;     //declaring file pointers for customer details
                        char SaveBill = 'y',usrfile[50],usrfile1[50];
                        struct orders ord;
                        struct orders order;
                        struct orders ords;
                        int size,opt,n,found,continuee=0;
                    
                        char name[50];
                        while(continuee==0)     // to loop the main menu
                        {   system("clear");
                            float total=0;
                            int invoicefound=0;
                            printf("        .-----------------------.");
                            printf("\n\t|                       |\n\t|     ABC RESTAURANT    |");
                            printf("\n\t|                       |");
                            printf("\n        '-----------------------'\n");
                            printf("\n\n       Select Your Perferred Option");
                            printf("\n\n1. Generate Invoice\n");
                            printf("\n2. Show All Invoices\n");
                            printf("\n3. Search Invoices\n");
                            printf("\n4. Delete invoice\n");
                            printf("\n5. Exit\n");
                            printf("\n\nYour Choice:\t");
                            scanf("%d",&opt);
                            fgetc(stdin); //to consume \n generated by fgets
                            switch(opt)
                        {
                            case 1:     //for generating invoice

                            system("clear");
                            printf("\nPlease Enter The Name of The Customer :  ");
                            fgets(ord.customer,50,stdin); // taking name of customer
                            ord.customer[strlen(ord.customer)-1] = 0; //to assign 0 at the end of string
                            strcpy(ord.date,__DATE__);  //DATE is predefined
                            strcpy(ord.time,__TIME__);  //TIME is predefined
                            printf("\nPlease Enter The Number Of The Items:\t"); // number of items customer bought
                            scanf("%d",&n);
                            ord.numofitems=n; // assigning n to numofitems
                    
                            for(int i=0;i<n;i++) // for differmt items
                            {   fgetc(stdin);
                    
                                printf("\n\n");
                                printf("Please Enter The Name Of Item %d:  ",i+1);
                                fgets(ord.itm[i].item,20,stdin); // name of the item
                                ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
                                printf("\nPlease enter the Quantity:\t");
                                scanf("%d",&ord.itm[i].qty);     //quantity of the item
                                printf("\nPlease Enter The Unit Price:\t");
                                scanf("%f",&ord.itm[i].price);   // price of one item
                                total += ord.itm[i].qty*ord.itm[i].price; // finding total
                            }
                            generatebillheading(ord.customer,ord.date,ord.time); // give name and predefined date as argument
                            for(int i=0;i<ord.numofitems;i++)
                            {                                
                                 generatebillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                            }
                    
                            generatebillfooter(total);   // giving total as argument
                            printf("\nDo You Want To Save The Invoice [y/n]:\t");
                            scanf("%s",&SaveBill);
                    
                            if(SaveBill=='y')  // for saving the bill file management
                            {   snprintf(usrfile, sizeof(usrfile),"%s.dat",name1);        // to store file name as user name in a string
                                fp=fopen(usrfile,"a+"); // ab for creating the file
                                fwrite(&ord,sizeof(struct orders),1,fp);
                                if(fwrite!=0){
                                printf("\nSuccessfully Saved");
                                }
                                else
                                printf("\n Error Occurred");
                                fclose(fp);
                            }
                            break;
                    
                            case 2:     //to show all invoices

                            system("clear");
                            snprintf(usrfile, sizeof(usrfile),"%s.dat",name1);
                            if(fp =fopen(usrfile,"r+"))      // if file exists
                            {   printf("\n\t*Your Previous Invoices*");
                                while (fread(&order,sizeof(struct orders),1,fp))    // to read data from file one by one
                                {   
                                    float tot=0;
                                    generatebillheading(order.customer,order.date,order.time);
                                    for(int i=0;i<order.numofitems;i++)
                                    {
                                        generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                                        tot+=order.itm[i].qty*order.itm[i].price;
                    
                                    }
                                    generatebillfooter(tot);
                                    printf("\n\n\n");
                                }
                                if (fp !=NULL)      //if file exists
                                {
                                    fseek (fp, 0, SEEK_END);   // to move file pointer to the end of user file
                                    size = ftell(fp);       //to store the current file position wrt starting
                    
                                    if (0 == size) 
                                    {
                                        system("clear");
                                        printf("\n\n\t  No Invoices available.\n");
                                    }
                                }
                                fclose(fp);
                            }
                            else
                            {
                                printf("\n\tFile does not exist.");
                            }
                            break;
                    
                            case 3:     //to search invoice

                            printf("\nEnter The Name of The Customer:\t");
                            fgets(name,50,stdin);       // taking name of customer
                            name[strlen(name)-1]=0;     //to assign 0 at the end of string
                            system("clear");
                            snprintf(usrfile, sizeof(usrfile),"%s.dat",name1);
                            if(fp =fopen(usrfile,"r+"))     //if file exists
                            {   printf("\n\t*Invoice of %s*",name);
                                while (fread(&ords,sizeof(struct orders),1,fp))     // to read data from file one by one
                                {   
                                    float tot=0;
                                    if(!strcmp(ords.customer,name))     //strcmp returns 0 if strings match
                                    {
                                        generatebillheading(ords.customer,ords.date,ords.time);
                                        for(int i=0;i<ords.numofitems;i++)  //for different items
                                        {
                                            generatebillbody(ords.itm[i].item,ords.itm[i].qty,ords.itm[i].price);
                                            tot+=ords.itm[i].qty*ords.itm[i].price;
                    
                                        }
                                        generatebillfooter(tot);
                                        invoicefound =1;
                                    }
                                }
                                if(!invoicefound)   //if invoicefound=0
                                {    system("clear");
                                    printf("\nSorry The Invoice For %s does not exist",name);
                                }
                                fclose(fp); //close file
                            }
                            else
                            {
                                printf("\n\tFile Does Not Exist");
                            }
                            break;
                            
                            case 4:     //for deleting invoice

                            printf("\nEnter name of invoice to delete: ");
                            fgets(name,50,stdin);
                            name[strlen(name)-1]=0;
                            system("clear");
                            snprintf(usrfile, sizeof(usrfile),"%s.dat",name1);
                            if(fp = fopen(usrfile,"r")){       //if file exists
                            snprintf(usrfile1, sizeof(usrfile1),"%stemp.dat",name1);
                            fp1 = fopen(usrfile1,"w");     //open temporary file in write mode to store data
                            found=0;
                            while(fread(&ord,sizeof(struct orders),1,fp))    // to read data from file one by one
                            {
                                if(strcmp(ord.customer,name)==0)    // strcmp returns 0 if strings match    
                                {   
                                    found=1;
                                }
                                else
                                {
                                    fwrite(&ord,sizeof(struct orders),1,fp1);   // write data in temp file
                                }
                            }
                            fclose(fp);         //close files
                            fclose(fp1);
                            
                            
                            if(found==1)
                            {   
                                fp1 = fopen(usrfile1,"r");  //open temporary file in read mode
                                fp = fopen(usrfile,"w");    //open user file in write mode
                                
                                while(fread(&ord,sizeof(struct orders),1,fp1)){     // to write data from temp file to user file
                                    fwrite(&ord,sizeof(struct orders),1,fp);
                                }
                                printf("\n\n\tInvoice Deleted Successfully\n");
                                fclose(fp);         //close files
                                fclose(fp1);
                                
                            }
                            else
                            {
                                printf("\nSorry The Invoice For %s Does Not Exist\n",name);
                            }
                            remove(usrfile1);       // remove temporary file
                            }
                            else{
                                printf("\nFile Does Not Exist\n");
                            }
                            break;
                    
                            case 5:     //for ending the programme
                            printf("\n\n\t    Thank You For Using Our Service\n\n\n\n");
                            exit(0);        
                            break;
                    
                            default:
                            printf("\nSorry Invalid Option\n");
                            break;
                    
                    
                        }
                        printf("\nPress 0 to do another operation: ");
                        scanf("%d",&continuee);
                        }
                        printf("\n\n");


                }
            }
            if((strcmp(detmatch.username,name1)!=0)||(strcmp(detmatch.password,psword)!=0)){
            printf("\n\nWrong Details\n");
            }
            fclose(lg);
        }
        else{
            printf("\n\n\t\tPassword Does Not Match\n\n");
        }    
        break;
    }
 return 0;   
}
