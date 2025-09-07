import collections

class Process:
    def __init__(self, pid, arrival_time, burst_time):
        self.pid = pid
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.remaining_time = burst_time
        self.completion_time = 0
        self.waiting_time = 0
        self.turnaround_time = 0

    def __repr__(self):
        return f"PID({self.pid})"

class Scheduler:
    def __init__(self, processes):
        self.processes = collections.deque(sorted(processes, key=lambda p: p.arrival_time))
        self.completed_processes = []
        self.current_time = 0
        self.cpu_busy_time = 0

    def run_simulation(self):
        print("--- Starting FCFS Simulation ---")
        
        while self.processes:
            process = self.processes.popleft()
            
            if self.current_time < process.arrival_time:
                self.current_time = process.arrival_time
            
            print(f"Time {self.current_time}: Process {process.pid} starts execution.")
            
            self.current_time += process.burst_time
            self.cpu_busy_time += process.burst_time
            
            process.completion_time = self.current_time
            process.turnaround_time = process.completion_time - process.arrival_time
            process.waiting_time = process.turnaround_time - process.burst_time
            
            self.completed_processes.append(process)
            print(f"Time {self.current_time}: Process {process.pid} finishes.")

        print("\n--- Simulation Complete ---")
        self.print_metrics()

    def print_metrics(self):
        total_waiting_time = 0
        total_turnaround_time = 0
        
        print("\n--- Performance Metrics ---")
        print("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting")
        print("---\t-------\t-----\t----------\t----------\t-------")
        
        for p in self.completed_processes:
            print(f"{p.pid}\t{p.arrival_time}\t{p.burst_time}\t{p.completion_time}\t\t{p.turnaround_time}\t\t{p.waiting_time}")
            total_waiting_time += p.waiting_time
            total_turnaround_time += p.turnaround_time
            
        num_processes = len(self.completed_processes)
        avg_waiting_time = total_waiting_time / num_processes
        avg_turnaround_time = total_turnaround_time / num_processes
        cpu_utilization = (self.cpu_busy_time / self.current_time) * 100
        
        print("\n--- Averages ---")
        print(f"Average Waiting Time: {avg_waiting_time:.2f}")
        print(f"Average Turnaround Time: {avg_turnaround_time:.2f}")
        print(f"CPU Utilization: {cpu_utilization:.2f}%")

if __name__ == "__main__":
    process_list = [
        Process(1, 0, 8),
        Process(2, 1, 4),
        Process(3, 2, 9),
        Process(4, 3, 5)
    ]
    
    fcfs_scheduler = Scheduler(process_list)
    fcfs_scheduler.run_simulation()