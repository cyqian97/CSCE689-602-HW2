import numpy as np
import matplotlib.pyplot as plt


fnames = ["results/Corel16k001_filtered_results.txt",
          "results/Corel16k002_filtered_results.txt",
          "results/Corel16k003_filtered_results.txt",
          "results/Corel16k004_filtered_results.txt",
          "results/Corel16k005_filtered_results.txt",
          "results/Corel16k006_filtered_results.txt",
          "results/Corel16k007_filtered_results.txt",
          "results/Corel16k008_filtered_results.txt",
          "results/Corel16k009_filtered_results.txt",]


fig, axs = plt.subplots(3,3)

for i, fname in enumerate(fnames):
    data = np.loadtxt(fname,dtype=int,delimiter=',')
    axs[int(i/3),i%3].plot(data[:,0],data[:,1],'.-',label="Standard Greedy")
    axs[int(i/3),i%3].plot(data[:,0],data[:,3],'v-',label="Streaming Greedy")
    axs[int(i/3),i%3].plot(data[:,0],data[:,2],'o-',label="Seservoir Sampling")
    # axs[int(i/3),i%3].legend()
    axs[int(i/3),i%3].set_title(fname.split('/')[1].split('_')[0])
    
# fig.tight_layout()
plt.show()
