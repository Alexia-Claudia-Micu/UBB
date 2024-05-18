from services import Service
from service_exceptions import ServiceException
from repo_exceptions import RepositoryException

class Ui():
    def __init__(self):
        self._service = Service()
        self.read_graph("graph1k.txt")

    def menu(self):
        command = 0
        while command != "0":
            try:
                print("--------------------------------------------------------------------")
                print("0. Exit.")
                print("p. Print the graph.")
                print("1. Get the number of vertices.")
                print("2. Parse the set of vertices.")
                print("3. Check for the existence of an edge.")
                print("4. Get <in> and <out> degree of a vertex.")
                print("5.a. Parse the set of outbound edges of a vertex.")
                print("5.b. Parse the set of inbound edges of a vertex.")
                print("- Get the endpoints of a an edge_id (not applicable).")
                print("6.a. Retrieve the cost of an edge.")
                print("6.b. Modify the cost of an edge.")
                print("7.1.a. Add vertex.")
                print("7.1.b. Remove vertex.")
                print("7.2.a. Add edge.")
                print("7.2.b. Remove edge.")
                print("8. Make a copy.")
                print("9. Read graph from a text file.")
                print("10. Write graph to a text file.")
                print("11. Create random graph with specified number of vertices and edges.")
                print("12. Show the minimal cost path by using reverse Dijkstra.")
                print("--------------------------------------------------------------------")
                command = input("Give command > ")
                if command == "p":
                    graph_iterator = self._service.display()
                    for edge in graph_iterator:
                        print(str(edge))
                if command == "1":
                    print(f"The graph has {str(self._service.get_number_of_vertices())} vertices.")
                elif command == "2":
                    print(self._service.parse_graph())
                elif command == "3":
                    u = self._read_integer("first vertex")
                    v = self._read_integer("second vertex")
                    if self._service.check_existence_of_edge(u, v) is False:
                        print(f"Edge <{str(u)}->{str(v)}> does not exist.")
                    else:
                        print(f"Edge <{str(u)}->{str(v)}> exists.")
                elif command == "4":
                    v = self._read_integer("vertex")
                    in_degree = self._service.get_in_degree(v)
                    out_degree = self._service.get_out_degree(v)
                    print(f"In degree: {str(in_degree)}\nOut degree: {str(out_degree)}")
                elif command == "5.a":
                    v = self._read_integer("vertex")
                    result = self._service.parse_out_list_vertex(v)
                    print(f"List of outbound vertices for {str(v)}-> {str(result)}")
                elif command == "5.b":
                    v = self._read_integer("vertex")
                    result = self._service.parse_in_list_vertex(v)
                    print(f"List of inbound vertices for {str(v)}<- {str(result)}")
                elif command == "6.a":
                    u = self._read_integer("first vertex")
                    v = self._read_integer("second vertex")
                    print(f"The cost of edge <{str(u)}->{str(v)}> is {str(self._service.retrieve_cost_of_edge(u, v))}.")
                elif command == "6.b":
                    u = self._read_integer("first vertex")
                    v = self._read_integer("second vertex")
                    new_cost = self._read_integer("new cost")
                    self._service.modify_cost_of_edge(u, v, new_cost)
                elif command =="7.1.a":
                    vertex = self._read_integer("vertex to add")
                    print("Vertex has been added\n")
                    self._service.add_vertex(vertex)
                elif command =="7.1.b":
                    vertex = self._read_integer("vertex to remove")
                    self._service.remove_vertex(vertex)
                elif command =="7.2.a":
                    print("You need to input the vertices and cost of the edge to be added:")
                    edge_start = self._read_integer("start vertex")
                    edge_end = self._read_integer("end vertex")
                    edge_cost = self._read_integer("cost")
                    self._service.add_edge(edge_start, edge_end, edge_cost)
                elif command =="7.2.b":
                    print("You need to input the vertices of the edge to be removed:")
                    edge_start = self._read_integer("edge start vertex")
                    edge_end = self._read_integer("edge end vertex")
                    self._service.remove_edge(edge_start, edge_end)
                elif command == "8":
                    self._service.copy_graph()
                elif command == "9":
                    file_name = input("Give file name > ")
                    self.read_graph_format2(file_name)
                elif command == "10":
                    file_name = input("Give file name > ")
                    self.write_graph_format2(file_name)
                elif command == "11":
                    nr_vertices = self._read_integer("number of vertices")
                    nr_edges = self._read_integer("number of edges")
                    self._service.generate_random_graph(nr_vertices, nr_edges)
                elif command == "12":
                    start_vertex = self._read_integer("start vertex")
                    end_vertex = self._read_integer("end vertex")
                    [path, cost] = self._service.reverse_min_dijkstra(start_vertex, end_vertex)
                    print(f"{str(path)} \nThe cost is {str(cost)}")
            except ServiceException as se:
                print(f"There was a {str(type(se))}, with message {str(se)}")
            except RepositoryException as se:
                print(f"There was a {str(type(se))}, with message {str(se)}")

    def _read_integer(self, purpose):
        try:
            integer = int(input(f"Give integer for {purpose} > "))
        except ValueError as ve:
            print(f"There was a {str(type(ve))}, with message {str(ve)}")
        else:
            return integer

    def read_graph_format2(self, file_name):
        self._service.clear()
        fin = open(file_name, "rt")
        first_line = fin.readline()
        first_line = first_line.split(" ")
        nr_of_vertices = int(first_line[0])
        nr_of_edges = int(first_line[1])
        line = fin.readline()
        while line != '':
            line = line.split(" ")
            if((int(line[1])) != -1):
                try:
                    self._service.add_vertex((int(line[0])))
                except RepositoryException as re:
                    print("")
                try:
                    self._service.add_vertex((int(line[1])))
                except RepositoryException as re:
                    print("")
                self._service.add_edge((int(line[0])), (int(line[1])), (int(line[2])))
            else: self._service.add_vertex((int(line[0])))
            line = fin.readline()
        fin.close()

    def read_graph(self, file_name):
        self._service.clear()
        fin = open(file_name, "rt")
        first_line = fin.readline()
        first_line = first_line.split(" ")
        nr_of_vertices = int(first_line[0])
        nr_of_edges = int(first_line[1])
        for i in range(nr_of_vertices):
            self._service.add_vertex(i)
        for i in range(nr_of_edges):
            line = fin.readline()
            line = line.split(" ")
            self._service.add_edge((int(line[0])), (int(line[1])), (int(line[2])))
        fin.close()

    def write_graph(self, file_name):
        fout = open(file_name, "wt")
        first_line = f"{str(self._service.get_number_of_vertices())} {str(self._service.get_number_of_edges())}\n"
        fout.write(first_line)
        for vertex in self._service.parse():
            for adjacentVertex in self._service.parse_out_list_vertex(vertex):
                line = f"{str(vertex)} {str(adjacentVertex)} {str(self._service.retrieve_cost_of_edge(vertex, adjacentVertex))}\n"
                fout.write(line)
        fout.close()

    def write_graph_format2(self, file_name):
        fout = open(file_name, "wt")
        first_line = f"{str(self._service.get_number_of_vertices())} {str(self._service.get_number_of_edges())}\n"
        fout.write(first_line)
        for vertex in self._service.parse():
            if len(self._service.parse_out_list_vertex(vertex)) == 0 and len(self._service.parse_in_list_vertex(vertex)) == 0:
                line = f"{str(vertex)} -1\n"
                fout.write(line)
            for adjacentVertex in self._service.parse_out_list_vertex(vertex):
                line = f"{str(vertex)} {str(adjacentVertex)} {str(self._service.retrieve_cost_of_edge(vertex, adjacentVertex))}\n"
                fout.write(line)
        fout.close()

if __name__ == "__main__":
    ui = Ui()
    ui.menu()

