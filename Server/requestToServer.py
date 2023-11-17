# function that create a 9 byte length data and seperate it to a request format for the project.
import struct


def convertByteToInt(byte):
    return int.from_bytes(byte, 'big')


def request_from_client(conn):
    # Receive id (16-byte), version (1-byte), code (2-byte), and payload length (4-byte)
    header = conn.recv(135)

    if not header:
        return None

    id_size = 128
    version_size = 1
    code_size = 2
    payload_length_size = 4

    id_data = header[:id_size].decode("utf-8")
    version_data = convertByteToInt(header[id_size:id_size + version_size])
    code_data = convertByteToInt(header[id_size+version_size:id_size + version_size + code_size])
    payload_length = header[id_size + version_size + code_size:id_size + version_size + code_size+payload_length_size]
    payload_length_decimal = convertByteToInt(payload_length)
    # Receive payload
    payload_data = conn.recv(payload_length_decimal)

    print("request data\n")
    print(id_data)
    print("\n")
    print(code_data)
    print("\n")


    return {
        'id': id_data,
        'version': version_data,
        'code': code_data,
        'payload_length': payload_length_decimal,
        'payload': payload_data
    }
# You can access the ID using result['id'] in your calling code.