from os import system

_n = [1, 2, 8, 8, 20, 50, 100, 10000, 100000, 1000000]
_normal = [5, 5, 0, 5, 3, 3, 3, 2, 2, 2]
_random = [2, 2, 0, 2, 1, 1, 1, 1, 1, 1, 1]
_special = [0, 0, 3, 0, 0, 0, 0, 0, 0, 0]

for i in range(len(_n)):
	cn = 0
	for j in range(_random[i]):
		cn += 1
		name = f'data\\subtask{i + 1}_{cn}'
		system(f'gen {j} -n {_n[i]} --random > {name}.in')
		system(f'std < {name}.in > {name}.ans')
	for j in range(_normal[i]):
		cn += 1
		name = f'data\\subtask{i + 1}_{cn}'
		system(f'gen {j} -n {_n[i]} > {name}.in')
		system(f'std < {name}.in > {name}.ans')
	for j in range(_special[i]):
		cn += 1
		name = f'data\\subtask{i + 1}_{cn}'
		system(f'gen {j} -n {_n[i]} --special > {name}.in')
		system(f'std < {name}.in > {name}.ans')
