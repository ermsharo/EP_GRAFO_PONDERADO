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
    

