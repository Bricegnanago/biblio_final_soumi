#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"

#define BOOK_STAT "\
#/bin/bash \n\
python python/stat_book.py \n\
"
#define BORROW_STAT "\
#/bin/bash \n\
python python/stat_borrow.py \n\
"

#define SHOW_BOOKS "\
#/bin/bash \n\
python python/book.py \n\
"
#define SHOW_CLIENTS "\
#/bin/bash \n\
python python/test.py \n\
"
GtkWidget * save_client_success;
GtkWidget *username;
GtkWidget *password;
GtkWidget *firstname;
GtkWidget *lastname;
GtkWidget *numcart;
GtkWidget *classroom;
GtkWidget *age;

//Book
GtkWidget *title;
GtkWidget *description;
GtkWidget *author;
GtkWidget *category;
GtkWidget *qty;
GtkWidget * save_book_success_label;

GtkWidget *message_text;
GtkWidget *container_to_save_client;
GtkWidget *container_to_remove_client;
GtkWidget * num_carte_to_remove;
GtkWidget * message_operation_on_saving_client;
GtkWidget * container_of_borrow;
GtkWidget * num_cart_label_to_borrow;
GtkWidget * title_of_book_to_borrow;
GtkWidget * title_of_book;
GtkWidget * show_all_clients;
GtkWidget * grid_of_client;
GtkWidget * return_on_book;
GtkWidget * hide_borrow_window;
GtkWidget * clear_fields_of_borrow;
GtkWidget * win_for_save_book;
GtkWidget * container_to_remove_book;
GtkWidget * container_to_save_book;
GtkWidget * message_operation_on_saving_book;


User user;
Book book;
Client client;
GtkBuilder      *builder;
GtkWidget       *window;   //page de connexion (première page)
GtkWidget       *borrow_window; //page d'emprunt et de depot
GtkWidget       *account_page; //deuxieme page
GtkWidget       *client_page;
GtkWidget       * win_for_save_client;
GtkWidget       *list;
GtkWidget       *vbox;
GtkWidget       *return_book_label;
GtkWidget       *message_text_borrow;
int flag_of_borrow = 0;
int f = 0;
int flag_remove = 0;
enum {

  LIST_ITEM = 0,
  N_COLUMNS
};


