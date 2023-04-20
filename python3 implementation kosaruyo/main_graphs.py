from Graph import Graph
from Node import Node
from Graph import LinkedList
from StronglyConnectedComponents import StronglyConnectedComponents


"""
Grafo curto
"""

"""
g =Graph(6)
g.add_edge(0, 1)
g.add_edge(0, 2)
g.add_edge(1, 2)
g.add_edge(1, 3)
g.add_edge(2, 1)
g.add_edge(3, 5)
g.add_edge(3, 4)
g.add_edge(4, 3)



Grafo Longo

g =Graph(8)
g.add_edge(0, 6)
g.add_edge(0, 5)
g.add_edge(1, 2)
g.add_edge(1, 0)
g.add_edge(2, 4)
g.add_edge(2, 6)
g.add_edge(3, 7)
g.add_edge(3, 2)
g.add_edge(3, 4)
g.add_edge(7, 6)
g.add_edge(6, 5)
g.add_edge(5, 1)
g.add_edge(4, 6)
"""

"""

g = Graph(9)

g.add_edge(0, 1)
g.add_edge(1, 2)
g.add_edge(2, 3)
g.add_edge(3, 0)
g.add_edge(2, 4)
g.add_edge(2, 3)
g.add_edge(4, 5)
g.add_edge(5, 6)
g.add_edge(6, 4)
g.add_edge(7, 6)
g.add_edge(7, 8)

"""

"""

g = Graph(11)

g.add_edge(0, 1) 
g.add_edge(1, 2) 
g.add_edge(2, 0) 
g.add_edge(1, 3) 
g.add_edge(3, 4) 
g.add_edge(4, 5) 
g.add_edge(5, 3) 
g.add_edge(6, 5) 
g.add_edge(6, 7) 
g.add_edge(7, 8) 
g.add_edge(8, 9) 
g.add_edge(9, 10) 
g.add_edge(9, 6) 

getStronglyConnectedComponentsKosarujoAproach(g,0)
"""

"""

GRAFO ENUCIADO EP ex - 1
"""
g = Graph(8)

g.set_labels(['a','b','c','d','e','f','g','h'])
g.add_edge('a', 'b')
g.add_edge('b', 'e')
g.add_edge('b', 'f')
g.add_edge('b', 'c')
g.add_edge('c', 'g')
g.add_edge('c', 'd')
g.add_edge('d', 'h')
g.add_edge('d', 'c')
g.add_edge('e', 'a')
g.add_edge('e', 'f')
g.add_edge('f', 'g')
g.add_edge('g', 'f')
g.add_edge('g', 'h')

g.print_graph()

scc = StronglyConnectedComponents()


scc.getStronglyConnectedComponentsKosarujoAproach(g,0)


"""
g.set_index_to_label('A',0)

g.add_edge('A', 1)
g.add_edge(1, 2)
g.add_edge(1, 4)
g.add_edge(1, 5)
g.add_edge(2, 3)
g.add_edge(2, 6)
g.add_edge(3, 7)
g.add_edge(3, 2)
g.add_edge(4, 0)
g.add_edge(4, 5)
g.add_edge(5, 6)
g.add_edge(6, 5)
g.add_edge(6, 7)

"""



"""

GRAFO ENUCIADO EP ex - 2


g = Graph(9)

g.set_labels(['undershorts','socks','pants','shoes','belt','shirt','tie','jacket','watch'])

g.add_edge('undershorts', 'pants')
g.add_edge('undershorts', 'shoes')
g.add_edge('pants', 'shoes')
g.add_edge('pants', 'belt')
g.add_edge('shirt', 'belt')
g.add_edge('shirt', 'tie')
g.add_edge('tie', 'jacket')
g.add_edge('belt', 'jacket')
g.add_edge('socks', 'shoes')

g.print_graph()

scc = StronglyConnectedComponents()

scc.getStronglyConnectedComponentsKosarujoAproach(g,0)

"""