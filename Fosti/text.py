import mysql.connector
cnx = mysql.connector.connect(user='root',password='baseball09',host='127.0.0.1',database='testing_stuff')
cursor=cnx.cursor()
query = ("SELECT * FROM first_table")
cursor.execute(query)
for (ID,first_name,last_name,age,cell_phone) in cursor: 
    print(", {}, {} is {} and his cell phone is {}".format(first_name,last_name,age,cell_phone))