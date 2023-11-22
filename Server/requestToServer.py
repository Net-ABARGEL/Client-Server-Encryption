
# function that convert Byte to Int
def convertByteToInt(byte):
    return int.from_bytes(byte, 'big')

# function that handle the request from the client and return it as struct of request
def request_from_client(conn):
    # Receive id (16-byte), version (1-byte), code (2-byte), and payload length (4-byte)
    header = conn.recv(135)

    if not header:
        return None # not request

    id_size = 128   # 16 byte
    version_size = 1
    code_size = 2
    payload_length_size = 4

    # receiving all the information from the request
    id_data = header[:id_size].decode("utf-8")
    version_data = convertByteToInt(header[id_size:id_size + version_size])
    code_data = convertByteToInt(header[id_size+version_size:id_size + version_size + code_size])
    payload_length = header[id_size + version_size + code_size:id_size + version_size + code_size+payload_length_size]
    payload_length_decimal = convertByteToInt(payload_length)

    # after knowing the payload size, reading the paylaod
    payload_data = conn.recv(payload_length_decimal)


    return {
        # the struct of request
        'id': id_data,
        'version': version_data,
        'code': code_data,
        'payload_length': payload_length_decimal,
        'payload': payload_data
    }
