typedef struct Client Client;
typedef struct Book Book;
typedef struct User User;
typedef char gchar;

struct User
{
    int user_id;
    const gchar * username;
    const gchar * password;
};



struct Client
{
    int client_id;
    const gchar * firstname;
    const gchar * lastname;
    const gchar * numcart;
    int age;
    const gchar * classroom;
    const gchar * created_cli;
    const gchar * last_update_cli;
    
};

struct Book
{
    int book_id;
    const gchar * title;
    const gchar * description;
    const gchar * author;
    const gchar * saved;
    const gchar * category;
    int nb_page;
    const gchar * last_update;
    int qty;
};

void insertClient(Client dataClientHost); //ok
void insertBook(Book dataBookHost); //ok

void readAll(char table_name[10]); //ok
void updateClient(Client dataClientHost, Client DataClientOfUpdate); //ok
void updateBook(Book dataBookHost, Book DataBookOfUpdate); //ok
void removeClient(Client dataClientHost); //ok
void removeBook(Book dataBookHost); //ok
int checkIfClientExist(Client data);
int checkIfBookExist(Book data);
int checkIfUserExist(User data);
int authentification(User user);
void borrowOneBook(Book book, Client client, User borrower);
int getIdUser(User user);
void returnOneBook(Book book, Client client, User borrower);
int getIdOfClient(Client client);
int getIdOfBook(Book book);
int checkStockOfBook(Book book);
int checkIfAlreadyBorrow(Client client);
int return_flag(int flag);
// bool authentification(User user);
// si un livre est emprunté alors on décrémente le nombre de livre est décrémenté dans la base
// de données on insère les 