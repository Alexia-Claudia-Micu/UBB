from repo_exceptions import RepositoryException
from copy import deepcopy
import heapq


def edge_key(u, v):
    return f"<{str(u)}, {str(v)}>"

class Graph:
    def __init__(self):
        self._vertex_number = 0
        self._edge_number = 0
        self._din = {}
        self._dout = {}
        self._dcost = {}

    @property
    def vertex_number(self):
        return self._vertex_number

    @property
    def edge_number(self):
        return self._edge_number

    @vertex_number.setter
    def vertex_number(self, value):
        self._vertex_number = value

    @edge_number.setter
    def edge_number(self, value):
        self._edge_number = value

    # O(1)
    def in_degree(self, v):
        if self._is_vertex(v) is True:
            return len(self._din[v])
        raise RepositoryException("InDegree - Vertex does not exist.")

    # O(1)
    def out_degree(self, v):
        if self._is_vertex(v) is True:
            return len(self._dout[v])
        raise RepositoryException("OutDegree - Vertex does not exist.")

    # Theta(1)
    def _is_vertex(self, v):
        if self._din.get(v) is None:
            return False
        return True

    # O(n)
    def is_edge(self, u, v):
        if self._is_vertex(v) is False or self._is_vertex(u) is False:
            raise RepositoryException("Is edge - One of the vertices does not exist.")
        edge = edge_key(u, v)
        #dict.get has worst case complexity: O(n)
        if self._dcost.get(edge) is None:
            return False
        return True

    # O(1)
    def add_vertex(self, v):
        if self._is_vertex(v) is False:
            self._din[v] = []
            self._dout[v] = []
            self._vertex_number += 1
        else:
            raise RepositoryException("Add vertex - Vertex already exists.")

    # O(1)
    def add_edge(self, u, v, cost):
        if self.is_edge(u, v) is False:
            edge = edge_key(u, v)
            self._din[v].append(u)
            self._dout[u].append(v)
            self._dcost[edge] = cost
            self._edge_number += 1
        else:
            raise RepositoryException("Add edge - Edge already exists.")

    def remove_vertex(self, vertexToDelete):
        if self._is_vertex(vertexToDelete) is True:
            for vertex in self._din[vertexToDelete]:
                self._dout[vertex].remove(vertexToDelete)
                del self._dcost[edge_key(vertex, vertexToDelete)]
                self.edge_number -= 1
            del self._din[vertexToDelete]
            for vertex in self._dout[vertexToDelete]:
                self._din[vertex].remove(vertexToDelete)
                del self._dcost[edge_key(vertexToDelete, vertex)]
                self.edge_number -= 1
            del self._dout[vertexToDelete]
            self.vertex_number -= 1
        else:
            raise RepositoryException("Remove vertex - Vertex does not exist")

    # O(1)
    def remove_edge(self, u, v):
        if self.is_edge(u, v) is True:
            del self._dcost[edge_key(u, v)]
            self._dout[u].remove(v)
            self._din[v].remove(u)
            self._edge_number -= 1
        else:
            raise RepositoryException("Remove Edge - Edge does not exist.")
    # O(1)
    def retrieve_cost(self, u, v):
        if self.is_edge(u, v) is True:
            return self._dcost[edge_key(u, v)]
        else:
            raise RepositoryException("Retrieve Cost - Edge does not exist.")

    # O(1)
    def modify_cost(self, u, v, new_cost):
        if self.is_edge(u, v) is True:
            self._dcost[edge_key(u, v)] = new_cost
        else:
            raise RepositoryException("Retrieve Cost - Edge does not exist.")

    # O(1) + complexity(range) - O(1)
    def parse(self):
        vertices = []
        for vertex in self._din:
            vertices.append(vertex)
        return vertices

    # O(1) + complexity(deepcopy) - O(n) worst case
    def parse_outbound(self, vertex):
        return deepcopy(self._dout[vertex])

    # O(1) + complexity(deepcopy) - O(n) worst case
    def parse_inbound(self, vertex):
        return deepcopy(self._din[vertex])

    def displayable_iterator(self):
        result = []
        for vertex in self._din:
            for adjacent_vertex in self._din[vertex]:
                result.append(f"in: {str(vertex)} <- {str(adjacent_vertex)}")
        for vertex in self._dout:
            for adjacent_vertex in self._dout[vertex]:
                result.append(f"out: {str(vertex)} -> {str(adjacent_vertex)}")
        return result

    def clear_graph(self):
        self._dcost.clear()
        self._din.clear()
        self._dout.clear()
        self.vertex_number = 0
        self.edge_number = 0

    def min_cost_path_dijkstra(self, start_vertex, end_vertex):
        '''Computes the min cost path from s to t in graph g using the costs in 'cost'
        (cost[(x,y)] = the cost of the edge (x,y)
        '''
        priority_queue = list()
        previous = {}
        previous[end_vertex] = None
        distance = {}
        heapq.heappush(priority_queue, (0, end_vertex))
        distance[end_vertex] = 0
        found = False

        while priority_queue and not found:
            current_priority, current_vertex = heapq.heappop(priority_queue)
            if current_priority > distance[current_vertex]:
                #print(f"Skipping vertex {current_vertex}");
                continue
            for inbound_neighbour in self.parse_inbound(current_vertex):
                if inbound_neighbour not in distance.keys() or (
                        distance[current_vertex] + self._dcost[edge_key(inbound_neighbour, current_vertex)] < distance[inbound_neighbour]):
                    distance[inbound_neighbour] = distance[current_vertex] + self._dcost[edge_key(inbound_neighbour, current_vertex)]
                    heapq.heappush(priority_queue, (distance[inbound_neighbour], inbound_neighbour))
                    previous[inbound_neighbour] = current_vertex
            #print(f"current_vertex={current_vertex}, dist={distance}, prev={previous}, q={priority_queue}")
            if current_vertex == start_vertex:
                found = True

        if found is not True:
            return ["Path does not exist.", 0]
        else:
            return [_extract_path(previous, start_vertex, end_vertex), distance[start_vertex]]


