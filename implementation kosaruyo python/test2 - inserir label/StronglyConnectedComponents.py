from Graph import Graph

class StronglyConnectedComponents:
    def __init__(self,g,mode):
        self.mode = mode

        if mode == 1 :
            self.getStronglyConnectedComponentsKosarujoAproachA(g,0)
        elif mode == 2 :
            self.getStronglyConnectedComponentsKosarujoAproachB(g,0)
        else:
            print("mode not found")
        
        print(self.mode)

    def getStronglyConnectedComponentsKosarujoAproachA( self, g, source ):
        stack = []
        result = ""
        # 1. Calcular A^T
        graphReversed,  stronglyConnectedComponentsByLoop = self.invertEdges(g, source)
        # 2. Chamar DFS (V, A^T) para calcular f[u]
        result, stack = self.dfs_traversal(graphReversed, source )
        invertedOrder = stack[::-1]
        # 3. Chamar DFS (V, A) considerando no laço principal
        stronglyConnectedComponentsExtra = self.clusterizeStronglyConnectedComponentsA(g, invertedOrder)

        stronglyConnectedComponents = stronglyConnectedComponentsByLoop + stronglyConnectedComponentsExtra

        scc_list_conv = self.convert_list_numbers_to_chars( g, stronglyConnectedComponents )
        
        #print(scc_list_conv);

        self.isGraphScc(scc_list_conv, g) 
        self.getNumberOfComponents(scc_list_conv)

        self.create_scc_graphs(g,stronglyConnectedComponents)
        

    
    def clusterizeStronglyConnectedComponentsA(self, g, invertedOrder):

        stronglyConnectedComponents = []

        visited = []
        for i in range(g.get_number_of_vertices()):
            visited.append(False)

        for source in invertedOrder:
            if ( visited[source] == False ):
                # 4. Devolva os vértices de cada árvore resultante da linha 3 como uma componente fortemente conectada separada
                result, stackReturned, visited = self.dfs_traversal_cluster(g, source, visited )
    
                stronglyConnectedComponents.append(result)

        return stronglyConnectedComponents



    # Implementation of Kosarujo Algorithm
    def getStronglyConnectedComponentsKosarujoAproachB( self, g, source ):
        stack = []
        result = ""
        result, stack = self.dfs_traversal(g, source )
        stronglyConnectedComponentsByLoop = []
        graphReversed,  stronglyConnectedComponentsByLoop = self.invertEdges(g, source)
        stronglyConnectedComponentsExtra = self.clusterizeStronglyConnectedComponents(graphReversed, stack)
        
        stronglyConnectedComponents = stronglyConnectedComponentsByLoop + stronglyConnectedComponentsExtra
        #print("stronglyConnectedComponents")
        #print(stronglyConnectedComponents);
        
        scc_list_conv = self.convert_list_numbers_to_chars( g, stronglyConnectedComponents )
        
        #print(scc_list_conv);

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
        # print(scc_list)
        # print(scc_list_conv_stringfied)
        scc_graph.set_labels(scc_list_conv_stringfied)

        indexes_of_nodes_to_labels_of_scc = self.set_components_label_to_original_graph_nodes(g, scc_graph, scc_list_conv, scc_list, scc_list_conv_stringfied)
        # print("indexes_of_nodes_to_labels_of_scc")
        # print(indexes_of_nodes_to_labels_of_scc)
        scc_graph = self.add_vertices_on_scc_graph(g, scc_graph, scc_list_conv, scc_list ,indexes_of_nodes_to_labels_of_scc)
        sorted_nodes = scc_graph.topological_sort()
        print(sorted_nodes)
        scc_graph.print_graph()
        
    def stringfy_components(self, scc_list_conv):
        scc_list_conv_stringfied = []
        component_stringfied = ""
        for i in range(len(scc_list_conv)):
            for j in range(len(scc_list_conv[i])):
                component_stringfied += str(scc_list_conv[i][j])
            scc_list_conv_stringfied.append(component_stringfied)
            component_stringfied = ""

        #print("Stringfied components : ",scc_list_conv_stringfied);
        return scc_list_conv_stringfied
    
    # CONVERTED
    def dfs_traversal_helper( self, g, source, visited, stack):
        #print(source)
        resultList = []
        if ( source is not None ):
            visited[source] = True 
            # print("inserting : ",source)
            # print("result list before: ",resultList)
            resultList.append(str(source)) # insertion of node
            # print("result list after: ",resultList)
            neighbour = g.array[source].get_head()
            while ( neighbour is not None ):
                if ( visited[neighbour.data] == False ):
                    result_new, visited, stack = self.dfs_traversal_helper(g, neighbour.data, visited, stack)
                    resultList = result_new + resultList # invert order
                    # print("result_new : ",result_new)
                    # print("resultList : ",resultList)
                neighbour = neighbour.next_element
            stack.append(source)
            return resultList, visited , stack
        return resultList, visited, stack

    # CONVERTED
    def dfs_traversal( self, g, source ):
        result = []
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
                result = result + result_new

        return result, stack

    # CONVERTED
    def dfs_traversal_cluster( self, g, source, visited):
        result = []
        stack = []
        num_of_vertices = g.vertices
        if( num_of_vertices == 0):
            return result

        result, visited, stack = self.dfs_traversal_helper(g, source, visited, stack)

        return result, stack, visited
    """  
    def invertEdges( self, g, source ):
        graphReversed = Graph(g.get_number_of_vertices())
        array_vertices = g.get_array_of_vertices()

        for current in range(g.get_number_of_vertices()):
            temp = array_vertices[ current ].get_head()
            while ( temp is not None ):
                graphReversed.add_edge_by_index( temp.data, current )
                temp = temp.next_element
        
        graphReversed.print_graph()
        return graphReversed
  """
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

        #graphReversed.print_graph()
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
        
        #print(g.labels_to_index)
        # traverse to the exdisting labels 
        for label, idx in g.labels_to_index.items():

            orig_label = g.get_label_by_index(idx)

            # traverse throught the stronlgy connected components list 
            for i in range(len(scc_list_orig)):
              
                component_orig = scc_list_orig[i]
                component_orig_char = scc_list_conv_stringfied[i]

                for j in range(len(component_orig)):
                    node_orig = scc_list_orig[i][j]
                    
                    # when the linked list node is equal to the component 
                    # set the respective component to the vector 
                    if str(idx) == str(node_orig):
                        indexes_of_nodes_to_labels_of_scc_T[orig_label] = component_orig_char

        #print("indexes_of_nodes_to_labels_of_scc_T")
        #print(indexes_of_nodes_to_labels_of_scc_T)

        

        return indexes_of_nodes_to_labels_of_scc_T

    
    # Uses the original graph to make all the connection that the SCC have
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