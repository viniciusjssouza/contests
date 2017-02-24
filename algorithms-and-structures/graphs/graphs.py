#!python
#
# Graph library
# 
# Author: Vinicius J. S. Souza
############################################

from cStringIO import StringIO
from collections import deque

class Edge:
    """ A bidirectional connection between two vertexes in the graph
        (DOES NOT HAVE A DIRECTION)
    """
    def __init__(self, u, v):
        self.u = u
        self.v = v
    
    def other(self, w):
        if w == self.v:
            return self.u
        elif w == self.u:
            return self.v
        else:    
            raise ValueError('vertex not connected to edge ' + self)
    
    def __eq__(self, other):
        return (self.u == other.u and self.v == other.v) or \
                (self.v == other.u and self.u == other.v)

    def __hash__(self):
        return hash(self.u) + hash(self.v)
        
    def __str__(self):
        return '%s <-> %s' % (self.u, self.v)
    __repr__ = __str__    
    
class Graph:
    """A simple graph whose edges does not have direction"""
    
    def __init__(self):
        self.edges = dict()
     
    def connect(self, a,b):
        e = Edge(a,b)
        self.edges.setdefault(a, set()).add(e)
        self.edges.setdefault(b, set()).add(e)
        return self
    
    def edgesOf(self,v):
        return self.edges.setdefault(v,set())
    
    def vertexes(self):
        return self.edges.keys()
    
    def findEdge(self, a, b):
        for e in self.edges[a]:
            if e.other(a) == b:
                return e
        return None   
        
    def __str__(self):   
        file_str = StringIO()
        for e in self.edges:
            file_str.write(str + '\n')   
        return file_str.getvalue()  
        
    __repr__ = __str__    

class BipartiteGraph:
    """ A bipartite graph with disjoint sets of vertexes U and V"""
    BLACK = 1
    WHITE = 0    
    
    def __init__(self, graph):
        self.graph = graph        
        self.color = dict()
        self.isBipartite = True
        self._colorify()
    
    def _colorify(self):
        """Try to color the graph using two colors. If it is possible, then
            the graph is not bipartite.
        """
        for v in self.graph.vertexes():
            if self.isBipartite and v not in self.color:
                self._bfs(v)
        self.U = set()
        self.V = set()
        for w in self.color:
            if self.color[w] == self.BLACK:
                self.U.add(w)
            else:
                self.V.add(w)    
        
    def _bfs(self, source):       
        q = deque([source])
        if source not in self.color:
            self.color[source] = BipartiteGraph.BLACK
        while q:
            v = q.popleft()            
            for e in self.graph.edgesOf(v):
                w = e.other(v)
                if w not in self.color:
                    self.color[w] = self._nextColor(v)
                    q.append(w)
                elif self.color[v] == self.color[w]:
                    self.isBipartite = False
                    return
                    
    def _nextColor(self, v):
        return self.BLACK if self.color[v] == self.WHITE else self.WHITE
        
class MaxMatching:
    """ 
        Find the maximum matching between the sets U and V. 
        The maximum matching is the maximum number of edges
        which does not connect repeated vertexes. In other words,
        every vertex connected by these edges must have a degree of one.
        
        This implementation used the Hopcroft-Karp algorithm, which runs on
        O(E sqrt(V)).
        
        The input graph MUST BE A BIPARTITE GRAPH object.
        
        This function returns a dictionary containing pair of vertexes in U and V  
        connected by an edge selected to be part of the match.
    """
    def __init__(self, graph):
        self.graph = graph
        self.dist = dict()
        self.matches = dict()    
        self.partition = BipartiteGraph(graph)
        if not self.partition.isBipartite:
            raise ValueError('The provided graph is not bipartite!')
        self._match()    
        
    def _match(self):
        while (1):
            visited = set()
            augmented = False
            for u in self.partition.U:
                if u not in self.matches:
                    if self._findAugmentingPath(u, visited):
                        augmented = True                
            if not augmented:
                break
        return self.matches        
    
    def size(self):
        # cut the half which is composed by back edges.
        return len(self.matches) / 2 
    
    def _findAugmentingPath(self, source, visited):
        """ Search the graph for unmatched vertexes on V, starting on U. Just augment paths are
            considered. An path is an augmenting path if it starts on an unmatched vertex of U
            and ends on a unmatched vertex of V, passing through alternate edges: the first edge
            must be an unmatched edge, the second must be matched edge, third unmatched, and so on.
            
            Return True only if managed to find a new augmenting path.
        """
        parent = dict()
        q = deque()
        
        # populate the queue with unmatched vertexes
        for u in self.partition.U:
            if u not in self.matches:
                q.append(u)
                visited.add(u)
        while q:            
            w = q.popleft()
            for e in self.graph.edgesOf(w):
                other = e.other(w)                
                if self._isAlternatingEdge(w,other) and other not in visited:
                    visited.add(other)
                    parent[other] = w
                    if other not in self.matches:
                        self._matchEdges(other, parent)
                        return True
                    else: 
                        q.append(other)
        return False
    
    def _isAlternatingEdge(self, a,b):
        return (a in self.partition.U and self.matches.get(a) != b) or \
            (a in self.partition.V and self.matches.get(a) == b)            
    
    def _matchEdges(self, dest, parent):            
        """ Walk through the augmenting path starting on the destination,
           inverting the status of the edges: matched edges become unmatched
           and unmatched edges become matched.           
        """ 
        curr = dest
        while curr in parent:
            if curr in self.partition.V:              
                u = parent[curr]    
                self.matches[curr] = u
                self.matches[u] = curr
            curr = parent[curr]