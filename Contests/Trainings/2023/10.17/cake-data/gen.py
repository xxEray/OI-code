from os import system

count = 6
lim_n = [10, 50, 300, 3000, 3000, 3000]
lim_V = [
	[3, 5, 10, 100, 10000, 1000000, 100000000],
	[5, 100, 1000, 1000000, 1000000000],
	[5, 10, 300, 1000000000],
	[5, 10, 100, 1000, 3000, 5000],
	[3, 10, 100, 10000, 1000000, 1000000000],
	[3, 5, 10, 20, 50, 100, 1000, 100000, 10000000, 1000000000, 1000000000, 1000000000, 1000000000]
]
lim_distinct = [False, False, False, False, True, False]

for sub in range(0, count):
	for id in range(0, len(lim_V[sub])):
		s = f'gen -n {lim_n[sub]} -V {lim_V[sub][id]}'
		if lim_distinct[sub]:
			s += ' --distinct'
		s += f' > data\\subtask{sub + 1}_{id + 1}.in'
		system(s)
		system(f'std < data\\subtask{sub + 1}_{id + 1}.in > data\\subtask{sub + 1}_{id + 1}.ans')

system('gen -n 3000 -V 1000000000 --sorted > data\\hack_sorted.in')
system('std < data\\hack_sorted.in > data\\hack_sorted.ans')
