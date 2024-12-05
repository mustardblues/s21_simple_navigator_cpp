// 0 Ok
{
    "\033[32m[Ok]\033[0m\n"
},

// 1 Fail
{
    "\033[31m[Fail]\033[0m\n"
},

// 2 logo
{
    "\033[32m   ____    __             __  ___ ___\n" \
    "  / __/___/ /  ___  ___  / / |_  <  /\n" \
    " _\\ \\/ __/ _ \\/ _ \\/ _ \\/ / / __// / \n" \
    "/___/\\__/_//_/\\___/\\___/_/ /____/_/  \033[0m\n"
},

// 3 Main menu
{   
    "+----+----------------------+-----------------------------------------------------------------------------+\n" \
    "|  # | Option               | Description                                                                 |\n" \
    "+----+----------------------+-----------------------------------------------------------------------------+\n" \
    "| -1 | Exit                 |                                                                             |\n" \
    "|  0 | Main menu            | Shows this message.                                                         |\n" \
    "|  1 | Load                 | Loads graph data from an adjacency matrix file.                             |\n" \
    "|  2 | Export               | Creates a .dot file with the graph data.                                    |\n" \
    "|  3 | Depth first search   | Performs graph traversal using a depth first search algorithm.              |\n" \
    "|  4 | Breadth first search | Performs graph traversal using a breadth first search algorithm.            |\n" \
    "|  5 | Dijkstra             | Outputs the shortest distance between two vertices of the graph.            |\n" \
    "|  6 | Floyd-Warshall       | Outputs a matrix with the shortest paths between all vertices of the graph. |\n" \
    "|  7 | Prim                 | Outputs the matrix of the graph's spanning tree.                            |\n" \
    "+----+----------------------+-----------------------------------------------------------------------------+\n"
},

// 4 Select the file name
{
    "Select file name:\n"
},

// 5 Select graph format

{
    "Select graph format? 0 (undirected) 1 (directed):\n"
},

// 6 Select start vertex
{
    "Select start vertex:\n"
},

// 7 Select start vertex
{
    "Select last vertex:\n"
}