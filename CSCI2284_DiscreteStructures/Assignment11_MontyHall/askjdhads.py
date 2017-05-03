def recurse(n):
    if n is 0:
        return 1
    return 2 * recurse(n - 1) + n + 1

def ethan(n):
    return -n - (3/2) + (5/2) * 3**n

def matt(n):
    return -(1/2) * n - 1 + 2 * 2**n

print(recurse(5), ethan(5), matt(5))
