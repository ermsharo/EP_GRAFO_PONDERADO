from LinkedList import LinkedList

class Graph:
    def __init__( self, vertices ):
        self.array = []
        self.vertices = vertices 

        for i in range( self.vertices ):
            temp = LinkedList()
            self.array.append( temp )

    def get_number_of_vertices( self ):
        return self.vertices
    
    def get_array_of_vertices( self ):
        return self.array

    def add_edge( self, source, destination ):
        if ( source < self.vertices and destination < self.vertices  ):
            self.array[ source ].insert_at_head( destination )
            #self.array[ destination ].insert_at_head( source )

    def print_graph( self ):
        print (" Printing graph in adjacency list mode")

        num_of_vertices = self.vertices

        for i in range( num_of_vertices ):
            print("|", i ,end=" |=> ")
            temp = self.array[ i ].get_head()
            while ( temp is not None ):
                print("[", temp.data, end=" ]->")
                temp = temp.next_element
            print(" None ")

    

            