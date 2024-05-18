from repository import Graph
from service_exceptions import ServiceException
from copy import deepcopy
from random import randint, choice
import heapq

class Service():
    def __init__(self):
        #self._graph = Graph()
        #Graph.__init__(self._graph)
        self._graph = Graph()
        self.copies = []

    @property
    def nrCopies(self):
        return len(self.copies)

    # def read_graph_from_file(self, file_name):
    #     self._graph.read_graph(file_name)
    #
    # def write_graph_to_file(self, file_name):
    #     self._graph.write_graph(file_name)

    def read_and_print_graph(self):
        self._graph.read_graph("graph1k.txt")
        #self._graph.display()

    def add_edge(self, u, v, cost):
        self._graph.add_edge(u, v, cost)

    def remove_edge(self, u, v):
        self._graph.remove_edge(u, v)

    def add_vertex(self, vertex_to_add):
        #vertex_to_add = self._graph.vertex_number
        self._graph.add_vertex(vertex_to_add)

    def modify_cost(self, u, v, new_cost):
        self._graph.modify_cost(u, v, new_cost)

    def retrieve_cost(self, u, v):
        return self._graph.retrieve_cost(u, v)

    def remove_vertex(self, v):
        self._graph.remove_vertex(v)

    def parse_graph(self):
        # result = ""
        # # result +="Parsing the <in> dictionary" + str(self._graph.parse_in()) + '\n'
        # # result +="Parsing the <out> dictionary" + str(self._graph.parse_out()) + '\n'
        # return result
        listOfVertices = []
        for vertex in self._graph.parse():
            listOfVertices.append(vertex)
        return str(listOfVertices) + '\n'

    def display(self):
        return self._graph.displayable_iterator()

    def get_number_of_vertices(self):
        return self._graph.vertex_number

    def get_number_of_edges(self):
        return self._graph.edge_number

    def check_existence_of_edge(self, u, v):
        return self._graph.is_edge(u, v)

    def get_in_degree(self, v):
        return self._graph.in_degree(v)

    def get_out_degree(self, v):
        return self._graph.out_degree(v)

    def retrieve_cost_of_edge(self, u, v):
        return self._graph.retrieve_cost(u, v)

    def modify_cost_of_edge(self, u, v, new_cost):
        self._graph.modify_cost(u, v, new_cost)

    def parse_in_list_vertex(self, vertex):
        return self._graph.parse_inbound(vertex)

    def parse_out_list_vertex(self, vertex):
        return self._graph.parse_outbound(vertex)

    def copy_graph(self):
        self.copies.append(deepcopy(self._graph))

    def generate_random_graph(self, nr_vertices, nr_edges):
        self._graph.clear_graph()
        if nr_edges > nr_vertices * nr_vertices:
            raise ServiceException(f"Graph of size {str(nr_vertices)} cannot have that many edges.")
        for i in range(nr_vertices):
            self._graph.add_vertex(i)

        current_edge_number = 0
        if nr_edges < nr_vertices * (nr_vertices - 1) // 3 or nr_vertices > 500:
            while current_edge_number < nr_edges:
                v = randint(0, nr_vertices - 1)
                u = randint(0, nr_vertices - 1)
                if self._graph.is_edge(u, v) is False:
                    self._graph.add_edge(u, v, randint(0, 100))
                    current_edge_number += 1
        else:
            possible_edges = []
            for i in range(nr_vertices):
                for j in range(nr_vertices):
                        possible_edges.append([i, j])
            for i in range(nr_edges):
                [u, v] = choice(possible_edges)
                possible_edges.remove([u, v])
                self._graph.add_edge(u, v, randint(0, 100))

    def parse(self):
        return self._graph.parse()

    def clear(self):
        self._graph.clear_graph()

    def reverse_min_dijkstra(self, start_vertex, end_vertex):
        return self._graph.min_cost_path_dijkstra(start_vertex, end_vertex)