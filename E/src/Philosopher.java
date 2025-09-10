import java.util.Random;

public class Philosopher implements Runnable {
    private int philosopherNumber;
    private DiningServer server;
    private Random random = new Random();

    public Philosopher(int philosopherNumber, DiningServer server) {
        this.philosopherNumber = philosopherNumber;
        this.server = server;
    }

    @Override
    public void run() {
        while (true) {
            try {
                think();
                server.takeForks(philosopherNumber);
                eat();
                server.returnForks(philosopherNumber);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
        }
    }

    private void think() throws InterruptedException {
        System.out.println("Philosopher " + philosopherNumber + " is thinking.");
        Thread.sleep(random.nextInt(3000) + 1000);
    }

    private void eat() throws InterruptedException {
        System.out.println("Philosopher " + philosopherNumber + " is EATING.");
        Thread.sleep(random.nextInt(3000) + 1000);
    }
}