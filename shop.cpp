#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<fstream>
#include<string.h>
#include<ctype.h>
using namespace std;
void placeorder();
void invoice(int,int*,int*);
void Entry_menu();
class product
{   
    int pronum;
    char name[100];
    float price,qty,tax,discount;
    public:
    product()
    {
        pronum = 0;
        strcpy(name,"Not set");
        price=qty=tax=discount=0.0;
    }
    void createProduct()
    {
        cout<<"\n\n\tEnter the product number: ";
        cin>>pronum;
        cout<<"\n\n\tEnter the name of the product: ";
        cin>>name;
        cout<<"\n\n\tEnter the Price of the product:";
        cin>>price;
        cout<<"\n\n\tEnter the Discount of the product:";
        cin>>discount;
        
    }
    void showProduct()
    {
        cout<<"\n\n\tThe product number: "<<pronum;
        cout<<"\n\n\tThe name of the product: "<<name;
        cout<<"\n\n\tThe price of the product: "<<price;
        cout<<"\n\n\tThe discount of the product: "<<discount;
    }
    int returnpronum()
    {
        return pronum;
    }
    float returnprice()
    {
        return price;
    }
    char* returnname()
    {
        return name;
    }
    float returndiscount()
    {
        return discount;
    }
    
};
fstream fp;
product pr;

