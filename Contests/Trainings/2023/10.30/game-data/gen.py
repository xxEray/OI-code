from os import system

_n = [1000, 100000, 1000000, 10000000, 20000000]
_count = [10, 10, 10, 5, 5]

for i in range(len(_n)):
	for j in range(_count[i]):
		name = f'data\\subtask{i + 1}_{j + 1}'
		system(f'gen {j + 1} -n {_n[i]} > {name}.in')
		system(f'std < {name}.in > {name}.ans')
