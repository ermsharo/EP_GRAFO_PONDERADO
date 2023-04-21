from Graph import Graph
"""
from Queue import Queue

def bfs_traversal_helper( g, source, visited ):
    result = "" 
    queue = Queue()
    queue.enqueue( source )
    visited[ source ] = True

    while( queue.is_empty() is False ):
        current_node = queue.dequeue()
        result += str( current_node )
        temp = g.array[ current_node ].head
        print( current_node )
        while( temp is not None ):
            if ( visited[ temp0.data ] == False ):
                visited[ temp.data ] = True 
                queue.enqueue( temp.data )
            temp = temp.next_element
    return result, visited

def bfs_traversal( g, source ):
    result = ""
    num_of_vertices = g.vertices
    if ( num_of_vertices == 0 ):
        return result
    visited = [] 
    for i in range( num_of_vertices ):
        visited.append( False )
    result, visited = bfs_traversal_helper( g, source, visited )
    for i in range( num_of_vertices ):
        if ( visited[ i ] == False ):
            result_new, visited = bfs_traversal_helper( g, i, visited )
            result += result_new
    return result
"""
def dfs_traversal_helper( g, source, visited, stack):
    result = ""
    # print(source)
    if ( source is not None ):
        visited[source] = True 
        result += str(source)
        neighbour = g.array[source].get_head()
        while ( neighbour is not None ):
            if ( visited[neighbour.data] == False ):
                result_new, visited, stack = dfs_traversal_helper(g, neighbour.data, visited, stack)
                result += result_new 
            neighbour = neighbour.next_element
        stack.append(source)
        return result, visited , stack
    return result, visited, stack

def dfs_traversal( g, source ):
    result = ""
    stack = []
    num_of_vertices = g.vertices
    if( num_of_vertices == 0):
        return result
    visited = []
    for i in range(num_of_vertices):
        visited.append(False)

    result, visited, stack = dfs_traversal_helper(g, source, visited, stack)
    
    for i in range(num_of_vertices):
        if (visited[i] == False):
            result_new, visited, stack = dfs_traversal_helper(g, i, visited, stack)
            result += result_new

    return result, stack

def dfs_traversal_cluster( g, source, visited):
    result = ""
    stack = []
    num_of_vertices = g.vertices
    if( num_of_vertices == 0):
        return result

    result, visited, stack = dfs_traversal_helper(g, source, visited, stack)

    return result, stack, visited

def invertEdges( g, source ):
    graphReversed = Graph(g.get_number_of_vertices())
    array_vertices = g.get_array_of_vertices()

    for current in range(g.get_number_of_vertices()):
        temp = array_vertices[ current ].get_head()
        while ( temp is not None ):
            graphReversed.add_edge( temp.data, current )
            temp = temp.next_element
    
    return graphReversed

def clusterizeStronglyConnectedComponents( g, stack ):

    stronglyConnectedComponents = []

    visited = []
    for i in range(g.get_number_of_vertices()):
        visited.append(False)

    while len(stack) != 0:
        source = stack.pop()
        if ( visited[source] == False ):
            result, stackReturned, visited = dfs_traversal_cluster(g, source, visited )
            stronglyConnectedComponents.append(result)

    return stronglyConnectedComponents

def getStronglyConnectedComponentsKosarujoAproach( g, source ):
    stack = []
    result = ""
    result, stack = dfs_traversal(g, source )
    graphReversed = invertEdges(g, source)
    stronglyConnectedComponents = clusterizeStronglyConnectedComponents(graphReversed, stack)
    print(stronglyConnectedComponents)



def testA():
    #Grafo curto
    g =Graph(6)
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 2)
    g.add_edge(1, 3)
    g.add_edge(2, 1)
    g.add_edge(3, 5)
    g.add_edge(3, 4)
    g.add_edge(4, 3)
    return g



def testB():

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

    return g

def testC():

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

    return g


#GRAFO ENUCIADO EP ex - 1
def exemplo1():

    g = Graph(8)

    g.add_edge(0, 1)
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

    return g


#GRAFO ENUCIADO EP ex - 2

def exemplo2():

    g = Graph(9)

    g.add_edge(0, 1)
    g.add_edge(1, 2)
    g.add_edge(1, 4)
    g.add_edge(2, 8)
    g.add_edge(3, 4)
    g.add_edge(6, 2)
    g.add_edge(6, 7)
    g.add_edge(7, 8)

    return g

#g = exemplo1()
#g = exemplo2()
#g = testA()
#g = testB()
#g = testC()
g.print_graph()
getStronglyConnectedComponentsKosarujoAproach(g,0)
