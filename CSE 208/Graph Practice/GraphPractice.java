/**
 * Jan25 CSE208 
 * Practice Session on Graphs
 * 
 * 
 * Complete the following code by implementing the methods. Please be mindful of the corner cases. 
 * Run the provided input file. 
 * Be ready to explain the generated output to the evaluator.
 * 
 * 
 * The usage of any online tool and/or any GenAI is absolutely forbidden in this course 
 * unless otherwise mentioned. 
*/

import java.util.ArrayList;
import java.util.Scanner;

abstract class AbstractGraph {
    protected int V;
    protected ArrayList<ArrayList<Integer>> adj;

    public AbstractGraph(int vertices) {
        this.V = vertices;
        this.adj = new ArrayList<>(vertices);
        for (int i = 0; i < vertices; i++) {
            adj.add(new ArrayList<>());
        }
    }

    // Abstract methods
    public abstract void addEdge(int u, int v);
    public abstract void removeEdge(int u, int v);
    public abstract int inDegree(int u);
    public abstract int outDegree(int u);
    public abstract boolean removeVertex(int u);
    public abstract void printGraph();
    public abstract void printInNeighbors(int u);
    public abstract void printOutNeighbors(int u);

    // please note that once a vertex is removed, it will not be printed in the printGraph function 
}

// extend AbstractGraph into a concrete Graph class 
class Graph extends AbstractGraph {
    private ArrayList<Integer> restricted;
    public Graph(int vertices){
        super(vertices);
        restricted = new ArrayList<>();
        for(int i=0;i<vertices;i++){
            restricted.add(0);
        }
    }
    public void addEdge(int u,int v){
        if(u<0 || v<0 || u>=V || v>=V || restricted.get(u)==1 || restricted.get(v)==1)
            return;
        adj.get(u).add(v);
    }
    public void removeEdge(int u,int v){
        if(u<0 || v<0 || u>=V || v>=V)
            return;
        adj.get(u).remove(Integer.valueOf(v));
    }
    public int outDegree(int u){
        if(u < 0 || u >= V || restricted.get(u)==1)
            return -1;
        return adj.get(u).size();
    }
    public int inDegree(int u){
        if(u < 0 || u >= V || restricted.get(u)==1)
        return -1;
        int count=0;
        for(int i=0;i<V;i++){
            if(adj.get(i).contains(u))
                count++;
        }
        return count;
    }
    public boolean removeVertex(int u){
        if(u<0 || u>=V || restricted.get(u)==1)
            return false;
        restricted.set(u,1);
        for(int i=0;i<V;i++){
            adj.get(i).remove(Integer.valueOf(u));
        }
        adj.get(u).clear();
        return true;
    }
    public void printGraph(){
        for(int i=0;i<V;i++){
            if(restricted.get(i)==1)
                continue;
            System.out.print(i+" -> ");
            for(int x:adj.get(i)){
                if(restricted.get(x)==0)
                    System.out.print(x+" ");
            }
            System.out.println();
        }
    }
    public void printInNeighbors(int u){
        if(u < 0 || u >= V || restricted.get(u)==1){
            System.out.println("Node doesnt exist");
            return;
        }
        for(int i=0;i<V;i++){
            if(adj.get(i).contains(u))
                System.out.print(i+" ");
        }
        System.out.println();
    }
    public void printOutNeighbors(int u){
        if(u < 0 || u >= V || restricted.get(u)==1){
            System.out.println("Node doesnt exist");
            return;
        }
        for(int x:adj.get(u))
            System.out.print(x+" ");
        System.out.println();
    }
}


public class GraphPractice {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter number of initial vertices: ");
        int initialVertices = scanner.nextInt();
        Graph g = new Graph(initialVertices);

        while (true) {
            System.out.println("\n========== MENU ==========");
            System.out.println("1. Add Edge");
            System.out.println("2. Remove Edge");
            System.out.println("3. Remove Vertex");
            System.out.println("4. Print Graph");
            System.out.println("5. Find In-Degree of a Vertex");
            System.out.println("6. Find Out-Degree of a Vertex");
            System.out.println("7. Print In-Neighbors of a Vertex");
            System.out.println("8. Print Out-Neighbors of a Vertex");
            System.out.println("9. Exit");
            System.out.print("Choose an option: ");

            int choice = scanner.nextInt();

            if (choice == 9) break;

            switch (choice) {
                case 1:
                    System.out.print("Enter source and destination vertex: ");
                    int u1 = scanner.nextInt();
                    int v1 = scanner.nextInt();
                    g.addEdge(u1, v1);
                    break;
                case 2:
                    System.out.print("Enter source and destination vertex to remove edge: ");
                    int u2 = scanner.nextInt();
                    int v2 = scanner.nextInt();
                    g.removeEdge(u2, v2);
                    break;
                case 3:
                    System.out.print("Enter vertex to remove: ");
                    int u3 = scanner.nextInt();
                    if (g.removeVertex(u3)) {
                        System.out.println("Vertex " + u3 + " removed successfully.");
                    } else {
                        System.out.println("Failed to remove vertex " + u3 + ".");
                    }
                    break;
                case 4:
                    g.printGraph();
                    break;
                case 5:
                    System.out.print("Enter vertex to find in-degree: ");
                    int v5 = scanner.nextInt();
                    System.out.println("In-degree of " + v5 + " is: " + g.inDegree(v5));
                    break;
                case 6:
                    System.out.print("Enter vertex to find out-degree: ");
                    int v6 = scanner.nextInt();
                    System.out.println("Out-degree of " + v6 + " is: " + g.outDegree(v6));
                    break;
                case 7:
                    System.out.print("Enter vertex to find in-neighbors: ");
                    int u7 = scanner.nextInt();
                    g.printInNeighbors(u7);
                    break;
                case 8:
                    System.out.print("Enter vertex to find out-neighbors: ");
                    int u8 = scanner.nextInt();
                    g.printOutNeighbors(u8);
                    break;
                default:
                    System.out.println("Invalid choice. Try again.");
            }
        }

        System.out.println("Program exited.");
        scanner.close();
    }
}