int main(int argc, char *argv[])
{
    
    // User user_session;
    // int flag_auth=1;    
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    GtkCssProvider *cssProvider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(cssProvider,"./python/style.css",NULL);
    gtk_builder_add_from_file (builder, "window_main.glade", NULL);
    save_book_success_label = GTK_WIDGET(gtk_builder_get_object(builder, "save_book_success_label"));
    window = GTK_WIDGET(gtk_builder_get_object(builder, "connexion_page"));
    borrow_window = GTK_WIDGET(gtk_builder_get_object(builder, "borrow_window"));
    account_page = GTK_WIDGET(gtk_builder_get_object(builder, "account_page"));
    client_page = GTK_WIDGET(gtk_builder_get_object(builder, "client_page"));
    win_for_save_client = GTK_WIDGET(gtk_builder_get_object(builder, "win_for_save_client"));
    container_to_save_client = GTK_WIDGET(gtk_builder_get_object(builder, "container_to_save_client"));
    container_to_remove_client = GTK_WIDGET(gtk_builder_get_object(builder, "container_to_remove_client"));
    container_of_borrow = GTK_WIDGET(gtk_builder_get_object(builder, "container_of_borrow"));
    return_book_label = GTK_WIDGET(gtk_builder_get_object(builder, "return_book_label"));
    message_text_borrow = GTK_WIDGET(gtk_builder_get_object(builder, "message_text_borrow"));
    num_cart_label_to_borrow = GTK_WIDGET(gtk_builder_get_object(builder, "num_cart_label_to_borrow"));
    title_of_book_to_borrow = GTK_WIDGET(gtk_builder_get_object(builder, "title_of_book_to_borrow"));
    show_all_clients = GTK_WIDGET(gtk_builder_get_object(builder, "show_all_clients"));
    return_on_book = GTK_WIDGET(gtk_builder_get_object(builder, "return_on_book"));
    hide_borrow_window = GTK_WIDGET(gtk_builder_get_object(builder, "hide_borrow_window"));
    win_for_save_book = GTK_WIDGET(gtk_builder_get_object(builder, "win_for_save_book"));
    container_to_remove_book = GTK_WIDGET(gtk_builder_get_object(builder, "container_to_remove_book"));
    container_to_save_book = GTK_WIDGET(gtk_builder_get_object(builder, "container_to_save_book"));
    save_client_success = GTK_WIDGET(gtk_builder_get_object(builder, "save_client_success"));

    // Book
    

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_builder_connect_signals(builder, NULL);
    
    // get pointers to the two labels
    username = GTK_WIDGET(gtk_builder_get_object(builder, "username"));
    password = GTK_WIDGET(gtk_builder_get_object(builder, "password"));
    firstname = GTK_WIDGET(gtk_builder_get_object(builder, "firstname"));
    lastname = GTK_WIDGET(gtk_builder_get_object(builder, "lastname"));
    numcart = GTK_WIDGET(gtk_builder_get_object(builder, "numcart"));
    classroom = GTK_WIDGET(gtk_builder_get_object(builder, "classroom"));
    age = GTK_WIDGET(gtk_builder_get_object(builder, "age"));
    // return_book_label = GTK_WIDGET(gtk_builder_get_object(builder, "return_book_label"));
    // message_text_borrow = GTK_WIDGET(gtk_builder_get_object(builder, "message_text_borrow"));

    title = GTK_WIDGET(gtk_builder_get_object(builder, "title"));
    description = GTK_WIDGET(gtk_builder_get_object(builder, "description"));
    author = GTK_WIDGET(gtk_builder_get_object(builder, "author"));
    category = GTK_WIDGET(gtk_builder_get_object(builder, "category"));
    qty = GTK_WIDGET(gtk_builder_get_object(builder, "qty"));
    title_of_book = GTK_WIDGET(gtk_builder_get_object(builder, "title_of_book"));
    message_operation_on_saving_book = GTK_WIDGET(gtk_builder_get_object(builder, "message_operation_on_saving_book"));


    
    

    //label pour supprimer un client
    num_carte_to_remove = GTK_WIDGET(gtk_builder_get_object(builder, "num_carte_to_remove"));

    
    message_operation_on_saving_client = GTK_WIDGET(gtk_builder_get_object(builder, "message_operation_on_saving_client"));
    message_text = GTK_WIDGET(gtk_builder_get_object(builder, "message_text"));

    g_object_unref(builder);
    gtk_widget_hide(container_to_remove_client);
    
    gtk_widget_show(window);
    gtk_main();

    return 0;
}

// called when button is clicked
void on_submit_button_clicked()
{
    int flag_auth = 0;
    //const gchar * client_username; //valeur saisie par l'utilisateur
    //const gchar * client_password;  // mot de pass saisie par l'utilisateur

    user.username = gtk_entry_get_text(GTK_ENTRY(username));
    user.password = gtk_entry_get_text(GTK_ENTRY(password));

    //données recupérées
    //verification des donnée saisie

    flag_auth =  checkIfUserExist(user);

    if(flag_auth == 1)
        gtk_label_set_text(GTK_LABEL(message_text), "Username ou Mot de passe invalide !");
    else {
        gtk_label_set_text(GTK_LABEL(message_text), user.username);
        gtk_widget_hide(window);        
        gtk_widget_show(account_page);
    }

    // gtk_label_set_text(GTK_LABEL(message_text), user.password);

}