void writeproduct()
{
    system("clear");
    fp.open("shop.dat",ios::out|ios::app);
    pr.createProduct();
    fp.write((char*)&pr,sizeof(product));
    fp.close();
    cout<<"\n\n\tThe product has been created succesfully!!!!!";

}
void displayall()
{
    system("clear");
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
    cout<<"\n\n\t\tProduct Database";
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
    fp.open("shop.dat",ios::in|ios::app);
    while(fp.read((char*)&pr,sizeof(product)))
    {
        pr.showProduct();
    }
    fp.close();
}
void display_sp(int n)
{   
    cout<<"\n\n\n\n";
    system("clear");
    int flag =0;
    fp.open("shop.dat",ios::in|ios::app);
    while(fp.read((char*)&pr,sizeof(product)))
    {
        if(pr.returnpronum()==n)
        {
            flag=1;
            pr.showProduct();
        }
    }
    fp.close();
    if(flag==0)
    cout<<"\n\n\tThis product does not exist";
}
void modify()
{
    system("clear");
    int no,flag=0;
    cout<<"\n\n\tEnter the product number of the product t0 modify: ";
    cin>>no;
    fp.open("shop.dat",ios::in|ios::out|ios::app);
    while(fp.read((char*)&pr,sizeof(product)))
    {
        if(pr.returnpronum()==no)
            {
                pr.showProduct();
                cout<<"\n\nPlease the new details of the product:- ";
                pr.createProduct();
                int pos=-1*sizeof(product);
                fp.seekp(pos,ios::cur);
                fp.write((char  *)&pr,sizeof(product));
                cout<<"\n\n\tRecord updated";
                flag=1;
            }    

    }
    fp.close();
    if(flag==0)
        cout<<"\n\n\tProduct not found";

}
void deleteProduct()
{
    system("clear");
    int no;
    cout<<"\n\n\tDelete Product";
    cout<<"\n\n\tEnter the Product number of the product to delete: ";
    cin>>no;
    fp.open("shop.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("temp.dat",ios::out);
    fp.seekp(0,ios::beg);
    while(fp.read((char*)&pr,sizeof(product)))
    {
        if(pr.returnpronum()!=no)
        {
            fp2.write((char*)&pr,sizeof(product));
        }
    }
    fp2.close();    fp.close();
    remove("shop.dat");
    rename("temp.dat","shop.dat");
    cout<<"\n\n\tRecord Deleted";
}

void menu()
{   
    system("clear");
    system("clear");
    fp.open("shop.dat",ios::in);
    if(!fp)
    {
        cout<<"\n\n\tError!! File not found"<<endl;
        cout<<"\n\n\tGo to the Admin menu to create Product\n\n";
        exit(0);
    }
    cout<<"\n\n\t\tWelcome to the store";
    cout<<"\n\n=============================================================";
    cout<<"\n\n\t\tProduct Menu";
    cout<<"\n\n=============================================================";
    cout<<"\n\nProduct number\t\tProduct Name\t\tPrice\n";
    while(fp.read((char*)&pr,sizeof(product)))
    {
        cout<<"\n\n"<<pr.returnpronum()<<"\t\t\t"<<pr.returnname()<<"\t\t\t"<<pr.returnprice()<<endl;
    }
    fp.close();
    placeorder();
}
void placeorder()
{
    int order[50],quantity[50],c=0;
    
    string choice;
    cout<<"\n\n______________________________________________________________";
    cout<<"\n\n\t\tPlace order";
    cout<<"\n\n______________________________________________________________\n\n";
    do{
    cout<<"\nEnter the Product number of the product: ";
    cin>>order[c];
    cout<<"\nEnter the Quantity: ";
    cin>>quantity[c];
    c++;
    cout<<"\nDo you want to order another item: ";
    cin>>choice;
    }while(choice[0]=='y'||choice[0]=='Y');
    cout<<"\n\n\tThank you for placing the order";
    system("clear");
    invoice(c,order,quantity);
}
void invoice(int c,int order[],int quantity[])
{   
    float amt,damt,total=0;
    cout<<"\n\n\t\tInvoice-";
    cout<<"\n__________________________________________________________________________________________\n";
    cout<<"\n\nProduct Number\t\tProduct Name\t\tPrice\t\tdiscount\t\tAfter Discount\n";
    for(int x=0;x<= c;x++)
    {
            fp.open("shop.dat",ios::in);
            fp.read((char*)&pr,sizeof(product));
            while(!fp.eof())
            {
                if(pr.returnpronum()==order[x])
                {
                    amt=pr.returnpronum()*quantity[x];
                    damt=amt-(amt*pr.returndiscount()/100);
                    cout<<"\n\n"<<pr.returnpronum()<<"\t\t\t"<<pr.returnname()<<"\t\t\t"<<pr.returnprice()<<"\t\t\t"<<pr.returndiscount()<<"\t\t\t"<<damt<<endl;
                    total+=damt;
                }
                fp.read((char*)&pr,sizeof(product));
            }
            fp.close();
    }
    cout<<"\n__________________________________________________________________________________________\n";
    cout<<"\n\n\tTotal = "<<total<<endl;
}
void AdminMenu()
{
    system("clear");
    int ch;
    system("clear");
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n";
    cout<<"\t\tAdmin Menu"<<endl;
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n";
    cout<<"\n\n\t1.Create Product";
    cout<<"\n\n\t2.Display All products";
    cout<<"\n\n\t3.Query";
    cout<<"\n\n\t4.Modify Product";
    cout<<"\n\n\t5.Delete Product";
    cout<<"\n\n\t6.Customer View";
    cout<<"\n\n\t7.Back to main menu";
    cout<<"\n\n\t8.Exit";
    cout<<"\n\n\tEnter your choice(1-8): ";
    cin>>ch;
    switch(ch)
    {
        case 1:
            writeproduct();
            break;
        case 2:
            displayall();
            break;
        case 3:
        {
            int n;
            cout<<"\n\n\tEnter the product number: ";
            cin>>n;
            display_sp(n);
        }break;
        case 4:
            modify();
            break;
        case 5:
            deleteProduct();
            break;
        case 6:
            menu();
            break;
        case 7:
            
            break;
        case 8:
            exit(0);
            break;
        default:
            cout<<"\n\n\tWrong option\n";
            AdminMenu();
    }
}
void Entry_menu()
{
    system("clear");
    int ch1;
    do{
    cout<<"\n\n\tSelect one of the following options\n\n";
    cout<<"\n\n\t1.Customer";
    cout<<"\n\n\t2.Admin";
    cout<<"\n\n\t3.Exit";
    cout<<"\n\n\tEnter tour choice(1-3): ";
    cin>>ch1;
    switch(ch1)
    {
        case 1:
            menu();
            break;
        case 2:
            AdminMenu();
            break;
        case 3:
            exit(0);
            break;
        default:
        cout<<"\n\n\tInvalid Option";
        Entry_menu();


    }
    }while(ch1>=1&&ch1<=3);
}

int main()
{   
    Entry_menu();
}
