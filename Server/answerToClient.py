import json


def answer_to_client(code, payload_size, payload):
    code_byte = value_to_bytes(code, 2)
    payload_size_byte = value_to_bytes(payload_size, 4)
    if isinstance(payload, dict):
        payload = json.dumps(payload).encode('utf-8')

    return b''.join([
        value_to_bytes(3, 1),
        code_byte,
        payload_size_byte,
        payload
    ])


def value_to_bytes(number, num_bytes):
    try:
        # Convert the integer to bytes
        byte_representation = number.to_bytes(num_bytes, 'little')

        return byte_representation
    except OverflowError:
        raise ValueError(f"Integer {number} is too large for {num_bytes} bytes")
        print("error")
