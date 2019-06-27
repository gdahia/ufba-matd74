import sys
import pandas as pd

# read table from melo et al.'s
melo = pd.read_csv(sys.argv[1], sep=' ', index_col=0)

# read our results
ours = pd.read_csv(sys.argv[2], sep=' ', index_col=0)

# merged table
merged = pd.merge(melo, ours, how='inner', on=['instance'])

# print results
print(sum(merged['branches'] - merged['branches_melo']) / len(merged))
print(sum(merged['branches'] - merged['branches_carrabs']) / len(merged))