void on_save_client_clicked(){
    gtk_widget_show(win_for_save_client);

    // s'il y a soumission du formulaire faire
}
// Enregistrer un client
void on_register_button_clicked () {
    // recupération des valeurs des différents champs

    int client_exists = 1;
    client.firstname = gtk_entry_get_text(GTK_ENTRY(firstname));
    client.lastname = gtk_entry_get_text(GTK_ENTRY(lastname));
    client.numcart = client.firstname;
    client.classroom = gtk_entry_get_text(GTK_ENTRY(classroom));
    const gchar * age_saisie;
    age_saisie = (gtk_entry_get_text(GTK_ENTRY(age)));
    client.age = atoi(age_saisie);
    
    client_exists = checkIfClientExist(client);

    if(client_exists == 1){
        insertClient(client);
        gtk_label_set_text(GTK_LABEL(save_client_success), "Client ajouté avec succès !");
        gtk_label_set_text(GTK_LABEL(message_operation_on_saving_client), "");
    }
    else {
        // enregistrer ce utilisateur
        gtk_label_set_text(GTK_LABEL(save_client_success), "");
        gtk_label_set_text(GTK_LABEL(message_operation_on_saving_client), "Cet client existe déja !");        
    }
    //verification des la base de données
}




void on_hide_client_saver_page_clicked(){
    gtk_widget_hide(win_for_save_client);
}
int myflag = 1;
void on_remove_client_button_clicked(){
    if(myflag == 1){
        gtk_widget_hide(container_to_save_client);
        gtk_widget_show(container_to_remove_client);
        gtk_label_set_text(GTK_LABEL(message_operation_on_saving_client), "");

        myflag = 0;
    }
    else{
        gtk_widget_show(container_to_save_client);
        gtk_widget_hide(container_to_remove_client);
        gtk_label_set_text(GTK_LABEL(message_operation_on_saving_client), "");
        myflag = 1;
    }
    
}
void on_remove_action_clicked() {
    int flag = 1;
    client.numcart = gtk_entry_get_text(GTK_ENTRY(num_carte_to_remove));

    flag = checkIfClientExist(client);

    if(flag == 0){
        removeClient(client);
        gtk_label_set_text(GTK_LABEL(message_operation_on_saving_client), "Client supprimer avec succès !");
    }else{
        gtk_label_set_text(GTK_LABEL(message_operation_on_saving_client), "Client introuvable !");
    }
}


void on_hide_client_page_clicked(){

    gtk_widget_hide(client_page); 
           
}


/************************ EMPRUNT DE LIVRE ET DEPOT *******************************/



void on_borrow_return_button_clicked(){

    if( f == 0 ){
        printf("Emprunt ...\n");
        printf("flag_of_borrow : %d \n", flag_of_borrow);
        gtk_widget_show(borrow_window);
        gtk_label_set_text(GTK_LABEL(message_text_borrow), "");
        gtk_entry_set_text(GTK_ENTRY(num_cart_label_to_borrow), "");
        gtk_entry_set_text(GTK_ENTRY(title_of_book_to_borrow), "");
        // gtk_button_set_label(GTK_BUTTON(return_on_book), "Emprunter un livre");
        gtk_label_set_text(GTK_LABEL(return_book_label), "EMPRUNTER UN LIVRE");
        
    }
    else if(f == 1){
        printf("retourner ...\n");
        printf("flag_of_borrow : %d \n", flag_of_borrow);
        gtk_widget_show(borrow_window);
        gtk_label_set_text(GTK_LABEL(message_text_borrow), "");
        gtk_entry_set_text(GTK_ENTRY(num_cart_label_to_borrow), "");
        gtk_entry_set_text(GTK_ENTRY(title_of_book_to_borrow), "");
        // gtk_button_set_label(GTK_BUTTON(return_on_book), "Retourner un livre");

        gtk_label_set_text(GTK_LABEL(return_book_label), "RETOURNER UN LIVRE");        
        
    }
    f = return_flag(f);
    
}

