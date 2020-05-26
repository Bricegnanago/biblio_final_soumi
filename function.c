#include <my_global.h>
#include <mysql.h>
#include "biblio.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// #include <gtk/gtk.h>

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void insertClient(Client client)
{

    // Debut verfication d'existence
    int flag = checkIfClientExist(client);
    //Fin verification existence
    if (flag == 1)
    { //ok
        MYSQL *con = mysql_init(NULL);
        if (con == NULL)
        {
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }

        if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
        {
            finish_with_error(con);
        }
        char buf[1024] = {};

        char query_string[] = {
            "INSERT INTO Client VALUES(null, '%s', '%s', '%s', '%d', '%s', NOW(), null, null)"};
        sprintf(buf, query_string, client.firstname, client.lastname, client.numcart, client.age, client.classroom);
        printf("%s\n", buf);

        if (mysql_query(con, buf))
        {
            finish_with_error(con);
        }

        mysql_close(con);

        printf("\nDonnée insérée avec succès\n\n");
    }
    else
    {
        printf("\nCe Client existe déja dans la base de données\n\n");
        exit(1);
    }
}

void insertBook(Book book)
{

    // Debut verfication d'existence
    int flag = checkIfBookExist(book);
    //Fin verification existence
    if (flag == 1)
    { //ok
        MYSQL *con = mysql_init(NULL);
        if (con == NULL)
        {
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }

        if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
        {
            finish_with_error(con);
        }
        char buf[1024] = {};
        char query_string[] = {
            "INSERT INTO Book VALUES(null, '%d', '%s', '%s', '%s', '%s', NOW(), null, 0, '%d')"};
        sprintf(buf, query_string, book.nb_page, book.author, book.description, book.title, book.category, book.qty);

        if (mysql_query(con, buf))
        {
            finish_with_error(con);
        }

        mysql_close(con);
    }
    else
    {
        printf("\nCe Livre existe déja dans la base de données\n\n");
        exit(1);
    }
}

// Supprimer un client
void removeClient(Client data)
{

    // Debut verfication d'existence
    int flag = checkIfClientExist(data);
    //Fin verification existence

    if (flag == 0)
    { //ok
        MYSQL *con = mysql_init(NULL);
        if (con == NULL)
        {
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }

        // Connexion à la base de données
        if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
        {
            finish_with_error(con);
        }
        char buf[1024] = {};

        // Requete sql
        char query_string[] = {
            "UPDATE Client set status_client = 1 WHERE firstname='%s' OR lastname='%s' OR numcart='%s'"
            };
        sprintf(buf, query_string, data.firstname, data.lastname, data.numcart);
        if (mysql_query(con, buf))
        {
            finish_with_error(con);
        }

        mysql_close(con);
    }
    else
    {
        printf("\nClient introuvable\n");
    }
}

void removeBook(Book book)
{
    // Debut verfication d'existence
    // int flag = checkIfBookExist(book);
    //Fin verification existence

    // if (flag == 0){ //ok
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }
    char buf[1024] = {};

    char query_string[] = {
        "UPDATE Book SET statusBook=1 WHERE title='%s'"};
    sprintf(buf, query_string, book.title);
    if (mysql_query(con, buf))
    {
        finish_with_error(con);
    }

    mysql_close(con);
    // else{
    //     printf("\nSuppression impossible ! Client enexistant \n");
    // }
}

void updateClient(Client dataClientHost, Client dataClientToUpdate)
{
    // Debut verfication d'existence
    int flag = checkIfClientExist(dataClientHost);
    //Fin verification existence

    if (flag == 0)
    { //ok
        MYSQL *con = mysql_init(NULL);
        if (con == NULL)
        {
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }

        if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
        {
            finish_with_error(con);
        }
        char buf[1024] = {};

        char query_string[] = {
            "UPDATE Client SET firstname='%s', lastname='%s', numcart='%s', age='%d', classroom='%s', last_update=NOW() WHERE firstname='%s'"};
        sprintf(buf, query_string, dataClientToUpdate.firstname, dataClientToUpdate.lastname, dataClientToUpdate.numcart, dataClientToUpdate.age, dataClientToUpdate.classroom, dataClientHost.firstname);
        if (mysql_query(con, buf))
        {
            finish_with_error(con);
        }

        mysql_close(con);
    }
    else
        printf("\nMise à jour impossible Client inexistant\n");
}

