#include <iostream>
#include <iomanip> 
#include <string>
#include <conio.h>
#include <mysql.h> 
using namespace std;

void Register();
void Login();
void AgentMenu();
void ForgotPassword();
void insert();
void deletemenu();
void deleteitemname();
void deleteitemprice();
void deleteitemall();
void EditProduct();
void ViewProduct();
void SearchProduct();
void SearchProductID();
void SearchProductName();
void SearchProductPrice();
void GenerateOrder();
void salesReport();

int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

string ProductID;

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
            cout << "Database Connected" << endl;
        else
            cout << "Failed To Connect!" << endl;

        conn = mysql_real_connect(conn, "localhost", "root", "", "DABM", 3306, NULL, 0); 
        if (conn)
            cout << "Database Connected To MySql" << endl;
        else
            cout << "Failed To Connect!" << endl;
        system("cls");
    }

};


int main() {
    system("cls");
    system("title DABM");
    db_response::ConnectionFunction();

    int menu;
    cout << "................ WELCOME TO DROPSHIP AGENT BUSINESS MANAGEMENT SYSTEM (DABM) ................";
    cout << "\n\n1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Forgot Password" << endl;
    cout << "4. Exit" << endl;
    cout << ".............................................................................................";
    cout << "\n\nPLEASE CHOOSE:" ;
    cin >> menu;

    switch (menu)
    {
    case 1:
        Register();
        break;
    case 2:
        Login();
        break;
    case 3:
        ForgotPassword();
        break;
    case 4:
        cout << "Program Now Will Exit..." << endl;
        exit(0);
    default:
        cout << "Please choose between 1 - 4. Press Enter To Continue...";
        _getch(); 
        system("cls");
        main();
        break;
    }

    return 0;
}

void Register()
{
    system("cls");
    string agentID,fname,lname, phone, email, password, sword;
    cout << "--- New Agent Registration ---" << endl;
    cout << "Enter Agent ID:  ";
    cin.ignore(1,'\n');
    getline(cin, agentID);
    cout << "Enter First Name: ";
    cin.ignore(0,'\n');
    getline(cin, fname);
    cout << "Enter Last Name: ";
    cin.ignore(0, '\n');
    getline(cin, lname);
    cout << "Enter Contact Number: ";
    cin.ignore(0, '\n');
    getline(cin, phone);
    cout << "Enter Email Address: ";
    getline(cin, email);
    cout << "Enter Password: ";
    getline(cin, password);
    cout << "Enter your Favourite Word (Security Question): ";
    getline(cin, sword);
   
    string checkUser_query = "select * from agent where AgentID = '" + agentID + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            cout << "Agent ID is already exist. Press enter to login...";
            _getch();
            Login();
        }
        else
        {
            string insertAgent_query = "insert into agent (AgentID, FirstName, LastName, ContactNo, Email, Password, SecurityQuestion) values ('" + agentID + "', '" + fname + "', '" + lname + "', '" + phone + "', '" + email + "', '" + password +  "', '" + sword + "')";
            const char* q = insertAgent_query.c_str();
            qstate = mysql_query(conn, q);

            if (!qstate)
            {
                cout << endl << "You have been registered. Press Enter to Continue...";
                _getch();
                main();
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}

void Login()
{
    system("cls");
    string agentID;
    string password;

    cout << "--- Please Enter Your Login Info ---" << endl;
    cout << "AgentID : ";
    cin >> agentID;
    cout << "Password : ";
    char ch;
    while ((ch = _getch()) != 13)
    {
        password += ch;
        cout << '*';
    }

    string checkUser_query = "select AgentID from agent where AgentID = '" + agentID + "' and password = '" + password + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
                agentID = row[0];
 
            AgentMenu();
        }
        else
        {
            char c;
            cout << "\nInvalid username or password. Want to try again? (y/n): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
                Login();
            else
                main();
        }
    }
    else
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
}

