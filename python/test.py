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
mycursor.execute("select firstname, lastname, numcart, age, classroom from Client WHERE status_client=0")
listOfClient = mycursor.fetchall()

clients = listOfClient


# print(clients)

fig, ax = plt.subplots()

# hide axes
fig.patch.set_visible(False)
ax.axis('off')
ax.axis('tight')
list_column = ['Nom', 'Prenom', "N° Cart", "age", "Classe"]
df = pd.DataFrame(clients, columns=list_column)

ax.table(cellText=df.values, colLabels=df.columns, loc='center')

fig.tight_layout()

plt.show()