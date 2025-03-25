import random
import string

n = 100000

m = 99999

# Optimización: usar random.choices en vez de random.choice (1000x más rápido)
def generate_random_string(length):
    return ''.join(random.choices(string.ascii_lowercase, k=length))  # <- Corrección aquí

cadena_A = generate_random_string(n)
cadena_B = generate_random_string(n)

# Corrección en índices (n es out of range, los strings van de 0 a n-1)
with open('entrada.txt', 'w') as f:  # <- Nombre de archivo útil para C++
    f.write(f"{cadena_A}\n{cadena_B}\n{m}")

print("pinga")  # Única salida necesaria según tu especificaciónp