//
// CSC 125
// File Name: arai1_project1.cpp
// Author: Armaan Rai - 2/13/14

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

const int MAX_BOOKS = 10;

struct Books
{
    string title;
    int number_of_pages;
    int review;
    float price;
};


struct Library
{
    Books shelf[MAX_BOOKS];
    
    //keeps track of the amount of books in the library
    int size;
};

//initializes all the values of books to 0 values
void initialize(Library& library)
{
    int i;
    for(i=0;i<MAX_BOOKS;i++)
    {
        library.shelf[i].title="";
        library.shelf[i].number_of_pages=0;
        library.shelf[i].review=0;
        library.shelf[i].price=0;
    }
}

//displays the menu options and inputs the user's option
void menu(int& input)
{
    cout << "Menu\n";
    cout <<"1. Display List Of Books\n";
    cout <<"2. Find Book\n";
    cout <<"3. Add New Book \n";
    cout <<"4. Delete Book \n";
    cout <<"5. Save List To File \n";
    cout <<"6. Load List From File \n";
    cout <<"7. Sort List \n";
    cout <<"8. Exit\n\n";
    
    cout <<"Enter the number of your option\n";
    cin >>input;
    
    if(input<=0 || input>8)
    {
        cout<<"Please choose a valid option\n";
        input = -1;
    }
    
    
}

// Iterates through the library using the size integer and displays the different books
void display_list_of_books(Library& library)
{
    
    if(library.size==0)
    {
        cout<<"The library is empty \n\n";
    }
    else
    {
        int i;
        for(i=0; i<library.size ; i++)
        {
            cout<<"Book "<<(i+1)<<"\n\n";
            cout<<"Title: "<<library.shelf[i].title<<"\n";
            cout<<"Number of Pages: "<<library.shelf[i].number_of_pages<<"\n";
            cout<<"Review: "<<library.shelf[i].review<<"\n";
            cout<<"Price: "<<library.shelf[i].price<<"\n\n";
        }
    }
}

//Adds a new book variable to the library
void add_new_book(Library& library)
{
    //Checks if the library is full
    if(library.size==10)
    {
        cout<<" The library is full"<<"\n\n";
    }
    else
    {
        library.size++;
        
         //keeps looping until the user gives a valid input for title
        do
        {
            string title;
            cout<<"Enter the Book title ";
            cin>>title;
            int i;
            int new_title=0;
            
            //iterates through the library to see if the same book title already exists
            for(i=0;i<library.size;i++)
            {
                if(library.shelf[i].title==title)
                {
                    cout<<"A book with this title already exists. Use another title \n";
                    new_title = 1;
    
                }
            
            }
            
            if(new_title==1)
            {
                continue;
            }
            
            library.shelf[library.size-1].title = title;
            break;
            
        }while(true);
        
        cout<<"Enter number of pages in the book ";
        cin>>library.shelf[library.size-1].number_of_pages;
        
        //keeps looping until the user gives a valid input for review
        do
        {
            int review;
            cout<<"Rate the book out of 5 ";
            cin>>review;
            
            if(review>5 || review<0)
            {
                cout<<"Invalid rating. ";
                continue;
            }
            
            library.shelf[library.size-1].review = review;
            break;
            
        }while(true);
        
        cout<<"Enter the price ";
        cin>>library.shelf[library.size-1].price;
        
        cout<<"Your book has been added to the library \n\n";
    }
    
    
}

//Removes the book with the same title as the string find
void remove_book(Library& library, string find)
{
    int i;
    
    //Prints error if no books in library
    if(library.size==0)
    {
        cout<<"No books in the library";
    }
    else
    {
        for(i=0; i<library.size; i++)
        {   
            if(library.shelf[i].title == find)
            {
                int j;
                
                //iterates through the filled arrays and makes the current array equal to the next array
                for(j=i; j+1<=library.size-1 ;j++)
                {
                    library.shelf[j].title=library.shelf[j+1].title;
                    library.shelf[j].number_of_pages=library.shelf[j+1].number_of_pages;
                    library.shelf[j].review= library.shelf[j+1].review;
                    library.shelf[j].price= library.shelf[j+1].price;
                }
                
                //makes the last switched array equal to initial values
                library.shelf[j+1].title="";
                library.shelf[j+1].number_of_pages=0;
                library.shelf[j+1].review=0;
                library.shelf[j+1].price=0;
                
                library.size--;
                 cout<<"The Book with title '"<<find<<"' has been deleted from the library\n\n";
                break;
            }
            
        }
    }
    
    
};