void on_hide_borrow_window_clicked(){
    gtk_widget_hide(borrow_window);
}
void on_clear_fields_of_borrow_clicked(){
    gtk_entry_set_text(GTK_ENTRY(num_cart_label_to_borrow), "");
    gtk_entry_set_text(GTK_ENTRY(title_of_book_to_borrow), "");
}

void on_submit_borrow_clicked(){
    client.numcart = gtk_entry_get_text(GTK_ENTRY(num_cart_label_to_borrow));
    book.title = gtk_entry_get_text(GTK_ENTRY(title_of_book_to_borrow));
    int flag_exist = checkIfAlreadyBorrow(client);
    int flag_client = checkIfClientExist(client);
    int flag_stock = checkStockOfBook(book);    
    int flag_book = checkIfBookExist(book);

    //Verifier d'abord si l'on veut faire un retrait ou un dépot
    if(f == 0){
        // le client veut returne
        //le client a déja fait objet d'emprunt
        printf("faire un retour \n");
        if(flag_exist == 1){ // le client a-t-il déjà fait un emprunt sans retourner ?
            gtk_label_set_text(GTK_LABEL(message_text_borrow), "Aucun retour pour !!!");
        }else if(flag_client == 1){
            gtk_label_set_text(GTK_LABEL(message_text_borrow), "Veuillez avant tout enregistrer le client !!!");
        }else if(flag_stock == 0){
            gtk_label_set_text(GTK_LABEL(message_text_borrow), "Le stock de livre est epuisé. Veuillez repasser plutard");
        }
        else if(flag_book == 1){
            gtk_label_set_text(GTK_LABEL(message_text_borrow), "Ce livre n'a pas encore été enregistré");
        }else{
            // borrowOneBook(book,client, user);
            returnOneBook(book,client, user);
            gtk_label_set_text(GTK_LABEL(message_text_borrow), "Opération de depot enregistré avec succès");            
        }        
    }else{
        // le client veut faire un emprunt
        printf("faire un emprunt \n");
        if(flag_exist == 0){
            gtk_label_set_text(GTK_LABEL(message_text_borrow), "Veuillez déposer le livre précedent !!!");
        }else if(flag_client == 1){
            gtk_label_set_text(GTK_LABEL(message_text_borrow), "Veuillez avant tout enregistrer le client !!!");
        }else if(flag_stock == 0){
            gtk_label_set_text(GTK_LABEL(message_text_borrow), "Le stock de livre est epuisé. Veuillez repasser plutard");
        }
        else if(flag_book == 1){
            gtk_label_set_text(GTK_LABEL(message_text_borrow), "Ce livre n'a pas encore été enregistré");
        }else{
            borrowOneBook(book,client, user);
            gtk_label_set_text(GTK_LABEL(message_text_borrow), "Emprunt effectué avec succès");
        }
    }

}
// printf("flag_of_borrow : %d\n", flag_of_borrow);
void on_return_on_book_clicked(){    
    //Changer le label du haut
    // gtk_popover_popdown(container_of_borrow) ;
    // gtk_widget_(container_of_borrow);        
    // flag_of_borrow 
    if(f == 0){
        gtk_label_set_text(GTK_LABEL(return_book_label), "EMPRUNTER UN LIVRE");        
        gtk_label_set_text(GTK_LABEL(message_text_borrow), "");
        gtk_entry_set_text(GTK_ENTRY(num_cart_label_to_borrow), "");
        gtk_entry_set_text(GTK_ENTRY(title_of_book_to_borrow), "");
        gtk_button_set_label(GTK_BUTTON(return_on_book), "Emprunter");
        
        // printf("flag_to_borrow : %d\n", flag_to_borrow);
           
    }
    else{
        gtk_label_set_text(GTK_LABEL(return_book_label), "RETOURNER UN LIVRE");
        gtk_label_set_text(GTK_LABEL(message_text_borrow), "");
        gtk_entry_set_text(GTK_ENTRY(num_cart_label_to_borrow), "");
        gtk_entry_set_text(GTK_ENTRY(title_of_book_to_borrow), "");
        gtk_button_set_label(GTK_BUTTON(return_on_book), "Retourner");               
        // l'utilisateur veut faire un emprunt
    }
    f = return_flag(f);
   
    // gtk_widget_show(container_of_borrow);


}