void updateBook(Book dataBookHost, Book dataBookToUpdate)
{
    // Debut verfication d'existence
    int flag = checkIfBookExist(dataBookHost);
    //Fin verification existence

    if (flag == 0)
    { //ok
        MYSQL *con = mysql_init(NULL);
        if (con == NULL)
        {
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }

        if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
        {
            finish_with_error(con);
        }
        char buf[1024] = {};

        char query_string[] = {
            "UPDATE Book SET nb_page='%d', author='%s', description='%s', title='%s', category='%s', last_update=NOW() WHERE title='%s'"};
        sprintf(buf, query_string, dataBookToUpdate.nb_page, dataBookToUpdate.author, dataBookToUpdate.description, dataBookToUpdate.title, dataBookToUpdate.category, dataBookHost.title);
        if (mysql_query(con, buf))
        {
            finish_with_error(con);
        }

        mysql_close(con);
    }
    else
    {
        printf("\n Mise à jour impossible ! Données inexistante \n");
    }
}

void readAll(char table_name[10])
{

    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }
    char buf[1024] = {};

    char query_string[] = {
        "SELECT firstname, lastname, classroom, age FROM %s WHERE status_client=0"};
    sprintf(buf, query_string, table_name);

    printf("%s", buf);
    if (mysql_query(con, buf))
    {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    int num_fields = mysql_num_rows(result);
    MYSQL_ROW row;
    if(num_fields == 0){
        printf("Aucun données trouvée");
        return;
    }
    
    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    //Fin affichage client
    mysql_free_result(result);
    mysql_close(con);
}

int checkIfClientExist(Client data)
{
    int flag;

    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }
    char buf[1024] = {};

    char query_string[] = {
        "SELECT count(*) FROM Client WHERE numcart='%s' OR firstname='%s' AND status_client = 0"};

    sprintf(buf, query_string, data.numcart, data.numcart);
    if (mysql_query(con, buf))
    {
        finish_with_error(con);
    }
    printf("%s\n", buf);

    MYSQL_RES *result = mysql_store_result(con);
    int num_fields = mysql_num_rows(result);
    if(num_fields == 0){
        return -1;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
        num_fields = atoi(row[0]);

    if (num_fields > 0)
        flag = 0; //ok
    else
        flag = 1; //nok
    mysql_free_result(result);
    mysql_close(con);
    return flag;
}

int checkIfBookExist(Book data)
{
    int flag;

    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }
    char buf[1024] = {};

    char query_string[] = {
        "SELECT count(*) FROM Book WHERE title='%s' AND statusBook=0 "};

    sprintf(buf, query_string, data.title);
    printf("%s", buf);
    if (mysql_query(con, buf))
    {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);
    int num_fields = mysql_num_rows(result);
    printf("\nnum == %d\n\n", num_fields);
    if(num_fields == 0) {
        return -1;
    }
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            // printf("%s", row[i] ? row[i] : "NULL");
            num_fields = atoi(row[i]);
        }
        printf("\n");
    }

    // printf("\nj === %d\n\n", j);
    if (num_fields > 0)
        flag = 0; // 0 si le client existe
    else
        flag = 1; //nok 1 si le client n'existe pas
    mysql_free_result(result);
    mysql_close(con);
    return flag;
}

int checkIfUserExist(User data)
{
    int flag;

    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
        finish_with_error(con);

    char buf[1024] = {};

    char query_string[] = {
        "SELECT count(*) FROM superuser WHERE username='%s'AND password=sha1('%s')"};

    sprintf(buf, query_string, data.username, data.password);
    if (mysql_query(con, buf))
    {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);
    int num_fields = mysql_num_rows(result);
    if(num_fields == 0){
        return -1;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
            num_fields = atoi(row[i]);
        printf("\n");
    }

    if (num_fields > 0)
        flag = 0; //ok 0 si l'utilisateur existe
    else
        flag = 1; //nok 1 si l'utilisateur n'existe pas
    mysql_free_result(result);
    mysql_close(con);
    return flag;
}

