from Node import Node

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

"""            
test = LinkedList()
test.insert_at_head(1)
test.insert_at_head(2)
test.insert_at_head(3)
print(test.getNode(2))
test.setNode(2,True)
print(test.getNode(2))
test.print_list()

"""