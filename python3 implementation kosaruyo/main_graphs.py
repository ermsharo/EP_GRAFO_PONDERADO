from Graph import Graph
from Node import Node
from Graph import LinkedList
from StronglyConnectedComponents import StronglyConnectedComponents

def testA():
    g =Graph(6)
    g.add_edge('0', '1')
    g.add_edge('0', '2')
    g.add_edge('1', '2')
    g.add_edge('1', '3')
    g.add_edge('2', '1')
    g.add_edge('3', '5')
    g.add_edge('3', '4')
    g.add_edge('4', '3')

    g.print_graph()
    scc = StronglyConnectedComponents()
    scc.getStronglyConnectedComponentsKosarujoAproach(g,0)

def testB():

    g =Graph(8)
    g.add_edge('0', '6')
    g.add_edge('0', '5')
    g.add_edge('1', '2')
    g.add_edge('1', '0')
    g.add_edge('2', '4')
    g.add_edge('2', '6')
    g.add_edge('3', '7')
    g.add_edge('3', '2')
    g.add_edge('3', '4')
    g.add_edge('7', '6')
    g.add_edge('6', '5')
    g.add_edge('5', '1')
    g.add_edge('4', '6')

    g.print_graph()
    scc = StronglyConnectedComponents()
    scc.getStronglyConnectedComponentsKosarujoAproach(g,0)

def testC():

    g = Graph(11)

    g.add_edge('0', '1') 
    g.add_edge('1', '2') 
    g.add_edge('2', '0') 
    g.add_edge('1', '3') 
    g.add_edge('3', '4') 
    g.add_edge('4', '5') 
    g.add_edge('5', '3') 
    g.add_edge('6', '5') 
    g.add_edge('6', '7') 
    g.add_edge('7', '8') 
    g.add_edge('8', '9') 
    g.add_edge('9', '10') 
    g.add_edge('9', '6') 

    g.print_graph()
    scc = StronglyConnectedComponents()
    scc.getStronglyConnectedComponentsKosarujoAproach(g,0)



#GRAFO ENUCIADO EP ex - 1
def testD():
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



#GRAFO ENUCIADO EP ex - 1 - Com labels maiores
def testE():
    g = Graph(8)

    g.set_labels(['apoli','brexit','cuba','dina','eritr','finla','guan','hondur'])
    g.add_edge('apoli', 'brexit')
    g.add_edge('brexit', 'eritr')
    g.add_edge('brexit', 'finla')
    g.add_edge('brexit', 'cuba')
    g.add_edge('cuba', 'guan')
    g.add_edge('cuba', 'dina')
    g.add_edge('dina', 'hondur')
    g.add_edge('dina', 'cuba')
    g.add_edge('eritr', 'apoli')
    g.add_edge('eritr', 'finla')
    g.add_edge('finla', 'guan')
    g.add_edge('guan', 'finla')
    g.add_edge('guan', 'hondur')

    g.print_graph()
    scc = StronglyConnectedComponents()
    scc.getStronglyConnectedComponentsKosarujoAproach(g,0)

#GRAFO ENUCIADO EP exemplo - 2
def testF():
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

    scc = StronglyConnectedComponents()

    scc.getStronglyConnectedComponentsKosarujoAproach(g,0)


#GRAFO ENUCIADO EP exemplo - 2 - com nomes substituidos por letras 
def textG():
    g = Graph(9)

    g.set_labels(['a','b','c','d','e','f','g','h','i'])

    g.add_edge('a', 'b')
    g.add_edge('a', 'h')
    g.add_edge('b', 'h')
    g.add_edge('b', 'c')
    g.add_edge('c', 'f')
    g.add_edge('d', 'e')
    g.add_edge('d', 'c')
    g.add_edge('e', 'f')
    g.add_edge('g', 'h')

    g.print_graph()

    scc = StronglyConnectedComponents()
    scc.getStronglyConnectedComponentsKosarujoAproach(g,0)

#testE()
testD()
#textG()