void borrowOneBook(Book book, Client client, User borrower)
{

    // Debut verfication d'existence
    int flag_client = checkIfClientExist(client);

    int flag_book = checkIfBookExist(book);
    int flag_stock = checkStockOfBook(book);

    int flag_exist = checkIfAlreadyBorrow(client);
    if (flag_exist == 0)
    {
        printf("Veuillez retourner le dernier livre que vous avez emprunté !\n\n");
        // exit(1);
    }
    if (flag_stock == 0)
    {
        // Impossible d'aller plus loin; sortir du programme
        printf("Le stock du livre %s est epuisé. Veuillez repasser plutard ! \n\n", book.title);
        // exit(1);
    }
    else if (flag_client == 1)
    {
        printf("Veuillez enregistrer le client svp !!! \n\n");
        // exit(1);
    }
    else if (flag_book == 1)
    {
        printf("Ce livre n'a pas encore été enregistré !!!\n\n");
        // exit(1);
    }
    else
    {
        //Fin verification existence

        MYSQL *con = mysql_init(NULL);
        if (con == NULL)
        {
            fprintf(stderr, "mysql_init() failed\n");
            // exit(1);
        }

        if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
        {
            finish_with_error(con);
        }

        /***************** Recuperer l'identifiant du livre ********************/

        /***************** Fin Recuperer l'identifiant du livre **********************/
        /***************** Debut Recuperer l'identifiant du livre ********************/

        /***************** Fin Recuperer l'identifiant du livre ********************/

        char buf[1024] = {};

        char query_string[] = {
            "INSERT INTO Borrow VALUES(null, '%d', '%d', NOW(), '%d', 0, null)"};
        sprintf(buf, query_string, getIdOfClient(client), getIdOfBook(book), getIdUser(borrower));

        if (mysql_query(con, buf))
        {
            finish_with_error(con);
        }

        /****** Modification du status de disponibilié du livre emprunté ***********/
        // Juste après insertion dans la base de données il faut decrementer le stock
        // de ce livre
        char query_status_book[] = {
            "UPDATE Book SET qty='%d'-1 WHERE livre_id='%d'"};
        sprintf(buf, query_status_book, flag_stock, getIdOfBook(book));
        // printf("query status : %s", buf);
        if (mysql_query(con, buf))
        {
            finish_with_error(con);
        }
        mysql_close(con);

        printf("\nDonnée insérée avec succès\n\n");
    }
}

/* Retourner une livre dejà emprunté */
void returnOneBook(Book book, Client client, User borrower)
{
    int flag_stock = checkStockOfBook(book);
    int flag_client = checkIfClientExist(client);
    int flag_exist = checkIfAlreadyBorrow(client);
    if (flag_exist == 1)
    { // le client a-t-il déjà fait un emprunt sans retourner ?
        printf("Aucun retour pour %s !\n\n", client.firstname);
        // exit(1);
    }

    if (flag_client == 1)
    {
        printf("Ce client n'existe pas dans notre base de données");
        // exit(1);
    }
    int flag_book = checkIfBookExist(book);
    /*Ce livre a-t-il vraiment emprunté ce livre */
    if (flag_book == 1)
    {
        printf("Ce livre n'existe pas dans notre base de données");
        // exit(1);
    }
    else
    {
        MYSQL *con = mysql_init(NULL);
        if (con == NULL)
        {
            fprintf(stderr, "mysql_init() failed\n");
            // exit(1);
        }
        //connexion à la base de données
        if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
            finish_with_error(con);

        char buf[1024] = {};
        char query_string[] = {
            "UPDATE Borrow SET DateOfReturn = NOW(), status='1' WHERE client_id='%d' AND livre_id='%d' AND DateOfReturn IS NULL "};

        sprintf(buf, query_string, getIdOfClient(client), getIdOfBook(book));
        // printf("query status : %s", buf);
        if (mysql_query(con, buf))
        {
            finish_with_error(con);
        }

        /****** Modification du status de disponibilié du livre emprunté ***********/
        // Juste après insertion dans la base de données il faut decrementer le stock
        // de ce livre
        char query_status_book[] = {
            "UPDATE Book SET qty='%d'+1, last_update=NOW() WHERE livre_id='%d'"};
        sprintf(buf, query_status_book, flag_stock, getIdOfBook(book));
        // printf("query status : %s", buf);

        if (mysql_query(con, buf))
        {
            finish_with_error(con);
        }
        mysql_close(con);
    }
}