void AgentMenu()
{
    int menu;

    system("cls");
    cout << "................ WELCOME TO DROPSHIP AGENT BUSINESS MANAGEMENT SYSTEM (DABM) ................" << endl;
    cout << "1. Add New Product" << endl;
    cout << "2. View Product" << endl;
    cout << "3. Search Product" << endl;
    cout << "4. Delete Prodcut" << endl;
    cout << "5. Update Product" << endl;
    cout << "6. Make Order" << endl;
    cout << "7. View Sales Report" << endl;
    cout << "8. Return to Main Menu" << endl;
    cout << ".............................................................................................";
    cout << "\n\nPLEASE CHOOSE:";

    cin >> menu;


    switch (menu)
    {
    case 1:
        insert();
        break;
    case 2:
        ViewProduct();
        break;
    case 3:
        SearchProduct();
        break;
    case 4:
        deletemenu();
        break;
    case 5:
        EditProduct();
        break;
    case 6:
        GenerateOrder();
        break;
    case 7:
        salesReport();
        break;
    case 8:
        main();
        break;
    default:
        cout << "Please choose between 1 - 8. Press Enter To Continue...";
        _getch();
        system("cls");
        AgentMenu();
        break;
    }
}

void ForgotPassword()
{
    system("cls");
    char choose;
    string swordf;
   

    cout << "--- Please Enter Your Security Question Answer To Retrieve Your Password ---" << endl;
    cout << "Security Question Answer For What Is Your Favourite Word : ";
    cin >> swordf;
   

    //qstate = mysql_query(conn, "select SecurityQuestion, Password from agent");

    string checkUser_query = "select Password, SecurityQuestion from agent where SecurityQuestion like '%" + swordf + "%'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);

 

    if (!qstate)
    {
       /* cout << "Your Password is : "<< endl;*/
        cout << setw(11) << "Your Password is : ";

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(1) << row[0] << endl;
        
        //res = mysql_store_result(conn);
        //if (res->row_count == 1)
        //{
        //    while (row = mysql_fetch_row(res))
        //        /*swordf = row[5];*/
        //        cout << "Your Password is : ";
        //    cout << row[1] << endl;
        //    {
        //        /*cout << row[6];*/

        //    }
        }
        
    }
    else
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;


    do
    {
        cout << "Do you want to reattempt? (y/n): ";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
        {
            ForgotPassword();
        }
        else if (choose == 'n' || choose == 'N')
        {
            main();
        }
    } while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'N');
}





void insert()
{
    system("cls");
    string ProductID,ProductName, PricePerUnit, Description, SKU;
    char choose;
    cout << "-----Welcome to Insert New Product Page-----" << endl;

    cin.ignore(1, '\n');
    cout << "Please enter Product ID: ";
    getline(cin, ProductID);
    cout << "Please enter Product Name: ";
    getline(cin, ProductName);
    cout << "Please enter Price Per Unit: ";
    getline(cin, PricePerUnit);
    cout << "Please enter Product Description: ";
    getline(cin, Description);
    cout << "Please enter Product SKU: ";
    getline(cin, SKU);


    string insert_query = "insert into product (ProductID, ProductName, PricePerUnit, Description, SKU) values ('" + ProductID + "', '" + ProductName + "', '" + PricePerUnit + "', '" + Description + "', '" + SKU + "')";
    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << endl << "New product succesfully added to the system!." << endl;
    }
    else
    {
        cout << "Product ID is already exist! Please try again" << mysql_errno(conn) << endl;
    }

    do
    {
        cout << "Do you want add another product? (y/n): ";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
        {
            insert();
        }
        else if (choose == 'n' || choose == 'N')
        {
            AgentMenu();
        }
    } while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'N');
}




void deletemenu()
{
    int menu;

    system("cls");
    cout << "................ WELCOME TO DROPSHIP AGENT BUSINESS MANAGEMENT SYSTEM (DABM) ................" << endl;
    cout << "Delete Item" << endl;
    cout << "1. Search by Name" << endl;
    cout << "2. Search by Price" << endl;
    cout << "3. Delete by list" << endl;
    cout << "4. Go Back to Menu" << endl;
    cout << ".............................................................................................";
    cout << "\n\nPLEASE CHOOSE:";
    cin >> menu;
    switch (menu)
    {
    case 1:
        deleteitemname();
        break;
    case 2:
       deleteitemprice();
        break;
    case 3:
        deleteitemall();
        break;
    case 4:
        AgentMenu();
        break;
    default:
        cout << "Please choose between 1 - 4. Press Enter To Continue...";
        _getch();
        system("cls");
        AgentMenu();
        break;
    }



}

