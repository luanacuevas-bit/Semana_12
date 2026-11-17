# Verificación Python
def djb2(s: str) -> int:
    h = 5381
    for c in s:
        h = ((h << 5) + h) + ord(c)  # h*33+ord(c)
    return h

print(djb2('SIS') % 31)
print(djb2('AVL') % 31)
