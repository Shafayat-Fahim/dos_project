public class DiningTable implements DiningServer {
    private enum State { THINKING, HUNGRY, EATING }
    private State[] philosopherStates;
    private final int numPhilosophers;
    private final Object lock = new Object();

    public DiningTable(int numPhilosophers) {
        this.numPhilosophers = numPhilosophers;
        this.philosopherStates = new State[numPhilosophers];
        for (int i = 0; i < numPhilosophers; i++) {
            philosopherStates[i] = State.THINKING;
        }
    }

    @Override
    public void takeForks(int pNum) {
        synchronized (lock) {
            philosopherStates[pNum] = State.HUNGRY;
            System.out.println("Philosopher " + pNum + " is hungry and trying to take forks.");
            
            while (!areForksAvailable(pNum)) {
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }
            
            philosopherStates[pNum] = State.EATING;
        }
    }

    @Override
    public void returnForks(int pNum) {
        synchronized (lock) {
            philosopherStates[pNum] = State.THINKING;
            System.out.println("Philosopher " + pNum + " returned forks.");
            
            lock.notifyAll();
        }
    }

    private boolean areForksAvailable(int pNum) {
        int left = (pNum + numPhilosophers - 1) % numPhilosophers;
        int right = (pNum + 1) % numPhilosophers;
        
        return philosopherStates[left] != State.EATING && philosopherStates[right] != State.EATING;
    }

    public static void main(String[] args) {
        int numPhilosophers = 5;
        DiningTable server = new DiningTable(numPhilosophers);

        Thread[] philosophers = new Thread[numPhilosophers];
        for (int i = 0; i < numPhilosophers; i++) {
            philosophers[i] = new Thread(new Philosopher(i, server));
            philosophers[i].start();
        }
    }
}