def _extract_path(previous, start_vertex, end_vertex):
    vertex_path = []
    vertex_path.append(start_vertex)
    vertex = start_vertex
    while vertex != end_vertex:
        vertex = previous[vertex]
        vertex_path.append(vertex)
    return vertex_path


def remove_vertex_wrong(self, vertexToDelete):
    '''
        Remove a vertex from the graph and replace it with the last vertex of the graph so as to preserve the continuity of vertex indices
    :param vertexToDelete: the vertex that is to be removed
    :param vertexToMoveUp: Initial state: last vertex; Exit state: replace vertex to delete
    '''
    if self._is_vertex(vertexToDelete) is True:
        vertexToMoveUp = self.vertex_number - 1
        for vertex in self._din[vertexToDelete]:
            self._dout[vertex].remove(vertexToDelete)
            del self._dcost[edge_key(vertex, vertexToDelete)]
            self.edge_number -= 1
        self._din[vertexToDelete] = []
        for vertex in self._dout[vertexToDelete]:
            self._din[vertex].remove(vertexToDelete)
            del self._dcost[edge_key(vertexToDelete, vertex)]
            self.edge_number -= 1
        self._dout[vertexToDelete] = []
        for vertex in self._din[vertexToMoveUp]:
            self._dout[vertex].remove(vertexToMoveUp)
            self._dout[vertex].append(vertexToDelete)
            self._din[vertexToDelete].append(vertex)
            self._dcost[edge_key(vertex, vertexToDelete)] = self._dcost[edge_key(vertex, vertexToMoveUp)]
            del self._dcost[edge_key(vertex, vertexToMoveUp)]
        for vertex in self._dout[vertexToMoveUp]:
            self._din[vertex].remove(vertexToMoveUp)
            self._din[vertex].append(vertexToDelete)
            self._dout[vertexToDelete].append(vertex)
            self._dcost[edge_key(vertexToDelete, vertex)] = self._dcost[edge_key(vertexToMoveUp, vertex)]
            del self._dcost[edge_key(vertexToMoveUp, vertex)]
        # delete the former index of VertexToMoveUp
        # decrease the number of vertices in the graph
        del self._din[vertexToMoveUp]
        del self._dout[vertexToMoveUp]
        self.vertex_number -= 1
    else:
        raise RepositoryException("Remove vertex - Vertex does not exist")
