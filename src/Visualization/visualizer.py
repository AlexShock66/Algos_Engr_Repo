# First networkx library is imported 
# along with matplotlib

#Adapted from https://www.geeksforgeeks.org/visualize-graphs-in-python/# 
import networkx as nx
import matplotlib.pyplot as plt
import os
  
# Defining a Class
class GraphVisualization:
   
    def __init__(self):
          
        # visual is a list which stores all 
        # the set of edges that constitutes a
        # graph
        self.visual = []
        self.single_nodes = []
          
    # addEdge function inputs the vertices of an
    # edge and appends it to the visual list
    def addEdge(self, a, b):
        temp = [a, b]
        self.visual.append(temp)

    def addSoloNode(self,a):
        self.single_nodes.append(a)
          
    # In visualize function G is an object of
    # class Graph given by networkx G.add_edges_from(visual)
    # creates a graph with a given list
    # nx.draw_networkx(G) - plots the graph
    # plt.show() - displays the graph
    def visualize(self,filename=None):
        G = nx.Graph()
        G.add_edges_from(self.visual)
        G.add_nodes_from(self.single_nodes)
        nx.draw_networkx(G)
        
        if filename is not None:
            # print('Hello World')
            plt.savefig(filename)
        else:
            plt.show()
        plt.clf()
    
    def _print_contents(self):
        
        for val in self.visual:
            print(val)
  


def visualize_single(filepath):
    G = GraphVisualization()

    

    with open(filepath) as f:
        lines = [line.rstrip() for line in f]
        for line in lines:
            root, nodes = line.split(':',maxsplit=1)
            # print(root,nodes)
            nodes = nodes.split(',')
            for val in nodes:
                G.addEdge(root,val)

        G.visualize()
        # G._print_contents()

def visualize_folder(src:str,dest:str):
    for filepath in os.listdir(src):
        G = GraphVisualization()
        location = filepath.split('.')[0]
        location = f"{dest}/{location}.png"
        print(f'Filepath: {filepath}\nlocation: {location}')

        with open(f"{src}/{filepath}") as f:
            lines = [line.rstrip() for line in f]
            for line in lines:
                root, nodes = line.split(':',maxsplit=1)
                # print(root,nodes)
                nodes = nodes.split(',')
                if len(nodes) == 0 or nodes[0] == '' :
                    G.addSoloNode(root)
                    continue
                for val in nodes:
                    G.addEdge(root,val)
            del lines
        G.visualize(location)
        del G

    
# visualize_single("cmake-build-debug/complete_5.txt")
visualize_folder('graph_files/','visuals')
