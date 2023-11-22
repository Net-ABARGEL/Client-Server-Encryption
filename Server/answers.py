import base64
import sys
import struct


from Crypto.PublicKey import RSA

import checksum
import handler
from AES_implement import rsa_encrypt, rsa_decrypt
from answerToClient import answer_to_client
from checkDB import get_public_key, get_aes_key, get_UUID
from nameToUUID import text_to_hex_id
from requestToServer import request_from_client


def case_2100(conn, uuid):
    print("Sending UUID")
    uuid_byte = uuid.encode("utf-8")
    answer = answer_to_client(2100, len(uuid_byte), uuid_byte)
    conn.sendall(answer)
    request = request_from_client(conn)
    return handler.handle_req(request, conn)


def case_2101():
    return "Processing for Case 2101"


# sending aes after receive public key
def case_2102(conn, client_name):
    print("Sending AES encrypted key\n")
    # get public key in RSA format
    public_key_bytes = get_public_key(client_name)
    # public_key_bytes = public_key_bytes.replace(b'\n', b'')
    decoded_public_key_bytes = base64.b64decode(public_key_bytes)
    public_key = RSA.import_key(decoded_public_key_bytes)

    # get AES key and encrypt with public key
    aes_key = get_aes_key(client_name)
    encrypt_aes_key = rsa_encrypt(public_key, aes_key)

    # create answer format
    client_id = get_UUID(client_name)
    payload_list = [client_id.encode("utf-8"), encrypt_aes_key]
    payload = b''.join(payload_list)
    payload_size =len(client_id) + len(encrypt_aes_key)
    answer = answer_to_client(2102, payload_size, payload)

    # send answer
    conn.sendall(answer)

    # receive request and handle it
    request = request_from_client(conn)
    return handler.handle_req(request, conn)


def case_2103(conn, client_id, payload, decrypted_file):
    print( "Checking CRC")
    checkSum  = checksum.readfile(decrypted_file)
    checkSum = checkSum.ljust(32, '\x00')
    payload_new = payload + checkSum.encode("utf-8")
    payload_size = len(payload_new)
    answer = answer_to_client(2103, payload_size, payload_new)
    conn.sendall(answer)

    request = request_from_client(conn)
    return handler.handle_req(request, conn)




def case_2104(clientrequest, conn):
    print("Logging off the client ")
    client_id = clientrequest['id'].encode("utf-8")
    answer = answer_to_client(2104, len(client_id), client_id) # sending the answer to the client
    return conn.sendall(answer)


# handling case 2105 - reconnecting to the system
def case_2105(client_name, conn):
    print("Reconnected accepted, Sending AES encrypted key\n")
    # get public key in RSA format
    public_key_bytes = get_public_key(client_name)
    # public_key_bytes = public_key_bytes.replace(b'\n', b'')
    decoded_public_key_bytes = base64.b64decode(public_key_bytes)
    public_key = RSA.import_key(decoded_public_key_bytes)

    # get AES key and encrypt with public key
    aes_key = get_aes_key(client_name)
    encrypt_aes_key = rsa_encrypt(public_key, aes_key)

    # create answer format
    client_id = get_UUID(client_name)
    payload_list = [client_id.encode("utf-8"), encrypt_aes_key]
    payload = b''.join(payload_list)
    payload_size = len(client_id) + len(encrypt_aes_key)
    answer = answer_to_client(2105, payload_size, payload)

    # send answer
    conn.sendall(answer)

    # receive request and handle it
    request = request_from_client(conn)
    return handler.handle_req(request, conn)


# handling the 2106- employee that is not registered to the system and
def case_2106(client_name, conn):
    print("the user isn't exist, Please Register")
    uuid = text_to_hex_id(client_name)
    answer = answer_to_client(2106, 128, uuid.encode("utf-8"))
    conn.sendall(answer)

    request = request_from_client(conn)
    return handler.handle_req(request, conn)


# handling case 2107 - error with the server
def case_2107(conn):
    print("having error with the server")
    answer = answer_to_client(2107, 0,) # sending error
    return conn.sendall(answer)


def default_case():
    return "Default Case"


# handling case 1030 - resending the file because of CRC error
def case_1030(clientrequest, conn):
    print("CRC Error - file sent again\n")
    request = request_from_client(conn)
    return handler.handle_req(request, conn)
