
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



# Padding oracle attack: recover one block
def attack_block(previous, target, check):
    intermediate = bytearray(BLOCK)
    plaintext = bytearray(BLOCK)

    for pos in range(BLOCK - 1, -1, -1):
        padding = BLOCK - pos
        modified = bytearray(previous)

        for j in range(pos + 1, BLOCK):
            modified[j] = intermediate[j] ^ padding

        for guess in range(256):
            modified[pos] = guess ^ padding

            if check(bytes(modified) + target):
                intermediate[pos] = guess
                plaintext[pos] = guess ^ previous[pos]
                break
        else:
            raise RuntimeError("Could not recover plaintext")

    return bytes(plaintext)


def attack(iv, ciphertext, check):
    plaintext = b""
    previous = iv

    for i in range(0, len(ciphertext), BLOCK):
        target = ciphertext[i:i + BLOCK]
        plaintext += attack_block(previous, target, check)
        previous = target

    return unpad(plaintext, BLOCK)

def main():
    # Sample encryption setup
    key = get_random_bytes(16)
    iv = get_random_bytes(16)
    original = b"Hello World! This is my assignment."

    ciphertext = AES.new(key, AES.MODE_CBC, iv).encrypt(
        pad(original, BLOCK)
    )

    # The attack queries the oracle without receiving the key.
    def check(data):
        return oracle(key, data)

    recovered = attack(iv, ciphertext, check)

    print("Original plaintext:", original.decode())
    print("Recovered plaintext:", recovered.decode())
    print("Oracle queries:", queries)
    print("Attack successful:", recovered == original)


if __name__ == "__main__":
    main()


