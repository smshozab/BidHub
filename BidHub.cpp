//Shozab Mehdi
//22k-4522

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class item
{
    string name_of_item, name_of_owner, desc;
    float price;

public:
    int b_id, flag;

    item()
    {
        price = 0;
        b_id = 0;
        flag = 1;
    }

    void setNameOfItem(string name);
    void setNameOfOwner(string name);
    void setDesc(string desc);
    void setPrice(float price);

    string getNameOfItem();
    string getNameOfOwner();
    string getDesc();
    float getPrice();
};

float item::getPrice()
{
    return this->price;
}

string item::getDesc()
{
    return this->desc;
}

string item::getNameOfItem()
{
    return this->name_of_item;
}

string item::getNameOfOwner()
{
    return this->name_of_owner;
}

void item::setPrice(float price)
{
    this->price = price;
}

void item::setNameOfItem(string name)
{
    this->name_of_item = name;
}

void item::setNameOfOwner(string name)
{
    this->name_of_owner = name;
}

void item::setDesc(string desc)
{
    this->desc = desc;
}

void disp(item obji)
{
    if (obji.flag == 1)
    {
        cout << obji.getNameOfItem() << "\t\t" << obji.getNameOfOwner() << "\t\t" << obji.getDesc() << endl;
    }
}

item create()
{
    item obji;
    string temp;
    cin.ignore();
    cout << "\nEnter the Name of the Item\n";
    getline(cin, temp);
    obji.setNameOfItem(temp);

    cout << "\nEnter the Name of the Owner\n";
    getline(cin, temp);
    obji.setNameOfOwner(temp);

    cout << "\nEnter Description of Item in less than 50 words\n";
    getline(cin, temp);
    obji.setDesc(temp);
    cout << "\nName of item\tName of Owner\tDescription\n";
    obji.flag = 1;
    disp(obji);
    return obji;
}

vector<string> take_auctioneers()
{
    int no_auctioneer = 0;
    string temp;
    vector<string> name;
    char again = 'y';
    cin.ignore();
    bool wflag = true;
    do
    {
        cin.ignore();
        no_auctioneer++;
        cout << "\nEnter Name of Auctioneer number " << no_auctioneer << endl;
        getline(cin, temp);
        name.push_back(temp);
        cout << "\nThe Auctioning ID of Auctioneer " << name[no_auctioneer - 1] << " is " << no_auctioneer << endl;

        cout << "\nDo you want to enter again(y/n) ?";
        cin >> again;

        if (again != 'y')
            wflag = false;
    } while (wflag);

    return name;
}

void auction(vector<item> obj)
{
    float price = 0.0, pre = 0.0;
    int i, j;

    int names_entered = 0;
    vector<string> name;

    string line = "\nSummary\n";
    fstream afile;
    afile.open("samp.txt", ios::in | ios::out | ios::app);
    afile << line;
    line = "\nThe List of Items Sold are:\n";

    int no_auctioneer;
    bool wflag = true;
    while (wflag)
    {
        name = take_auctioneers();
        no_auctioneer = name.size();
        if (no_auctioneer < 2)
            cout << "\nNumber Auctioneers cannot be less than 2.....Try entering names again\n";
        else
        {
            wflag = false;
        }
    }

    cout << "\n\nStarting Auction..................";

    for (int i = 0; i < obj.size(); i++)
    {
    SALE:
        cout << "\nItem on sale is:\nName:\t" << obj[i].getNameOfItem() << "\nDesc\t" << obj[i].getDesc() << endl;
        cout << "\nBase Price: 100.00\n(Press 0 0 to Pass)";

    Lab:
        cout << "\nBidder Input Price as: Bidder_ID Price\n";
        cin >> j >> price;

        if ((j == 0) && (price == 0) && (obj[i].flag == 1))
        {
            //   obj[i].b_id = obj[i].price = j;
            i++;
            if (i < obj.size())
                goto SALE;
            else
            {
                goto time_out;
            }
        }

        if (((price < 100.00) || (price < pre)) || ((j < 1) || (j > no_auctioneer)))
        {
            cout << "\nCannot Except Either ID or Price\n";
            goto Lab;
        }
        else
        {
            pre = price;
            obj[i].b_id = j;
            obj[i].setPrice(pre);
            obj[i].flag = 0;
            clock_t start = clock();
            cout << "\nTimer: 5 sec\nPlease enter the input:\n";

            while (!_kbhit()) //Check for keyboard hit
            {
                if (((clock() - start) / CLOCKS_PER_SEC) >= 5)
                {
                    cout << "\nTIMEOUT 5 sec .........................................................................\n";

                    if (i < (no_auctioneer - 1))
                    {
                        pre = 0.0;
                        price = 0.0;
                        i++;
                        goto SALE;
                    }

                    else
                    {
                        goto time_out;
                    }
                }
            }

            goto Lab;
        }
    }

time_out:
    cout << "\nAuction Complete!\nThe List of Items Sold and to whom at price are:\nName of Item\tOwner ID\tPrice\n";
    afile << line;

    //	for(i = 0; ((i < n) && obj[i].flag == 0); i++)
    for (int i = 0; i < obj.size(); i++)
    {
        cout << obj[i].getNameOfItem() << "\t\t" << obj[i].b_id << "\t\t" << obj[i].getPrice() << endl;
        afile << obj[i].getNameOfItem() << "\t\t" << obj[i].b_id << "\t\t" << obj[i].getPrice() << endl;
    }

    cout << "\nDo you want to Display the complete file of the items sold?(1/0)\n";
    cin >> i;

    if (i == 1)
    {
        afile.seekg(0, ios::beg);

        while (afile)
        {
            getline(afile, line);
            cout << line << endl;
        }
    }

    afile.close();
}

int main()
{
    int choice, no_of_items = 0;
    item temp;
    vector<item> obj;
    ifstream f;
    do
    {
        cout << "\nEnter Choice\n1. Add item to Auction\n2. To Display the list of items\n3. To Start the auction\n4. Get details of previous Auction\n5. To Exit\n";

        cin >> choice;

        switch (choice)
        {
        case 1:
            temp = create();
            no_of_items++;
            obj.push_back(temp);
            cout << "\nItem added Successfully!\n";
            break;

        case 2:
            cout << "\nName of item\tName of Owner\tDescription\n";
            for (int i = 0; i < obj.size(); i++)
            {
                disp(obj[i]);
            }
            break;

        case 3:
            if (obj.empty())
                cout << "\nList is Empty\n";
            else
            {
                auction(obj);
            }
            break;

        case 4:

            try
            {
                f.open("samp.txt");

                if (f.fail())
                    throw "Error: File does not exist....!!!!Complete at least one auction....";

                if (f.is_open())
                    cout << f.rdbuf();
            }
            catch (const char* msg)
            {
                cerr << "\n"
                    << msg << '\n';
            }

            break;

        case 5:
            cout << "\nExitting.....!!!!";
            break;

        default:
            cout << "\nInvalid Input\n";
            break;
        }
    } while (choice != 5);

    return 0;
}