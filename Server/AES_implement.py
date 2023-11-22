from typing import Union

from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.Random import get_random_bytes
from Crypto.PublicKey import RSA
from Crypto.Util import Padding

from checkDB import get_public_key, get_aes_key

from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad
from Crypto.Util.strxor import strxor_c


def generate_aes_key() -> bytes:
    return get_random_bytes(16)


def rsa_encrypt(public_key, plaintext: bytes):
    """
        Encrypt plaintext using RSA public key.

        Parameters:
        - public_key (RSA key): RSA public key.
        - plaintext (bytes): Data to be encrypted.

        Returns:
        - bytes: Encrypted ciphertext.
        """

    cipher = PKCS1_OAEP.new(public_key)
    ciphertext = cipher.encrypt(plaintext)
    return ciphertext


def rsa_decrypt(public_key, ciphertext):
    """
        Decrypt ciphertext using RSA private key.

        Parameters:
        - public_key (RSA key): RSA public key.
        - ciphertext (bytes): Encrypted data.

        Returns:
        - bytes: Decrypted plaintext.
        """

    cipher = PKCS1_OAEP.new(public_key)
    plaintext = cipher.decrypt(ciphertext)
    return plaintext


def encrypt_AES_key(clientName):
    public_key = get_public_key(clientName)
    aes_key = get_aes_key(clientName)
    encrypted_aes_key = rsa_encrypt(public_key, aes_key)
    print("AES Key encrypted successfully")
    return encrypted_aes_key


def decrypt_aes_value(key, encrypted_value):

    # Initialize AES cipher in CBC mode with an all-zeros IV
    cipher = AES.new(key, AES.MODE_CBC, iv=bytes(16))

    # Decrypt the ciphertext
    decrypted_data = Padding.unpad(cipher.decrypt(encrypted_value), AES.block_size)

    return decrypted_data
