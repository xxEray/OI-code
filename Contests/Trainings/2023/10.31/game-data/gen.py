from os import system

_conf = [
	{
		"C": 10,
		"n": 12,
		"L": 0,
		"S": 500,
		"T": 500
	},
	{
		"C": -1,
		"n": 500,
		"L": 1000000,
		"S": 1,
		"T": 500
	},
	{
		"C": -1,
		"n": 500,
		"L": 1000000,
		"S": 500,
		"T": 1
	},
	{
		"C": -1,
		"n": 500,
		"L": 1000000,
		"S": 500,
		"T": 500
	},
]

for i in range(len(_conf)):
	for j in range(10):
		name = f'data\\subtask{i + 1}_{j + 1}'
		system(f'gen {j + 1} -C {_conf[i]["C"]} -n {_conf[i]["n"]} -L {_conf[i]["L"]} -S {_conf[i]["S"]} -T {_conf[i]["T"]} > {name}.in')
		system(f'std < {name}.in > {name}.ans')
