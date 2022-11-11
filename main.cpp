#include <iostream>
# include<algorithm>
using namespace std;

int total_books;
int total_users;

struct book
{
    int id;
    string name;
    int total_quantity;
    int quantity_borrowed[10]={0};
    void read()
    {
        cout<<"enter book info: id & name & total_quentity :";
        cin>>id>>name>>total_quantity;
    }
};
struct user
{
    int id;
    string name;
    int total_borrowed[10][10]={0};
    int borrowed_nums[10]={0};
    void read()
    {
        cout<<"enter id & name :";
        cin>>id>>name;
    }
};

book books[10];
user users[10];

void search_books_by_prefix()
{
    string str;
    cout<<"enter book name prefix:"<<endl;
    cin>>str;
    int found;
    int check=0;
    for(int i=0;i<total_books;i++)
    {
        int found=1;
        for(int j=0;j<str.size();j++)
        {
            if(!(str[j]==books[i].name[j]))
            {
                found=0;
            }
        }
        if(found==1)
        {
            cout<<books[i].name<<endl;
            check=1;
        }
    }
    if(check==0)
    {
        cout<<"no books with such prefix"<<endl;
    }
}

void user_borrow_book()
{
    string use;
    string nam;
    cout<<"enter user name and book name\n";
    cin>>use>>nam;

    for(int i=0;i<total_users;i++)
    {
        if(use==users[i].name)
        {
           for(int j=0;j<total_books;j++)
           {
               if(nam==books[j].name)
               {
                  users[i].total_borrowed[i][users[i].borrowed_nums[i]]=books[j].id;
                  users[i].borrowed_nums[i]++;
                  books[j].quantity_borrowed[j]++;
                  break;
               }
           }
        }
    }
}

void print_who_borrowed_book_by_name()
{
    string s;
    cout<<"enter book name\n";
    cin>>s;
    int d;
    for(int i=0;i<total_books;i++)
    {
        if(s==books[i].name)
        {
            d=books[i].id;
        }
    }
    for(int i=0;i<total_users;i++)
    {
        int k=0;
        for(int j=0;j<users[i].borrowed_nums[i];j++)
        {
            if(users[i].total_borrowed[i][k++]==d)
            {
               cout<<users[i].name<<endl;
            }
        }
    }
}

bool cmp_book_by_id(book &a , book &b)
{
   return a.id<b.id;
}

bool cmp_book_by_name(book &a , book &b)
{
   return a.name<b.name;
}

void print_library_by_id()
{
    sort(books, books + total_books, cmp_book_by_id);
    for(int i=0;i<total_books;i++)
    {
        cout<<"id = "<<books[i].id<<" name = "<<books[i].name
        <<" total_quantity = "<<books[i].total_quantity<<" total_borrowed = "
        <<books[i].quantity_borrowed[i]<<endl;
    }
}

void print_library_by_name()
{
    sort(books, books + total_books, cmp_book_by_name);
    for(int i=0;i<total_books;i++)
    {
        cout<<"id = "<<books[i].id<<" name = "<<books[i].name
        <<" total_quantity = "<<books[i].total_quantity<<" total_borrowed = "
        <<books[i].quantity_borrowed[i]<<endl;
    }
}

void user_return_book()
{
    string ss,nn;
    cout<<"enter user name and book name"<<endl;
    cin>>ss>>nn;
    for(int i=0;i<total_users;i++)
    {
        if(users[i].name==ss)
        {
            int d;
            for(int j=0;j<books[i].total_quantity;j++)
            {
               if(nn==books[i].name)
               {
                   d=books[i].id;
               }
            }
            books[i].quantity_borrowed[i]--;
            for(int s=0;s<users[i].borrowed_nums[i];s++)
            {
                if(users[i].total_borrowed[i][s]==d)
                {
                    for(int k=s;k<users[i].borrowed_nums[i]-1;k++)
                    {
                        users[i].total_borrowed[i][s]=users[i].total_borrowed[i][s+1];
                    }
                    users[i].borrowed_nums[i]--;
                }
            }
        }
    }
}

void print_users()
{
    for(int i=0;i<total_users;i++)
    {
        cout<<"user "<<users[i].name<<" id "<<users[i].id<<" borrowed books ids :";
        for(int j=0;j<users[i].borrowed_nums[i];j++)
        {
            cout<<users[i].total_borrowed[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

struct library_system
{
    library_system()
    {
        total_books=total_users=0;
    }

    void run()
    {
        while(true)
        {
            int choice=menu();
            if (choice == 1)
				add_book();
			else if (choice == 2)
				search_books_by_prefix();
			else if (choice == 3)
				print_who_borrowed_book_by_name();
			else if (choice == 4)
				print_library_by_id();
			else if (choice == 5)
				print_library_by_name();
			else if (choice == 6)
				add_user();
			else if (choice == 7)
				user_borrow_book();
			else if (choice == 8)
				user_return_book();
			else if (choice == 9)
				print_users();
			else
				break;
        }
    }
    int menu()
    {
        int choice;
        while(true)
        {
            cout<<"Library Menu"<<endl;
            cout<<"1) add book"<<endl;
            cout<<"2) search_books_by_prefix"<<endl;
            cout<<"3) print_who_borrowed_abook_by_name"<<endl;
            cout<<"4) print_library_by_id"<<endl;
            cout<<"5) print_library_by_name"<<endl;
            cout<<"6) add_user"<<endl;
            cout<<"7) user_borrow_book"<<endl;
            cout<<"8) user_return_book"<<endl;
            cout<<"9) print_users"<<endl;
            cout<<"10) exit\n"<<endl;
            cout<<"Enter your menu choice [1 : 10]:"<<endl;
            cin>>choice;
            while(!(choice>=1&&choice<=10))
            {
                cout<<"invalid choice please try again"<<endl;
                choice=-1;
            }
            return choice;
        }
    }

    void add_book()
    {
        books[total_books++].read();

    }

    void add_user()
    {
        users[total_users++].read();
    }

};

int main()
{
   library_system library;
   library.run();
}

