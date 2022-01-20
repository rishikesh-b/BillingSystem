#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

void generatebillheading(char name[50],char date[30],char time[30]) //two arguments for name and date
{
    printf("\n\n");
    // \t is used for spacing(4 spaces)
    printf("        .-----------------------.");
    printf("\n\t|                       |\n\t|     ABC RESTAURANT    |");
    printf("\n\t|                       |");
    printf("\n        '-----------------------'\n"); // name of the restaurant
    
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

// function for bill body taking input of item price and qty of material and displaying
void generatebillbody(char item[30],int qty,float price)
{
     printf("%s\t\t",item);
     printf("%d\t\t",qty);
     printf("%.2f\t\t",qty*price);
     printf("\n");
}
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
    FILE *lg;
    int option;
    char name1[30],psword[30],cpsword[30];
    char Saveinfo = 'y';
    struct details detail,det,detmatch;
    system("cls");
    printf("\n\t........Choose your desired option........\n\n");
    printf("\n\n1.Create Account\n");
    printf("\n\n2.Login to your account\n");
    printf("\n\nYour Choice:\t\t");
    scanf("%d",&option);

    switch(option)
    {   
        case 1:

        fgetc(stdin);
        system("cls");
        printf("\n\nEnter your name:\t ");
        fgets(detail.name,30,stdin);
        detail.name[strlen(detail.name)-1]=0;
        printf("\n\nCreate your username:\t");
        fgets(detail.username,30,stdin);
        detail.username[strlen(detail.username)-1]=0;
        printf("\n\nEnter your password:\t");
        fgets(detail.password,30,stdin);
        detail.password[strlen(detail.password)-1]=0;
        printf("\n\n Confirm password:\t");
        scanf("%s",cpsword);
        if(strcmp(detail.password,cpsword)==0){
        printf("\n\n\tDo You want to save the details?[y/n]\t");
        scanf("%s",&Saveinfo);
        if(Saveinfo=='y')
        {
            lg=fopen("logindetails.dat","ab");
            fwrite(&detail,sizeof(struct details),1,lg);
            if(fwrite!=0)
            printf("\n\t\tSuccessfully Saved");
            
            else
            printf("\n Error Occurred");
            fclose(lg);
            goto label;
            
        }
        break;

        case 2:

        label:
        fgetc(stdin);
        system("cls");
        printf("\n\n\n\t\tLogin\n\n");
        printf("\n\nEnter Your Username:\t");
        fgets(name1,30,stdin);
        name1[strlen(name1)-1]=0;
        printf("\n\nEnter Your Password:\t");
        fgets(psword,30,stdin);
        psword[strlen(psword)-1]=0;

            lg =fopen("logindetails.dat","rb");
            while(fread(&detmatch,sizeof(struct details),1,lg))
            {   
                
                if((strcmp(detmatch.username,name1)==0)&&(strcmp(detmatch.password,psword)==0))
                {       system("cls");
                        printf("\n\n\t\tWELCOME %s\n",detmatch.name);
                        sleep(2);
                        FILE *fp, *fp1;
                        char SaveBill = 'y',usrfile[50],usrfile1[50];
                        struct orders ord;
                        struct orders order;
                        struct orders ords;
                        int size,opt,n,found,continuee=0;
                    
                        char name[50];
                        while(continuee==0)
                        {   system("cls");
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
                            case 1:

                            system("cls");
                            printf("\nPlease Enter The Name of The Customer :  ");
                            fgets(ord.customer,50,stdin); // taking name of customer
                            ord.customer[strlen(ord.customer)-1] = 0; //to assign 0 at the end of string
                            strcpy(ord.date,__DATE__);  //DATE is predefined
                            strcpy(ord.time,__TIME__);
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
                            {                                //
                                 generatebillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                            }
                    
                            generatebillfooter(total);   // giving total as argument
                            printf("\nDo You Want To Save The Invoice [y/n]:\t");
                            scanf("%s",&SaveBill);
                    
                            if(SaveBill=='y')  // for saving the bill file management
                            {   sprintf(usrfile,"%s.dat",name1);
                                fp=fopen(usrfile,"ab"); // ab for creating the file
                                fwrite(&ord,sizeof(struct orders),1,fp);
                                if(fwrite!=0){
                                printf("\nSuccessfully Saved");
                                }
                                else
                                printf("\n Error Occurred");
                                fclose(fp);
                            }
                            break;
                    
                            case 2:

                            system("cls");
                            sprintf(usrfile,"%s.dat",name1);
                            if(fp =fopen(usrfile,"rb"))
                            {   printf("\n\t*Your Previous Invoices*");
                                while (fread(&order,sizeof(struct orders),1,fp))
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
                                if (fp !=NULL) 
                                {
                                    fseek (fp, 0, SEEK_END);
                                    size = ftell(fp);
                    
                                    if (0 == size) 
                                    {
                                        system("cls");
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
                    
                            case 3:

                            printf("\nEnter The Name of The Customer:\t");
                            fgets(name,50,stdin);
                            name[strlen(name)-1]=0;
                            system("cls");
                            sprintf(usrfile,"%s.dat",name1);
                            if(fp =fopen(usrfile,"rb"))
                            {   printf("\n\t*Invoice of %s*",name);
                                while (fread(&ords,sizeof(struct orders),1,fp))
                                {   
                                    float tot=0;
                                    if(!strcmp(ords.customer,name))
                                    {
                                        generatebillheading(ords.customer,ords.date,ords.time);
                                        for(int i=0;i<ords.numofitems;i++)
                                        {
                                            generatebillbody(ords.itm[i].item,ords.itm[i].qty,ords.itm[i].price);
                                            tot+=ords.itm[i].qty*ords.itm[i].price;
                    
                                        }
                                        generatebillfooter(tot);
                                        invoicefound =1;
                                    }
                                }
                                if(!invoicefound)
                                {    system("cls");
                                    printf("\nSorry The Invoice For %s does not exist",name);
                                }
                                fclose(fp);
                            }
                            else
                            {
                                printf("\n\tFile does not exist");
                            }
                            break;
                            
                            case 4:

                            printf("\nEnter name of invoice to delete: ");
                            fgets(name,50,stdin);
                            name[strlen(name)-1]=0;
                            system("cls");
                            sprintf(usrfile,"%s.dat",name1);
                            if(fp = fopen(usrfile,"rb")){
                            sprintf(usrfile1,"%stemp.dat",name1);
                            fp1 = fopen(usrfile1,"w+");     //temporary file to store data
                            found=0;
                            while(fread(&ord,sizeof(struct orders),1,fp))
                            {
                                if(strcmp(ord.customer,name)==0)    //strcmp returns 0    
                                {   
                                    found=1;
                                }
                                else
                                {
                                    fwrite(&ord,sizeof(struct orders),1,fp1);
                                }
                            }
                            fclose(fp);
                            fclose(fp1);
                            
                            
                            if(found==1)
                            {   
                                fp1 = fopen(usrfile1,"rb");
                                fp = fopen(usrfile,"wb");
                                
                                while(fread(&ord,sizeof(struct orders),1,fp1)){
                                    fwrite(&ord,sizeof(struct orders),1,fp);
                                }
                                printf("\n\ninvoice deleted Successfully\n");
                                fclose(fp);
                                fclose(fp1);
                                
                            }
                            else
                            {
                                printf("\nSorry The Invoice For %s doesnot exists",name);
                            }
                            remove(usrfile1);
                            }
                            else{
                                printf("\nFile does not exist\n");
                            }
                            break;
                    
                            case 5:
                            printf("\n\n\t    Thanks For Using Our Service\n\n\n\n");
                            exit(0);        //for ending the programme
                            break;
                    
                            default:
                            printf("Sorry Invalid Option");
                            break;
                    
                    
                        }
                        printf("\nPress 0 to do another operation: ");
                        scanf("%d",&continuee);
                        }
                        printf("\n\n");


                }
            }
            if((strcmp(detmatch.username,name1)!=0)||(strcmp(detmatch.password,psword)!=0)){
            printf("\n\nWrong details\n");
            }
            fclose(lg);
        }
        else{
            printf("\n\n\t\tPassword does not match\n\n");
        }    
        break;
    }
 return 0;   
}