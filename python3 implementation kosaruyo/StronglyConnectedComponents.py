from Graph import Graph

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
        if len(scc_list_conv) != g.get_number_of_vertices() :
            print("Não")
        else:
            print("Sim")
    
    def getNumberOfComponents(self, scc_list_conv):
        print(len(scc_list_conv))

    # Create the Strongly Connected Components Graph
    def create_scc_graphs( self,g, scc_list):

        scc_list_conv = self.convert_list_numbers_to_chars( g, scc_list )

        print(scc_list)

        scc_graph = Graph(len(scc_list_conv))
        scc_graph.set_labels(scc_list_conv)

        indexes_of_nodes_to_labels_of_scc = self.set_components_label_to_original_graph_nodes(g, scc_graph, scc_list_conv, scc_list)

        scc_graph = self.add_vertices_on_scc_graph(g, scc_graph, scc_list_conv, scc_list ,indexes_of_nodes_to_labels_of_scc)
        
        scc_graph.print_graph()
    
    def dfs_traversal_helper( self, g, source, visited, stack):
        result = ""
        if ( source is not None ):
            visited[source] = True 
            result += str(source)
            neighbour = g.array[source].get_head()
            while ( neighbour is not None ):
                if ( visited[neighbour.data] == False ):
                    result_new, visited, stack = self.dfs_traversal_helper(g, neighbour.data, visited, stack)
                    result += result_new 
                neighbour = neighbour.next_element
            stack.append(source)
            return result, visited , stack
        return result, visited, stack

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
        result = ""
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

            if temp != None and current == temp.data:
                stronglyConnectedComponents.append([current])
            while temp is not None:
                if current != temp.data:
                    graphReversed.add_edge_by_index(temp.data, current)
                temp = temp.next_element

        for component in stronglyConnectedComponents:
            graphReversed.add_vertex()

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
        comp = ""
        for i in range(len(scc_list)):
            for j in range(len(scc_list[i])):
                coverted_element = g.get_label_by_index(int(scc_list[i][j]))
                comp += coverted_element
            scc_list_conv.append(comp)
            comp = ""
        
        return scc_list_conv

    # Set components labels on nodes 
    def set_components_label_to_original_graph_nodes( self, g, scc_graph, scc_list_conv, scc_list_orig):

        indexes_of_nodes_to_labels_of_scc = {}

        for label, idx in g.labels_to_index.items():
            temp = g.get_array_of_vertices()[int(idx)].get_head()
            while temp is not None:
                temp_label = g.get_label_by_index(temp.data)
                for i in range(len(scc_list_conv)):
                    component_orig = scc_list_conv[i]
                    component_label_orig = scc_graph.get_index_by_label(component_orig)
                    for j in range(len(component_orig)):
                        node_orig = scc_list_conv[i][j]
                        if str(temp_label) == str(node_orig):
                            indexes_of_nodes_to_labels_of_scc[temp_label] = component_orig
                temp = temp.next_element
        
        indexes_of_nodes_to_labels_of_scc_T ={}

        for label, idx in g.labels_to_index.items():
            temp = g.get_array_of_vertices()[int(idx)].get_head()
            while temp is not None:
                temp_label = g.get_label_by_index(temp.data)
                for i in range(len(scc_list_orig)):
                    component_orig = scc_list_orig[i]
                    component_orig_char = scc_list_conv[i]
                    component_label_orig = scc_graph.get_index_by_label(component_orig)
                    for j in range(len(component_orig)):
                        node_orig = scc_list_orig[i][j]

                        if str(temp.data) == str(node_orig):
                            indexes_of_nodes_to_labels_of_scc_T[temp_label] = component_orig_char
                temp = temp.next_element

        #print(indexes_of_nodes_to_labels_of_scc)
        #print(indexes_of_nodes_to_labels_of_scc_T)

        return indexes_of_nodes_to_labels_of_scc_T

    
    # Uses the original grapho to make all the connection that the SCC have
    def add_vertices_on_scc_graph(self, g, scc_graph, scc_list_label, scc_list_index,indexes_of_nodes_to_labels_of_scc):

        print(indexes_of_nodes_to_labels_of_scc)

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

        """
        for component_orig in scc_list_label:   
            for node_orig in component_orig:
                node_orig_index = g.get_index_by_label(node_orig)
                node_dest = g.get_array_of_vertices()[node_orig_index].get_head()
                while node_dest is not None:
                    print("node_orig")
                    print(node_orig)
                    label_orig = indexes_of_nodes_to_labels_of_scc[node_orig]
                    label_dest = indexes_of_nodes_to_labels_of_scc[g.get_label_by_index(int(node_dest.data))]
                    if label_orig != label_dest:
                        scc_graph.add_edge(label_orig, label_dest)
                    node_dest = node_dest.next_element
        """
        return scc_graph