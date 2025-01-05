from pathlib import Path

import basicmath as bm

MAX_POWERS: int = 8  # TODO: can go up to 12
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
        if bm.check_prime(n=n, num_checks=5):
            prime_count += 1
        # if number is power of 10, record the count
        if n in NUMBERS_TO_CHECK:
            test_results[n] = prime_count

    # checking that results match up
    for n, c in test_results.items():
        assert c == PRIME_RESULTS.get(n)
        print(f"{n}: {c} vs. {PRIME_RESULTS.get(n)}")


def test_large_primes() -> None:
    """
    Testing prime count for large primes.

    Useful URL:
    https://markknowsnothing.weebly.com/primes.html
    """
    # billions
    assert bm.check_prime(1_000_082_257, num_checks=3)
    assert bm.check_prime(314_159_265_359, num_checks=3)

    # trillions
    assert bm.check_prime(1_000_000_071_143, num_checks=3)
    assert bm.check_prime(1_000_000_026_959, num_checks=3)
    assert bm.check_prime(1_000_000_099_643, num_checks=3)

    # (almost) quadrillions
    assert bm.check_prime(900_000_000_014_261, num_checks=3)
    assert bm.check_prime(950_000_000_072_087, num_checks=3)
    assert bm.check_prime(999_999_999_999_989, num_checks=3)

    # values that should fail
    assert not bm.check_prime(101_010_101_010, num_checks=3)
    assert not bm.check_prime(999_999_999_999_998, num_checks=3)


if __name__ == "__main__":
    test_prime_count()
