def string_compression(string: str):

    length = len(string)
    if length == 0: return string

    i,j = 0,0
    count = 1
    curr = string[i]
    i += 1
    results = ""

    while i < length :
        if string[i] == curr:
            count += 1
        else:
            results += curr
            results += str(count)
            if len(results) >= length: return string
            curr = string[i]
            count = 1

        i += 1

    results += curr
    results += str(count)
    if len(results) >= length: return string

    return results

assert string_compression("aloha") == "aloha"
assert string_compression("aabbcc") == "aabbcc"
assert string_compression("aaabbbbbbcc") == "a3b6c2"
assert string_compression("") == ""
assert string_compression("aa") == "aa"
assert string_compression("a") == "a"
