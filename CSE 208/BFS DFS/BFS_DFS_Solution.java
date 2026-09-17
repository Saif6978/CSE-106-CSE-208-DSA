import java.util.*;

abstract class AbstractGraph {
    protected int V;
    protected ArrayList<ArrayList<Integer>> adj;

    public AbstractGraph(int vertices) {
        V = vertices;
        adj = new ArrayList<>();

        for(int i = 0; i < vertices; i++)
            adj.add(new ArrayList<>());
    }

    public abstract void addEdge(int u, int v);
    public abstract void removeEdge(int u, int v);
    public abstract void printGraph();
    public abstract void checkBipartite();
}

class Graph extends AbstractGraph {

    public Graph(int vertices) {
        super(vertices);
    }

    public void addEdge(int u, int v) {
        if(u < 0 || v < 0 || u >= V || v >= V)
            return;

        adj.get(u).add(v);
        adj.get(v).add(u);
    }

    public void removeEdge(int u, int v) {
        if(u < 0 || v < 0 || u >= V || v >= V)
            return;

        adj.get(u).remove(Integer.valueOf(v));
        adj.get(v).remove(Integer.valueOf(u));
    }

    public void printGraph() {
        for(int i = 0; i < V; i++) {
            System.out.print(i + " -> ");
            for(int x : adj.get(i))
                System.out.print(x + " ");
            System.out.println();
        }
    }

    public void checkBipartite() {
        int[] color = new int[V];
        Arrays.fill(color, -1);

        for(int start = 0; start < V; start++) {
            if(color[start] != -1)
                continue;

            Queue<Integer> q = new LinkedList<>();
            q.add(start);
            color[start] = 0;

            while(!q.isEmpty()) {
                int u = q.poll();

                for(int v : adj.get(u)) {
                    if(color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.add(v);
                    }
                    else if(color[v] == color[u]) {
                        System.out.println("Not Bipartite");
                        return;
                    }
                }
            }
        }

        System.out.println("Bipartite");
    }
}

public class BFS_DFS_Solution {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int vertices = scanner.nextInt();
        int edges = scanner.nextInt();

        Graph g = new Graph(vertices);

        for(int i = 0; i < edges; i++) {
            int u = scanner.nextInt();
            int v = scanner.nextInt();
            g.addEdge(u, v);
        }

        g.checkBipartite();

        scanner.close();
    }
}
