from os import system

_n = [3, 4, 5, 6, 7, 100, 500, 1000, 1500, 2000, 2500]
_V = [1, 1, 1, 1, 1, 1, 10000000, 10000000, 10000000, 10000000, 10000000]
_count = [1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5]

for i in range(len(_n)):
	for j in range(_count[i]):
		name = f'data\\subtask{i + 1}_{j + 1}'
		system(f'gen {j + 1} -n {_n[i]} -V {_V[i]} > {name}.in')
		system(f'std < {name}.in > {name}.ans')
