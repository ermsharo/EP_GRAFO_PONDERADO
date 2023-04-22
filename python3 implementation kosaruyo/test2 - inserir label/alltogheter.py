class Node:
    def __init__( self, data ):
        self.data = data
        self.visited = False
        self.next_element = None


class LinkedList:
    def __init__( self ):
        self.head = None 

    def get_head( self ):
        return self.head 

    def is_empty( self ):
        return self.get_head() is None

    def insert_at_head( self, data ):
        newNode = Node( data )
        newNode.next_element = self.head
        self.head = newNode
        return True
    
    #rewrite on notes
    def insert_at_tail( self, data ):
        if ( self.is_empty() ):
            self.insert_at_head( data )
            return True
        newNode = Node( data )
        temp = self.get_head()
        while ( temp.next_element is not None ):
            temp = temp.next_element
        temp.next_element = newNode
        return True
    
    #rewrite on notes
    def print_list( self ):
        if( self.is_empty() ):
            print ("List is empty")

        #print("Printing list : ")
        temp = self.get_head()
        while ( temp is not None ):
            print( temp.data,end=" -> ")
            temp = temp.next_element
        print("None")
    
    def delete_at_head( self ):
        if( self.is_empty() ):
            return False
        deleted = self.head.data
        self.head = self.head.next_element
        return deleted
    
    #rewrite
    def delete( self, data ):
        if ( self.head.data == data ):
            return self.delete_at_head()

        previous = None
        current = self.get_head()
        while( current.next_element is not None ):
            if( current.data == data ):
                previous.next_element = current.next_element
                current.data = None
                return data
            previous = current
            current = current.next_element
        return False
    
    def pop(self):
        if ( self.head.data == None ):
            print("Nothing to pop")
            return 
        if self.head.next_element == None :
            print("Pop First : "+str(self.head.data))
            self.delete_at_head() 
            return
        tempRef = self.get_head()

        previous = None
        current = self.get_head()

        while current.next_element is not None:
            previous = current
            current = current.next_element
        print("Poping : "+str(previous.next_element.data))
        previous.next_element = None
        self.head = tempRef

    def reverse(self):
        if (self.is_empty()):
            return False
        previous = None 
        current = self.head
        next = None 

        while( current is not None ):
            next = current.next_element
            current.next_element = previous
            previous = current
            current = next

            self.head = previous
        return True
    def getNode(self, val):
        if ( self.head.data == None ):
            return False
        temp = self.get_head()
        while ( temp is not None ):
            if temp.data == val :
                return temp.visited
            temp = temp.next_element
        return False

    def setNode(self, val, booleanValue):
        if ( self.head.data == None ):
            return False
        temp = self.get_head()
        while ( temp is not None ):
            if temp.data == val :
                temp.visited = booleanValue
            temp = temp.next_element


class Graph:
    def __init__( self, vertices ):
        self.array = []
        self.vertices = vertices 
        self.labels_to_index = {}
        self.index_to_label = {}
        for i in range( self.vertices ):
            temp = LinkedList()
            self.array.append( temp )

    def add_edge( self, source, destination ):
        #destination_index = self.get_index_by_label(destination)

        if self.node_contains(source, destination):
            return 

        if source in self.labels_to_index and destination in self.labels_to_index :
            source_index = self.get_index_by_label(source)
            destination_index = self.get_index_by_label(destination)
            self.array[ source_index ].insert_at_head( destination_index )

    def add_edge_by_index( self, source, destination ):

        
        
        if ( source < self.vertices and destination < self.vertices  ) and not self.node_contains(source, destination):
            self.array[ source ].insert_at_head( destination )

    def node_contains(self, source, destination):
    
        source_index = self.get_index_by_label(source)
        dest_index = self.get_index_by_label(destination)

        temp = self.get_array_of_vertices()[int(source_index)].get_head()

        while temp is not None:
            if temp.data == dest_index :
                return True
            temp = temp.next_element

        return False

    def print_graph( self ):
        for label, idx in self.labels_to_index.items():
            print( label, ": ", end="")
            temp = self.array[idx].get_head()
            while temp is not None:
                print( self.index_to_label[temp.data], "; ", end="")
                temp = temp.next_element
            print()

    def get_number_of_vertices( self ):
        return self.vertices
    
    def get_array_of_vertices( self ):
        return self.array
    
    def set_index_to_label( self, label, index):
        self.labels_to_index[label] = index
        self.labels_to_index[index] = label

    def get_index_by_label( self, label ):
        if label in self.labels_to_index:
            return self.labels_to_index[label]
        return False
    
    def set_labels(self, labels):
        self.labels_to_index = {label: i for i, label in enumerate(labels)}
        self.index_to_label = {i: label for i, label in enumerate(labels)}
    
    def get_label_by_index(self, index):
        return self.index_to_label[index]
    
    def get_both_maps(self):
        print()
        print("labels_to_index")
        print(self.labels_to_index)
        print()
        print("index_to_label")
        print(self.index_to_label)
        print()
    

