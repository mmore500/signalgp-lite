import sys
import pandas as pd

expected = int(sys.argv[1])
filename = sys.argv[2]

df = pd.read_csv(filename)

max_fitness = df["max_fitness"].max()

if max_fitness >= expected:
    sys.exit(0)

sys.exit(max_fitness)
