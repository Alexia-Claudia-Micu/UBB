from repo_exceptions import RepositoryException
from copy import deepcopy

class GraphUndirected:
    def __init__(self):
        self._vertex_number = 0
        self._edge_number = 0
        self._neighbours = {}

    @property
    def vertex_number(self):
        return self._vertex_number

    @property
    def edge_number(self):
        return self._edge_number

    # Theta(1)
    def _is_vertex(self, v):
        if self._neighbours.get(v) is None:
            return False
        return True

    # O(n)
    def is_edge(self, u, v):
        if self._is_vertex(v) is False or self._is_vertex(u) is False:
            raise RepositoryException("Is edge - One of the vertices does not exist.")        #dict.get has worst case complexity: O(n)
        if self._neighbours.get(u).get(v) is None:
            return False
        return True

    # O(1)
    def add_vertex(self, v):
        if self._is_vertex(v) is False:
            self._neighbours[v] = {}
            self._vertex_number += 1
        else:
            raise RepositoryException("Add vertex - Vertex already exists.")

    # O(1)
    def add_edge(self, u, v, cost):
        if self.is_edge(u, v) is False:
            self._neighbours[u][v] = cost
            self._edge_number += 1
            if u != v:
                self._neighbours[v][u] = cost
                self._edge_number += 1
        else:
            raise RepositoryException("Add edge - Edge already exists.")

    def remove_vertex(self, vertexToDelete):
        if self._is_vertex(vertexToDelete) is True:
            self._edge_number -= len(self._neighbours[vertexToDelete])
            for vertex in self._neighbours[vertexToDelete]:
                del self._neighbours[vertex][vertexToDelete]
                self._edge_number -= 1
            del self._neighbours[vertexToDelete]
            self.vertex_number -= 1
        else:
            raise RepositoryException("Remove vertex - Vertex does not exist")

    # O(1)
    def remove_edge(self, u, v):
        if self.is_edge(u, v) is True:
            del self._neighbours[u][v]
            del self._neighbours[v][u]
            self._edge_number -= 1
        else:
            raise RepositoryException("Remove Edge - Edge does not exist.")
    # O(1)
    def retrieve_cost(self, u, v):
        if self.is_edge(u, v) is True:
            return self._neighbours[u][v]
        else:
            raise RepositoryException("Retrieve Cost - Edge does not exist.")

    # O(1)
    def modify_cost(self, u, v, new_cost):
        if self.is_edge(u, v) is True:
            self._neighbours[u][v] = new_cost
            self._neighbours[v][u] = new_cost
        else:
            raise RepositoryException("Retrieve Cost - Edge does not exist.")

    # O(1) + complexity(range) - O(1)
    def parse(self):
        list = []
        for vertex in self._neighbours.keys():
            list.append(vertex)
        return list

    def parse_neighbours(self, v):
        list = []
        for vertex in self._neighbours[v].keys():
            list.append(vertex)
        return list

    def clear_graph(self):
        list_to_parse = self.parse()
        for vertex in list_to_parse:
            del self._neighbours[vertex]
        self._vertex_number = 0
        self._edge_number = 0