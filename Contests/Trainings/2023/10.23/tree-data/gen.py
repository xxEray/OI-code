from cyaron import *

std_path = 'std.exe'


subtask = 0
cn = 0
def gen(n, graph):
	global cn
	cn += 1
	io = IO(file_prefix=f'data/subtask{subtask}_', data_id=cn, output_suffix='.ans')
	io.input_writeln(n)
	io.input_writeln(graph.to_str(output=Edge.unweighted_edge, shuffle=True))
	io.output_gen(std_path)
	io.close()

subtask = 1
cn = 0
gen(10, Graph.tree(10))
gen(10, Graph.binary_tree(10, 0.2, 0.5))
gen(10, Graph.chain(10))

subtask = 2
cn = 0
gen(4000, Graph.tree(4000))
gen(4000, Graph.tree(4000, 0.1, 0.2))
gen(4000, Graph.chain(4000))
gen(4000, Graph.binary_tree(4000))
gen(4000, Graph.flower(4000))

subtask = 3
cn = 0
gen(500000, Graph.chain(500000))
gen(500000, Graph.chain(500000))
gen(500000, Graph.chain(500000))

subtask = 4
cn = 0
gen(500000, Graph.tree(500000))
gen(500000, Graph.tree(500000))
gen(500000, Graph.tree(500000))

subtask = 5
cn = 0
gen(500000, Graph.binary_tree(500000))
gen(500000, Graph.binary_tree(500000, 0.2, 0.8))
gen(500000, Graph.binary_tree(500000, 0.01, 0.99))
gen(500000, Graph.flower(500000))
gen(500000, Graph.chain(500000))
gen(500000, Graph.tree(500000, 0.3, 0.7))
gen(500000, Graph.tree(500000, 0.4, 0.5))
gen(500000, Graph.tree(500000, 0.8, 0.1))
gen(500000, Graph.tree(500000, 0.6, 0.3))
