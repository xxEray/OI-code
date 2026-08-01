from os import system

lim_n = [8, 10, 20, 100, 500, 1000, 1000]
special = [False, False, False, False, False, True, False]
case_count = [20, 10, 10, 5, 5, 5, 10]

for i in range(len(lim_n)):
	for j in range(case_count[i]):
		name = f'data\\subtask{i + 1}_{j + 1}'
		system(f'gen {j} -n {lim_n[i]}' + (' --special' if special else '') + f' > {name}.in')
		system(f'cd . > {name}.ans')
