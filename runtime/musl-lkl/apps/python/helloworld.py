print("Hello world from CHERI python\n");

import threading

# Global variable shared by threads
counter = 0

# Lock for synchronization
counter_lock = threading.Lock()

# Function to increment the counter
def increment_counter():
    thread_id = threading.get_ident()
    print(f"Thread ID {thread_id} is starting.")
    global counter
    for _ in range(1000000):
        with counter_lock:  # Acquire the lock
            counter += 1
        # Release the lock automatically when exiting the 'with' block

# Create two threads
thread1 = threading.Thread(target=increment_counter)
thread2 = threading.Thread(target=increment_counter)

# Start the threads
thread1.start()
thread2.start()

# Wait for both threads to finish
thread1.join()
thread2.join()

# Print the final counter value
print("Final counter value:", counter)
