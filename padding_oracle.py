
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes

BLOCK = 16
queries = 0


# Padding oracle
def oracle(key, data):
    global queries
    queries += 1

    iv = data[:BLOCK]
    ciphertext = data[BLOCK:]

    try:
        decrypted = AES.new(key, AES.MODE_CBC, iv).decrypt(ciphertext)
        unpad(decrypted, BLOCK)
        return True
    except ValueError:
        return False