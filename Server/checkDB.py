import sqlite3
import os
from datetime import datetime


def check_and_create_tables():
    # Check if the "defensive.db" file exists
    if not os.path.exists("defensive.db"):
        # If the file does not exist, use the code from "createDBCode" to create the database and tables

        # Open the file in write mode, creating it if it doesn't exist
        with open("defensive.db", "w"):
            pass

        with open("createDBCode.py", "r") as code_file:
            create_db_code = code_file.read()

        # Execute the code to create the database and tables
        exec(create_db_code)
        print("Tables not found. Created tables using the code in 'createDBCode'.")
        return

    # Connect to the database
    conn = sqlite3.connect("defensive.db")

    # Create a cursor object
    cursor = conn.cursor()

    # Check if the "clients" table exists
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='clients'")
    clients_table_exists = cursor.fetchone() is not None

    # Check if the "files" table exists
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='files'")
    files_table_exists = cursor.fetchone() is not None

    # Close the cursor and connection
    cursor.close()
    conn.close()

    # Return True if both tables exist, False otherwise
    if clients_table_exists and files_table_exists:
        print("Tables already exist.")


# Check and create tables if needed

# check if the name of the client already exist
def check_name_exists(name):
    # Connect to the SQLite database file
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()

    # Execute a SELECT query to check if the name exists in the "clients" table
    cursor.execute("SELECT COUNT(*) FROM clients WHERE name=?", (name,))

    result = cursor.fetchone()

    # Close the database connection
    conn.close()

    # If the count is greater than 0, the name exists; otherwise, it does not
    return result[0] > 0


# function that add a new client
def add_new_client(name):
    if not check_name_exists(name):
        # connect to DB
        conn = sqlite3.connect("defensive.db")
        cursor = conn.cursor()
        # Insert a new row with the provided name into the "clients" table
        cursor.execute("INSERT INTO clients (name) VALUES (?)", (name,))
        # save the DB
        conn.commit()
        conn.close()
        print(f"Client '{name}' has been added to the database.")
    else:
        print(f"Client '{name}' already exists in the database.")


def add_uuid_client(uuid, name):
    # connect to DB
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    # update the UUID with the provided name into the "clients" table
    cursor.execute("UPDATE clients SET ID = ? WHERE name = ?", (uuid, name))
    # save the DB
    conn.commit()
    conn.close()
    print(f"UUId '{uuid}' has been added to the Client.")


def last_time_seen_update(name):
    # connect to DB
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    current_datetime = datetime.now()
    # update the Last Seen with the provided name into the "clients" table
    cursor.execute("UPDATE clients SET LastSeen = ? WHERE name = ?", (current_datetime, name))
    conn.commit()
    conn.close()
    print("Last seen has updated for client" + name)


def add_pub_key_client(client_name, pubkey):
    # connect to the DB
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    # update the Public Key with the provided name into the "clients" table
    cursor.execute("UPDATE clients SET PublicKey = ? WHERE name = ?", (pubkey, client_name))
    # save DB
    conn.commit()
    conn.close()
    print("Client public key has updated for client")


def add_aes_key_db(client_name, aes_key):
    # connect to the DB
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    # update the AES Key with the provided name into the "clients" table
    cursor.execute("UPDATE clients SET AESKey = ? WHERE name = ?", (aes_key, client_name))
    conn.commit()
    conn.close()
    print("Client AES KEY key has updated")


def add_file_db(ID, file_name,file_path):
    # connect to the DB
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    # Insert a new row with the provided file_name into the "files" table
    cursor.execute("INSERT INTO files (FileName) VALUES (?)", (file_name,))
    # update the ID and PathName with the provided name into the "clients" table
    cursor.execute("UPDATE files SET ID = ? WHERE FileName = ?", (ID, file_name))
    cursor.execute("UPDATE files SET PathName = ? WHERE ID = ?", (file_path, ID))
    conn.commit()
    conn.close()
    print("file has been updated in DB successfully")


def set_file_verification_db(file_name):
    # connect to the DB
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    # update the Verified value to TRUE with the provided name into the "clients" table
    cursor.execute("UPDATE files SET Verified = ? WHERE FileName = ?", (1, file_name))
    conn.commit()
    conn.close()
    print("Verified file has been updated")


def get_public_key(client_name):
    # connect to the DB
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    # get the public key of a client by the client name
    cursor.execute("SELECT PublicKey FROM clients WHERE name=?", (client_name,))
    result = cursor.fetchone()
    conn.close()
    if result:
        # Extract the bytes object from the tuple
        public_key_bytes = result[0].strip()
        return public_key_bytes
    else:
        # public key is empty
        return None


def get_aes_key(client_name):
    # connect to DB
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    # get the AES key of a client by the client name
    cursor.execute("SELECT AESKey FROM clients WHERE name=?", (client_name,))
    result = cursor.fetchone()
    conn.close()
    if result:
        # Extract the bytes object from the tuple
        aes_key_bytes = result[0].strip()
        return aes_key_bytes
    else:
        return None


def get_UUID(client_name):
    # connect to DB
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    # get the ID of a client by the client name
    cursor.execute("SELECT ID FROM clients WHERE name=?", (client_name,))
    result = cursor.fetchone()
    conn.close()
    if result:
        # Extract the bytes object from the tuple
        id_bytes = result[0].strip()
        return id_bytes
    else:
        return None


def get_aes_key_by_id(client_id):
    # connect to DB
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    # get the AES key of a client by the client ID
    cursor.execute("SELECT AESKey FROM clients WHERE ID=?", (client_id,))
    result = cursor.fetchone()
    conn.close()
    if result:
        # Extract the bytes object from the tuple
        aes_key_bytes = result[0].strip()
        return aes_key_bytes
    else:
        return None