from os import system

_n = [60, 60, 15, 60]
_m = [1, 15, 15, 15]
_k = [1000000000, 1000000000, 2, 1000000000]
_count = [3, 6, 6, 15]

for i in range(len(_n)):
	for j in range(_count[i]):
		name = f'data\\subtask{i + 1}_{j + 1}'
		system(f'gen {j + 1} -n {_n[i]} -m {_m[i]} -K {_k[i]} > {name}.in')
		system(f'std < {name}.in > {name}.ans')