void on_submit_button_to_statistic_clicked(){
    printf("comment \n");
    // gtk_widget_show(client_page);
    system(BOOK_STAT);
    system(BORROW_STAT);
}


void on_client_button_clicked() {
    
    gtk_widget_show(client_page);
    
}

void on_book_button_clicked(){
    gtk_widget_hide(container_to_remove_book);
    gtk_widget_show(win_for_save_book);    
}


void on_remove_book_button_clicked(){
    // flag_remove = return_flag(flag_remove);
    flag_remove = return_flag(flag_remove);
    if(flag_remove == 0){
        gtk_widget_hide(container_to_remove_book);
        gtk_widget_show(container_to_save_book);
        
    }else{
        gtk_widget_show(container_to_remove_book);
        gtk_widget_hide(container_to_save_book);
    }
}
void on_hide_book_saver_page_clicked(){
    gtk_widget_hide(win_for_save_book);
}
// void container_to_save_book(){

// }

void on_register_book_button_clicked(){
    // enregistrer un livre
    // verif
    //recupérer toutes les valeurs des champs
    book.title = gtk_entry_get_text(GTK_ENTRY(title));
    // book.qty = gtk_entry_get_text(GTK_ENTRY(qty));
    book.description = gtk_entry_get_text(GTK_ENTRY(description));
    book.author = gtk_entry_get_text(GTK_ENTRY(author));
    book.category = gtk_entry_get_text(GTK_ENTRY(category));
    book.qty = atoi(gtk_entry_get_text(GTK_ENTRY(qty)));
      
    int flag_book = checkIfBookExist(book);

    if(flag_book == 1){
        // Le livre existe belle et bien
        insertBook(book);
        gtk_label_set_text(GTK_LABEL(save_book_success_label), "Livre inséré avec succès");
        gtk_label_set_text(GTK_LABEL(message_operation_on_saving_book), "");
        
        
    }else{
        printf("Le livre existe belle et bien");
        gtk_label_set_text(GTK_LABEL(message_operation_on_saving_book), "Insertion de livre impossible");
    }
}

// supprimer un livre 
void on_remove_book_submit_clicked(){
    // recupérer la donnée du label
    book.title = gtk_entry_get_text(GTK_ENTRY(title_of_book));
    // verifier l'existence du livre dans la bd
    int flag_book_exist = checkIfBookExist(book);

    if(flag_book_exist == 0){
        //le livre existe alors supprimer autorisé
        removeBook(book);
        gtk_label_set_text(GTK_LABEL(save_book_success_label), "Suppression reussie");
        gtk_label_set_text(GTK_LABEL(save_book_success_label), "");
    }else{
        gtk_label_set_text(GTK_LABEL(message_operation_on_saving_book), "Impossible ! Livre inexistant !");
        gtk_label_set_text(GTK_LABEL(save_book_success_label), "");
    }
}

void on_close_book_saver_clicked(){
    gtk_entry_set_text(GTK_ENTRY(title), "");
    gtk_entry_set_text(GTK_ENTRY(description), "");
    gtk_entry_set_text(GTK_ENTRY(author), "");
    gtk_entry_set_text(GTK_ENTRY(category), "");
    gtk_entry_set_text(GTK_ENTRY(qty), "");
    gtk_entry_set_text(GTK_ENTRY(title_of_book), "");
}

void add_grid_to_box(){
    
}
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}


void show_list_of_book_clicked_cb(){
    system(SHOW_BOOKS);
}

void save_client_button_cb(){
    system(SHOW_CLIENTS);
}