void deleteitemname()
{
    system("cls");
    char choose;
    string pname;
    cin.ignore(1, '\n');
    cout << "Search by Product Name ";
    getline(cin, pname);

    cout << "--- List of Searched Product ---" << endl;

    string search_query = "select ProductID, ProductName, PricePerUnit, Description, SKU from product where ProductName like '%" + pname + "%'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << setw(11) << "Product ID" << setw(17) << "Product Name" << setw(20) << "Price Per Unit" << setw(20) << "Description" << setw(20) << "SKU" << endl;

        res = mysql_store_result(conn);
        if (res->row_count >= 1)
        {
            while (row = mysql_fetch_row(res))
            {

                cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << endl;
            }
        }
        else if (res->row_count == 0)
        {
            cout << "\t Product Does not Exist!....Enter to continue" << endl;
            _getch();
            deleteitemname();
        }

        cout << "\n";
        cout << "Please choose Product ID that you want to delete: ";
        cin >> ProductID;

        string delete_query = "delete from product where ProductID = '" + ProductID + "'";
        const char* q = delete_query.c_str();
        qstate = mysql_query(conn, q);
        cout << "\n";
        cout << "Product DELETED!, Do you want to delete other product? (y/n): ";
        cin >> choose;

        if (choose == 'y' || choose == 'Y')
            deleteitemall();
        else
            AgentMenu();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    }


void deleteitemprice()
{
    system("cls");
    char choose;
    string pprice;
    cin.ignore(1, '\n');
    cout << "Search by Product Price ";
    getline(cin, pprice);

    cout << "--- List of Searched Product ---" << endl;

    string search_query = "select ProductID, ProductName, PricePerUnit, Description, SKU from product where PricePerUnit like '%" + pprice + "%'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << setw(11) << "Product ID" << setw(17) << "Product Name" << setw(20) << "Price Per Unit" << setw(20) << "Description" << setw(20) << "SKU" << endl;

        res = mysql_store_result(conn);
        if (res->row_count >= 1)
        {
            while (row = mysql_fetch_row(res))
            {

                cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << endl;
            }
        }
        else if (res->row_count == 0)
        {
            cout << "\t Product Does not Exist!....Enter to continue" << endl;
            _getch();
            deleteitemprice();
        }
        cout << "\n";
        cout << "Please choose Product ID that you want to delete: ";
        cin >> ProductID;

        string delete_query = "delete from product where ProductID = '" + ProductID + "'";
        const char* q = delete_query.c_str();
        qstate = mysql_query(conn, q);
        cout << "\n";
        cout << "Product DELETED!, Do you want to delete other product? (y/n): ";
        cin >> choose;

        if (choose == 'y' || choose == 'Y')
            deleteitemall();
        else
            AgentMenu();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}




void deleteitemall()
{
    system("cls");
    char choose;
    cout << "--- Delete Product By List ---" << endl;

    qstate = mysql_query(conn, "select ProductID, ProductName, PricePerUnit, Description, SKU from product");

    if (!qstate)
    {
        cout << setw(11) << "ProductID" << setw(17) << "Product Name" << setw(20) << "Price Per Unit" << setw(20) << "Description" << setw(20) << "SKU" << endl;
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {

            cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << endl;
        }
        cout << "Choose Product ID: ";
        cin >> ProductID;

            string delete_query = "delete from product where ProductID = '" + ProductID + "'";
            const char* q = delete_query.c_str();
            qstate = mysql_query(conn, q);
            cout << "\n";
            cout << "Product DELETED!, Do you want to delete other product? (y/n): ";
   
        cin >> choose;

        if (choose == 'y' || choose == 'Y')
            deleteitemall();
        else
            AgentMenu();

    }
    else 
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}

