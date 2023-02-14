def palindrome_permutation(string: str) -> bool:
    dic = dict()
    for c in string:
        if c == ' ': continue
        c = c.lower()
        if dic.get(c): dic[c] += 1
        else: dic[c] = 1

    frequency_of_odd = 0
    for v in dic.values():
        if v % 2: frequency_of_odd += 1
        if frequency_of_odd > 1: return False
        
    return True
    
assert palindrome_permutation("Tact Coa") == True
assert palindrome_permutation("civic") == True
assert palindrome_permutation("livci") == False
assert palindrome_permutation("Step on no pets") == True

