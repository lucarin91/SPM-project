import json
import numpy as np
import scipy as sp
import pandas as pd
from pandas.tools.plotting import scatter_matrix
import seaborn as sns
from matplotlib.pylab import *
from mpl_toolkits.axes_grid.inset_locator import inset_axes


plt.rc('text', usetex=True)
plt.rc('font', family='Times-Roman')
sns.set_style(style='white')

# with open('busy_test_ts_ta5000x30_3.json') as data_file:
# 	 data = json.load(data_file)
#
#
#x=[str(val[0]) for val in data]
#li_1=list()
#li_2=list()
#li_3=list()
#li_4=list()
#
#tc1=data[0][1][2]
#print tc1
#for val in data:
#	M1=list()
#	M2=list()
#	M3=list()
#	M4=list()
#
#	flag=0
#	for e in val:
#		if flag==0:
#			flag+=1
#			M1.append(e)
#			M2.append(e)
#			M3.append(e)
#			M4.append(e)
#
#		else:
#			s=tc1/float(e[2])
#			speedup=27/float(e[2])
#
#			M1.append(speedup)
#			M2.append(s)
#			M3.append(e[2])
#			M4.append( s/float(val[0]) )
#
#	li_1.append(M1)
#	li_2.append(M2)
#	li_3.append(M3)
#	li_4.append(M4)
#




#### CLN1
#a=np.array(li_1)
#data=np.transpose(a)
#df = pd.DataFrame(data,columns=x)
#ax=sns.boxplot(data=df,fliersize=0,linewidth=0.75,width=0.5)
#ax.set_yscale('log')
#
#
#ax.yaxis.grid(True)
##ax.set_ylim([0,0.0])
#plt.ylabel(r'$second$',fontsize=20)
#plt.xlabel(r'$treads$',fontsize=20)
#plt.title(r'$Title$',fontsize=25)
#inset_axes = inset_axes(ax, width="60%",height="50%")
#
#sns.boxplot(data=df,fliersize=0,linewidth=0.75,width=0.5,ax=inset_axes)
#inset_axes.set_ylim([0.0001,0.0006])
#inset_axes.set_xlim([2,15])
#inset_axes.yaxis.grid(True)
#inset_axes.set_yscale('log')
#plt.show()


#### CLN2
#a=np.array(li_2)
#data=np.transpose(a)
#
#df = pd.DataFrame(data,columns=x)
#print df
#ax=sns.boxplot(data=df,fliersize=0,linewidth=0.75,width=0.5)
##ax.set_yscale('log')
#
#
#ax.yaxis.grid(True)
#ax.set_ylim([0,3])
#plt.ylabel(r'$second$',fontsize=20)
#plt.xlabel(r'$treads$',fontsize=20)
#plt.title(r'$Title$',fontsize=25)
#inset_axes = inset_axes(ax, width="60%",height="50%")
#
#sns.boxplot(data=df,fliersize=0,linewidth=0.75,width=0.5,ax=inset_axes)
#inset_axes.set_ylim([0.4,1.1])
#inset_axes.set_xlim([3,15])
#inset_axes.yaxis.grid(True)
##inset_axes.set_yscale('log')
#plt.show()
#

'''
with open('busy_test_N_10000x15_(1000,4500,10000,45000,100000).json') as data_file:
	data = json.load(data_file)

data= data[2]
x=[val[0]for val in data]
y=[val[1:]for val in data]

print x
### CLN3
a=np.array(y)
data=np.transpose(a)

df = pd.DataFrame(data,columns=x)
print df
ax=sns.boxplot(data=df,fliersize=0,linewidth=0.75,width=0.5)
#ax.set_yscale('log')


ax.yaxis.grid(True)
#ax.set_ylim([0,40])
plt.ylabel(r'$\textit{second}$',fontsize=20)
plt.xlabel(r'$\textit{Thread}$',fontsize=20)

inset_axes = inset_axes(ax, width="60%",height="60%")

sns.boxplot(data=df,fliersize=0,linewidth=0.75,width=0.5,ax=inset_axes)
inset_axes.set_ylim([1,12])
inset_axes.set_xlim([2,13])
inset_axes.yaxis.grid(True)
#inset_axes.set_yscale('log')
inset_axes.yaxis.set_minor_formatter(FormatStrFormatter("%.2f"))
plt.show()






















####FINAL GOOD

'''
with open('busy_test_N_2000x30_2_(0, 1000, 4500, 10000, 45000)_no234.json') as data_file:
	data = json.load(data_file)



with open('busy_test_mic_multy_5000x30.json') as data_file:
	data_free = json.load(data_file)

#print data

#data.append(data_free)
print len(data)
fig = plt.figure()
dim=['0 sin', '1000 sin', '4500 sin', '10000 sin', '45000 sin','free']
base=[0.015, 2.73133333333333, 14.8964666666667, 41.9095333333333, 164.357866666667,164.357866666667]
marker=['o','v','s','D','8','^']
ax1=fig.add_subplot(2,2,1)
ax2=fig.add_subplot(2,2,2)
ax3=fig.add_subplot(2,2,3)
inset1 = inset_axes(ax1, width="60%",height="60%")
inset2 = inset_axes(ax2,width="45%",height="45%",loc=2)
inset3 = inset_axes(ax3, width="45%",height="45%",loc=2)
i=0

