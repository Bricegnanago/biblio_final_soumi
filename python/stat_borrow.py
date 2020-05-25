import matplotlib.pyplot as plt
import mysql.connector



# On veut savoir les étudiants qui lisent beaucoup
# Algorithme : recupérer dans la table d'emprunt tous
# 1 - Recuperer le nombre d'enregistrement dans la table Borrow
# 2 - stocker cette valeur dans une variable
# 3 - Recuperer le nombre d'enregistrement dans la table Borrow d'emprunt sans retour de livre
#


mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  passwd="root",
  database="testdb"
)
#virtualenv -p python3 sqlenv


mycursor = mydb.cursor()
mycursor.execute("select count(*) as effectif from Borrow")
count_boroow_table = mycursor.fetchall()

# Tout les livre emprunté
mycursor.execute("SELECT count(*) FROM Borrow where DateOfReturn IS NULL")
qty_books_returned = mycursor.fetchall()

qty_books = []
for x in qty_books_returned:
  qty_books.append(x[0])


qty_books.append(count_boroow_table[0][0] - qty_books[0])


titles = ['Livres emprunté', 'Livres returné']


name = titles
data = qty_books

plt.title("ETAT DE LA BIBLIOTHEQUE CONCERNANT LES EMPRUNTS", loc='center')
plt.pie(qty_books, labels=name, autopct='%.2f', startangle=90, shadow=True, radius=5)
plt.axis('equal')
plt.show()
