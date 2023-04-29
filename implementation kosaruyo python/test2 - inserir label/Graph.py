from LinkedList import LinkedList

class Graph:
    def __init__( self, vertices ):
        self.array = []
        self.vertices = vertices 
        self.labels_to_index = {}
        self.index_to_label = {}
        for i in range( self.vertices ):
            temp = LinkedList()
            self.array.append( temp )

    #COVERTED
    def add_edge( self, source, destination ):
        #destination_index = self.get_index_by_label(destination)

        if self.node_contains(source, destination):
            return 

        if source in self.labels_to_index and destination in self.labels_to_index :
            source_index = self.get_index_by_label(source)
            destination_index = self.get_index_by_label(destination)
            self.array[ source_index ].insert_at_head( destination_index )

    # COVERTED
    def add_edge_by_index( self, source, destination ):
        if ( source < self.vertices and destination < self.vertices  ) and not self.node_contains(source, destination):
            self.array[ source ].insert_at_head( destination )
    
    # CONVERTED
    def node_contains(self, source, destination):
    
        source_index = self.get_index_by_label(source)
        dest_index = self.get_index_by_label(destination)

        temp = self.get_array_of_vertices()[int(source_index)].get_head()

        while temp is not None:
            if temp.data == dest_index :
                return True
            temp = temp.next_element

        return False
    
    # CONVERTED
    def print_graph( self ):
        for label, idx in self.labels_to_index.items():
            print( label, ": ", end="")
            temp = self.array[idx].get_head()
            while temp is not None:
                print( self.index_to_label[temp.data], "; ", end="")
                temp = temp.next_element
            print()

    def print_graph_indexes(self):
        for idx in range(len(self.array)):
            print(idx, ": ", end="")
            temp = self.array[idx].get_head()
            while temp is not None:
                print(temp.data, "; ", end="")
                temp = temp.next_element
            print()

    # CONVERTED
    def get_number_of_vertices( self ):
        return self.vertices
    
    # CONVERTED
    def get_array_of_vertices( self ):
        return self.array
    
    # NOT USED
    def set_index_to_label( self, label, index):
        self.labels_to_index[label] = index
        self.labels_to_index[index] = label

    # CONVERTED
    def get_index_by_label( self, label ):
        if label in self.labels_to_index:
            return self.labels_to_index[label]
        return False
    
    # CONVERTED
    def set_labels(self, labels):
        self.labels_to_index = {label: i for i, label in enumerate(labels)}
        self.index_to_label = {i: label for i, label in enumerate(labels)}
    
    # CONVERTED
    def get_label_by_index(self, index):
        return self.index_to_label[index]
    
    # CONVERTED
    def get_both_maps(self):
        print()
        print("labels_to_index")
        print(self.labels_to_index)
        print()
        print("index_to_label")
        print(self.index_to_label)
        print()
    
    def topological_sort(self):
        visited = [False] * self.vertices
        stack = []

        for i in range(self.vertices):
            if not visited[i]:
                self.topological_sort_util(i, visited, stack)

        return [self.index_to_label[node] for node in stack[::-1]]

    def topological_sort_util(self, node, visited, stack):
        visited[node] = True
        neighbour = self.array[node].get_head()

        while neighbour is not None:
            if not visited[neighbour.data]:
                self.topological_sort_util(neighbour.data, visited, stack)
            neighbour = neighbour.next_element

        stack.append(node)