from ._basicmath import miller_rabin


def check_prime(n: int) -> bool:
    """
    Checks if number is prime or not.
    """
    # any number <= 2 is not prime
    if n <= 2:
        return False

    # checking using Miller-Rabin
    return miller_rabin(n, 100)
