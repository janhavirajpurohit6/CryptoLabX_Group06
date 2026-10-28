import os
import subprocess
from pathlib import Path

Path("data").mkdir(exist_ok=True)

with open("data/linux_urandom.bin", "wb") as f:
    f.write(open("/dev/urandom", "rb").read(1048576))

subprocess.run([
    "openssl", "rand", "-out",
    "data/openssl_rand.bin", "1048576"
], check=True)

print("Generated Linux and OpenSSL data.")
