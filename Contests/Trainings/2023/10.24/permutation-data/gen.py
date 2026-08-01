from os import system

_n = [10, 18, 100, 5000, 100000]
_w = [
	[10, 9, 8, 7, 6, 5, 4, 3, 2, 1],
	[18, 16, 13, 11, 9, 7, 5, 4, 3, 2, 1],
	[100, 80, 50, 30, 20, 10, 8, 5, 4, 3, 2, 1],
	[5000, 2000, 1000, 500, 300, 100, 50, 30, 10, 5, 3, 2, 1],
	[100000, 50000, 30000, 1000, 500, 80, 20, 8, 4, 3, 2, 1],
]

for i in range(len(_n)):
	for j in range(len(_w[i])):
		name = f'data\\subtask{i + 1}_{j + 1}'
		system(f'gen {j + 1} -n {_n[i]} --upper={_w[i][j]} > {name}.in')
		system(f'std < {name}.in > {name}.ans')

system('copy /Y hacks\\* data\\ > nul')
