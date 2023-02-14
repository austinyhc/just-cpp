def check_permutation(a: str, b: str):
    if len(a) != len(b): return False

    dic = dict()
    for c in a:
        found = dic.get(c)
        if found: dic[c] += 1
        else: dic[c] = 1

    for c in b:
        found = dic.get(c)
        if not found: return False
        dic[c] -= 1
        if dic[c] < 0: return False
        
    return True


assert check_permutation("aloha", "ahola") == True
assert check_permutation("aloha", "alo")   == False
assert check_permutation("apple", "accle") == False
assert check_permutation("apple", "elppa") == True
assert check_permutation("zero matrix", "matrix zero") == True
assert check_permutation("", " ") == False
assert check_permutation(" ", " ") == True
