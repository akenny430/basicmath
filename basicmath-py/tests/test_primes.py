from pathlib import Path

import basicmath as bm

MAX_POWERS: int = 4  # TODO: can go up to 12
NUMBERS_TO_CHECK: list[int] = [int(10**k) for k in range(1, MAX_POWERS)]
MAX_NUMBERS: int = NUMBERS_TO_CHECK[-1]

# reading results of prime count
PRIME_RESULTS: dict[int, int] = {}
with open(
    file=Path(__file__).parent / "data" / "prime_counts_results.csv",
    mode="r",
    encoding="utf8",
) as rf:
    rf.readline()
    for rl in rf.readlines():
        k, c = rl.split(",")
        PRIME_RESULTS[10 ** int(k)] = int(c)


def test_prime_count() -> None:
    """
    Checking results of Prime Counting Function.
    """
    test_results: dict[int, int] = {}

    prime_count: int = 1
    for n in range(2, MAX_NUMBERS + 1):
        # if prime, update count
        if bm.check_prime(n=n):
            prime_count += 1
        # if number is power of 10, record the count
        if n in NUMBERS_TO_CHECK:
            test_results[n] = prime_count

    # checking that results match up
    for n, c in test_results.items():
        assert c == PRIME_RESULTS.get(n)
        # print(f"{n}: {c} vs. {PRIME_RESULTS.get(n)}")


def test_large_primes() -> None:
    """
    Testing prime count for large primes.

    Useful URL:
    https://markknowsnothing.weebly.com/primes.html
    """
    assert bm.check_prime(1_000_082_257)
    # assert bm.check_prime(1000000071143)


if __name__ == "__main__":
    test_prime_count()
