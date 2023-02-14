def is_unique(string: str):
    lut = dict()
    for c in string:
        found = lut.get(c)
        if found: return False
        else: lut[c] = 1
    return True
    
assert is_unique("aloha") == False
assert is_unique("aloh") == True
assert is_unique("Fran") == True
