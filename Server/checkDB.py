import sqlite3
import os
from datetime import datetime

from nameToUUID import text_to_hex_id


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

    # Fetch the result
    result = cursor.fetchone()

    # Close the database connection
    conn.close()

    # If the count is greater than 0, the name exists; otherwise, it does not
    return result[0] > 0


def add_new_client(name):
    if not check_name_exists(name):
        conn = sqlite3.connect("defensive.db")
        cursor = conn.cursor()
        # Insert a new row with the provided name into the "clients" table
        cursor.execute("INSERT INTO clients (name) VALUES (?)", (name,))
        conn.commit()
        conn.close()
        print(f"Client '{name}' has been added to the database.")
    else:
        print(f"Client '{name}' already exists in the database.")


def add_uuid_client(uuid, name):
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    # Insert a new row with the provided name into the "clients" table
    cursor.execute("UPDATE clients SET ID = ? WHERE name = ?", (uuid, name))
    conn.commit()
    conn.close()
    print(f"UUId '{uuid}' has been added to the Client.")


def last_time_seen_update(name):
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    current_datetime = datetime.now()
    # Insert a new row with the provided name into the "clients" table
    cursor.execute("UPDATE clients SET LastSeen = ? WHERE name = ?", (current_datetime, name))
    conn.commit()
    conn.close()
    print("Last seen has updated for client" + name)


def add_pub_key_client(client_name, pubkey):
    conn = sqlite3.connect("defensive.db")
    cursor = conn.cursor()
    # Insert a new row with the provided name into the "clients" table
    cursor.execute("UPDATE clients SET PublicKey = ? WHERE name = ?", (pubkey, client_name))
    conn.commit()
    conn.close()
    print("Client public key has updated for client")
