import hashlib


def text_to_hex_id(name):
    # Ensure the input is encoded as bytes
    text_bytes = name.encode('utf-8')

    # Calculate the SHA-256 hash
    sha256_hash = hashlib.sha256(text_bytes).digest()

    # Take the first 16 bytes of the hash and convert to hex
    hex_id = sha256_hash[:16].hex()

    return hex_id


# Example usage
text_input = "ido"
result_hex_id = text_to_hex_id(text_input)
print(result_hex_id)
