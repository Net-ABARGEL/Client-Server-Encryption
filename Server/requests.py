import os

import AES_implement
from answers import case_1030
from checkDB import check_name_exists, add_uuid_client, last_time_seen_update, add_pub_key_client, add_aes_key_db, \
    get_aes_key, get_aes_key_by_id, add_file_db, set_file_verification_db
from checkDB import add_new_client
from nameToUUID import text_to_hex_id
from handler import case_2100, case_2101, case_2102, case_2103, case_2104, case_2105, case_2106, case_2107


# handling answer N1025
def case1025(clientrequest, conn):
    print("Trying register to the system\n")
    client_name_byte = clientrequest['payload'].decode("utf-8").rstrip('\x00')
    if check_name_exists(client_name_byte): # if user already exist - go handle case 1027 - reconnect
        print("User Exist\n")
        return case1027(clientrequest, conn)
    # exporting client info
    add_new_client(client_name_byte)
    uuid = text_to_hex_id(client_name_byte)

    # add uuid and lastseen to DB
    add_uuid_client(uuid, client_name_byte)
    last_time_seen_update(client_name_byte)

    # generate AES key and add to DB
    aes_key = AES_implement.generate_aes_key()
    add_aes_key_db(client_name_byte, aes_key)

    return case_2100(conn, uuid)


# handling case n1026 - receiving public key
def case1026(clientrequest, conn):
    print("Received Public Key\n")
    payload = clientrequest['payload']
    client_name = payload[:255].decode("utf-8").rstrip('\x00')

    # exporting public key and import to the DB
    client_pub_key = payload[255:]
    add_pub_key_client(client_name, client_pub_key)

    return case_2102(conn, client_name)


# handling case 1027  - reconnecting to the system
def case1027(clientrequest, conn):
    print("Reconnecting to the system\n")
    client_name_byte = clientrequest['payload'].decode("utf-8").rstrip('\x00')
    # if the user not exist - registering to the system
    if not check_name_exists(client_name_byte):
        return case_2106(client_name_byte, conn)
    return case_2105(client_name_byte, conn)


# handling cast 1028 request - Receive encrypted file
def case1028(clientrequest,conn):
    print("Received the File\n")
    client_id = clientrequest['id'].rstrip('\x00')
    payload = clientrequest['payload']

    # exporting the file, add to DB and decrypt it
    file_path_name = payload[4:259].decode("utf-8").rstrip('\x00')
    path, filename = os.path.split(file_path_name)
    add_file_db(client_id, filename, path)
    encrypt_file = payload[259:]
    aes_key = get_aes_key_by_id(client_id)
    decrypted_value = AES_implement.decrypt_aes_value(aes_key, encrypt_file)

    return case_2103(conn, client_id, payload, decrypted_value)


# handling case 1029 - CRC is correct
def case1029(clientrequest, conn):
    print("CRC Correct\n")
    # sending message and close the connection with the client
    file_path_name = clientrequest['payload'].decode("utf-8").rstrip('\x00')
    path, filename = os.path.split(file_path_name)
    set_file_verification_db(filename)
    return case_2104(clientrequest, conn)


# handling case 1030 - error with CRC less than 4th time
def case1030(clientrequest, conn):
    return case_1030(clientrequest, conn) # trying to receive the file again


# handling case 1030 - error with CRC for the 4th time
def case1031(clientrequest, conn):
    print("This is case 1031\n")
    return case_2104(conn) # sending message and close the connection with the client


# error case
def default(clientrequest, conn):
    return print("something went wrong\n")
