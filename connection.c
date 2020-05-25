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

#define GLOBAL_STAT "\
#/bin/bash \n\
python python/global_stat.py \n\
"



// On veut savoir les étudiants qui lisent beaucoup
// Le pourcentage d'etudiant ayant emprunté sans retourner le livre



int main(int argc, char **argv)
{
    int choix;
    int choix_operation_on;
    Client client;
    Client clientHost;
    Book bookHost;
    Client dataClientToUpdate;
    Book book;
    Book dataBookToUpdate;
    User user_session;
    int flag_auth=1;
    do
    {
        /* Authentification */
        printf("Login : ");
        scanf("%s", user_session.username);

        printf("Mode de passe : ");
        scanf("%s", user_session.password);
        flag_auth =  checkIfUserExist(user_session);        
    } while (flag_auth == 1);
    //Authentification réussi
    printf("Bienvenue sur notre plateforme");
    

    printf("Bonjour à tous !!!\n\n");


    do
    {
        printf("*************************************************************\n");
        printf("\t 1 > Gerer client \n");
        printf("*************************************************************\n");

        printf("*************************************************************\n");
        printf("\t 2 -> Gerer pour livre \n");
        printf("*************************************************************\n");

        printf("*************************************************************\n");
        printf("\t 3 -> Enregistrer un emprunt \n");
        printf("*************************************************************\n");

        printf("*************************************************************\n");
        printf("\scort 4 -> Enregistrer un depot \n");
        printf("*************************************************************\n");
        printf("*************************************************************\n");
        printf("\t 0 -> Quitter le programme \n");
        printf("*************************************************************\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                //Le choix est client
                printf("*************************************************************\n");
                printf("\t 11 ->  Creer enregistrer un nouveau client \n");
                printf("*************************************************************\n");

                printf("*************************************************************\n");
                printf("\t 12 -> Mettre à jour les donnees d'un client \n");
                printf("*************************************************************\n");

                printf("*************************************************************\n");
                printf("\t 13 -> supprimer un client \n");
                printf("*************************************************************\n");

                printf("Votre choix : ");
                scanf("%d", &choix_operation_on);

                //Afficher tous les clients
                readAll("Client");
                //Fin affichage client
                //Deconnexion

                switch (choix_operation_on)
                {
                    case 11 :
                        //code création client
                        printf("\n*** Creer maintenant un nouveau client ***\n\n");
                        printf("Nom : ");
                        scanf("%s", client.lastname);                

                        printf("prenom : ");
                        scanf("%s", client.firstname);

                        printf("numero carte etudiant : ");
                        scanf("%s", client.numcart);

                        printf("Classe Etudiant : ");
                        scanf("%s", client.classroom);

                        printf("Age Etudiant : ");
                        scanf("%d", &client.age);

                        //Debut insertion
                        insertClient(client);
                        //Fin insertion
                        break;

                    case 12 :
                        //code mise à jour donnée client
                        /* code Mise à jour*/
                        // Selectionner la variable à mettre à jour
                        // puis demander à l'utilisateur de saisir de nouvelles données
                        printf("Voici là tous les livres enregistré dans notre base\n\n");
                        printf("Veuillez saisir le titre du livre à mettre à jour : ");
                        scanf("%s", clientHost.firstname); //
                        
                        // verifier si la donnée existe
                        
                        printf("Nom etudiant: ");
                        scanf("%s", client.lastname);                

                        printf("prenom etudiant : ");
                        scanf("%s", client.firstname);

                        printf("numero carte etudiant : ");
                        scanf("%s", client.numcart);

                        printf("Classe etudiant : ");
                        scanf("%s", client.classroom);

                        printf("Age Etudiant : ");
                        scanf("%d", &client.age);

                        // mise à jour
                        updateClient(clientHost, client);
                        break;
                    case 13 :
                        //code   suppression client
                        printf("Veuillez saisir le nom du client à supprimer : ");
                        scanf("%s", client.firstname);
                        removeClient(client);
                        break;
                        
                    default:
                        printf("Saisie incorrecte !!!\n");
                        break;
                }
                break;
            
            case 2:
                //Le choix est livre
                //Afficher avant la liste de tous les utilisateurs
                printf("*************************************************************\n");
                printf("\t 21 ->  Creer enregistrer un nouveau Livre \n");
                printf("*************************************************************\n");

                printf("*************************************************************\n");
                printf("\t 22 -> Mettre à jour les donnees d'un Livre \n");
                printf("*************************************************************\n");

                printf("*************************************************************\n");
                printf("\t 23 -> supprimer un Livre \n");
                printf("*************************************************************\n");

                printf("*************************************************************\n");
                printf("\t 24 -> Statistique un Livre \n");
                printf("*************************************************************\n");

                printf("Votre choix : ");
                scanf("%d", &choix_operation_on);


                //Debut affichage livre
                readAll("Book");

                //Fin affichage livre           
                //Deconnexion
                switch (choix_operation_on)
                {
                case 21:
                    /* code creation livres*/
                    // 1 - L'utilisateur renseigne les informations du livre à inserer
                    // livre_id, nb_page author description title category created last_update
                    printf("Veuillez renseigner les informations concernant le nouveau livre !!!\n\n");

                    printf("Titre du livre : ");
                    scanf("%s", book.title);

                    printf("Description : ");
                    scanf("%s", book.description);

                    printf("Auteur du livre : ");
                    scanf("%s", book.author);

                    printf("Nombre de pages : ");
                    scanf("%d", &book.nb_page);                            
                    
                    printf("Categorie : ");
                    scanf("%s", book.category);

                    printf("Quantité en stock : ");
                    scanf("%d", &book.qty);
                    // insertion
                    insertBook(book);                
                    
                    break;
                

                case 22:
                    /* code Mise à jour*/
                    // Selectionner la variable à mettre à jour
                    // puis demander à l'utilisateur de saisir de nouvelles données
                    printf("Voici là tous les livres enregistrés dans notre base\n\n");
                    printf("Veuillez saisir le titre du livre à mettre à jour : ");
                    scanf("%s", bookHost.title);
                    
                    // verifier si la donnée existe
                    
                    printf("\n Titre du livre : ");
                    scanf("%s", book.title);

                    printf("Description : ");
                    scanf("%s", book.description);

                    printf("Auteur du livre : ");
                    scanf("%s", book.author);

                    printf("Nombre de pages : ");
                    scanf("%d", &book.nb_page);                            
                    
                    printf("Categorie : ");
                    scanf("%s", book.category);

                    updateBook(bookHost, book);

                    break;

                case 23:
                    //suppression code of book
                    printf("Veuillez saisir le nom du client à supprimer : ");
                    scanf("%s", book.title);
                    removeBook(book);
                    break; 
                case 24:
                    //suppression code of book
                    system(BOOK_STAT);
                    break;             
                default:
                    printf("Saisie incorrecte");
                    break;
                }

                break;
            
            case 3:
                // code empreint

                    //Le choix est livre
                //Afficher avant la liste de tous les utilisateurs
                printf("*************************************************************\n");
                printf("\t 31 -> Enregistrer un nouvel emprunt \n");
                printf("*************************************************************\n");

                printf("*************************************************************\n");
                printf("\t 32 -> Visualiser les statistiques \n");
                printf("*************************************************************\n");

                printf("Votre choix : ");
                scanf("%d", &choix_operation_on);

                switch (choix_operation_on)
                {
                case 31:
                     printf("Quel livre aimeriez-vous emprunter ?\n\n");
                    /********* Info Client ********/
                    printf("Veuillez saisir le nom du client : ");
                    scanf("%s", client.firstname);
                    printf("Veuillez saisir le numero de carte du client : ");
                    scanf("%s", client.numcart);

                    printf("Saisir ici le title du livre : ");
                    scanf("%s", bookHost.title);

                    borrowOneBook(bookHost, client, user_session);
                     
                    break;
                
                case 32:
                    printf("\nVeuillez patienter svp...\n");
                    system(BORROW_STAT);     
                    break;
                default:
                    printf("Saisie incorrecte");
                    break;
                }
               
               
                printf("\n\n********************** Opération effectuée avec succès ********************** \n\n");
                break;

            case 4:
                // code empreint            
                printf("Quel livre aimeriez-vous deposer ?\n\n");
                /********* Info Client ********/
                printf("Veuillez saisir le nom du client : ");
                scanf("%s", client.firstname);
                printf("Veuillez saisir le numero de carte du client : ");
                scanf("%s", client.numcart);
                
                
                printf("Saisir ici le title du livre : ");
                scanf("%s", bookHost.title);

                returnOneBook(bookHost, client, user_session);
                
                printf("*********** \n\n Opération effectuée avec succès ***************** \n\n");
                break;
            
            default:
                printf("\n Saisie incorrecte !!! \n\n");
                
                break;
        }
        printf("Voulez-vous vraiment quitter le programme 0 (Oui) et 1-9 (Non) ?\n");
        printf("Saisir ici : ");
        scanf("%d", &choix);
        if(choix == 0)
            printf("\nBye\n");


    } while (choix != 0);
    
    


    
    
   
  exit(0);
}