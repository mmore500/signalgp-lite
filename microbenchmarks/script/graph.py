import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from keyname import keyname as kn
from slugify import slugify
import subprocess
import sys
from iterpop import iterpop as ip

def facet(df):
    df['Benchmark'] = df['Library']
    df['Num Agents'] = df['num agents']

    return sns.FacetGrid(
        df,
        col='Benchmark',
        margin_titles="true",
        sharey=False,
        col_wrap=3,
    )


def draw_plots(measurement, df):

    facet(df).map(
        sns.barplot,
        'Num Agents',
        measurement,
        'Implementation',
        hue_order=sorted(df['Implementation'].unique()),
        palette=sns.color_palette(),
    ).add_legend()

    plt.savefig(
      kn.pack({
        'measurement' : slugify(measurement),
        'ext' : '.png',
      }),
      transparent=True,
      dpi=300,
    )

    plt.savefig(
      kn.pack({
        'measurement' : slugify(measurement),
        'ext' : '.pdf',
      }),
      transparent=True,
      dpi=300,
    )

    plt.clf()

    for showfliers in True, False:
        facet(df).map(
            sns.boxplot,
            'Num Agents',
            measurement,
            'Implementation',
            hue_order=sorted(df['Implementation'].unique()),
            palette=sns.color_palette(),
            showfliers=showfliers,
        ).add_legend()

        plt.savefig(
          kn.pack({
            'fliers' : showfliers,
            'measurement' : slugify(measurement),
            'ext' : '.png',
          }),
          transparent=True,
          dpi=300,
        )

        plt.savefig(
          kn.pack({
            'fliers' : showfliers,
            'measurement' : slugify(measurement),
            'ext' : '.pdf',
          }),
          transparent=True,
          dpi=300,
        )

        plt.clf()

__, filename = sys.argv

nproc = int(subprocess.check_output(['nproc']))

df = pd.read_csv(filename)

for k, v in kn.unpack(filename).items():
    df[k] = v

df = df.astype({ 'num agents' : int })

for measurement in [
        'Wall Nanoseconds',
        'CPU Nanoseconds',
    ]:
        draw_plots(measurement, df)