class StronglyConnectedComponents:

    # Implementation of Kosarujo Algorithm
    def getStronglyConnectedComponentsKosarujoAproach( self, g, source ):
        stack = []
        result = ""
        result, stack = self.dfs_traversal(g, source )
        stronglyConnectedComponentsByLoop = []
        graphReversed,  stronglyConnectedComponentsByLoop = self.invertEdges(g, source)
        stronglyConnectedComponentsExtra = self.clusterizeStronglyConnectedComponents(graphReversed, stack)
        
        stronglyConnectedComponents = stronglyConnectedComponentsByLoop + stronglyConnectedComponentsExtra
        scc_list_conv = self.convert_list_numbers_to_chars( g, stronglyConnectedComponents )
        print()
        self.isGraphScc(scc_list_conv, g) 
        self.getNumberOfComponents(scc_list_conv)
        self.create_scc_graphs(g,stronglyConnectedComponents)

    def isGraphScc(self, scc_list_conv, g):
        if len(scc_list_conv) == 1 :
            print("Sim")
        else:
            print("Não")
    
    def getNumberOfComponents(self, scc_list_conv):
        print(len(scc_list_conv))

    # Create the Strongly Connected Components Graph
    def create_scc_graphs( self,g, scc_list):

        scc_list_conv = self.convert_list_numbers_to_chars( g, scc_list )


        scc_graph = Graph(len(scc_list_conv))
        scc_list_conv_stringfied = self.stringfy_components(scc_list_conv)

        scc_graph.set_labels(scc_list_conv_stringfied)
        
        indexes_of_nodes_to_labels_of_scc = self.set_components_label_to_original_graph_nodes(g, scc_graph, scc_list_conv, scc_list, scc_list_conv_stringfied)
        
        scc_graph = self.add_vertices_on_scc_graph(g, scc_graph, scc_list_conv, scc_list ,indexes_of_nodes_to_labels_of_scc)
        """"""
        scc_graph.print_graph()
        
    def stringfy_components(self, scc_list_conv):
        scc_list_conv_stringfied = []
        component_stringfied = ""
        for i in range(len(scc_list_conv)):
            for j in range(len(scc_list_conv[i])):
                component_stringfied += str(scc_list_conv[i][j])
            scc_list_conv_stringfied.append(component_stringfied)
            component_stringfied = ""
        return scc_list_conv_stringfied
        
    def dfs_traversal_helper( self, g, source, visited, stack):
        resultList = []
        if ( source is not None ):
            visited[source] = True 
            resultList.append(str(source))
            neighbour = g.array[source].get_head()
            while ( neighbour is not None ):
                if ( visited[neighbour.data] == False ):
                    result_new, visited, stack = self.dfs_traversal_helper(g, neighbour.data, visited, stack)
                    resultList = resultList + result_new 
                neighbour = neighbour.next_element
            stack.append(source)
            return resultList, visited , stack
        return resultList, visited, stack

    def dfs_traversal( self, g, source ):
        result = ""
        stack = []
        num_of_vertices = g.vertices
        if( num_of_vertices == 0):
            return result
        visited = []
        for i in range(num_of_vertices):
            visited.append(False)

        result, visited, stack = self.dfs_traversal_helper(g, source, visited, stack)
        
        for i in range(num_of_vertices):
            if (visited[i] == False):
                result_new, visited, stack = self.dfs_traversal_helper(g, i, visited, stack)
                result += result_new

        return result, stack

    def dfs_traversal_cluster( self, g, source, visited):
        result = []
        stack = []
        num_of_vertices = g.vertices
        if( num_of_vertices == 0):
            return result

        result, visited, stack = self.dfs_traversal_helper(g, source, visited, stack)

        return result, stack, visited

    def invertEdges(self, g, source):
        graphReversed = Graph(g.get_number_of_vertices())
        array_vertices = g.get_array_of_vertices()

        stronglyConnectedComponents = []

        for current in range(g.get_number_of_vertices()):
            temp = array_vertices[current].get_head()

            while temp is not None:
                if current != temp.data:
                    graphReversed.add_edge_by_index(temp.data, current)
                temp = temp.next_element

        graphReversed.print_graph()
        return graphReversed, stronglyConnectedComponents


    # Used to let the Strongly connected components toghether in the respective
    # components 
    def clusterizeStronglyConnectedComponents( self, g, stack ):

        stronglyConnectedComponents = []

        visited = []
        for i in range(g.get_number_of_vertices()):
            visited.append(False)

        while len(stack) != 0:
            source = stack.pop()
            if ( visited[source] == False ):
                result, stackReturned, visited = self.dfs_traversal_cluster(g, source, visited )
    
                stronglyConnectedComponents.append(result)

        return stronglyConnectedComponents


    # Covert list from number to letters 
    def convert_list_numbers_to_chars( self, g, scc_list):
        scc_list_conv = []
        comp = []
        for i in range(len(scc_list)):
            for j in range(len(scc_list[i])):
                coverted_element = g.get_label_by_index(int(scc_list[i][j]))
                comp.append(coverted_element)
            scc_list_conv.append(comp)
            comp = []
        
        return scc_list_conv

    # Set components labels on nodes 
    def set_components_label_to_original_graph_nodes( self, g, scc_graph, scc_list_conv, scc_list_orig, scc_list_conv_stringfied):

        indexes_of_nodes_to_labels_of_scc_T ={}
        
      
        # percorre por todos labels existentes
        for label, idx in g.labels_to_index.items():

            # pega o primeiro e acha a lista ligada dele pelo array
            orig_label = g.get_label_by_index(idx)



            # para cada no percorre todos os nos detre  
            # a listas dos componentes fortemente conexos
            for i in range(len(scc_list_orig)):
              
                component_orig = scc_list_orig[i]
                component_orig_char = scc_list_conv_stringfied[i]

                for j in range(len(component_orig)):
                    node_orig = scc_list_orig[i][j]
                    
                    # quando o no atual da lista ligada for igual a um no do 
                    # componente, setamos o componente de origem daquele no   
                    # label
                    if str(idx) == str(node_orig):
                        indexes_of_nodes_to_labels_of_scc_T[orig_label] = component_orig_char

        return indexes_of_nodes_to_labels_of_scc_T

    
    # Uses the original grapho to make all the connection that the SCC have
    def add_vertices_on_scc_graph(self, g, scc_graph, scc_list_label, scc_list_index,indexes_of_nodes_to_labels_of_scc):

        for i in range(len(scc_list_index)):   
            component_orig = scc_list_index[i]
            for j in range(len(component_orig)):
                node_orig = scc_list_index[i][j]
                node_orig_label = g.get_label_by_index(int(node_orig))
                node_dest = g.get_array_of_vertices()[int(node_orig)].get_head()
                while node_dest is not None:
                    
                    label_orig = indexes_of_nodes_to_labels_of_scc[node_orig_label]
                    label_dest = indexes_of_nodes_to_labels_of_scc[g.get_label_by_index(int(node_dest.data))]
                    if label_orig != label_dest:
                        scc_graph.add_edge(label_orig, label_dest)
                    node_dest = node_dest.next_element

        return scc_graph