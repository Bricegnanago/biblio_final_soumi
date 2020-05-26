import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import mysql.connector


mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  passwd="root",
  database="testdb"
)

mycursor = mydb.cursor()
mycursor.execute("select title, author, nb_page, qty from Book WHERE statusBook = 0")
listOfClient = mycursor.fetchall()

clients = listOfClient


# print(clients)

fig, ax = plt.subplots()

# hide axes
fig.patch.set_visible(False)
ax.axis('off')
ax.axis('tight')
list_column = ['Titre', 'Auteur', "Nbre pages", "qte"]
df = pd.DataFrame(clients, columns=list_column)

ax.table(cellText=df.values, colLabels=df.columns, loc='center')
fig.tight_layout()

plt.show()