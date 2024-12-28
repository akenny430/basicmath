import plotnine as pn
import polars as pl

import basicmath as bm

# checking primes for each
N_PRIMES: int = 100
prime_count: int = 0
prime_data: list[tuple[int, int]] = []
for n in range(1, N_PRIMES + 1):
    if bm.check_prime(n):
        prime_count += 1
    prime_data.append((n, prime_count))

# making dataframe
prime_df: pl.DataFrame = pl.DataFrame(
    data=prime_data,
    schema={"N": pl.Int64, "PrimeCount": pl.Int64},
    orient="row",
)

# making plot
prime_plot: pn.ggplot = (
    pn.ggplot(
        data=prime_df,
    )
    + pn.geom_point(
        mapping=pn.aes(
            x="N",
            y="PrimeCount",
        ),
        color="black",
    )
    + pn.labs(
        title="Prime counting function",
        x="$N$",
        y="$\\pi(N)$",
    )
    + pn.theme_bw()
)
prime_plot.save(
    filename="./prime_plot.svg",
    width=12,
    height=6,
    verbose=False,
)
