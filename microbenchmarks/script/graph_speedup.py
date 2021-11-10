import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from keyname import keyname as kn
from slugify import slugify
import subprocess
import sys
from iterpop import iterpop as ip
import numpy as np

__, filename = sys.argv

nproc = int(subprocess.check_output(['nproc']))

df = pd.read_csv(filename)

for k, v in kn.unpack(filename).items():
    df[k] = v

df = df.astype({ 'num agents' : int })

df['Benchmark'] = df['Library']
df['Num Agents'] = df['num agents']

df = df.groupby([
    'Benchmark',
    'Implementation',
    'Num Agents',
]).mean().reset_index()

vanilla = df[df['Implementation'] == 'vanilla']
lite = df[df['Implementation'] == 'lite']

ratio = pd.DataFrame()
ratio['Benchmark'] = vanilla['Benchmark']
ratio['Num Agents'] = vanilla['Num Agents']

ratio['Wall Speedup'] = (
    np.array( vanilla['Wall Nanoseconds'] )
    / np.array( lite['Wall Nanoseconds'] )
)

ratio['CPU Speedup'] = (
    np.array( vanilla['CPU Nanoseconds'] )
    / np.array( lite['CPU Nanoseconds'] )
)

ax = sns.barplot(
    data=ratio,
    x='Num Agents',
    y='Wall Speedup',
    hue='Benchmark',
)

ax.set_axisbelow(True)
ax.yaxis.grid(color='gray', linestyle='dashed')

plt.legend(bbox_to_anchor=(1.02, 1), loc=2, borderaxespad=0.)


plt.savefig(
  kn.pack({
    'measurement' : slugify('Wall Time Speedup'),
    'ext' : '.png',
  }),
  transparent=True,
  dpi=300,
  bbox_inches='tight'
)

plt.savefig(
  kn.pack({
    'measurement' : slugify('Wall Time Speedup'),
    'ext' : '.pdf',
  }),
  transparent=True,
  dpi=300,
  bbox_inches='tight'
)

plt.clf()

sns.barplot(
    data=ratio,
    x='Num Agents',
    y='CPU Speedup',
    hue='Benchmark',
)

plt.savefig(
  kn.pack({
    'measurement' : slugify('CPU Time Speedup'),
    'ext' : '.png',
  }),
  transparent=True,
  dpi=300,
)

plt.savefig(
  kn.pack({
    'measurement' : slugify('CPU Time Speedup'),
    'ext' : '.pdf',
  }),
  transparent=True,
  dpi=300,
)

plt.clf()
