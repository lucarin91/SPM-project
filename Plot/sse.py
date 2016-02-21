import json
import numpy as np
import scipy as sp
import pandas as pd
from pandas.tools.plotting import scatter_matrix
import seaborn as sns
from matplotlib.pylab import *
from mpl_toolkits.axes_grid.inset_locator import inset_axes


def plot(seq, data):
    plt.rc('text', usetex=True)
    plt.rc('font', family='Times-Roman')
    sns.set_style(style='white')

    fig = plt.figure(num=None,
                     figsize=(10, 8),
                     dpi=100,
                     facecolor='w',
                     edgecolor='k')
    dim = ['0 sin', '1000 sin', '4500 sin', '10000 sin', '45000 sin']
    # base = [0.015, 2.73133333333333, 14.8964666666667,
    #        41.9095333333333, 164.357866666667, 164.357866666667]
    marker = ['o', 'v', 's', 'D', '8', '^']
    ax1 = fig.add_subplot(2, 2, 1)
    ax2 = fig.add_subplot(2, 2, 2)
    ax3 = fig.add_subplot(2, 2, 3)
    inset1 = inset_axes(ax1, width="60%", height="60%")
    inset2 = inset_axes(ax2, width="45%", height="45%", loc=2)
    inset3 = inset_axes(ax3, width="45%", height="45%", loc=2)

    '''
    Completion Time
    '''
    i = 0
    for val in data:
        tc1 = val[0][1]
        x = [e[0] for e in val]
        y = [e[1] for e in val]
        ax1.plot(x, y, label=str(dim[i]), linewidth=0.85,
                 alpha=0.8, marker=marker[i], markersize=5)

        inset1.plot(x, y, marker=marker[i],
                    linewidth=0.85, alpha=0.8, markersize=3)
        inset1.set_ylim([0, 5])
        inset1.set_xlim([5, 60])
        inset1.yaxis.grid(True)
        # inset_axes.set_yscale('log')
        # plt.legend(fontsize = 'large',loc='opt')
        ax1.set_xticks(np.arange(min(x) - 1, max(x) + 1, 5.0))
        ax1.set_xlabel(r'$\textit{Thread}$')
        ax1.set_ylabel(r'$\textit{Seconds}$')
        # ax1.xaxis.grid(True)
        ax1.yaxis.grid(True)
        i += 1

    '''
    Scalability PloSt
    '''
    i = 0
    for val in data:
        tc1 = val[0][1]
        ax2 = fig.add_subplot(2, 2, 2)
        x = [e[0] for e in val]
        y = [tc1 / float(e[1]) for e in val]
        ax2.plot(x, y, label=str(dim[i]), linewidth=0.85,
                 alpha=0.8, marker=marker[i], markersize=5)
        x_new = np.linspace(0, 60, 100)
        ax2.plot(x_new, x_new, label='Opt', linewidth=1.95,
                 alpha=0.2, color='gray', linestyle='dashed')

        inset2.plot(x, y, marker=marker[i],
                    linewidth=0.85, alpha=0.8, markersize=3)
        inset2.plot(x_new, x_new, linewidth=1.95, alpha=0.4,
                    color='gray', linestyle='dashed')

        inset2.set_ylim([0, 8])
        inset2.set_xlim([0, 15])
        inset2.yaxis.grid(True)
        inset2.yaxis.tick_right()
        # plt.legend(loc='left center', bbox_to_anchor=(0.46, -0.08),
        #            fancybox=True,
        #            shadow=True, ncol=5)
        ax2.set_xticks(np.arange(min(x) - 1, max(x) + 1, 5.0))
        ax2.set_xlabel(r'$\textit{Thread}$')
        ax2.set_ylabel(r'$\textit{Scalability}$')
        # ax2.xaxis.grid(True)
        ax2.yaxis.grid(True)
        i += 1

    '''
    Speed-up Plot
    '''
    i = 0
    for val in data:
        tc1 = val[0][1]
        x = [e[0] for e in val]
        y = [seq[i] / float(e[1]) for e in val]
        ax3.plot(x, y, label=str(dim[i]), linewidth=0.85,
                 alpha=0.8, marker=marker[i], markersize=5)
        x_new = np.linspace(0, 60, 100)
        ax3.plot(x_new, x_new, linewidth=1.95, alpha=0.2,
                 color='gray', linestyle='dashed')

        inset3.plot(x, y, marker=marker[i],
                    linewidth=0.85, alpha=0.8, markersize=3)
        inset3.plot(x_new, x_new, linewidth=1.95, alpha=0.4,
                    color='gray', linestyle='dashed')
        inset3.set_ylim([0, 40])
        inset3.set_xlim([0, 60])
        inset3.yaxis.grid(True)
        inset3.yaxis.tick_right()
        # plt.legend(fontsize = 'large',loc='opt')
        ax3.set_xticks(np.arange(min(x) - 1, max(x) + 1, 5.0))
        ax3.set_xlabel(r'$\textit{Thread}$')
        ax3.set_ylabel(r'$\textit{Speedup}$')
        # ax3.xaxis.grid(True)
        ax3.yaxis.grid(True)
        i += 1

    '''
    Efficienty Plot
    '''
    i = 0
    for val in data:
        tc1 = val[0][1]
        ax4 = fig.add_subplot(2, 2, 4)
        x = [e[0] for e in val]
        y = [tc1 / float(e[1]) / float(e[0]) for e in val]
        for z in range(0, len(y)):
            if y[z] > 1:
                y[z] = 1
        ax4.plot(x, y, label=str(dim[i]), linewidth=0.85,
                 alpha=0.8, marker=marker[i], markersize=5)
        x_new = np.linspace(1, 60, 100)
        y_new = [1 / float(val) for val in x_new]

        plt.xticks(np.arange(min(x) - 1, max(x) + 1, 5.0))
        plt.xlabel(r'$\textit{Thread}$')
        plt.ylabel(r'$\textit{Efficienty}$')
        # ax4.xaxis.grid(True)
        ax4.yaxis.grid(True)
        ax4.set_ylim([0, 1.1])
        i += 1

    ax4.plot(x_new, y_new, label='ideal', linewidth=1.95,
             alpha=0.5, color='gray', linestyle='dashed')
    plt.subplots_adjust(left=0.05, bottom=0.05, right=0.99,
                        top=0.98, wspace=0.25, hspace=0.25)
    plt.legend(loc='lower center', bbox_to_anchor=(0.52, 0.43),
               bbox_transform=plt.gcf().transFigure)

    plt.draw()
    return plt
