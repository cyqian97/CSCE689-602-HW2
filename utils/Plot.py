import numpy as np
import matplotlib.pyplot as plt


plt.rcParams.update({'font.size': 12})

### Function Value Comparisons
fnames = ["results/Corel16k001_filtered_results.txt",
          "results/Corel16k002_filtered_results.txt",
          "results/Corel16k003_filtered_results.txt",
          "results/Corel16k004_filtered_results.txt",
          "results/Corel16k005_filtered_results.txt",
          "results/Corel16k006_filtered_results.txt",
          "results/Corel16k007_filtered_results.txt",
          "results/Corel16k008_filtered_results.txt",
          "results/Corel16k009_filtered_results.txt",]
fig, axs = plt.subplots(3, 3, figsize=(10, 8))

for i, fname in enumerate(fnames):
    data = np.loadtxt(fname, dtype=int, delimiter=',')
    l1, = axs[int(i/3), i % 3].plot(data[:, 0], data[:, 1],
                                    's-', label="Standard Greedy")
    l2, = axs[int(i/3), i % 3].plot(data[:, 0], data[:, 3],
                                    'v-', label="Streaming Greedy")
    l3, = axs[int(i/3), i % 3].plot(data[:, 0], data[:, 2],
                                    'o-', label="Seservoir Sampling")
    # axs[int(i/3),i%3].legend()
    axs[int(i/3), i % 3].set_title(fname.split('/')[1].split('_')[0])
    if(int(i/3)==2):
        axs[int(i/3), i % 3].set_xlabel('k')
    if( i % 3==0):
        axs[int(i/3), i % 3].set_ylabel('Function Value')


plt.figlegend(handles=[l1, l2, l3],  loc="lower center",
              bbox_to_anchor=(0.5, -0.002), ncols=3)
fig.tight_layout()
plt.subplots_adjust(bottom=0.1)
plt.savefig('images/Fval Comparisons.pdf')
plt.show()

### Number of Evaluations Comparison
fname = "results/delicious_filtered-k_results.txt"
data = np.loadtxt(fname, dtype=int, delimiter=',')
fig, axs = plt.subplots(1, 2, figsize=(8, 4))
axs[0].plot(data[:,0],data[:, 4],'s-', label="Standard Greedy")
axs[0].plot(data[:,0],data[:,  5],'v-', label="Streaming Greedy")
axs[0].set_xlabel("k")
axs[0].set_ylabel("# Function Evaluations")

l1, =axs[1].plot(data[:12, 1],data[:12, 4],'s-', label="Standard Greedy")
l2, =axs[1].plot(data[:16, 3],data[:16, 5],'v-', label="Streaming Greedy")
axs[1].set_xlabel("Function Value")
axs[1].set_ylabel("# Function Evaluations")
plt.figlegend(handles=[l1, l2],  loc="lower center",
              bbox_to_anchor=(0.5, -0.017), ncols=2)
fig.tight_layout()
plt.subplots_adjust(bottom=0.2)
plt.savefig('images/Neval Comparison.pdf')
plt.show()


### Effect of Epsilon
fname = "results/delicious_filtered-e_results.txt"
data = np.loadtxt(fname, delimiter=',')
fig, axs = plt.subplots(1, 2, figsize=(8, 4))
axs[0].plot(data[:, 0], data[:, 1], '-', label="Standard Greedy")
axs[0].plot(data[:, 0], data[:, 2], 'v-', label="Streaming Greedy")
axs[0].set_xlabel("$\epsilon$")
axs[0].set_ylabel("Function Value")

l1, = axs[1].plot(data[:, 0], data[:, 3], '-', label="Standard Greedy")
l2, = axs[1].plot(data[:, 0], data[:, 4], 'v-', label="Streaming Greedy")
axs[1].set_xlabel("$\epsilon$")
axs[1].set_ylabel("# Function Evaluations")

plt.figlegend(handles=[l1, l2],  loc="lower center",
              bbox_to_anchor=(0.5, -0.017), ncols=2)
fig.tight_layout()
plt.subplots_adjust(bottom=0.2)
plt.savefig('images/Eps Effect.pdf')
plt.show()
