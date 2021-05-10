import sys
import pandas as pd

expected = int(sys.argv[1])

df = pd.read_csv("fitness.csv")

max_fitness = df["max_fitness"].max()

if max_fitness >= expected:
    sys.exit(0)

sys.exit(max_fitness)