//Finds a book according to title in the library
void find_book(Library& library, string find)
{
    //turns the search key to uppercase
    for (int i=0; i < find.size(); i++)
    {
        find[i] = toupper(find[i]);
    }
    

    for(int i=0; i< library.size; i++ )
    {
        string check = library.shelf[i].title;
        int j;
        
        for(j=0 ; j<check.size(); j++ )
        {
            check[j]= toupper(check[j]);
        }
        
        int key_count=0;
        
        //compares each letter of the search key with each letter of a title
        for(j=0; j<check.size(); j++)
        {
            if(find[key_count]== check[j] )
            {
                key_count++;
                if(key_count==find.size())
                {
                    cout<<"The book you are looking for is book number "<<i+1<<" in our library\n\n";
                    cout<<"Title: "<<library.shelf[i].title<<"\n";
                    cout<<"Number of Pages: "<<library.shelf[i].number_of_pages<<"\n";
                    cout<<"Review: "<<library.shelf[i].review<<"\n";
                    cout<<"Price: "<<library.shelf[i].price<<"\n\n";
                }
            }
            else
            {
                key_count=0;
            }
        }
        
        if(key_count==find.size())
        {
            break;
        }
    }
};

//saves a list to an output file
void save_list_to_file(Library& library)
{
    ofstream output;
    
     // open the file for output (change the location to work on your txt file)
    output.open("/Users/Armaanistan/Desktop/My_Stuff/CS/CS125_2/CS125_2/outputFile.txt", ios::out);
    
    if (!output.is_open())
    {
        cout << "File is not open!" << endl;
    }

    int i;
    
    //outputs the information from the library from the output file
    if(library.size!=0)
    {
        int number = library.size ;
        string sentence="";
        float price;
        output<< number << endl;
        
        for(i=0; i<library.size; i++)
        {
            sentence = library.shelf[i].title;
            output<< sentence << endl;
            number = library.shelf[i].number_of_pages;
            output<< number << endl;
            number = library.shelf[i].review;
            output<< number << endl;
            price = library.shelf[i].price;
            output<< price << endl;
        }
        
        
    }
    else
    {
        cout<<"the library is empty\n\n";
    }
    
    //closes output
    output.close();
};

//loads a list from an input file
void load_list_from_file(Library& library)
{
    ifstream input;
    
     // open the file for input (change the location to work on your txt file)
    input.open("/Users/Armaanistan/Desktop/My_Stuff/CS/CS125_2/CS125_2/inputFile.txt", ios::in);
    
    int i;
            
    string sentence = "";
    int number;
    float price;
    
    input>> number;
    
    library.size = number;
    
    //inputs the information to the library from the input file
    for(i=0; i<library.size; i++)
    {
        input>> sentence;
        library.shelf[i].title = sentence;
        input>> number;
        library.shelf[i].number_of_pages = number;
        input>> number;
        library.shelf[i].review = number;
        input>> price;
        library.shelf[i].price = price;
    }
    
    if (!input.is_open())
    {
        cout << "File is not open!" << endl;
    }
    
    //closes the input
    input.close();

};

//swaps between two Book variables in the shelf array using a temporary variable 
void swap(Library& library, int sorted, int min)
{
    
    Books Temp;
    
    Temp.title = library.shelf[sorted].title;
    Temp.number_of_pages = library.shelf[sorted].number_of_pages;
    Temp.review = library.shelf[sorted].review;
    Temp.price = library.shelf[sorted].price;
    
    library.shelf[sorted].title =  library.shelf[min].title;
    library.shelf[sorted].number_of_pages =  library.shelf[min].number_of_pages;
    library.shelf[sorted].review =  library.shelf[min].review;
    library.shelf[sorted].price =  library.shelf[min].price;
    
    library.shelf[min].title =  Temp.title;
    library.shelf[min].number_of_pages = Temp.number_of_pages;
    library.shelf[min].review =  Temp.review;
    library.shelf[min].price =  Temp.price;
    
}


//uses the selection sort algorithm according to title
void sort_title(Library& library, int high_low)
{
    int sorted=0;
    int min=0;
    int j;
    
    
    for(sorted=0; sorted<library.size-1; sorted++)
    {
        min=sorted;
        
        for(j=sorted+1; j<library.size ; j++)
        {
            //compares the elements differently based on the high_low number
            if(high_low==1)
            {
                if(library.shelf[j].title<library.shelf[min].title)
                {
                    min=j;
                }
            }
            else if(high_low==2)
            {
                if(library.shelf[j].title>library.shelf[min].title)
                {
                    min=j;
                }
            }
            
        }
        
        if(min!=sorted)
            swap(library,sorted,min);
        
    }

}

