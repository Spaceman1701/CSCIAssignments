from math import ceil, sqrt
from time import time


def find_factor_slow(n, start_time, timeout):  # simple trial division
    n_sqrt = int(ceil(sqrt(n)))
    for i in range(2, n_sqrt + 1):
        if n % i == 0:
            return i
        if time() - start_time > timeout:
            break
    return False


def factorize_slow(num, max_time):
    start_time = time()
    first_factor = find_factor_slow(num, start_time, max_time)

    if not first_factor:  # if timeout
        return False

    return first_factor, num // first_factor, time() - start_time


