#!python
#
# Graph library test suite
# 
# Author: Vinicius J. S. Souza
################################################

from graphs import *
import unittest

class GraphTest(unittest.TestCase):
    def sampleGraph(self):
        g = Graph()
        g.connect(2,4)
        g.connect(1,3)
        g.connect(3,5)
        return g
    
    def test_edgeEquals(self):
        self.assertEquals(Edge(2,4), Edge(2,4))
        self.assertNotEquals(Edge(2,4), Edge(4,2))
    
    def test_edgeToStr(self):
        self.assertEquals(str(Edge(2,4)), '2 <-> 4')
    
    def test_findEdge(self):
        g = self.sampleGraph()
        
        self.assertEquals(g.findEdge(1,3), Edge(1,3))
        self.assertEquals(g.findEdge(2,4), Edge(2,4))
        self.assertFalse(g.findEdge(1,5))
    
    def test_vertexes(self):
        g = self.sampleGraph()
        
        self.assertEquals(len(g.vertexes()), 5)
        self.assertTrue(1 in g.vertexes())
        self.assertTrue(2 in g.vertexes())
        self.assertFalse(6 in g.vertexes())
        
    def test_connect(self):
        g = self.sampleGraph()
        
        self.assertTrue(g.findEdge(2,4))
        self.assertTrue(g.findEdge(1,3))
        self.assertTrue(g.findEdge(3,5))
        self.assertFalse(g.findEdge(1,4))
        self.assertFalse(g.findEdge(1,5))
    
    def test_edgesOf(self):
        g = self.sampleGraph()
        
        self.assertTrue(Edge(1,3) in g.edgesOf(1))
        self.assertTrue(Edge(3,1) in g.edgesOf(3))
        self.assertTrue(Edge(2,4) in g.edgesOf(4))
        self.assertFalse(Edge(2,5) in g.edgesOf(2))
        self.assertFalse(Edge(2,3) in g.edgesOf(3))

class BipartiteGraphTest(unittest.TestCase):
    def test_notBipartite(self):
        g = Graph()
        g.connect(1,2)
        g.connect(2,3)
        g.connect(3,4)
        g.connect(4,5)
        g.connect(5,6)
        g.connect(1,5)
        
        bipartite = BipartiteGraph(g)
        
        self.assertFalse(bipartite.isBipartite)
        
    def test_Bipartite(self):
        g = Graph()
        g.connect(1,2)
        g.connect(2,3)
        g.connect(3,4)
        g.connect(4,5)
        g.connect(5,6)
        
        bipartite = BipartiteGraph(g)
        
        self.assertTrue(bipartite.isBipartite)    
        
class MaxMatchingTest(unittest.TestCase):
    def sampleGraph1(self):
        g = Graph()
        g.connect(1,'a')
        g.connect(1,'b')
        g.connect(2,'a')
        g.connect(3,'b')
        g.connect(3,'c')
        g.connect(3,'d')
        g.connect(4,'d')
        g.connect(4,'e')
        g.connect(5,'d')
        return g
    
    def sampleGraph2(self):
        g = Graph()
        g.connect('a', 5)
        g.connect('b', 1)
        g.connect('b', 4)
        g.connect('c', 1)
        g.connect('c', 2)
        g.connect('c', 4)
        g.connect('d', 5)
        g.connect('e', 3)        
        g.connect('e', 5)        
        g.connect('e', 6)        
        g.connect('f', 4)        
        return g    
        
    def test_emptyGraph(self):
        g = Graph()
        
        alg = MaxMatching(g)
        
        self.assertEquals(alg.size(), 0)
        self.assertEquals(alg.matches, {})
        
    def test_matchingGraph1(self):
        g = self.sampleGraph1()
       
        alg = MaxMatching(g)
        
        self.assertEquals(alg.size(), 5)
        
        self.assertEquals(alg.matches['a'], 2)
        self.assertEquals(alg.matches['b'], 1)
        self.assertEquals(alg.matches['c'], 3)
        self.assertEquals(alg.matches['e'], 4)
        self.assertEquals(alg.matches[5], 'd')
        
    def test_matchingGraph2(self):
        g = self.sampleGraph2()
        alg = MaxMatching(g)
        
        self.assertEquals(alg.size(), 5)
        
        self.assertEquals(alg.matches['a'], 5)
        self.assertEquals(alg.matches[1], 'b')
        self.assertEquals(alg.matches['c'], 2)
        self.assertEquals(alg.matches['e'], 6)
        self.assertEquals(alg.matches[4], 'f')
        
if __name__ == '__main__':
    unittest.main()