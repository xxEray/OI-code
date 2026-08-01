from os import system

lim_n = [1000000000000, 1000000, 1000000000000]
lim_T = [1000, 100000, 100000]
lim_V = [
	[1, 2, 5, 10, 20, 50, 100, 1000, 10000, 1000000],
	[1, 10, 1000, 10000, 100000, 1000000, 10000000, 100000000, 10000000000],
	[1, 5, 10, 20, 40, 60, 80, 80, 100, 1000, 100000, 100000000, 100000000000, 1000000000000]
]

for i in range(len(lim_n)):
	for j in range(len(lim_V[i])):
		name = f'data\\subtask{i + 1}_{j + 1}'
		system(f'gen -n {lim_n[i]} -T {lim_T[i]} -V {lim_V[i][j]} > {name}.in')
		system(f'std < {name}.in > {name}.ans')