void EditProduct()
{
    system("cls");

    string data;
    int choose;
    char option;
    cout << "................ WELCOME TO DROPSHIP AGENT BUSINESS MANAGEMENT SYSTEM (DABM) ................" << endl;
    cout << "........................................PRODUCT LIST ........................................" << endl;

    qstate = mysql_query(conn, "select ProductID, ProductName, PricePerUnit, Description, SKU from Product");

    if (!qstate)
    {
        cout << setw(11) << "Product ID" << setw(17) << "Product Name" << setw(20) << "Price Per Unit" << setw(20) << "Description" << setw(20) << "SKU" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << endl;
        }
        cout << "\n";
        cout << "Choose Product ID That You Want To Update: ";
        cin >> ProductID;

        cout << endl << "-----Category-----" << endl;
        cout << "1. Product ID." << endl;
        cout << "2. Product Name" << endl;
        cout << "3. Price Per Unit" << endl;
        cout << "4. Description" << endl;
        cout << "5. SKU" << endl;
        cout << "Choose 1-5: ";
        cin >> choose;

        cin.ignore(1, '\n');
        if (choose == 1)
        {
            cout << "New Product ID.: ";
            getline(cin, data);
            string update_query = "update product set ProductID = '" + data + "' where ProductID = '" + ProductID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
        }
        else if (choose == 2)
        {
            cout << "New Product Name: ";
            getline(cin, data);
            string update_query = "update product set ProductName = '" + data + "' where ProductID = '" + ProductID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
        }
        else if (choose == 3)
        {
            cout << "New Price Per Unit: ";
            getline(cin, data);
            string update_query = "update product set PricePerUnit = '" + data + "' where ProductID = '" + ProductID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
        }
        else if (choose == 4)
        {
            cout << "New Description: ";
            getline(cin, data);
            string update_query = "update product set Description = '" + data + "' where ProductID = '" + ProductID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
        }

        else if (choose == 5)
        {
            cout << "New SKU: ";
            getline(cin, data);
            string update_query = "update product set SKU = '" + data + "' where ProductID = '" + ProductID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
        }
        cout << "\n";
        cout << "Do you want to edit other detail? (y/n): ";
        cin >> option;

        if (option == 'y' || option == 'Y')
            EditProduct();
        else
            AgentMenu();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}

    




    void ViewProduct()
    {
        system("cls");

        string data;
        char choose;
        cout << "................ WELCOME TO DROPSHIP AGENT BUSINESS MANAGEMENT SYSTEM (DABM) ................" << endl;
        cout << "............................. ..........VIEW PRODUCT ........................................" << endl;

        qstate = mysql_query(conn, "select ProductID, ProductName, PricePerUnit, Description, SKU from Product");

        if (!qstate)
        {
            cout << setw(11) << "Product ID" << setw(17) << "Product Name" << setw(20) << "Price Per Unit" << setw(20) << "Description" << setw(20) << "SKU" << endl;

            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << endl;
            }

            cout << "............................. ..........VIEW PRODUCT ........................................" << endl;
       
        
      
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }

        do
        {
            cout << "Do you want to go back to Menu? (y/n): ";
            cin >> choose;
            if (choose == 'y' || choose == 'Y')
            {
                AgentMenu();
            }
            else if (choose == 'n' || choose == 'N')
            {
                exit(0);
            }
        } while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'N');
}

    void SearchProduct()
    {
        int menu;

        system("cls");
        cout << "................ WELCOME TO DROPSHIP AGENT BUSINESS MANAGEMENT SYSTEM (DABM) ................" << endl;
        cout << "Search Product" << endl;
        cout << "1. Search by ID" << endl;
        cout << "2. Search by Name" << endl;
        cout << "3. Search by Price" << endl;
        cout << "4. Go back to Menu" << endl;
        cout << ".............................................................................................";
        cout << "\n\nPLEASE CHOOSE:";
        cin >> menu;
        switch (menu)
        {
        case 1:
            SearchProductID();
            break;
        case 2:
            SearchProductName();
            break;
        case 3:
            SearchProductPrice();
            break;
        case 4:
            AgentMenu();
            break;
        default:
            cout << "Please choose between 1 - 4. Press Enter To Continue...";
            _getch();
            system("cls");
            AgentMenu();
            break;
        }



    }


    void SearchProductID()
    {
        system("cls");
        char choose;
        string pid;
        cin.ignore(1, '\n');
        cout << "Search For a Product by ID:";
        getline(cin, pid);

        cout << "--- List of Searched Product ---" << endl;

        string search_query = "select ProductID, ProductName, PricePerUnit, Description, SKU from product where ProductID like '%" + pid + "%'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << setw(11) << "Product ID" << setw(17) << "Product Name" << setw(20) << "Price Per Unit" << setw(20) << "Description" << setw(20) << "SKU" << endl;

            res = mysql_store_result(conn);
            if (res->row_count >= 1)
            {
                while (row = mysql_fetch_row(res))
                {
                
                    cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << endl;
                }
            }
            else if (res->row_count == 0)
            {
                cout << "\t Product Does not Exist!....Enter to continue" << endl;
                _getch();
            }
           
            cout << "\n";
            cout << "Do you want to search another product? (y/n): ";
            cin >> choose;

            if (choose == 'y' || choose == 'Y')
                SearchProductID();
            else
                AgentMenu();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
    }

    void SearchProductName()
    {
        system("cls");
        char choose;
        string pname;
        cin.ignore(1, '\n');
        cout << "Search For a Product by Name:";
        getline(cin, pname);

        cout << "--- List of Searched Product ---" << endl;

        string search_query = "select ProductID, ProductName, PricePerUnit, Description, SKU from product where ProductName like '%" + pname + "%'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << setw(11) << "Product ID" << setw(17) << "Product Name" << setw(20) << "Price Per Unit" << setw(20) << "Description" << setw(20) << "SKU" << endl;

            res = mysql_store_result(conn);
            if (res->row_count >= 1)
            {
                while (row = mysql_fetch_row(res))
                {

                    cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << endl;
                }
            }
            else if (res->row_count == 0)
            {
                cout << "\t Product Does not Exist!....Enter to continue" << endl;
                _getch();
            }
            cout << "\n";
            cout << "Do you want to search another product? (y/n): ";
            cin >> choose;

            if (choose == 'y' || choose == 'Y')
                SearchProductPrice();
            else
                AgentMenu();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
    }


    void SearchProductPrice()
    {
        system("cls");
        char choose;
        string ppricee;
        cin.ignore(1, '\n');
        cout << "Search For a Product by Price:";
        getline(cin, ppricee);

        cout << "--- List of Searched Product ---" << endl;

        string search_query = "select ProductID, ProductName, PricePerUnit, Description, SKU from product where PricePerUnit like '%" + ppricee + "%'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << setw(11) << "Product ID" << setw(17) << "Product Name" << setw(20) << "Price Per Unit" << setw(20) << "Description" << setw(20) << "SKU" << endl;

            res = mysql_store_result(conn);
            if (res->row_count >= 1)
            {
                while (row = mysql_fetch_row(res))
                {

                    cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << endl;
                }
            }
            else if (res->row_count == 0)
            {
                cout << "\t Product Does not Exist!....Enter to continue" << endl;
                _getch();
            }
            cout << "\n";
            cout << "Do you want to search another product? (y/n): ";
            cin >> choose;

            if (choose == 'y' || choose == 'Y')
                SearchProductPrice();
            else
                AgentMenu();
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
    }

    void GenerateOrder()
    {
        system("cls");
        string OrderID, Orderdesc, TotalPrice, AgentID;
        char choose;
        cout << "-----Welcome to Generate Order Page-----" << endl;

        cin.ignore(1, '\n');
        cout << "Please enter Order ID: ";
        getline(cin, OrderID);
        cout << "Please enter Order Description: ";
        getline(cin, Orderdesc);
        cout << "Please enter Total Price: ";
        getline(cin, TotalPrice);
        cout << "Please enter AgentID: ";
        getline(cin, AgentID);
       
   


        string insert_query = "insert into order1 (OrderID, OrderDescription, TotalPrice, AgentID) values ('" + OrderID + "', '" + Orderdesc + "', '" + TotalPrice + "', '" + AgentID+ "')";
        const char* q = insert_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << endl << "Order Successfully Created!." << endl;
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }



        do
        {
            cout << "Do you want to make another order? (y/n): ";
            cin >> choose;
            if (choose == 'y' || choose == 'Y')
            {
                GenerateOrder();
            }
            else if (choose == 'n' || choose == 'N')
            {
                AgentMenu();
            }
        } while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'N');
    }


    void salesReport()
    {
        system("cls");
        string month;
        cin.ignore(1, '\n');
        cout << "Please Enter Month For Example 01 for January:";
        getline(cin, month);
        std::string search_query = "SELECT DATE(OrderDate), SUM(TotalPrice) FROM order1 WHERE MONTH(OrderDate) = " + month + " GROUP BY MONTH(OrderDate)";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
       

        if (!qstate)
        {
            cout << endl << endl << endl;
            cout << "\t\t\t\t********** SALES REPORT **********" << endl << endl;
            cout << "\t\t\t\t**********************************" << endl;
            cout << "\t\t\t\t|" << " DATE  " << "       |" << "TOTAL SALES " << "| " << endl;
            cout << "\t\t\t\t**********************************" << endl;

            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "\t\t\t\t|" << setw(6) << right << row[0] << setw(5) << "   |" << setw(15) << left << row[1] << setw(5) << "    |" << endl;
            }
            cout << "\t\t\t\t**********************************" << endl;
        }
        else
        {
            cout << "\t\t\t\tQuery Execution Problem!" << mysql_errno(conn) << endl;
        }
        cout << endl;
        cout << "\t\t\t\tPress Enter To Back...";
        _getch();
        AgentMenu();
    }