//uses the selection sort algorithm according to pages
void sort_pages(Library& library, int high_low)
{
    int sorted=0;
    int min=0;
    int j;
    
    
    for(sorted=0; sorted<library.size-1; sorted++)
    {
        min=sorted;
        
        for(j=sorted+1; j<library.size ; j++)
        {
            //compares the elements differently based on the high_low number
            if(high_low==1)
            {
                if(library.shelf[j].number_of_pages<library.shelf[min].number_of_pages)
                {
                    min=j;
                }
            }
            else if(high_low==2)
            {
                if(library.shelf[j].number_of_pages>library.shelf[min].number_of_pages)
                {
                    min=j;
                }
            }

        }
        
        if(min!=sorted)
        swap(library,sorted,min);
        
    }

}

//uses the selection sort algorithm according to review
void sort_review(Library& library, int high_low)
{
    int sorted=0;
    int min=0;
    int j;
    
    
    for(sorted=0; sorted<library.size-1; sorted++)
    {
        min=sorted;
        
        
        for(j=sorted+1; j<library.size ; j++)
        {
            //compares the elements differently based on the high_low number
            if(high_low==1)
            {
                if(library.shelf[j].review<library.shelf[min].review)
                {
                    min=j;
                }
            }
            else if(high_low==2)
            {
                if(library.shelf[j].review>library.shelf[min].review)
                {
                    min=j;
                }
            }
            
        }
        
        if(min!=sorted)
            swap(library,sorted,min);
        
    }
}

//uses the selection sort algorithm according to prices
void sort_price(Library& library, int high_low)
{
    int sorted=0;
    int min=0;
    int j;
    
    
    for(sorted=0; sorted<library.size-1; sorted++)
    {
        min=sorted;
        
        for(j=sorted+1; j<library.size ; j++)
        {
            //compares the elements differently based on the high_low number
            if(high_low==1)
            {
                if(library.shelf[j].price<library.shelf[min].price)
                {
                    min=j;
                }
            }
            else if(high_low==2)
            {
                if(library.shelf[j].price>library.shelf[min].price)
                {
                    min=j;
                }
            }
            
        }
        
        if(min!=sorted)
        {
            swap(library,sorted,min);
        }
    }
}

void sort_list(Library& library, int high_low, int attribute )
{
    // Depending on the attribute this uses a different function
    
    if(attribute==1)
    {
        sort_title(library, high_low);
    }
    else if(attribute==2)
    {
        sort_pages(library, high_low);
    }
    else if(attribute==3)
    {
        sort_review(library, high_low);
    }
    else if(attribute==4)
    {
        sort_price(library, high_low);
    }
    
    cout<<"The list has been sorted\n\n";
};

int main(int argc, const char * argv[])
{
    
    Library library;
    initialize(library);
    
    int input = 0 ;
    
    //repeats the Menu until 8 is input
    do {
        
        int input = 0 ;
        menu(input);
        
        if(input==-1)
        {
            continue;
        }
        
        if(input!=8)
        {
            //uses a particular function based on input number
            switch (input)
            {
                case 1:
                {
                    display_list_of_books(library);
                    continue;
                }
                    
                case 2:
                {
                    string find;
                    cout<<"Name the title of the book you want to find \n";
                    cin>>find;
                    find_book(library, find);
                    continue;
                }
                    
                case 3:
                {
                    add_new_book(library);
                    continue;
                }
                    
                case 4:
                {
                    string find;
                    cout<<"Name the title of the book you want to remove \n";
                    cin>>find;
                    remove_book(library,find);
                    continue;
                }
                    
                case 5:
                {
                    save_list_to_file(library);
                    continue;
                }
                    
                case 6:
                {
                    load_list_from_file(library);
                    continue;
                }
                    
                case 7:
                {
                    int att;
                    int high_low;
                    
                    //Checks for valid attribute input
                    do {
                        cout<<"Each book has 4 attributes, enter the number of the attribute you want to sort by\n";
                        cout<<"1)Title\n2)Number of Pages\n3)Review\n4)Price\n";
                        cin>>att;
                        
                        if(att>4 || att <0)
                        {
                            cout<<"Please enter a valid option\n";
                            continue;
                        }
                        
                        break;
                    
                    } while (true);
                    
                     //Checks for valid high_ low input
                    do {
                        cout<<"Enter the number of how you want to sort this\n";
                        cout<<"1)Low to high\n2)High to low\n";
                        cin>>high_low;
                        
                        if(high_low==1 || high_low==2)
                        {
                            break;
                           
                        }
                        
                        cout<<"Please enter a valid option\n";
                        
                        
                    } while (true);
                    
                    
                    
                    sort_list(library, high_low, att);
                    continue;
                }
                    
            }
        }
        
    } while (input!=8);
    
    return 0;
    
};

