from os import system

_n = [19, 1000, 2000000]
_type = ['enumerate', 'enumerate', 'random']
_count = [1, 1, 10]

for i in range(len(_n)):
	for j in range(_count[i]):
		name = f'data\\subtask{i + 1}_{j + 1}'
		system(f'gen {j + 1} -n {_n[i]} --type={_type[i]} > {name}.in')
		system(f'cd . > {name}.ans')
