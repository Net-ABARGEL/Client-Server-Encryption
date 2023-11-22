import hashlib

# create a UUID from a text to 16 byte number hex base 64
def text_to_hex_id(name):
    # Ensure the input is encoded as bytes
    text_bytes = name.encode('utf-8')

    # Calculate the SHA-256 hash
    sha256_hash = hashlib.sha256(text_bytes).digest()

    # Take the first 16 bytes of the hash and convert to hex
    hex_id = sha256_hash[:16]    #.hex()
    binary_string = ''.join(format(byte, '08b') for byte in hex_id)

    return binary_string

