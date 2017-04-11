from fractions import gcd
from random import randint
from time import time


def find_factor_fast(n, sequence, start_time, timeout):  # implements the Pollard Rho algorithm
    x, c = randint(1, n - 1), randint(1, n - 1)
    y = x
    g = 1
    while g == 1:
        x = sequence(x, n)  # sequence is passed as a parameter to improve flexibility
        y = sequence(sequence(y, n), n)
        g = gcd(abs(x - y), n)
        if time() - start_time > timeout:
            return False
    if g == n:
        return False  # failed
    return g


def factorize_fast(num, max_time):
    """
    :param num: number to be factored
    :param max_time: time until timeout in seconds
    :return: tuple in the format of (factor_one, factor_two, run_time) or False if the number could not be factored
    """
    first_factor = False
    start_time = time()
    while not first_factor:
        a = randint(1, num - 1)
        if not a % num == 0 and not a % num == -2 % num:  # to ensure that cycling actually occurs
            first_factor = find_factor_fast(num, lambda x, n: ((x * x) + a) % n, start_time, max_time)
        if time() - start_time > max_time:
            return False

    second_factor = num // first_factor
    return first_factor, second_factor, time() - start_time