int checkStockOfBook(Book book)
{
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
        finish_with_error(con);
    char buf[1024] = {};
    char query_string[] = {
        "SELECT qty FROM Book WHERE title='%s'"};

    sprintf(buf, query_string, book.title);
    if (mysql_query(con, buf))
        finish_with_error(con);

    MYSQL_RES *result = mysql_store_result(con);
    int num_fields = mysql_num_rows(result);
    if(num_fields == 0){
        return -1;
    }
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
        num_fields = atoi(row[0]);

    mysql_free_result(result);
    mysql_close(con);

    return num_fields; // retourne le nombre de livre en stock
}

int getIdOfClient(Client client)
{
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }
    // select count(*) from borrow where book_id='%d' and client_id='%d'
    char buf[1024] = {};
    char query_string[] = {
        "SELECT client_id FROM Client WHERE firstname='%s' OR numcart='%s'"};    
    sprintf(buf, query_string, client.numcart, client.numcart);

    if (mysql_query(con, buf))
    {
        finish_with_error(con);
    }
    printf("get_id_of_client : %s\n", buf);
    MYSQL_RES *result = mysql_store_result(con);
    
    int num_fields = mysql_num_rows(result);
    printf("num : %d \n", num_fields);
    if(num_fields == 0) {
        return -1;
    }
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
        num_fields = atoi(row[0]);

    printf("get_id_of_client : num_fields %d\n", num_fields);
    mysql_free_result(result);
    mysql_close(con);
    return num_fields;
}

int getIdOfBook(Book book)
{

    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }
    // select count(*) from borrow where book_id='%d' and client_id='%d'
    char buf[1024] = {};
    char query_string[] = {
        "SELECT livre_id FROM Book WHERE title='%s'"};
    sprintf(buf, query_string, book.title);

    if (mysql_query(con, buf))
    {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    int book_id = mysql_num_rows(result);

    if(book_id == 0){
        return -1;
    }
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
        book_id = atoi(row[0]);

    mysql_free_result(result);
    mysql_close(con);
    return book_id;
}

int checkIfAlreadyBorrow(Client data_client)
{
    printf("dataclient : %s\n", data_client.numcart);
    data_client.client_id = getIdOfClient(data_client);
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
        finish_with_error(con);
    char buf[1024] = {};
    char query_string[] = {
        "select count(*) from Borrow where client_id='%d' AND DateOfreturn is null"};

    sprintf(buf, query_string, data_client.client_id);

    // printf("\n\n requete : %s\n\n", buf);
    if (mysql_query(con, buf))
    {
        finish_with_error(con);
    }
    printf("buf borrow %s\n", buf);
    MYSQL_RES *result = mysql_store_result(con);
    int num_fields = mysql_num_rows(result);
    MYSQL_ROW row;
    if(num_fields == 0){
        return -1;
    }
    while ((row = mysql_fetch_row(result)))
        num_fields = atoi(row[0]);

    mysql_free_result(result);
    mysql_close(con);

    if (num_fields != 0)
        return 0; // le client a empreinter sans retourner
    else
        return 1; //contraire
    // retourne le nombre de livre en stock
}

int getIdUser(User borrower)
{
    /***************** Recuperer l'identifiant de l'emprunteur ********************/
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }
    // select count(*) from borrow where book_id='%d' and client_id='%d'

    char buf[1024] = {};
    char query_string_Borrower[] = {
        "SELECT user_id from superuser WHERE username='%s'"};
    sprintf(buf, query_string_Borrower, borrower.username);
    if (mysql_query(con, buf))
    {
        finish_with_error(con);
    }

    MYSQL_RES *result_borrower = mysql_store_result(con);
    int user_id = mysql_num_rows(result_borrower);
    if(user_id == 0 ){
        return -1;
    }

    MYSQL_ROW row_borrower;
    while ((row_borrower = mysql_fetch_row(result_borrower)))
        user_id = atoi(row_borrower[0]);

    mysql_free_result(result_borrower);
    mysql_close(con);

    return user_id;
    /***************** Fin Recuperer l'identifiant de l'emprunteur ********************/
}

int return_flag(int flag)
{
    int res;
    if (flag == 0)
        flag = 1;
    else
        flag = 0;

    res = flag;
    return res;
}