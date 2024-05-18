from repository import GraphUndirected
from repo_exceptions import RepositoryException
from service_exceptions import ServiceException
from copy import deepcopy
from random import randint, choice

class Service():
    def __init__(self):
        #self._graph = Graph()
        #Graph.__init__(self._graph)
        self._graph = GraphUndirected()
        self.copies = []

    @property
    def nrCopies(self):
        return len(self.copies)

    def add_edge(self, u, v, cost):
        self._graph.add_edge(u, v, cost)

    def remove_edge(self, u, v):
        self._graph.remove_edge(u, v)

    def add_vertex(self, vertex_to_add):
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
        return listOfVertices

    def get_number_of_vertices(self):
        return self._graph.vertex_number

    def get_number_of_edges(self):
        return self._graph.edge_number

    def check_existence_of_edge(self, u, v):
        return self._graph.is_edge(u, v)

    def copy_graph(self):
        self.copies.append(deepcopy(self._graph))

    def generate_random_graph(self, nr_vertices, nr_edges):
        self._graph.clear_graph()
        if nr_edges > nr_vertices * nr_vertices:
            raise ServiceException(f"Graph of size {str(nr_vertices)} cannot have that many edges.")
        for i in range(nr_vertices):
            self._graph.add_vertex(i)

        current_edge_number = 0
        while current_edge_number < nr_edges:
            v = randint(0, nr_vertices - 1)
            u = randint(0, nr_vertices - 1)
            if self._graph.is_edge(u, v) is False:
                self._graph.add_edge(u, v, randint(0, 100))
                current_edge_number += 2

    def parse(self):
        return self._graph.parse()

    def parse_neighbours(self):
        return self._graph.parse_neighbours()

    def clear(self):
        self._graph.clear_graph()

    def display(self):
        result = ""
        for vertex in self._graph.parse():
            for adjacent_vertex in self._graph.parse_neighbours(vertex):
                result += f"[{str(vertex)}, {str(adjacent_vertex)}] - {str(self._graph.retrieve_cost(vertex, adjacent_vertex))} "
            result += "\n"
        return result

    def _fill_using_depth_first(self, vertex, list_not_visited):
        '''
        The subprogram receives a vertex and the list of vertices that are yet to be visited
            Step 1: adds the vertex to the top of the stack
            Step 2: iterates through the adjacent vertices and adds the available ones to the top
                    - pops these vertices from the list of unvisited vertices
                    - appends them to the list of vertices for the current component
            Step 3: takes the top of the stack and repeats the steps 2, 3 until all vertices of the component are checked
        :param vertex: the vertex from which we start building a connected component around
        :param list_not_visited: the list of vertices that are yet to be assigned to a component
        :return: the list of vertices that were added using the received <vertex> parameter
                -> the list of vertices for the component of <vertex>
        '''
        added_vertices = []
        added_vertices.append(vertex)
        stack = []
        stack.append(vertex)
        while len(stack) is not 0:
            new_vertex = stack.pop()
            for adjacent_vertex in self._graph.parse_neighbours(new_vertex):
                try:
                    if list_not_visited.index(adjacent_vertex) is not None:
                        list_not_visited.pop(list_not_visited.index(adjacent_vertex))
                        stack.append(adjacent_vertex)
                        added_vertices.append(adjacent_vertex)
                except ValueError:
                    pass
        return added_vertices

    def _save_graph_object(self, component, component_dictionary):
        '''
        Saves each component as a separate graph in the graph copies of the service
        :param component: the number of components
        :param component_dictionary: a dictionary in the form of:
                                    - <component number> : list of vertices of the component
        '''
        for current_component in range(1, component):
            newGraph = GraphUndirected()
            for vertex in component_dictionary[current_component]:
                newGraph.add_vertex(vertex)
            for vertex in component_dictionary[current_component]:
                for adjacent_vertex in self._graph.parse_neighbours(vertex):
                    try:
                        newGraph.add_edge(vertex, adjacent_vertex, self._graph.retrieve_cost(vertex, adjacent_vertex))
                    except RepositoryException:
                        pass
            self.copies.append(newGraph)

    def depth_first_components(self):
        ''''
        Step 1: Saves all vertices of the graph as a list of unvisited
        Step 2: While unvisited vertices exist, call fill_dfs on the vertices that have not been assigned to a component
        Step 3: Save each component as a graph object

        :return: a dictionary in the form of <component number> : list of vertices of the component
        '''
        list_not_visited = self.parse()
        component_dictionary = {}
        component = 1
        while len(list_not_visited) != 0:
            vertex = list_not_visited.pop(0)
            component_dictionary[component] = self._fill_using_depth_first(vertex,  list_not_visited)
            component += 1
        self._save_graph_object(component, component_dictionary)
        return component_dictionary

