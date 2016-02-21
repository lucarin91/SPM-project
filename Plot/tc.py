import numpy as np
import scipy as sp
import pandas as pd
from pandas.tools.plotting import scatter_matrix
import seaborn as sns
from matplotlib.pylab import *
from mpl_toolkits.axes_grid.inset_locator import inset_axes


def plot(data):
    plt.rc('text', usetex=True)
    plt.rc('font', family='Times-Roman')
    plt.figure(num=None,
               figsize=(10, 8),
               dpi=80,
               facecolor='w',
               edgecolor='k')
    sns.set_style(style='white')

    data = data[3]
    x = [val[0] for val in data]
    y = [val[1:] for val in data]

    a = np.array(y)
    data = np.transpose(a)

    df = pd.DataFrame(data, columns=x)
    # print df
    ax = sns.boxplot(data=df, fliersize=0, linewidth=0.75, width=0.5)
    # ax.set_yscale('log')

    ax.yaxis.grid(True)
    # ax.set_ylim([0,40])
    plt.ylabel(r'$\textit{second}$', fontsize=20)
    plt.xlabel(r'$\textit{Thread}$', fontsize=20)

    axes = inset_axes(ax, width="60%", height="60%")

    sns.boxplot(data=df, fliersize=0, linewidth=0.75, width=0.5, ax=axes)
    axes.set_ylim([1, 12])
    axes.set_xlim([2, 13])
    axes.yaxis.grid(True)
    # axes.set_yscale('log')
    axes.yaxis.set_minor_formatter(FormatStrFormatter("%.2f"))
    plt.draw()
    return plt
