import json

# a function that create an answer struct that sent to the client
def answer_to_client(code, payload_size, payload):
    # convert the values to the size it needs to be
    code_byte = value_to_bytes(code, 2)
    payload_size_byte = value_to_bytes(payload_size, 4)
    if isinstance(payload, dict):
        payload = json.dumps(payload).encode('utf-8')

    # create the struct
    return b''.join([
        value_to_bytes(3, 1),
        code_byte,
        payload_size_byte,
        payload
    ])


# convert each value to bytes
def value_to_bytes(number, num_bytes):
    try:
        # Convert the integer to bytes
        byte_representation = number.to_bytes(num_bytes, 'little')

        return byte_representation
    except OverflowError:
        raise ValueError(f"Integer {number} is too large for {num_bytes} bytes")
        print("error")
