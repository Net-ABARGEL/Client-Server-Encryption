from checkDB import check_name_exists, add_uuid_client, last_time_seen_update, add_pub_key_client
from checkDB import add_new_client
from nameToUUID import text_to_hex_id
from handler import case_2100,case_2101,case_2102,case_2103,case_2104,case_2105,case_2106,case_2107



# def handleRequests(clientrequest):
#    requestnum = getclientrequestnum(clientrequest)
#    switch_case(requestnum, clientrequest)


def convertByteToInt(byte):
    return int.from_bytes(byte, 'big')


def onvertByteToString(byte):
    return


def getclientrequestnum(clientrequest):
    requestnum = convertByteToInt(clientrequest['code'])
    return requestnum


def case1025(clientrequest, conn):
    print("Trying register to the system\n")
    client_name_byte = clientrequest['payload'].decode("utf-8").rstrip('\x00')
    if check_name_exists(client_name_byte):
        case1027(clientrequest)
       # return

    add_new_client(client_name_byte)
    uuid = text_to_hex_id(client_name_byte)
    add_uuid_client(uuid, client_name_byte)
    last_time_seen_update(client_name_byte)

    case_2100(conn, uuid)


def case1026(clientrequest, conn):
    print("Received Public Key\n")
    client_id = clientrequest['id']
    payload = clientrequest['payload']
    client_name = payload[:255].decode("utf-8").rstrip('\x00')
    client_pub_key = payload[255:]
    add_pub_key_client(client_name, client_pub_key)

def case1027(clientrequest):
    print("User exist, Reconnecting to the system\n")



def case1028(clientrequest):
    print("Received the File\n")


def case1029(clientrequest):
    print("CRC Correct\n")


def case1030(clientrequest):
    print("CRC Error - sending again\n")


def case1031(clientrequest):
    print("This is case 1031\n")


def default(clientrequest):
    print("somethong not good happened\n")



