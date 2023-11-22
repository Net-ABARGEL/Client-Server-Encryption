import sqlite3

conn = sqlite3.connect('defensive.db')

# Create a cursor object to execute SQL commands
cursor = conn.cursor()

# Define the SQL command to create the "clients" table
create_table_query = '''
CREATE TABLE clients (
    ID BLOB(16) PRIMARY KEY,
    name TEXT(255) NOT NULL,
    PublicKey BLOB(160),
    LastSeen DATETIME,
    AESKey BLOB(16)
);
'''

# Execute the SQL command to create the table
cursor.execute(create_table_query)

# Commit the changes and close the connection
conn.commit()

create_table_query = '''
CREATE TABLE files (
    ID BLOB(16),
    FileName TEXT(255) NOT NULL,
    PathName TEXT(255) ,
    Verified BOOLEAN
);
'''

# Execute the SQL command to create the table
cursor.execute(create_table_query)

conn.commit()
conn.close() # close the SQL file