for val in data:
	tc1=val[0][1]
	### eff

	x=[e[0] for e in val]
	y=[e[1] for e in val]
	ax1.plot(x,y,label=str(dim[i]),linewidth=0.85,alpha=0.8,marker=marker[i],markersize=5)


	inset1.plot(x,y,marker=marker[i],linewidth=0.85,alpha=0.8,markersize=3)
	inset1.set_ylim([0,5])
	inset1.set_xlim([5,60])
	inset1.yaxis.grid(True)
	#inset_axes.set_yscale('log')
	#plt.legend(fontsize = 'large',loc='opt')
	ax1.set_xticks(np.arange(min(x)-1, max(x)+1, 5.0))
	ax1.set_xlabel(r'$\textit{Thread}$')
	ax1.set_ylabel(r'$\textit{second}$')
	#ax1.xaxis.grid(True)
	ax1.yaxis.grid(True)
	i+=1





i=0
for val in data:
	tc1=val[0][1]

	### s
	ax2=fig.add_subplot(2,2,2)
	x=[e[0] for e in val]
	y=[tc1/float(e[1]) for e in val]
	ax2.plot(x,y,label=str(dim[i]),linewidth=0.85,alpha=0.8,marker=marker[i],markersize=5)
	x_new = np.linspace(0,60,100)
	ax2.plot(x_new,x_new,label='Opt',linewidth=1.95,alpha=0.2,color='gray',linestyle='dashed')


	inset2.plot(x,y,marker=marker[i],linewidth=0.85,alpha=0.8,markersize=3)
	inset2.plot(x_new,x_new,linewidth=1.95,alpha=0.4,color='gray',linestyle='dashed')

	inset2.set_ylim([0,8])
	inset2.set_xlim([0,15])
	inset2.yaxis.grid(True)
	inset2.yaxis.tick_right()
	#plt.legend(loc='left center', bbox_to_anchor=(0.46, -0.08),fancybox=True, shadow=True, ncol=5)
	ax2.set_xticks(np.arange(min(x)-1, max(x)+1, 5.0))
	ax2.set_xlabel(r'$\textit{Thread}$')
	ax2.set_ylabel(r'$\textit{s}$')
	#ax2.xaxis.grid(True)
	ax2.yaxis.grid(True)
	i+=1




i=0
for val in data:
	tc1=val[0][1]
	### speedup

	x=[e[0] for e in val]
	y=[base[i]/float(e[1]) for e in val]
	ax3.plot(x,y,label=str(dim[i]),linewidth=0.85,alpha=0.8,marker=marker[i],markersize=5)
	x_new = np.linspace(0,60,100)
	ax3.plot(x_new,x_new,linewidth=1.95,alpha=0.2,color='gray',linestyle='dashed')


	inset3.plot(x,y,marker=marker[i],linewidth=0.85,alpha=0.8,markersize=3)
	inset3.plot(x_new,x_new,linewidth=1.95,alpha=0.4,color='gray',linestyle='dashed')

	inset3.set_ylim([0,40])
	inset3.set_xlim([0,60])
	inset3.yaxis.grid(True)
	inset3.yaxis.tick_right()


	#plt.legend(fontsize = 'large',loc='opt')
	ax3.set_xticks(np.arange(min(x)-1, max(x)+1, 5.0))
	ax3.set_xlabel(r'$\textit{Thread}$')
	ax3.set_ylabel(r'$\textit{Speedup}$')
	#ax3.xaxis.grid(True)
	ax3.yaxis.grid(True)
	i+=1






i=0
for val in data:
	tc1=val[0][1]
	### epsilon
	ax4=fig.add_subplot(2,2,4)
	x=[e[0] for e in val]
	y=[tc1/float(e[1]) /float(e[0])  for e in val]
	for z in range(0,len(y)):
		if y[z]>1:
			y[z]=1
	ax4.plot(x,y,label=str(dim[i]),linewidth=0.85,alpha=0.8,marker=marker[i],markersize=5)
	x_new = np.linspace(1,60,100)
	y_new=[1/float(val) for val in x_new]

	plt.xticks(np.arange(min(x)-1, max(x)+1, 5.0))
	plt.xlabel(r'$\textit{Thread}$')
	plt.ylabel(r'$\epsilon$',fontsize=20)
	#ax4.xaxis.grid(True)
	ax4.yaxis.grid(True)
	ax4.set_ylim([0,1.1])
	i+=1
ax4.plot(x_new,y_new,label='ideal',linewidth=1.95,alpha=0.5,color='gray',linestyle='dashed')

plt.subplots_adjust(left=0.05, bottom=0.05, right=0.99, top=0.95, wspace=0.18, hspace=0.17)
plt.legend( loc = 'lower center', bbox_to_anchor = (0.512, 0.4),bbox_transform = plt.gcf().transFigure )
plt.show()



x=[1000, 5000, 10000, 50000, 100000]
label=range(0,90,5)
label[0]=label[0]+1
color=sns.color_palette("Set2", 13)
fig = plt.figure()
matrix=list()
for val in data:

	row=list()
	for i in range(0,13):
		row.append(val[i][1])
	matrix.append(row)

a=np.array(matrix)
matrix=np.transpose(a)
matrix=matrix.tolist()
i=0
for r in matrix:
	ax=fig.add_subplot(1,1,1)
	#ax.set_yscale('log')
	ax.plot(x,r,color=color[i],label=str(label[i]))
	plt.legend(fontsize = 'large',loc='opt')
	i+=1
plt.show()
